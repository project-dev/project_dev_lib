// DevExcel.h: CDevExcel �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVEXCEL_H__8D6FF7D5_E29B_4C24_A8AE_90FDE6278A18__INCLUDED_)
#define AFX_DEVEXCEL_H__8D6FF7D5_E29B_4C24_A8AE_90FDE6278A18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DevMsofObject.h"
#include "MsImport.h"

typedef struct tagBORDERINFO{
	BOOL bIsBorder;
	COLORREF crBorder;
	int nBorderType;
}BORDERINFO, *PBORDERINFO;

typedef struct tagCELLDATA{
	char* pszValue;
	COLORREF crText;
	COLORREF crBack;
	BOOL bIsBold;
	BOOL bIsItalic;
	BOOL bIsUnderLine;
	char* pszFontFace;
	int nFontSize;
	BOOL bIsUnionCell_H;
	int nUnionCnt_H;
	BOOL bIsUnionCell_V;
	int nUnionCnt_V;
	BORDERINFO borders[4];
}CELLDATA, *PCELLDATA;

/**
 * @verify MS-EXCEL��COM�I�u�W�F�N�g�̃��b�v�N���X
 * 1�C���X�^���X1�u�b�N�Ƃ��Ĉ����B
 * �܂��A�l�̐ݒ�݂̂��s�����Ƃ�z�肵�Ă���
 * (�ȒP�ȃG�N�Z���t�@�C�����쐬�ł���Ηǂ����x�̔F��)
 */
class DEV_EXPORT CDevExcel : public CDevMsofObject{
public:
	void IndexToRangeStr(long nRow, long nCol, CString &strRangeStr);
	BOOL SetData(long nIndex, long nRow, long nCol, PCELLDATA pData, long nSize, BOOL bIsRow);
	BOOL Close();
	CDevExcel();
	virtual ~CDevExcel();
	virtual BOOL Initalize();
	virtual BOOL Finalize();
	virtual BOOL Show(BOOL bIsSHow);
	virtual BOOL Quit(LPCTSTR pszFileName, BOOL bIsSaveQuit);
	BOOL Load(LPCTSTR pszFileName); 
	BOOL Save(int nIndex, LPCTSTR pszFileName, BOOL isOverWrite);

protected:
	Excel::_ApplicationPtr m_pExcel;
	Excel::WorkbooksPtr m_pBooks;
	Excel::_WorkbookPtr m_pCurBook;


};

#endif // !defined(AFX_DEVEXCEL_H__8D6FF7D5_E29B_4C24_A8AE_90FDE6278A18__INCLUDED_)
