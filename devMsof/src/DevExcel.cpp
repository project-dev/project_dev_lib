// DevExcel.cpp: CDevExcel �N���X�̃C���v�������e�[�V����
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
// �\�z/����
//////////////////////////////////////////////////////////////////////

/**
 * @verify �R���X�g���N�^
 */
CDevExcel::CDevExcel(){
	m_pExcel = NULL;
	m_pBooks = NULL;
	m_pCurBook = NULL;
}

/**
 * @verify �f�X�g���N�^
 */
CDevExcel::~CDevExcel(){
}

/**
 * @verify ������
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
 * @verify �㏈��
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
 * @verify Excel�̕\��/��\����ݒ肵�܂��B
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
 * @verify �u�b�N����܂��B
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
 * @verify �u�b�N���J���܂�
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
 * @verify ���݊J���Ă���u�b�N��ۑ����܂��B
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
 * @verify ���݊J���Ă���u�b�N����܂��B
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
 * @verify �f�[�^��ݒ肵�܂��B
 * @param nIndex �V�[�g�̃C���f�b�N�X
 * @param nRow �J�n�_
 * @param nCol �J�n�_
 * @param pData �ݒ�f�[�^
 * @param nSize �ݒ�f�[�^��
 * @param bIsRow �c�����ɐݒ肩�������ɐݒ肩
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
			SetLastErrorMsg("�V�[�g�����݂��܂���B");
			ShowErrorMsg();
			return FALSE;
		}

		long lSize = sheets->Count;
		if(lSize <= nIndex){
			SetLastErrorMsg("�C���f�b�N�X���s���ł��B");
			ShowErrorMsg();
			bRet = FALSE;
		}else if(lSize > 0){
			COleVariant vIndex = nIndex;
			sheet = sheets->GetItem(vIndex);
			if(sheet == NULL){
				SetLastErrorMsg("�V�[�g�����݂��܂���B");
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

						//�l�ݒ�
						COleVariant vtValue;
						vtValue		= pData[i].pszValue;
						range->Value	= vtValue;

						//�t�H���g�ݒ�
						COleVariant vtBold		= (long)pData[i].bIsBold;
						COleVariant vtItalic	= (long)pData[i].bIsItalic;
						COleVariant vtUnderLine	= (long)pData[i].bIsUnderLine;
						COleVariant vtSize		= (long)pData[i].nFontSize;
						COleVariant vtName		= pData[i].pszFontFace;
						range->Font->Bold		= vtBold;
						range->Font->Italic		= vtItalic;
						//Underline�͂Ȃ����ݒ�ł��Ȃ�����
						//range->Font->Underline	= vtUnderLine;
						range->Font->Size		= vtSize;
						range->Font->Name		= vtName;

						//�{�[�_�[�ݒ�
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

	//�A���t�@�x�b�g�� A �� 0x41����
	strCol += (char)nEndCol + 0x41;

	strRangeStr.Format("%s%d", strCol, nRow);
}

