// DevExcel.cpp: CDevExcel クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "devMsof.h"
#include "DevExcel.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @verify コンストラクタ
 */
CDevExcel::CDevExcel(){
	m_pExcel = NULL;
	m_pBooks = NULL;
	m_pCurBook = NULL;
}

/**
 * @verify デストラクタ
 */
CDevExcel::~CDevExcel(){
}

/**
 * @verify 初期化
 */
BOOL CDevExcel::Initalize(){
	try{
		if(!CDevMsofObject::Initalize()){
			return FALSE;
		}
		HRESULT hRes = m_pExcel.CreateInstance( "Excel.Application.9");
		if(hRes != S_OK){
			return FALSE;
		}
		 m_pBooks = m_pExcel->GetWorkbooks();
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}

/**
 * @verify 後処理
 */
BOOL CDevExcel::Finalize(){
	try{
		if(m_pCurBook){
			m_pCurBook.Release();
			m_pCurBook = NULL;
		}
		if(m_pBooks){
			m_pBooks.Release();
			m_pBooks = NULL;
		}
		
		if(m_pExcel){
			m_pExcel.Release();
			m_pExcel = NULL;
		}
		
		if(!CDevMsofObject::Finalize()){
			return FALSE;
		}
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}

/**
 * @verify Excelの表示/非表示を設定します。
 */
BOOL CDevExcel::Show(BOOL bIsShow){
	try{
		if(m_pExcel){
			m_pExcel->PutVisible(0, bIsShow);
			return TRUE;
		}else{
			return FALSE;
		}
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
}

/**
 * @verify ブックを閉じます。
 */
BOOL CDevExcel::Quit(LPCTSTR pszFileName, BOOL bIsSaveQuit){
	try{
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}

/**
 * @verify ブックを開きます
 */
BOOL CDevExcel::Load(LPCTSTR pszFileName){
	if(m_pBooks == NULL){
		return FALSE;
	}

	if(m_pCurBook){
		return false;
	}

	try{
		m_pCurBook = m_pBooks->Open(pszFileName);
		if(m_pCurBook == NULL){
			return FALSE;
		}
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}

	return TRUE;
}

/**
 * @verify 現在開いているブックを保存します。
 */
BOOL CDevExcel::Save(int nIndex, LPCTSTR pszFileName, BOOL isOverWrite){
	try{
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	return TRUE;
}

/**
 * @verify 現在開いているブックを閉じます。
 */
BOOL CDevExcel::Close(){
	try{
		HRESULT hRes = m_pCurBook->Close();
	}catch(_com_error e){
		ShowComError(e);
		return FALSE;
	}
	m_pCurBook = NULL;
	return TRUE;
}

/**
 * @verify データを設定します。
 * @param nIndex シートのインデックス
 * @param nRow 開始点
 * @param nCol 開始点
 * @param pData 設定データ
 * @param nSize 設定データ数
 * @param bIsRow 縦方向に設定か横方向に設定か
 */
BOOL CDevExcel::SetData(long nIndex, long nRow, long nCol, PCELLDATA pData, long nSize, BOOL bIsRow){
	if(!pData || !nSize){
		return FALSE;
	}
	BOOL bRet = TRUE;
	Excel::SheetsPtr sheets = NULL;
	Excel::_WorksheetPtr sheet = NULL;
	try{
		sheets = m_pCurBook->GetSheets();
		if(sheets == NULL){
			SetLastErrorMsg("シートが存在しません。");
			ShowErrorMsg();
			return FALSE;
		}

		long lSize = sheets->Count;
		if(lSize <= nIndex){
			SetLastErrorMsg("インデックスが不正です。");
			ShowErrorMsg();
			bRet = FALSE;
		}else if(lSize > 0){
			COleVariant vIndex = nIndex;
			sheet = sheets->GetItem(vIndex);
			if(sheet == NULL){
				SetLastErrorMsg("シートが存在しません。");
				ShowErrorMsg();
				bRet = FALSE;
			}else{
				CString strRange;
				Excel::RangePtr range = NULL;
				Excel::BorderPtr borLeft = NULL;
				Excel::BorderPtr borTop = NULL;
				Excel::BorderPtr borRight = NULL;
				Excel::BorderPtr borBottom = NULL;

				for(long i = 0; i < nSize; i++){
					if(bIsRow){
						IndexToRangeStr(nRow + i, nCol, strRange);
					}else{
						IndexToRangeStr(nRow, nCol + i, strRange);
					}
		
					try{
						COleVariant vtRange = strRange;
						range = sheet->GetRange(vtRange, vtRange);

						//値設定
						COleVariant vtValue;
						vtValue		= pData[i].pszValue;
						range->Value	= vtValue;

						//フォント設定
						COleVariant vtBold		= (long)pData[i].bIsBold;
						COleVariant vtItalic	= (long)pData[i].bIsItalic;
						COleVariant vtUnderLine	= (long)pData[i].bIsUnderLine;
						COleVariant vtSize		= (long)pData[i].nFontSize;
						COleVariant vtName		= pData[i].pszFontFace;
						range->Font->Bold		= vtBold;
						range->Font->Italic		= vtItalic;
						//Underlineはなぜか設定できなかった
						//range->Font->Underline	= vtUnderLine;
						range->Font->Size		= vtSize;
						range->Font->Name		= vtName;

						//ボーダー設定
						borLeft		= range->Borders->GetItem(Excel::xlEdgeLeft);
						borTop		= range->Borders->GetItem(Excel::xlEdgeTop);
						borRight	= range->Borders->GetItem(Excel::xlEdgeRight);
						borBottom	= range->Borders->GetItem(Excel::xlEdgeBottom);
						//borLeft->Color			= 				
						//borLeft->LineStyle.iVal	=
						//borLeft->Weight.iVal		= 
						//borTop->Color				= 				
						//borTop->LineStyle.iVal	=
						//borTop->Weight.iVal		= 
						//borRight->Color			= 				
						//borRight->LineStyle.iVal	=
						//borRight->Weight.iVal		= 
						//borBottom->Color			= 				
						//borBottom->LineStyle.iVal	=
						//borBottom->Weight.iVal	= 
						borLeft.Release();
						borLeft = NULL;
						borTop.Release();
						borTop = NULL;
						borRight.Release();
						borRight = NULL;
						borBottom.Release();
						borBottom = NULL;

						range.Release();
						range = NULL;
					}catch(_com_error e){
						ShowComError(e);
						if(borLeft){
							borLeft.Release();
							borLeft = NULL;
						}
						if(borTop){
							borTop.Release();
							borTop = NULL;
						}
						if(borRight){
							borRight.Release();
							borRight = NULL;
						}
						if(borBottom){
							borBottom.Release();
							borBottom = NULL;
						}
						if(range){
							range.Release();
							range = NULL;
						}
						if(sheet){
							sheet.Release();
							sheet = NULL;
						}
						if(sheets){
							sheets.Release();
							sheets = NULL;
						}
						return FALSE;
					}
				}
			}
		}
		if(sheet){
			sheets.Release();
			sheets = NULL;
		}
	}catch(_com_error e){
		ShowComError(e);
		if(sheet){
			sheet.Release();
			sheet = NULL;
		}
		if(sheets){
			sheets.Release();
			sheets = NULL;
		}
		bRet = FALSE;
	}
	return bRet;
}

void CDevExcel::IndexToRangeStr(long nRow, long nCol, CString &strRangeStr){
	strRangeStr.Empty();
	if((nRow <= 0) || (nCol <= 0)){
		return;
	}

	CString strCol = "";
	long nCnt = (nCol - 1) / 26;
	long nEndCol = (nCol - 1) % 26;
	for(long i = 0; i < nCnt; i++){
		strCol +="A";
	}

	//アルファベットの A は 0x41から
	strCol += (char)nEndCol + 0x41;

	strRangeStr.Format("%s%d", strCol, nRow);
}

