// DrawInfo.cpp: CDrawInfo クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CDrawInfo::CDrawInfo(LPCTSTR pszName /*= NULL*/){
	m_bPaint	= FALSE;
	eType		= eUNKNOW;		//描画種別
	m_bDrawing	= FALSE;
	if(pszName){
		m_strName = pszName;
	}else{
		//自動名前生成
		char szDir[MAX_PATH];
		char szTmp[MAX_PATH];
		memset(szDir, 0, MAX_PATH);
		memset(szTmp, 0, MAX_PATH);
		::GetTempPath(MAX_PATH, szDir);
		::GetTempFileName(szDir, "DR", 0, szTmp);
		::DeleteFile(szTmp);
		char szName[MAX_PATH];
		memset(szName, 0, MAX_PATH);
		_splitpath(szTmp, NULL, NULL, szName, NULL);
		m_strName = szName;
	}

}

CDrawInfo::~CDrawInfo()
{
	while(m_arrRect.GetSize() > 0){
		CRect *pRect = m_arrRect.GetAt(0);
		if(pRect){
			delete pRect;
		}
		m_arrRect.RemoveAt(0);
	}
}

CRect* CDrawInfo::GetRect(int nIndex){
	while(nIndex >= m_arrRect.GetSize()){
		m_arrRect.Add(new CRect(0, 0, 0, 0));
	}
	return m_arrRect.GetAt(nIndex);

}

BOOL CDrawInfo::IsSelect(){
	return m_bSel;
}
void CDrawInfo::Select(BOOL bSelect){
	m_bSel = bSelect;
}

BOOL CDrawInfo::IsDrawing(){
	return m_bDrawing;
}

void CDrawInfo::SetDrawing(BOOL bDrawing){
	m_bDrawing = bDrawing;
}

BOOL CDrawInfo::IsPaint(){
	return m_bPaint;
}

void CDrawInfo::SetPaint(BOOL bPaint){
	m_bPaint = bPaint;
}

void CDrawInfo::GetString(CString &strText){
	strText = m_strText;
}

void CDrawInfo::SetString(CString strText){
	m_strText = strText;
}

void CDrawInfo::SetString(LPCTSTR pszStr){
	m_strText = pszStr;
}

void CDrawInfo::GetXMLData(CString &strXML){
	strXML.Empty();

	strXML.Format("\t<DRAWERITEM type=\"%d\" paint=\"%d\">\n"
				  "\t\t<FONT-CR></FONT-CR>\n"
				  "\t\t<BACK-CR></BACK-CR>\n"
				  "\t\t<EDGE-CR></EDGE-CR>\n"
				  "\t\t<HALIGN></HALIGN>\n"
				  "\t\t<VALIGN></VALIGN>\n"
				  "\t\t<FONT>\n"
				  "\t\t</FONT>\n"
				  "\t\t<TEXT>%s</TEXT>\n"
				  "\t</DRAWERITEM>\n"
				  ,eType
				  ,m_bPaint
				  ,m_strText
				  ); 
}

/**
 * @brif CDrawInfoをコピーします。
 * @attention リンク情報はコピーしません
 */
BOOL CDrawInfo::Copy(CDrawInfo* pFrom){
	if(!pFrom){
		return FALSE;
	}

//public
	eType		= pFrom->eType;
	judgeRect	= pFrom->judgeRect;
	crBack		= pFrom->crBack;
	crEdge		= pFrom->crEdge;
	cfFront		= pFrom->cfFront;
	nRectCnt	= pFrom->nRectCnt;
	nLinkCnt	= 0;
	hAlign		= pFrom->hAlign;

//protected	
	int nSize = pFrom->m_arrRect.GetSize();
	for(int i = 0; i < nSize; i++){
		CRect *pRect = pFrom->m_arrRect.GetAt(i);
		CRect *pToRect = new CRect(pRect->left, pRect->top, pRect->right, pRect->bottom);
		m_arrRect.Add(pToRect);
	}
	//m_arrLinks
	memcpy(&m_lFont, &pFrom->m_lFont, sizeof(LOGFONT));
	m_bSel		= FALSE;
	m_bDrawing	= FALSE;
	m_bPaint	= pFrom->m_bPaint;
	m_strText	= pFrom->m_strText;

	return TRUE;
}

