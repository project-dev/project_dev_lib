#if !defined(__DEVSTRUCT__)
#define __DEVSTRUCT__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagTECHNOLOGY{
	bool bPlotter;			//�x�N�^�v���b�^
	bool bRasDisplay;		//���X�^�f�B�X�v���C
	bool bRasPrinter;		//���X�^�v�����^ 
	bool bRasCamera;		//���X�^�J���� 
	bool bCharStream;		//�����X�g���[�� 
	bool bMetaFile;			//���^�t�@�C�� 
	bool bDispFile;			//�f�B�X�v���C�t�@�C�� 
}GDCTECHNOLOGY, *PGDCTECHNOLOGY;

#if 1
typedef struct tagSHADEBLENDCAPS{
	bool bCONST_ALPHA;		//���̃f�o�C�X�́ABLENDFUNCTION �\���̂� SourceConstantAlpha �����o�𑀍�ł��܂��B���̍\���̂́AAlphaBlend �֐��� blendFunction �p�����[�^�ŎQ�Ƃ������̂ł��B 
	bool bGRAD_RECT;		//���̃f�o�C�X�ɂ́AGradientFill �֐����g���Ē����`����������\�͂�����܂��B 
	bool bGRAD_TRI;			//���̃f�o�C�X�ɂ́AGradientFill �֐����g���ĎO�p�`����������\�͂�����܂��B 
	bool bNONE;				//���̃f�o�C�X�͂����̔\�͂��T�|�[�g���Ă��܂���B 
	bool bPIXEL_ALPHA;		//���̃f�o�C�X�ɂ́AAlphaBlend �֐����g���āA�s�N�Z�����Ƃ̃A���t�@�i�����x�A�P�x�j�𑀍삷��\�͂�����܂��B 
	bool bPREMULT_ALPHA;	//���̃f�o�C�X�ɂ́AAlphaBlend �֐����g���āA���炩���ߔ{����ݒ肳�ꂽ�A���t�@�𑀍삷��\�͂�����܂��B 
}GDCSHADEBLENDCAPS,*PGDCSHADEBLENDCAPS;
#endif

typedef struct tagRASTERCAPS{
	bool bBANDING;			//�o���h�����̃T�|�[�g���K�v�ł��B
	bool bBITBLT;			//���̃f�o�C�X�ɂ́A�r�b�g�}�b�v�̓]���\�͂�����܂��B 
	bool bBITMAP64;			//���̃f�o�C�X�́A64 �L���o�C�g�iKB�j���傫���r�b�g�}�b�v���T�|�[�g���Ă��܂��B 
	bool bDI_BITMAP;		//���̃f�o�C�X�́ASetDIBits �֐��� GetDIBits �֐����T�|�[�g���Ă��܂��B 
	bool bDIBTODEV;			//���̃f�o�C�X�́ASetDIBitsToDevice �֐����T�|�[�g���Ă��܂��B 
	bool bFLOODFILL;		//���̃f�o�C�X�ɂ́A�h��Ԃ����s���\�͂�����܂��B 
	bool bGDI20_OUTPUT;		//���̃f�o�C�X�́A16 �r�b�g�ł� Windows 2.0 �̋@�\���T�|�[�g���Ă��܂��B 
	bool bPALETTE;			//���̃f�o�C�X�́A�p���b�g�x�[�X�̃f�o�C�X�Ƃ��Ďw��ł��܂��B 
	bool bSCALING;			//���̃f�o�C�X�ɂ́A�X�P�[�����O���s���\�͂�����܂��B 
	bool bSTRETCHBLT;		//���̃f�o�C�X�ɂ́AStretchBlt �֐������s����\�͂�����܂��B 
	bool bSTRETCHDIB;		//���̃f�o�C�X�ɂ́AStretchDIBits �֐������s����\�͂�����܂��B 
}GDCRASTERCAPS, *PGDCRASTERCAPS;

