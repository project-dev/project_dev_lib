#include "stdafx.h"

#include "DevImgFunc.h"

/**
 * @brif 差分イメージを生成します。
 * @param HDC hOutDC	差分を描画するデバイスコンテキスト
 * @param HDC hDC1		差分元イメージ1
 * @param HDC hDC2		差分元イメージ2
 * @param int nWidth	画像の幅
 * @param int nHeight	画像の高さ
 */
BOOL WINAPI Diff(HDC hOutDC, HDC hDC1, HDC hDC2, int nWidth, int nHeight){
	//差分画像の色を変更する
	CWaitCursor objWait;
	if(!hOutDC || !hDC1 || !hDC2){
		return FALSE;
	}
	HDC hDiffImg = ::CreateCompatibleDC(hDC1);
	if(!hDiffImg){
		return FALSE;
	}
	HBITMAP hDiffBmp = ::CreateCompatibleBitmap(hDC1, nWidth, nHeight);
	if(!hDiffBmp){
		return FALSE;
	}
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hDiffImg, hDiffBmp);
	for(int y = 0; y < nHeight; y++){
		for(int x = 0; x < nWidth; x++){
			COLORREF crPix = ::GetPixel(hDC1, x, y);
			int nR = crPix & 0x00FF0000 >> 16;
			int nG = crPix & 0x0000FF00 >> 8;
			int nB = crPix & 0x000000FF;
			nR = (int)((double)nR * 0.8);	//赤を2割り弱くする
			nG = (int)((double)nG * 0.8);	//緑を2割り弱くする
			nB = (int)((double)nB * 1.2);	//青を2割り強くする
			::SetPixel(hDiffImg, x, y, RGB(nR, nG, nB));
		}
	}
	::BitBlt(hOutDC, 0, 0, nWidth, nHeight, hOutDC, 0, 0, SRCCOPY);
	
	//排他
	::BitBlt(hOutDC, 0, 0, nWidth, nHeight, hDiffImg, 0, 0, SRCINVERT);
	::SelectObject(hDiffImg, hOldBmp);
	::DeleteObject(hDiffBmp);
	return TRUE;
}

/**
 * @brif イメージを2値化します
 * @param HDC hOutDC	差分を描画するデバイスコンテキスト
 * @param HDC hTargDC	２値化元画像
 * @param int nWidth	画像の幅
 * @param int nHeight	画像の高さ
 * @param int nLevel	2値化閾値
 */
BOOL WINAPI Binalize(HDC hOutDC, HDC hTargDC, int nWidth, int nHeight, int nLevel){
	CWaitCursor objWait;
	if(!hOutDC || !hTargDC){
		return FALSE;
	}
	for(int y = 0; y < nHeight; y++){
		for(int x = 0; x < nWidth; x++){
			COLORREF crPix = ::GetPixel(hTargDC, x, y);
			int luminance = GetLuminance(crPix);
			if(luminance < nLevel){
				::SetPixel(hOutDC, x, y, RGB(0x00, 0x00, 0x00));
			}else{
				::SetPixel(hOutDC, x, y, RGB(0xFF, 0xFF, 0xFF));
			}
		}
	}
	return TRUE;
}

/**
 * @brif グレースケール
 * @param HDC hOutDC	差分を描画するデバイスコンテキスト
 * @param HDC hTargDC	元画像
 * @param int nWidth	画像の幅
 * @param int nHeight	画像の高さ
 */
BOOL WINAPI Grayscale(HDC hOutDC, HDC hTargDC, int nWidth, int nHeight){
	CWaitCursor objWait;
	if(!hOutDC || !hTargDC){
		return FALSE;
	}
	for(int y = 0; y < nHeight; y++){
		for(int x = 0; x < nWidth; x++){
			COLORREF crPix = ::GetPixel(hTargDC, x, y);
			int luminance = GetLuminance(crPix);
			::SetPixel(hOutDC, x, y, RGB(luminance, luminance, luminance));
		}
	}
	return TRUE;
}

/**
 * @brif 擬似カラー
 * @param HDC hOutDC	描画するデバイスコンテキスト
 * @param HDC hTargDC	元画像
 * @param int nWidth	画像の幅
 * @param int nHeight	画像の高さ
 * @param int nType		擬似化種別
 */
BOOL WINAPI DummyColor(HDC hOutDC, HDC hTargDC, int nWidth, int nHeight, int nType){
	CWaitCursor objWait;
	if(!hOutDC || !hTargDC){
		return FALSE;
	}
	for(int y = 0; y < nHeight; y++){
		for(int x = 0; x < nWidth; x++){
			COLORREF crPix =::GetPixel(hTargDC, x, y);
			int luminance = GetLuminance(crPix);
			UINT nColor;
			int nSpan;
			int nSpanX;
			switch(nType){
			case 0:
				if(256 / 3 > luminance){
					nColor = RGB(0x00, 0x00, luminance * 3);
				}else if((256 / 3 * 2) > luminance){
					nColor = RGB(0x00, luminance /2 * 3, 0);
				}else{
					nColor = RGB(luminance, 0, 0);
				}
				break;
			case 1:
				nSpan = 0x00FF0000 - 0x000000FF;
				nSpanX = nSpan / 256;
				nColor = luminance * nSpanX + 0x000000FF;
				break;
			case 2:
				nSpan = 0x00FFFFFF - 0x00000000;
				nSpanX = nSpan / 256;
				nColor = luminance * nSpanX;
				break;
			default:
				break;
			}
			::SetPixel(hOutDC, x, y, nColor);
		}
	}
	return TRUE;
}

/**
 * @brif 強調
 * @param HDC hOutDC	描画するデバイスコンテキスト
 * @param HDC hTargDC	元画像
 * @param int nWidth	画像の幅
 * @param int nHeight	画像の高さ
 * @param int nLevel	強調輝度閾値
 */
BOOL WINAPI Strong(HDC hOutDC, HDC hTargDC, int nWidth, int nHeight, int nLevel){
	CWaitCursor objWait;
	if(!hOutDC || !hTargDC){
		return FALSE;
	}
	for(int y = 0; y < nHeight; y++){
		for(int x = 0; x < nWidth; x++){
			COLORREF crPix = ::GetPixel(hTargDC, x, y);
			int luminance = GetLuminance(crPix);
			if(luminance >= nLevel){
				::SetPixel(hOutDC, x, y, RGB(luminance, luminance, 0));
			}else{
				::SetPixel(hOutDC, x, y, crPix);
			}
		}
	}
	return TRUE;
}

/**
 * @brif カラービット変換
 * @param HDC hFromDC		変換元デバイスコンテキスト
 * @param HBITMAP hFromBmp	変換元ビットマップ
 * @param HDC hToDC			描画するデバイスコンテキスト
 * @param HBITMAP hToBmp	描画するビットマップ
 * @param int nToCrBit		変換したいカラービット
 */
