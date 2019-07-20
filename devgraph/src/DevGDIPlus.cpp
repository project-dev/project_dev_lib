// DevGDIPlus.cpp: CDevGDIPlus クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DevGDIPlus.h"
#include <comdef.h> 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////
const char* CDevGDIPlus::imgBMP = "image/bmp";
const char* CDevGDIPlus::imgGIF = "image/gif";
const char* CDevGDIPlus::imgJPG = "image/jpeg";
const char* CDevGDIPlus::imgPNG = "image/png";
const char* CDevGDIPlus::imgICON = "image/icon";
const char* CDevGDIPlus::imgTIFF = "image/tiff";
const char* CDevGDIPlus::imgEMF	= "image/emf";

/**
 * @brif エンコードしたCLSIDの取得
 * @param format
 * @param pClsid
 * @return
 */
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid){
    using namespace Gdiplus;//必要あれば
    UINT num  = 0; // number of image encoders
    UINT size = 0; // size of the image encoder array in bytes

    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if(size == 0)
        return -1; // Failure

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if(pImageCodecInfo == NULL)
        return -1; // Failure

    GetImageEncoders(num, size, pImageCodecInfo);

    for(UINT j = 0; j < num; ++j)
    {
        if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
        {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j; // Success
        } 
    }

    free(pImageCodecInfo);
    return -1; // Failure
}

/** 
 * @brif コンストラクタ
 */
CDevGDIPlus::CDevGDIPlus(){
	m_pImg = NULL;
	m_bImgLoad = FALSE;
}

/** 
 * @brif デストラクタ
 */
CDevGDIPlus::~CDevGDIPlus(){
	Close();
	UnInitalize();
}

/**
 * @brif 初期化
 */
BOOL CDevGDIPlus::Initalize(){
	//GDI+の開始
	try{
		::CoInitialize(NULL);
		GdiplusStartup(&m_gdiToken, &m_gdiSI, NULL);
	}catch(_com_error &e){
		const char *pszErr = e.ErrorMessage();
		TRACE("%s\n", pszErr);
		return FALSE;
	}
	return TRUE;
}

/**
 * @brif 終了
 */
BOOL CDevGDIPlus::UnInitalize(){
	//GDI+の終了
	try{
		GdiplusShutdown(m_gdiToken);
		::CoUninitialize();
	}catch(_com_error &e){
		const char *pszErr = e.ErrorMessage();
		TRACE("%s\n", pszErr);
		return FALSE;
	}
	return TRUE;
}

/**
 * @brif 生成
 */
BOOL CDevGDIPlus::Create(){
	return Initalize();
}

/**
 * @brif 画像保存
 * @brif pszSaveFile 保存ファイル名
 * @brif pszType 保存種別。CDevGDIPlus::imgBMP等を指定する
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDevGDIPlus::SaveImage(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile, LPCTSTR pszType){

	if(!hDc || !hBmp){
		return FALSE;
	}
	HPALETTE hPlt;
	hPlt = CreateHalftonePalette(hDc);
	Bitmap bmpSrc(hBmp, hPlt);

	_bstr_t fname( pszSaveFile );
	_bstr_t type( pszType );

	CLSID pngClsid;
	if(GetEncoderClsid( type, &pngClsid ) == -1){
		return FALSE;
	}
	bmpSrc.Save( fname, &pngClsid, NULL );
	return TRUE;
}

/**
 * @brif ビットマップ保存
 * @brif pszSaveFile 保存ファイル名
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDevGDIPlus::SaveBitmap(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile){
	return SaveImage(hDc, hBmp, pszSaveFile, imgBMP);
}

/**
 * @brif GIF保存
 * @brif pszSaveFile 保存ファイル名
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDevGDIPlus::SaveGif(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile){
	return SaveImage(hDc, hBmp, pszSaveFile, imgGIF);
}

/**
 * @brif JPEG保存
 * @brif pszSaveFile 保存ファイル名
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDevGDIPlus::SaveJpeg(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile){
	return SaveImage(hDc, hBmp, pszSaveFile, imgJPG);
}

/**
 * @brif PNG保存
 * @brif pszSaveFile 保存ファイル名
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDevGDIPlus::SavePng(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile){
	return SaveImage(hDc, hBmp,	pszSaveFile, imgPNG);
}

/**
 * @brif TIFF保存
 * @brif pszSaveFile 保存ファイル名
 * @return 保存に成功するとTRUE、失敗するとFALSE
 */
BOOL CDevGDIPlus::SaveTiff(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile){
	return SaveImage(hDc, hBmp, pszSaveFile, imgTIFF);
}

/**
 * @brif イメージを読み込んでデバイスコンテキストに転送します。
 * @param HDC hDc 転送先のデバイスコンテキスト
 * @param LPCTSTR pszFile 読み込むファイル名
 */
BOOL CDevGDIPlus::LoadImage(LPCTSTR pszFile){
	if(!pszFile){
		return FALSE;
	}

	WIN32_FIND_DATA wfd;
	memset(&wfd, 0, sizeof(WIN32_FIND_DATA));
	HANDLE hRet = ::FindFirstFile(pszFile, &wfd);
	if(hRet == INVALID_HANDLE_VALUE){
		DWORD dwErr = ::GetLastError();
		TRACE("%s\n", pszFile);
		return FALSE;
	}
	::FindClose(hRet);

	_bstr_t bsFileName(pszFile);
	if(m_pImg){
		delete m_pImg;
		m_pImg = NULL;
	}
// new はできない
//	m_pImg = new Image(bsFileName);
	m_pImg = Image::FromFile(bsFileName, FALSE);
	if(!m_pImg){
		m_bImgLoad = FALSE;
		return FALSE;
	}
	m_bImgLoad = TRUE;
	return TRUE;
}

