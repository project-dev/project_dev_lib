// BaseTabView.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "TabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabView

IMPLEMENT_DYNCREATE(CTabView, CView)

// 
// �֐��� : CTabView
// �T  �v : �R���X�g���N�^
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
CTabView::CTabView(){
}

// 
// �֐��� : ~CTabView
// �T  �v : �f�X�g���N�^
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
CTabView::~CTabView(){
}


BEGIN_MESSAGE_MAP(CTabView, CView)
	//{{AFX_MSG_MAP(CTabView)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_MESSAGE(WM_HWNDTABCHANGE, OnSelchange)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabView �`��

// 
// �֐��� : OnDraw
// �T  �v : �`��
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CTabView::OnDraw(CDC* pDC){
	CDocument* pDoc = GetDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CTabView �f�f

#ifdef _DEBUG
void CTabView::AssertValid() const{
	CView::AssertValid();
}

void CTabView::Dump(CDumpContext& dc) const{
	CView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabView ���b�Z�[�W �n���h��

// 
// �֐��� : OnCreate
// �T  �v : �������ɌĂяo�����
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
int CTabView::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	GetClientRect(rect);
	m_objTabCtrl.Create(WS_CHILD | WS_VISIBLE | TCS_TOOLTIPS | TCS_TABS | WS_TABSTOP, rect, this, 0);
	m_objTabCtrl.EnableToolTips();

	return 0;
}

/**
 * �V�K�y�[�W�̍쐬
 * @param nIndex    �C���f�b�N�X
 * @param strTitle  �^�u�̖��O
 * @param hWnd      �^�u�Ɋ֘A�t����E�B���h�E�n���h��
 * @return �}���ʒu
 */
int CTabView::CreatePage(int nIndex, LPCTSTR strTitle, HWND hWnd){
	if(!hWnd){
		return -1;
	}
	TCITEM tcItem;
	memset(&tcItem, 0, sizeof(TCITEM));
	tcItem.mask			= TCIF_TEXT | TCIF_PARAM;
	tcItem.pszText		= (LPTSTR)strTitle;
	tcItem.cchTextMax	= strlen(strTitle);
	tcItem.lParam		= (LPARAM)hWnd;
	
	int nRet = m_objTabCtrl.InsertItem(nIndex, &tcItem);
	::SetParent(hWnd, m_objTabCtrl.m_hWnd);
	return nRet;
}

// 
// �֐��� : OnPaint
// �T  �v : �`��
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CTabView::OnPaint(){
	CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g
	CRect rect;
	GetClientRect(rect);
	m_objTabCtrl.SetWindowPos(&wndTop, rect.left, rect.top, rect.Width(), rect.Height(), SWP_SHOWWINDOW);
	m_objTabCtrl.SetPagePosition();
}

/**
 * CCustTabCtrl�R���g���[�����擾
 * @return  CCustTabCtrl�I�u�W�F�N�g
 */
CHwndTabCtrl& CTabView::GetTabCtrl(){
	return m_objTabCtrl;
}

// 
// �֐��� : OnSelchange
// �T  �v : �I��ύX���̃n���h���֐�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
LRESULT CTabView::OnSelchange(WPARAM wParam, LPARAM lParam) {
	m_objTabCtrl.SetActivePage(m_objTabCtrl.GetCurSel());	
	NMHDR* pNMHDR = (NMHDR*)wParam; 
	LRESULT* pResult = (LRESULT*)lParam;
	*pResult = 0;
	OnSelChangeFunc(pNMHDR, pResult);
	return *pResult;
}

/**
 *�y�[�W�؂�ւ����ɌĂяo�����֐�
 * @param pNMHDR WM_HWNDTABCHANGE ��wParam
 * @param pResult WM_HWNDTABCHANGE ��lParam
 */
void CTabView::OnSelChangeFunc(NMHDR* pNMHDR, LRESULT* pResult){
}