typedef struct tagCURVECAPS{
	bool bNONE;				//���̃f�o�C�X�́A�Ȑ����T�|�[�g���Ă��܂���B 
	bool bCHORD;			//���̃f�o�C�X�́A�|�`�i�ʂƌ�����Ȃ�}�`�j�̌ʂ�`��ł��܂��B 
	bool bCIRCLES;			//���̃f�o�C�X�́A�~��`��ł��܂��B 
	bool bELLIPSES;			//���̃f�o�C�X�́A�ȉ~��`��ł��܂��B 
	bool bINTERIORS;		//���̃f�o�C�X�́A�����̓h��Ԃ����s���܂��B 
	bool bPIE;				//���̃f�o�C�X�́A��`��`��ł��܂��B 
	bool bROUNDRECT;		//���̃f�o�C�X�́A�p�̊ۂ������`��`��ł��܂��B 
	bool bSTYLED;			//���̃f�o�C�X�́A�X�^�C���t���̋��E����`��ł��܂��B 
	bool bWIDE;				//���̃f�o�C�X�́A�������E����`��ł��܂��B 
	bool bWIDESTYLED;		//���̃f�o�C�X�́A�X�^�C���t���̑������E����`��ł��܂��B
}GDCCURVECAPS, *PGDCCURVECAPS;

typedef struct tagLINECAPS{
	bool bNONE;				//���̃f�o�C�X�́A�������T�|�[�g���Ă��܂���B 
	bool bINTERIORS;		//���̃f�o�C�X�́A�����̓h��Ԃ����s���܂��B 
	bool bMARKER;			//���̃f�o�C�X�́A1 �̃}�[�J�[��`��ł��܂��B 
	bool bPOLYLINE;			//���̃f�o�C�X�́A�A��������`��ł��܂��B 
	bool bPOLYMARKER;		//���̃f�o�C�X�́A�����̃}�[�J�[��`��ł��܂��B 
	bool bSTYLED;			//���̃f�o�C�X�́A�X�^�C���t���̒�����`��ł��܂��B 
	bool bWIDE;				//���̃f�o�C�X�́A����������`��ł��܂��B 
	bool bWIDESTYLED;		//���̃f�o�C�X�́A�X�^�C���t���̑���������`��ł��܂��B 
}GDCLINECAPS, *PGDCLINECAPS;

typedef struct tagPOLYGONALCAPS{
	bool bNONE;				//���̃f�o�C�X�́A���p�`���T�|�[�g���Ă��܂���B 
	bool bINTERIORS;		//���̃f�o�C�X�́A�����̕`����s���܂��B 
	bool bPOLYGON;			//���̃f�o�C�X�́A���݃��[�h�̓h��Ԃ����s���܂��B
	bool bRECTANGLE;		//���̃f�o�C�X�́A�����`��`��ł��܂��B 
	bool bSCANLINE;			//���̃f�o�C�X�́A�P��̑����s��`��ł��܂��B 
	bool bSTYLED;			//���̃f�o�C�X�́A�X�^�C���t���̋��E����`��ł��܂��B 
	bool bWIDE;				//���̃f�o�C�X�́A�������E����`��ł��܂��B 
	bool bWIDESTYLED;		//���̃f�o�C�X�́A�X�^�C���t���̑������E����`��ł��܂��B 
	bool bWINDPOLYGON;		//���̃f�o�C�X�́A�S�惂�[�h�ł̑��p�`�̓h��Ԃ����s���܂��B
}GDCPOLYGONALCAPS, *PGDCPOLYGONALCAPS;

typedef struct tagTEXTCAPS{
	bool bOP_CHARACTER;		//���̃f�o�C�X�ɂ́A�L�����N�^�̏o�͐��x�𒲐�����\�͂�����܂��B 
	bool bOP_STROKE;		//���̃f�o�C�X�ɂ́A�X�g���[�N�̏o�͐��x�𒲐�����\�͂�����܂��B 
	bool bCP_STROKE;		//���̃f�o�C�X�ɂ́A�X�g���[�N�N���b�v�̐��x�𒲐�����\�͂�����܂��B 
	bool bCR_90;			//���̃f�o�C�X�ɂ́A�L�����N�^�� 90 �x��]���s���\�͂�����܂��B 
	bool bCR_ANY;			//���̃f�o�C�X�ɂ́A�L�����N�^�̔C�ӂ̊p�x�̉�]���s���\�͂�����܂��B 
	bool bSF_X_YINDEP;		//���̃f�o�C�X�́Ax ������ y �����̓Ɨ������X�P�[�����O�i���̂ƕ��́j���s���܂��B 
	bool bSA_DOUBLE;		//���̃f�o�C�X�́A�L�����N�^�� 2 �{�̃X�P�[�����O�i�{�p�j���s���܂��B 
	bool bSA_INTEGER;		//���̃f�o�C�X�́A�L�����N�^�̐����{�̃X�P�[�����O�in �{�p�j���s���܂��B 
	bool bSA_CONTIN;		//���̃f�o�C�X�́A�L�����N�^�̔C�ӂ̔{���̃X�P�[�����O���s���܂��B 
	bool bEA_DOUBLE;		//���̃f�o�C�X�́A2 �{�̑����̕����i�����j��`��ł��܂��B 
	bool bIA_ABLE;			//���̃f�o�C�X�́A�C�^���b�N�̂�`��ł��܂��B 
	bool bUA_ABLE;			//���̃f�o�C�X�́A������`��ł��܂��B 
	bool bSO_ABLE;			//���̃f�o�C�X�́A����������`��ł��܂��B 
	bool bRA_ABLE;			//���̃f�o�C�X�́A���X�^�t�H���g��`��ł��܂��B 
	bool bVA_ABLE;			//���̃f�o�C�X�́A�x�N�g���t�H���g��`��ł��܂��B 
	bool bRESERVED;			//�\��ς݂ł��B
	bool bSCROLLBLT;		//���̃f�o�C�X�́A�r�b�g�u���b�N�]���i�u���b�g�j�ɂ��X�N���[�����s���܂���B���̃t���O���A�\���Ƃ͋t�̂��Ƃ��Ӗ�����\�������邱�Ƃɒ��ӂ��Ă��������B 
}GDCTEXTCAPS, *PGDCTEXTCAPS;

#if 0
typedef struct tagCOLORMGMTCAPS{
	bool bCMYK_COLOR;		//���̃f�o�C�X�́ACMYK�i�V�A���A�}�[���^�A�C�G���[�A�u���b�N�j�̃J���[�X�y�[�X�i�F��ԁj�Ɋ�Â� ICC�iInternational Color Consortium�j�̃J���[�v���t�@�C�����󂯓���܂��B 
	bool bDEVICE_ICM;		//���̃f�o�C�X�́A�f�o�C�X�h���C�o�܂��̓f�o�C�X�̑��� ICM�i�C���[�W�F�̊Ǘ��j�����{�ł��܂��B 
	bool bGAMMA_RAMP;		//���̃f�o�C�X�́AGetDeviceGammaRamp �� SetDeviceGammaRamp �̊e�֐����T�|�[�g���Ă��܂��B 
	bool bNONE;				//���̃f�o�C�X�́AICM ���T�|�[�g���Ă��܂���B 
}GDCCOLORMGMTCAPS, *PGDCCOLORMGMTCAPS;
#endif

typedef struct tagDEVICEINFO{
	int					nDrvVersion;		//�f�o�C�X�h���C�o�̃o�[�W����
	GDCTECHNOLOGY		gdcTech;			//�f�o�C�X�e�N�m���W�i�^�C�v�j
	int					nHorzSize;			//�~�����[�g���imm�j�P�ʂ̉�ʂ̕����I�ȕ�
	int					nVertSize;			//�~�����[�g���imm�j�P�ʂ̉�ʂ̕����I�ȍ���
	int					nHorzRes;			//�s�N�Z���P�ʂ̉�ʂ̕�
	int					nVertRes;			//�s�N�Z���P�ʁi���X�^�s���j�̉�ʂ̍���
	int					nLogPixelsX;		//��ʂ̐��������ł́A�_���C���`������̃s�N�Z����
	int					nLogPixelsY;		//��ʂ̐��������ł́A�_���C���`������̃s�N�Z����
	int					nBitsPixel;			//�s�N�Z��������̃J���[�r�b�g�̐�
	int					nPlanes;			//�J���[�v���[���̐�
	int					nNumBrushes;		//�f�o�C�X�ŗL�̃u���V�̐�
	int					nNumPens;			//�f�o�C�X�ŗL�̃y���̐�
	int					nNumFonts;			//�f�o�C�X�ŗL�̃t�H���g�̐�
	int					nNumColors;			//�f�o�C�X�̃J���[�[�x
	int					nAspectX;			//���̕`��Ɏg���f�o�C�X�s�N�Z���̑��ΓI�ȕ�
	int					nAspectY;			//���̕`��Ɏg���f�o�C�X�s�N�Z���̑��ΓI�ȍ���
	int					nAspectXY;			//���̕`��Ɏg���f�o�C�X�s�N�Z���̑Ίp���̕�
	int					nPDeviceSize;		//�\��ς�
	int					nClipCaps;			//�f�o�C�X�̃N���b�s���O�\�͂������t���O
	int					nSizePalette;		//�V�X�e���p���b�g���̃G���g����
	int					nNumReserved;		//�V�X�e���p���b�g���̗\��G���g����
	int					nColorRes;			//�f�o�C�X�̎��ۂ̐F�[�x
	int					nPhysicalWidth;		//�y�[�W�̕����I�ȕ����f�o�C�X�P�ʂŕ\���܂�(����f�o�C�X�p)
	int					nPhysicalHeight;	//�y�[�W�̕����I�ȍ������f�o�C�X�P�ʂŕ\���܂�(����f�o�C�X�p)
	int					nPhysicalOffsetX;	//�����I�ȃy�[�W�̍��[�������\�̈�̍��[�܂ł̋������f�o�C�X�P�ʂŕ\���܂�(����f�o�C�X�p)
	int					nPhysicalOffsetY;	//�����I�ȃy�[�W�̏�[�������\�̈�̏�[�܂ł̋������f�o�C�X�P�ʂŕ\���܂�(����f�o�C�X�p)
#if 1
	int					nVRefresh;			//�̌��݂̃��t���b�V�����[�g�i�����������g���j�� 1 �b������̃T�C�N�����iHz�j�ŕ\���܂�(�f�B�X�v���C�f�o�C�X�p)
#endif	
	int					nScalingFactorX;	//�v�����^�̐������̔{��
	int					nScalingFactorY;	//�v�����^�̐������̔{��
#if 1	
	int					nBltAlignment;		//�������̃A���C�������g�i����P�ʁj�̗D��l���s�N�Z���P�ʂŎ擾���܂�
#endif
#if 0
	int					nShadeBlendCaps;	//�f�o�C�X�̃V�F�[�f�B���O�i�A�e�j�ƃu�����f�B���O�i���F�j�̔\�͂������l�ł�
#endif
	GDCRASTERCAPS		RasTerCaps;			//�f�o�C�X�̃��X�^�\�͂������܂�
	GDCCURVECAPS		CurVeCaps;			//�f�o�C�X�̋Ȑ��`��\�͂������܂� 
	GDCLINECAPS			LineCaps;			//�f�o�C�X�̒����`��\�͂������܂�
	GDCPOLYGONALCAPS	PolygonalCaps;		//�f�o�C�X�̑��p�`�`��\�͂������܂�
	GDCTEXTCAPS			TextCaps;			//�f�o�C�X�̃e�L�X�g�\���\�͂������܂�
#if 0
	GDCCOLORMGMTCAPS	ColorMGMTCaps;		//�f�o�C�X�̐F�̊Ǘ��i�J���[�}�l�W�����g�j�\�͂������܂��B
#endif
}DEVICEINFO, *PDEVICEINFO;

#ifdef __cplusplus
}
#endif

#endif