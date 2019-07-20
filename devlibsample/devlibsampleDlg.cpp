// devlibsampleDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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
	"�e�X�g",
	"�e�X�g",
	"�l�r �S�V�b�N"
	"MS UI Gothic"
};

static int nDataCnt = sizeof(strData) / sizeof(CString);

/////////////////////////////////////////////////////////////////////////////
// CSampleDlg �_�C�A���O

CSampleDlg::CSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSampleDlg)
		// ����: ���̈ʒu�� ClassWizard �ɂ���ă����o�̏��������ǉ�����܂��B
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSampleDlg)
		// ����: ���̏ꏊ�ɂ� ClassWizard �ɂ���� DDX �� DDV �̌Ăяo�����ǉ�����܂��B
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
// CSampleDlg ���b�Z�[�W �n���h��

BOOL CSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	OutputDebugString("������������Start������������\n");
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CSampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSampleDlg::OnBtnIniread() {
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
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
