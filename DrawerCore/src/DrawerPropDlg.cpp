// DrawerPropDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "drawercore.h"
#include "DrawerPropDlg.h"
#include "DrawerCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawerPropDlg �_�C�A���O


CDrawerPropDlg::CDrawerPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawerPropDlg::IDD, pParent)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	//{{AFX_DATA_INIT(CDrawerPropDlg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CDrawerPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawerPropDlg)
	DDX_Control(pDX, IDC_PROP_TAB, m_objTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDrawerPropDlg, CDialog)
	//{{AFX_MSG_MAP(CDrawerPropDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawerPropDlg ���b�Z�[�W �n���h��

BOOL CDrawerPropDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}
