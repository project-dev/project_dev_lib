// ColorComboBox.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "devmfc.h"
#include "ColorComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorComboBox

CColorComboBox::CColorComboBox()
{
}

CColorComboBox::~CColorComboBox()
{
}


BEGIN_MESSAGE_MAP(CColorComboBox, CComboBox)
	//{{AFX_MSG_MAP(CColorComboBox)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorComboBox ���b�Z�[�W �n���h��

BOOL CColorComboBox::Create(DWORD dwStyle, const RECT& rect, CWnd *pParent, UINT uID){
	
	dwStyle &= ~CBS_OWNERDRAWFIXED;

	//�F���̍쐬


	return CComboBox::Create(dwStyle, rect, pParent, uID);

}

int CColorComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CComboBox::OnCreate(lpCreateStruct) == -1){
		return -1;
	}
	return 0;
}

void CColorComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct){
	if(!lpDrawItemStruct){
		return;
	}

	if(lpDrawItemStruct->CtlType != ODT_COMBOBOX){
		return;
	}

	//�`���f�o�C�X�R���e�L�X�g
	HDC hDC = lpDrawItemStruct->hDC;

	//���ڂ̏��
	CString strValue = "";
	if(lpDrawItemStruct->itemData){
		strValue = (char*)lpDrawItemStruct->itemData;
	}

	if((lpDrawItemStruct->itemAction & ODA_DRAWENTIRE) == ODA_DRAWENTIRE){
	}else if((lpDrawItemStruct->itemAction & ODA_FOCUS) == ODA_FOCUS){
	}else if((lpDrawItemStruct->itemAction & ODA_SELECT) == ODA_SELECT){
	}

	if(lpDrawItemStruct->itemState & ODS_CHECKED){
	}
	if(lpDrawItemStruct->itemState & ODS_DISABLED){
	}
	if(lpDrawItemStruct->itemState & ODS_FOCUS){
	}
	if(lpDrawItemStruct->itemState & ODS_GRAYED){
	}
	if(lpDrawItemStruct->itemState & ODS_SELECTED){
	}
	if(lpDrawItemStruct->itemState & ODS_COMBOBOXEDIT){
	}
	if(lpDrawItemStruct->itemState & ODS_DEFAULT){
	}

}


void CColorComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: �w�肳�ꂽ�A�C�e���̃T�C�Y�𒲂ׂ邽�߂̃R�[�h��ǉ����Ă�������
	
}
