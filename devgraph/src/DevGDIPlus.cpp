// DevGDIPlus.cpp: CDevGDIPlus �N���X�̃C���v�������e�[�V����
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
// �\�z/����
//////////////////////////////////////////////////////////////////////
const char* CDevGDIPlus::imgBMP = "image/bmp";
const char* CDevGDIPlus::imgGIF = "image/gif";
const char* CDevGDIPlus::imgJPG = "image/jpeg";
const char* CDevGDIPlus::imgPNG = "image/png";
const char* CDevGDIPlus::imgICON = "image/icon";
const char* CDevGDIPlus::imgTIFF = "image/tiff";
const char* CDevGDIPlus::imgEMF	= "image/emf";

/**
 * @brif �G���R�[�h����CLSID�̎擾
 * @param format
 * @param pClsid
 * @return
 */
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid){
    using namespace Gdiplus;//�K�v�����
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
 * @brif �R���X�g���N�^
 */
CDevGDIPlus::CDevGDIPlus(){
	m_pImg = NULL;
	m_bImgLoad = FALSE;
}

/** 
 * @brif �f�X�g���N�^
 */
CDevGDIPlus::~CDevGDIPlus(){
	Close();
	UnInitalize();
}

/**
 * @brif ������
 */
BOOL CDevGDIPlus::Initalize(){
	//GDI+�̊J�n
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
 * @brif �I��
 */
BOOL CDevGDIPlus::UnInitalize(){
	//GDI+�̏I��
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
 * @brif ����
 */
BOOL CDevGDIPlus::Create(){
	return Initalize();
}

/**
 * @brif �摜�ۑ�
 * @brif pszSaveFile �ۑ��t�@�C����
 * @brif pszType �ۑ���ʁBCDevGDIPlus::imgBMP�����w�肷��
 * @return �ۑ��ɐ��������TRUE�A���s�����FALSE
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
 * @brif �r�b�g�}�b�v�ۑ�
 * @brif pszSaveFile �ۑ��t�@�C����
 * @return �ۑ��ɐ��������TRUE�A���s�����FALSE
 */
BOOL CDevGDIPlus::SaveBitmap(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile){
	return SaveImage(hDc, hBmp, pszSaveFile, imgBMP);
}

/**
 * @brif GIF�ۑ�
 * @brif pszSaveFile �ۑ��t�@�C����
 * @return �ۑ��ɐ��������TRUE�A���s�����FALSE
 */
BOOL CDevGDIPlus::SaveGif(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile){
	return SaveImage(hDc, hBmp, pszSaveFile, imgGIF);
}

/**
 * @brif JPEG�ۑ�
 * @brif pszSaveFile �ۑ��t�@�C����
 * @return �ۑ��ɐ��������TRUE�A���s�����FALSE
 */
BOOL CDevGDIPlus::SaveJpeg(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile){
	return SaveImage(hDc, hBmp, pszSaveFile, imgJPG);
}

/**
 * @brif PNG�ۑ�
 * @brif pszSaveFile �ۑ��t�@�C����
 * @return �ۑ��ɐ��������TRUE�A���s�����FALSE
 */
BOOL CDevGDIPlus::SavePng(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile){
	return SaveImage(hDc, hBmp,	pszSaveFile, imgPNG);
}

/**
 * @brif TIFF�ۑ�
 * @brif pszSaveFile �ۑ��t�@�C����
 * @return �ۑ��ɐ��������TRUE�A���s�����FALSE
 */
BOOL CDevGDIPlus::SaveTiff(HDC hDc, HBITMAP hBmp, LPCTSTR pszSaveFile){
	return SaveImage(hDc, hBmp, pszSaveFile, imgTIFF);
}

/**
 * @brif �C���[�W��ǂݍ���Ńf�o�C�X�R���e�L�X�g�ɓ]�����܂��B
 * @param HDC hDc �]����̃f�o�C�X�R���e�L�X�g
 * @param LPCTSTR pszFile �ǂݍ��ރt�@�C����
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
// new �͂ł��Ȃ�
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
 * @brif �ǂݍ��񂾉摜�����
 */
BOOL CDevGDIPlus::Close(){
	if(m_pImg && m_bImgLoad){
		//FromFile�Ŏ擾������ Delete����
		delete m_pImg;
		m_pImg = NULL;
		m_bImgLoad = FALSE;
	}
	return TRUE;
}

/**
 * @brif �w��t�@�C���̃T�C�Y���擾����
 * @param LPCTSTR pszFile �t�@�C����
 * @return CSize �T�C�Y
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
 * @brif ���݂̉摜�̃T�C�Y���擾����
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
 * @brif ���݂̉摜���f�o�C�X�R���e�L�X�g�֓]������
 */
BOOL CDevGDIPlus::DrawImage(HDC hDc){
	CSize size = GetImageSize();
	return DrawImage(hDc, 0, 0, size.cx, size.cy);
}
/**
 * @brif ���݂̉摜���f�o�C�X�R���e�L�X�g�֓]������
 */
BOOL CDevGDIPlus::DrawImage(HDC hDc, int x, int y){
	CSize size = GetImageSize();
	return DrawImage(hDc, x, y, size.cx, size.cy);
}
/**
 * @brif ���݂̉摜���f�o�C�X�R���e�L�X�g�֓]������
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
 * @brif �G���[���b�Z�[�W���擾����
 */
int CDevGDIPlus::GetGDIErrorMsg(Status st, char* pszMsg, int nLen){
	CString strMsg;
	switch(st){
	case Ok:
		strMsg = "����";
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
		strMsg = "�t�@�C����������܂���";
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
 * @brif �C���[�W��ێ����Ă��邩�`�F�b�N����
 */
BOOL CDevGDIPlus::IsHaveImage(){
//	return m_pImg ? TRUE : FALSE;
	return m_bImgLoad;
}
