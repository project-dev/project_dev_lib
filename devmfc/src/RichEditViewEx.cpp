// RichEditViewEx.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "devmfc.h"
#include "RichEditViewEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRichEditViewEx

IMPLEMENT_DYNCREATE(CRichEditViewEx, CRichEditView)

CRichEditViewEx::CRichEditViewEx()
{
}

CRichEditViewEx::~CRichEditViewEx()
{
}


BEGIN_MESSAGE_MAP(CRichEditViewEx, CRichEditView)
	//{{AFX_MSG_MAP(CRichEditViewEx)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRichEditViewEx �`��

void CRichEditViewEx::OnDraw(CDC* pDC){
	CDocument* pDoc = GetDocument();
	// TODO: ���̈ʒu�ɕ`��p�̃R�[�h��ǉ����Ă�������
}

/////////////////////////////////////////////////////////////////////////////
// CRichEditViewEx �f�f

#ifdef _DEBUG
void CRichEditViewEx::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CRichEditViewEx::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRichEditViewEx ���b�Z�[�W �n���h��
