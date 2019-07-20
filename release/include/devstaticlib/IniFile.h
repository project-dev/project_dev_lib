// IniFile.h: CIniFile �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__F200CC2B_42BF_499B_A6BD_E4B7515D1D7A__INCLUDED_)
#define AFX_INIFILE_H__F200CC2B_42BF_499B_A6BD_E4B7515D1D7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/**
 * �f�[�^�^��ʗ񋓌^
 */
typedef enum eINITYPE{
	IT_INT,
	IT_BOOL,
	IT_STRING,
	IT_DOUBLE,
};

/**
 * @brif Ini�t�@�C����`���\����
 */
typedef struct tagINIDATA{
	eINITYPE eType;			//�f�[�^�^���	
	char* szSecssion;		//�Z�b�V������
	char* szKey;			//�L�[��
	LPVOID pData;			//�f�[�^���i�[����Ă���/�i�[����ϐ��̃|�C���^
	LPVOID pDefault;		//�f�t�H���g�̒l
	int nLen;				//����
}INIDATA;


class CIniFile {
public:
	CIniFile();
	virtual ~CIniFile();
	BOOL IniFileAccess(LPCTSTR pszIniPath, BOOL bSave);
protected:
	virtual BOOL OnIniFileAccess(INIDATA* &pIniData, int &nCnt) = 0;
};

#endif // !defined(AFX_INIFILE_H__F200CC2B_42BF_499B_A6BD_E4B7515D1D7A__INCLUDED_)
