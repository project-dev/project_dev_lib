// DrawerPropDlg.cpp : インプリメンテーション ファイル
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
// CDrawerPropDlg ダイアログ


CDrawerPropDlg::CDrawerPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawerPropDlg::IDD, pParent)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
	//{{AFX_DATA_INIT(CDrawerPropDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
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
// CDrawerPropDlg メッセージ ハンドラ

BOOL CDrawerPropDlg::OnInitDialog(){
	CDialog::OnInitDialog();
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
