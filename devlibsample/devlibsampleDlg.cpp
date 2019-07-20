// devlibsampleDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "devlibsample.h"
#include "devlibsampleDlg.h"
#include "devlib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static CString strData[]={
	"Test",
	"テスト",
	"テスト",
	"ＭＳ ゴシック"
	"MS UI Gothic"
};

static int nDataCnt = sizeof(strData) / sizeof(CString);

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg ダイアログ

CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSampleDlg)
		// メモ: この位置に ClassWizard によってメンバの初期化が追加されます。
	//}}AFX_DATA_INIT
	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleDlg)
		// メモ: この場所には ClassWizard によって DDX と DDV の呼び出しが追加されます。
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSampleDlg, CDialog)
	//{{AFX_MSG_MAP(CSampleDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_INIREAD, OnBtnIniread)
	ON_BN_CLICKED(IDC_BTN_INIWRITE, OnBtnIniwrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg メッセージ ハンドラ

BOOL CSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	OutputDebugString("■■■■■■Start■■■■■■\n");
	// TODO: 特別な初期化を行う時はこの場所に追加してください。
	
	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CSampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSampleDlg::OnBtnIniread() {
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	char szFileName[MAX_PATH];
	memset(szFileName, 0, MAX_PATH);
	::GetModuleFileName(NULL, szFileName, MAX_PATH);
	CString strIni = szFileName;
	strIni.Replace(".exe", ".ini");

	for(int i = 0; i < nDataCnt; i++){
		CString strKey;
		char szBuff[1024];
		memset(szBuff, 0, 1024);
		strKey.Format("TestKet%03d", i);
		::GetInifileString("TESTINI", strKey, "", szBuff, 1024, strIni);
		if(strData[i].CollateNoCase(szBuff)){
			AfxMessageBox("Unmatch Data");
			break;
		}
	}
	
}

void CSampleDlg::OnBtnIniwrite() {
	char szFileName[MAX_PATH];
	memset(szFileName, 0, MAX_PATH);
	::GetModuleFileName(NULL, szFileName, MAX_PATH);
	CString strIni = szFileName;
	strIni.Replace(".exe", ".ini");

	for(int i = 0; i < nDataCnt; i++){
		CString strKey;
		strKey.Format("TestKet%03d", i);
		::WriteInifileString("TESTINI", strKey, strData[i], strIni);
	}
		
}
