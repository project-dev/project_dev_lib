// ImageObject.cpp: CImageObject クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageObject.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

// 
// 関数名 : CImageObject
// 概  要 : コンストラクタ
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
CImageObject::CImageObject(){
	m_hBmp = NULL;
	m_eImgType = IO_UNKNOW;
	memset(m_szFileName, 0, MAX_PATH);
}

// 
// 関数名 : ~CImageObject
// 概  要 : デストラクタ
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
CImageObject::~CImageObject(){
	if(m_hBmp){
		::DeleteObject(m_hBmp);
	}
}

// 
// 関数名 : LoadImage
// 概  要 : イメージをロードする
// 引  数 : pszFileName ロードするファイル名
// 戻り値 : 正常に読み込めた場合はTRUE
// 備  考 : なし
//
BOOL CImageObject::LoadImage(char *pszFileName){
	strcpy(m_szFileName, pszFileName);

	FILE *file = fopen(m_szFileName, "a+");
	if(file == NULL){
		return FALSE;
	}
	return TRUE;
}

// 
// 関数名 : SaveImage
// 概  要 : イメージを保存する
// 引  数 : pszFileName 保存するファイル名
// 戻り値 : 正常に保存した場合はTRUE
// 備  考 : なし
//
BOOL CImageObject::SaveImage(char *pszFileName){
	strcpy(m_szFileName, pszFileName);

	return TRUE;
}

// 
// 関数名 : GetBitmapHandle
// 概  要 : ビットマップハンドルの取得
// 引  数 : なし
// 戻り値 : ビットマップハンドル
// 備  考 : なし
//
HBITMAP CImageObject::GetBitmapHandle(){
	return m_hBmp;
}

// 
// 関数名 : GetType
// 概  要 : イメージのタイプ
// 引  数 : なし
// 戻り値 : タイプ
// 備  考 : なし
//
int CImageObject::GetType(){
	return m_eImgType;
}

// 
// 関数名 : SearchImageType
// 概  要 : イメージのタイプを判定する
// 引  数 : なし
// 戻り値 : なし
// 備  考 : なし
//
void CImageObject::SearchImageType(){
	m_eImgType = IO_UNKNOW;

	//解析します
}

// 
// 関数名 : DrawImage
// 概  要 : イメージを描画
// 引  数 : hDC デバイスコンテキストのハンドル
//          x   出力座標
//          y   出力座標
// 戻り値 : 正常に処理した場合TRUE
// 備  考 : なし
//
BOOL CImageObject::DrawImage(HDC hDC, int x, int y){
	DWORD dwRet = ::GetDeviceCaps(hDC, RASTERCAPS);
	if(dwRet & RC_BITBLT){
		//BitBltで描画
	}else if(dwRet & RC_DIBTODEV){
		//SetDIBitsToDeviceで描画
	}else if(dwRet & RC_DI_BITMAP){
		//SetDIBitsで描画
	}else if(dwRet & RC_STRETCHBLT){
		//StretchBltで描画
	}else if(dwRet & RC_STRETCHDIB){
		//StretchDIBitsで描画
	}
	return TRUE;
}

// 
// 関数名 : DrawStretchImage
// 概  要 : イメージを指定サイズで描画
// 引  数 : hDC デバイスコンテキストのハンドル
//          x      出力座標
//          y      出力座標
//          width  イメージの幅
//          height イメージの高さ
// 戻り値 : 正常に処理した場合TRUE
// 備  考 : なし
//
BOOL CImageObject::DrawStretchImage(HDC hDC, int x, int y, int width, int height){
	DWORD dwRet = ::GetDeviceCaps(hDC, RASTERCAPS);
	if(dwRet & RC_STRETCHBLT){
		//StretchBltで描画
	}else if(dwRet & RC_STRETCHDIB){
		//StretchDIBitsで描画
	}else if(dwRet & RC_BITBLT){
		//BitBltで描画
	}else if(dwRet & RC_DIBTODEV){
		//SetDIBitsToDeviceで描画
	}else if(dwRet & RC_DI_BITMAP){
		//SetDIBitsで描画
	}
	return TRUE;
}