BOOL WINAPI ConvColorBitImg(HDC hFromDC, HBITMAP hFromBmp, HDC hToDC, HBITMAP hToBmp, int nToCrBit){
	CString strErr = "";
	PBYTE pBmpiBuff = NULL;
	char *pBuff = NULL;
	HPALETTE hPalette = NULL;
	try{
		if(!hFromDC || !hFromBmp || !hToDC || !hToBmp){
			throw(0);
		}

		BITMAP chkBmp;
		::GetObject(hToBmp, sizeof(BITMAP), &chkBmp);
		switch(nToCrBit){
		case 8:
		case 16:
		case 24:
		case 32:
			break;
		default:
			throw(0);
		}
		BITMAP bmp;
		::GetObject(hFromBmp, sizeof(BITMAP), &bmp);
		int	xsize = bmp.bmWidth;
		int	ysize = bmp.bmHeight;
		DWORD dwSize = (DWORD)xsize * (DWORD)ysize * (DWORD)nToCrBit / 8;
		pBuff = new char[dwSize];
		if(!pBuff){
			strErr.Format("%d bit -> %d bit  Bitmap color bit change fault.", bmp.bmBitsPixel, nToCrBit);
			throw(0);
		}
		memset(pBuff, 0, dwSize);

		//8bit変換の際に、パレット情報が必要となるので、その分を考慮しておく必要がある
		pBmpiBuff = new BYTE[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256];
		PBITMAPINFO pBmpi = (PBITMAPINFO)pBmpiBuff;
		memset(pBmpi, 0, sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256);
		BOOL bAfterColorCheck = FALSE;
		RGBQUAD *pRgb = (RGBQUAD*)(pBmpiBuff + sizeof(BITMAPINFOHEADER));
		pBmpi->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);		//構造体のサイズ	
		pBmpi->bmiHeader.biBitCount		= nToCrBit;						//変換後のカラービット数
		pBmpi->bmiHeader.biPlanes		= 1;							//カラープレーン数(1)
		pBmpi->bmiHeader.biHeight		= ysize;						//高さ
		pBmpi->bmiHeader.biWidth		= xsize;						//幅
		pBmpi->bmiHeader.biCompression	= BI_RGB;						//圧縮方式
		pBmpi->bmiHeader.biSizeImage	= dwSize;						//イメージサイズ(幅x高さxカラービット)

		DWORD dwCrCnt = 0;
		if(nToCrBit <= 8){
			//変換先は8bitカラー
			DIBSECTION objDib;
			memset(&objDib, 0, sizeof(DIBSECTION));
			::GetObject(hFromBmp, sizeof(DIBSECTION), &objDib);
			if(objDib.dsBmih.biClrUsed != 0){
				dwCrCnt = objDib.dsBmih.biClrUsed;
			}else{
				dwCrCnt = (DWORD)1 << bmp.bmBitsPixel;
			}
			CWaitCursor objWait;
			if(bmp.bmBitsPixel > 8){
				BYTE *pChkBuff = new BYTE[objDib.dsBmih.biSizeImage];
				::GetBitmapBits(hFromBmp, objDib.dsBmih.biHeight * objDib.dsBmih.biWidth, pChkBuff);
				UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * (256 - 1));
				BYTE* pLPBuff = new BYTE[nSize];
				LOGPALETTE* pLP = (LOGPALETTE*)pLPBuff;
				pLP->palVersion = 0x300;
				pLP->palNumEntries = (int)256;
				for(int y = 0; y < ysize; y++){
					CString strLine = "";
					CString strCr = "";
					for(int x = 0; x < xsize; x++){
						COLORREF crData = ::GetPixel(hFromDC, x, y);
						int nColor = GetLuminance(crData);
						pBuff[x * y] = nColor;
						pRgb[nColor].rgbBlue	= nColor;
						pRgb[nColor].rgbRed		= nColor;
						pRgb[nColor].rgbGreen	= nColor;
					}
				}
				hPalette = ::CreatePalette(pLP);
				delete[] pLPBuff;
			}else{
				UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * (dwCrCnt - 1));
				BYTE* pLPBuff = new BYTE[nSize];
				LOGPALETTE* pLP = (LOGPALETTE*)pLPBuff;
				pLP->palVersion = 0x300;
				pLP->palNumEntries = (int)dwCrCnt;
				RGBQUAD *pRGB = new RGBQUAD[ dwCrCnt ];
				::GetDIBColorTable(hFromDC, 0, dwCrCnt, pRGB);
				for(int i = 0; i < (int)dwCrCnt; i++){
					pRgb[i].rgbBlue				= pRGB[i].rgbRed;
					pRgb[i].rgbRed				= pRGB[i].rgbGreen;
					pRgb[i].rgbGreen			= pRGB[i].rgbBlue;
					pLP->palPalEntry[i].peBlue	= pRGB[i].rgbRed;
					pLP->palPalEntry[i].peGreen	= pRGB[i].rgbGreen;
					pLP->palPalEntry[i].peRed	= pRGB[i].rgbBlue;
				}
				hPalette = ::CreatePalette(pLP);
				delete[] pLPBuff;
				delete[] pRGB;
			}
			::SelectPalette(hToDC, hPalette, FALSE);
		}
		int nScanLine = ::GetDIBits(hFromDC,								//変換元のデバイスコンテキスト
									hFromBmp,								//変換元のビットマップ
									0,									//最初の走査線(全体をとるので0)
									ysize,								//走査線数(全体をとるので高さ)
									pBuff,								//変換後のビットマップを格納するバッファ
									pBmpi,								//変換の情報を持つBITMAOINFO構造体
									DIB_PAL_COLORS);					//パレット形式
		if(!nScanLine){
			strErr.Format("%d bit -> %d bit  Bitmap color bit change fault.(compleat scanline = %d)", bmp.bmBitsPixel, nToCrBit, nScanLine);
			throw(0);
		}
		//バッファの内容を転送する
		::SetDIBits(hToDC, 
					hToBmp, 
					1, 
					ysize, 
					pBuff, 
					pBmpi, 
					DIB_PAL_COLORS);
		if(nToCrBit <= 8){
			::SelectPalette(hToDC, hPalette, FALSE);
		}

		delete pBmpiBuff;
		pBmpiBuff = NULL;
		pBmpi = NULL;
		delete pBuff;
		pBuff = NULL;
	}catch(...){
		if(!strErr.IsEmpty()){
			AfxMessageBox(strErr);
		}
		if(pBmpiBuff){
			delete pBmpiBuff;
		}
		if(pBuff){
			delete pBuff;
		}
		return FALSE;
	}
	return TRUE;
}

/**
 * @brif ふち付き文字列描画
 * @param HDC hDC			描画するデバイスコンテキスト
 * @param int nX			表示X座標
 * @param int nY			表示Y座標
 * @param LPCTSTR pszText	出力文字
 */
BOOL WINAPI TextOutWhiteEdge(HDC hDC, int nX, int nY, LPCTSTR pszText){
	if(!hDC){
		return FALSE;
	}
	CString strText = pszText;
	int nLen = strText.GetLength();
	COLORREF crText = ::GetTextColor(hDC);
	::SetTextColor(hDC, RGB(0xFF, 0xFF, 0xFF));
	::TextOut(hDC, nX-1, nY,   strText, nLen);
//	pDC->TextOut(nX,   nY,   strText, nLen);
	::TextOut(hDC, nX+1, nY,   strText, nLen);
	::TextOut(hDC, nX-1, nY-1, strText, nLen);
	::TextOut(hDC, nX,   nY-1, strText, nLen);
	::TextOut(hDC, nX+1, nY-1, strText, nLen);
	::TextOut(hDC, nX-1, nY+1, strText, nLen);
	::TextOut(hDC, nX,   nY+1, strText, nLen);
	::TextOut(hDC, nX+1, nY+1, strText, nLen);
	::SetTextColor(hDC, crText);
	::TextOut(hDC, nX,   nY,   strText, nLen);
	return TRUE;
}

/**
 * @brif 輝度を求める
 * @param COLORREF crTarget	輝度を求める色
 */
int WINAPI GetLuminance(COLORREF crTarget){
	int nR = crTarget & 0x00FF0000 >> 16;
	int nG = crTarget & 0x0000FF00 >> 8;
	int nB = crTarget & 0x000000FF;
	return (int)( 0.298912 * (double)nR + 0.586611 * (double)nG + 0.114478 * (double)nB );
}
