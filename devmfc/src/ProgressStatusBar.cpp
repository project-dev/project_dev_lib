// ProgressStatusBar.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "ProgressStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar
/**
 * �R���X�g���N�^
 */
CProgressStatusBar::CProgressStatusBar(){
	m_nIndex = -1;
}

/**
 *�f�X�g���N�^
 */
CProgressStatusBar::~CProgressStatusBar(){
}


BEGIN_MESSAGE_MAP(CProgressStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CProgressStatusBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressStatusBar ���b�Z�[�W �n���h��

// 
// �֐��� : GetProgressBar
// �T  �v : CProgressCtrl�̎擾
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
CProgressCtrl* CProgressStatusBar::GetProgressBar(){
	
	return &m_objProgress;
}

// 
// �֐��� : OnCreate
// �T  �v : �E�B���h�E�������̃n���h���֐�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
int CProgressStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct){
	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
    m_objProgress.Create(WS_CHILD, rect, this, 0);
	
	return 0;
}

// 
// �֐��� : ShowProgressBar
// �T  �v : �v���O���X�o�[�̕\��
// ��  �� : nIndex �\���ʒu
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
UINT CProgressStatusBar::ShowProgressBar(int nIndex){
	CRect rect;
    int nOldIndex = m_nIndex;
    m_nIndex = nIndex;
    GetItemRect(nIndex, rect);
    m_objProgress.MoveWindow(rect);
    m_objProgress.ShowWindow((nIndex == -1) ? SW_HIDE : SW_SHOWNA);
    return nOldIndex;

}

// 
// �֐��� : OnSize
// �T  �v : �T�C�Y�ύX���̃n���h���֐�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CProgressStatusBar::OnSize(UINT nType, int cx, int cy){
	CStatusBar::OnSize(nType, cx, cy);
    if (!::IsWindow(m_objProgress.m_hWnd) || m_nIndex == -1)
        return;

    // �ʒu���C��
    CRect rect;
    GetItemRect(m_nIndex, rect);
    m_objProgress.MoveWindow(rect, FALSE);
}

// 
// �֐��� : SetRange32
// �T  �v : �ő�A�ŏ��̐ݒ�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CProgressStatusBar::SetRange32(int nLower, int nUpper){
	m_objProgress.SetRange32(nLower, nUpper);
}

// 
// �֐��� : SetRange
// �T  �v : �ő�A�ŏ��̐ݒ�
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CProgressStatusBar::SetRange(short nLower, short nUpper){
	m_objProgress.SetRange(nLower, nUpper);
}

// 
// �֐��� : GetRange
// �T  �v : �ő�A�ŏ��̎擾
// ��  �� : �Ȃ�
// �߂�l : �Ȃ�
// ��  �l : �Ȃ�
//
void CProgressStatusBar::GetRange(int &nLower, int &nUpper){
	m_objProgress.GetRange(nLower, nUpper);
}

/**
 * �ڐ���̌��݈ʒu�̎擾
 * @return �ڐ���̌��݂̈ʒu
 */
int CProgressStatusBar::GetPos(){
	return m_objProgress.GetPos();
}

/**
 * �ڐ���̈ʒu��ݒ�
 * @param nPos �ʒu
 * @return ���O�̈ʒu
 */
int CProgressStatusBar::SetPos(int nPos){
	return m_objProgress.SetPos(nPos);
}

/**
 * �I�t�Z�b�g�ʒu���w��
 * @param nPos �ʒu��i�߂�ʂ��w�肵�܂�
 * @return ���O�̈ʒu
 */
int CProgressStatusBar::OffsetPos(int nPos){
	return m_objProgress.OffsetPos(nPos);
}

/**
 * �����l���w��
 * @return ���O�̑����l��Ԃ��܂��B
 */
int CProgressStatusBar::SetStep(int nStep){
	return m_objProgress.SetStep(nStep);
}


/**
 * �ڐ����i�߂܂�
 * @return ���O�̈ʒu��Ԃ��܂��B
 */
int CProgressStatusBar::StepIt(){
	return m_objProgress.StepIt();
}
