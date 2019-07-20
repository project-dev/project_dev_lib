// ColumnInfo.cpp: CColumnInfo �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ColumnInfo.h"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CColumnInfo::CColumnInfo()
{

}

CColumnInfo::~CColumnInfo(){
	for(int i = 0; i < m_arrInfo.GetSize(); i++){
		PCOLUMNINFO pInfo = m_arrInfo.GetAt(i);
		delete pInfo;
	}
	m_arrInfo.RemoveAll();

}

void CColumnInfo::AddInfo(PCOLUMNINFO pInfo){
	PCOLUMNINFO pColInfo = new COLUMNINFO;
	memcpy(pColInfo, pInfo, sizeof(COLUMNINFO));
	m_arrInfo.Add(pColInfo);
}
PCOLUMNINFO CColumnInfo::GetInfo(int nIndex){
	return m_arrInfo.GetAt(nIndex);
}
int CColumnInfo::GetSize(){
	return m_arrInfo.GetSize();
}