/**
 * @brif 読み込んだ画像を閉じる
 */
BOOL CDevGDIPlus::Close(){
	if(m_pImg && m_bImgLoad){
		//FromFileで取得したら Deleteする
		delete m_pImg;
		m_pImg = NULL;
		m_bImgLoad = FALSE;
	}
	return TRUE;
}

/**
 * @brif 指定ファイルのサイズを取得する
 * @param LPCTSTR pszFile ファイル名
 * @return CSize サイズ
 */
CSize CDevGDIPlus::GetImageSize(LPCTSTR pszFile){
	CSize size(-1, -1);
	if(!pszFile){
		return FALSE;
	}

	WIN32_FIND_DATA wfd;
	memset(&wfd, 0, sizeof(WIN32_FIND_DATA));
	HANDLE hRet = ::FindFirstFile(pszFile, &wfd);
	if(hRet == INVALID_HANDLE_VALUE){
		DWORD dwErr = ::GetLastError();
		TRACE("%s\n", pszFile);
		return FALSE;
	}
	::FindClose(hRet);

	_bstr_t bsFileName(pszFile);
	Image objImg(bsFileName);

	size.cx = objImg.GetWidth();
	size.cy = objImg.GetHeight();
	return size;
}

/**
 * @brif 現在の画像のサイズを取得する
 */
CSize CDevGDIPlus::GetImageSize(){
	CSize size(-1, -1);
	if(!m_pImg){
		return size;
	}

	size.cx = m_pImg->GetWidth();
	size.cy = m_pImg->GetHeight();
	return size;
}

/**
 * @brif 現在の画像をデバイスコンテキストへ転送する
 */
BOOL CDevGDIPlus::DrawImage(HDC hDc){
	CSize size = GetImageSize();
	return DrawImage(hDc, 0, 0, size.cx, size.cy);
}
/**
 * @brif 現在の画像をデバイスコンテキストへ転送する
 */
BOOL CDevGDIPlus::DrawImage(HDC hDc, int x, int y){
	CSize size = GetImageSize();
	return DrawImage(hDc, x, y, size.cx, size.cy);
}
/**
 * @brif 現在の画像をデバイスコンテキストへ転送する
 */
BOOL CDevGDIPlus::DrawImage(HDC hDc, int x, int y, int cx, int cy){
	Graphics* pGraph = Graphics::FromHDC(hDc);
	Status st = pGraph->DrawImage( m_pImg, x, y, cx, cy );
	if(st == Ok){
		return TRUE;
	}else{
		char szMsg[1025];
		memset(szMsg, 0, 1025);
		GetGDIErrorMsg(st, szMsg, 1024);
		AfxMessageBox(szMsg);
		TRACE("CDevGDIPlus::DrawImage %s\n", szMsg);
		return FALSE;
	}
}

/**
 * @brif エラーメッセージを取得する
 */
int CDevGDIPlus::GetGDIErrorMsg(Status st, char* pszMsg, int nLen){
	CString strMsg;
	switch(st){
	case Ok:
		strMsg = "正常";
		break;
	case GenericError:
		strMsg = "GenericError";
		break;
	case InvalidParameter:
		strMsg = "InvalidParameter";
		break;
	case OutOfMemory:
		strMsg = "OutOfMemory";
		break;
    case ObjectBusy:
		strMsg = "ObjectBusy";
		break;
    case InsufficientBuffer:
		strMsg = "InsufficientBuffer";
		break;
    case NotImplemented:
		strMsg = "NotImplemented";
		break;
    case Win32Error:
		strMsg = "Win32Error";
		break;
    case WrongState:
		strMsg = "WrongState";
		break;
    case Aborted:
		strMsg = "Aborted";
		break;
    case FileNotFound:
		strMsg = "ファイルが見つかりません";
		break;
    case ValueOverflow:
		strMsg = "ValueOverflow";
		break;
    case AccessDenied:
		strMsg = "AccessDenied";
		break;
    case UnknownImageFormat:
		strMsg = "UnknownImageFormat";
		break;
    case FontFamilyNotFound:
		strMsg = "???";
		break;
    case FontStyleNotFound:
		strMsg = "FontStyleNotFound";
		break;
    case NotTrueTypeFont:
		strMsg = "NotTrueTypeFont";
		break;
    case UnsupportedGdiplusVersion:
		strMsg = "UnsupportedGdiplusVersion";
		break;
    case GdiplusNotInitialized:
		strMsg = "GdiplusNotInitialized";
		break;
    case PropertyNotFound:
		strMsg = "PropertyNotFound";
		break;
    case PropertyNotSupported:
		strMsg = "PropertyNotSupported";
		break;
	default:
		strMsg = "Unknow";
		break;
	}

	if(pszMsg){
		strMsg += "(";
		strMsg += pszMsg;
		strMsg += ")";
		return nLen;
	}else{
		return strMsg.GetLength();
	}
}

/**
 * @brif イメージを保持しているかチェックする
 */
BOOL CDevGDIPlus::IsHaveImage(){
//	return m_pImg ? TRUE : FALSE;
	return m_bImgLoad;
}
