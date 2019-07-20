#if !defined(__DEVSTRUCT__)
#define __DEVSTRUCT__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tagTECHNOLOGY{
	bool bPlotter;			//ベクタプロッタ
	bool bRasDisplay;		//ラスタディスプレイ
	bool bRasPrinter;		//ラスタプリンタ 
	bool bRasCamera;		//ラスタカメラ 
	bool bCharStream;		//文字ストリーム 
	bool bMetaFile;			//メタファイル 
	bool bDispFile;			//ディスプレイファイル 
}GDCTECHNOLOGY, *PGDCTECHNOLOGY;

#if 1
typedef struct tagSHADEBLENDCAPS{
	bool bCONST_ALPHA;		//このデバイスは、BLENDFUNCTION 構造体の SourceConstantAlpha メンバを操作できます。この構造体は、AlphaBlend 関数の blendFunction パラメータで参照したものです。 
	bool bGRAD_RECT;		//このデバイスには、GradientFill 関数を使って長方形を処理する能力があります。 
	bool bGRAD_TRI;			//このデバイスには、GradientFill 関数を使って三角形を処理する能力があります。 
	bool bNONE;				//このデバイスはこれらの能力をサポートしていません。 
	bool bPIXEL_ALPHA;		//このデバイスには、AlphaBlend 関数を使って、ピクセルごとのアルファ（透明度、輝度）を操作する能力があります。 
	bool bPREMULT_ALPHA;	//このデバイスには、AlphaBlend 関数を使って、あらかじめ倍率を設定されたアルファを操作する能力があります。 
}GDCSHADEBLENDCAPS,*PGDCSHADEBLENDCAPS;
#endif

typedef struct tagRASTERCAPS{
	bool bBANDING;			//バンド処理のサポートが必要です。
	bool bBITBLT;			//このデバイスには、ビットマップの転送能力があります。 
	bool bBITMAP64;			//このデバイスは、64 キロバイト（KB）より大きいビットマップをサポートしています。 
	bool bDI_BITMAP;		//このデバイスは、SetDIBits 関数と GetDIBits 関数をサポートしています。 
	bool bDIBTODEV;			//このデバイスは、SetDIBitsToDevice 関数をサポートしています。 
	bool bFLOODFILL;		//このデバイスには、塗りつぶしを行う能力があります。 
	bool bGDI20_OUTPUT;		//このデバイスは、16 ビット版の Windows 2.0 の機能をサポートしています。 
	bool bPALETTE;			//このデバイスは、パレットベースのデバイスとして指定できます。 
	bool bSCALING;			//このデバイスには、スケーリングを行う能力があります。 
	bool bSTRETCHBLT;		//このデバイスには、StretchBlt 関数を実行する能力があります。 
	bool bSTRETCHDIB;		//このデバイスには、StretchDIBits 関数を実行する能力があります。 
}GDCRASTERCAPS, *PGDCRASTERCAPS;

typedef struct tagCURVECAPS{
	bool bNONE;				//このデバイスは、曲線をサポートしていません。 
	bool bCHORD;			//このデバイスは、弓形（弧と弦からなる図形）の弧を描画できます。 
	bool bCIRCLES;			//このデバイスは、円を描画できます。 
	bool bELLIPSES;			//このデバイスは、楕円を描画できます。 
	bool bINTERIORS;		//このデバイスは、内部の塗りつぶしを行えます。 
	bool bPIE;				//このデバイスは、扇形を描画できます。 
	bool bROUNDRECT;		//このデバイスは、角の丸い長方形を描画できます。 
	bool bSTYLED;			//このデバイスは、スタイル付きの境界線を描画できます。 
	bool bWIDE;				//このデバイスは、太い境界線を描画できます。 
	bool bWIDESTYLED;		//このデバイスは、スタイル付きの太い境界線を描画できます。
}GDCCURVECAPS, *PGDCCURVECAPS;

typedef struct tagLINECAPS{
	bool bNONE;				//このデバイスは、直線をサポートしていません。 
	bool bINTERIORS;		//このデバイスは、内部の塗りつぶしを行えます。 
	bool bMARKER;			//このデバイスは、1 個のマーカーを描画できます。 
	bool bPOLYLINE;			//このデバイスは、連続直線を描画できます。 
	bool bPOLYMARKER;		//このデバイスは、複数のマーカーを描画できます。 
	bool bSTYLED;			//このデバイスは、スタイル付きの直線を描画できます。 
	bool bWIDE;				//このデバイスは、太い直線を描画できます。 
	bool bWIDESTYLED;		//このデバイスは、スタイル付きの太い直線を描画できます。 
}GDCLINECAPS, *PGDCLINECAPS;

typedef struct tagPOLYGONALCAPS{
	bool bNONE;				//このデバイスは、多角形をサポートしていません。 
	bool bINTERIORS;		//このデバイスは、内部の描画を行えます。 
	bool bPOLYGON;			//このデバイスは、交互モードの塗りつぶしを行えます。
	bool bRECTANGLE;		//このデバイスは、長方形を描画できます。 
	bool bSCANLINE;			//このデバイスは、単一の走査行を描画できます。 
	bool bSTYLED;			//このデバイスは、スタイル付きの境界線を描画できます。 
	bool bWIDE;				//このデバイスは、太い境界線を描画できます。 
	bool bWIDESTYLED;		//このデバイスは、スタイル付きの太い境界線を描画できます。 
	bool bWINDPOLYGON;		//このデバイスは、全域モードでの多角形の塗りつぶしを行えます。
}GDCPOLYGONALCAPS, *PGDCPOLYGONALCAPS;

typedef struct tagTEXTCAPS{
	bool bOP_CHARACTER;		//このデバイスには、キャラクタの出力精度を調整する能力があります。 
	bool bOP_STROKE;		//このデバイスには、ストロークの出力精度を調整する能力があります。 
	bool bCP_STROKE;		//このデバイスには、ストローククリップの精度を調整する能力があります。 
	bool bCR_90;			//このデバイスには、キャラクタの 90 度回転を行う能力があります。 
	bool bCR_ANY;			//このデバイスには、キャラクタの任意の角度の回転を行う能力があります。 
	bool bSF_X_YINDEP;		//このデバイスは、x 方向と y 方向の独立したスケーリング（長体と平体）を行えます。 
	bool bSA_DOUBLE;		//このデバイスは、キャラクタの 2 倍のスケーリング（倍角）を行えます。 
	bool bSA_INTEGER;		//このデバイスは、キャラクタの整数倍のスケーリング（n 倍角）を行えます。 
	bool bSA_CONTIN;		//このデバイスは、キャラクタの任意の倍率のスケーリングを行えます。 
	bool bEA_DOUBLE;		//このデバイスは、2 倍の太さの文字（太字）を描画できます。 
	bool bIA_ABLE;			//このデバイスは、イタリック体を描画できます。 
	bool bUA_ABLE;			//このデバイスは、下線を描画できます。 
	bool bSO_ABLE;			//このデバイスは、取り消し線を描画できます。 
	bool bRA_ABLE;			//このデバイスは、ラスタフォントを描画できます。 
	bool bVA_ABLE;			//このデバイスは、ベクトルフォントを描画できます。 
	bool bRESERVED;			//予約済みです。
	bool bSCROLLBLT;		//このデバイスは、ビットブロック転送（ブリット）によるスクロールを行えません。このフラグが、予期とは逆のことを意味する可能性があることに注意してください。 
}GDCTEXTCAPS, *PGDCTEXTCAPS;

#if 0
typedef struct tagCOLORMGMTCAPS{
	bool bCMYK_COLOR;		//このデバイスは、CMYK（シアン、マゼンタ、イエロー、ブラック）のカラースペース（色空間）に基づく ICC（International Color Consortium）のカラープロファイルを受け入れます。 
	bool bDEVICE_ICM;		//このデバイスは、デバイスドライバまたはデバイスの側で ICM（イメージ色の管理）を実施できます。 
	bool bGAMMA_RAMP;		//このデバイスは、GetDeviceGammaRamp と SetDeviceGammaRamp の各関数をサポートしています。 
	bool bNONE;				//このデバイスは、ICM をサポートしていません。 
}GDCCOLORMGMTCAPS, *PGDCCOLORMGMTCAPS;
#endif

typedef struct tagDEVICEINFO{
	int					nDrvVersion;		//デバイスドライバのバージョン
	GDCTECHNOLOGY		gdcTech;			//デバイステクノロジ（タイプ）
	int					nHorzSize;			//ミリメートル（mm）単位の画面の物理的な幅
	int					nVertSize;			//ミリメートル（mm）単位の画面の物理的な高さ
	int					nHorzRes;			//ピクセル単位の画面の幅
	int					nVertRes;			//ピクセル単位（ラスタ行数）の画面の高さ
	int					nLogPixelsX;		//画面の水平方向での、論理インチ当たりのピクセル数
	int					nLogPixelsY;		//画面の垂直方向での、論理インチ当たりのピクセル数
	int					nBitsPixel;			//ピクセルあたりのカラービットの数
	int					nPlanes;			//カラープレーンの数
	int					nNumBrushes;		//デバイス固有のブラシの数
	int					nNumPens;			//デバイス固有のペンの数
	int					nNumFonts;			//デバイス固有のフォントの数
	int					nNumColors;			//デバイスのカラー深度
	int					nAspectX;			//線の描画に使うデバイスピクセルの相対的な幅
	int					nAspectY;			//線の描画に使うデバイスピクセルの相対的な高さ
	int					nAspectXY;			//線の描画に使うデバイスピクセルの対角線の幅
	int					nPDeviceSize;		//予約済み
	int					nClipCaps;			//デバイスのクリッピング能力を示すフラグ
	int					nSizePalette;		//システムパレット内のエントリ数
	int					nNumReserved;		//システムパレット内の予約エントリ数
	int					nColorRes;			//デバイスの実際の色深度
	int					nPhysicalWidth;		//ページの物理的な幅をデバイス単位で表します(印刷デバイス用)
	int					nPhysicalHeight;	//ページの物理的な高さをデバイス単位で表します(印刷デバイス用)
	int					nPhysicalOffsetX;	//物理的なページの左端から印刷可能領域の左端までの距離をデバイス単位で表します(印刷デバイス用)
	int					nPhysicalOffsetY;	//物理的なページの上端から印刷可能領域の上端までの距離をデバイス単位で表します(印刷デバイス用)
#if 1
	int					nVRefresh;			//の現在のリフレッシュレート（垂直同期周波数）を 1 秒当たりのサイクル数（Hz）で表します(ディスプレイデバイス用)
#endif	
	int					nScalingFactorX;	//プリンタの水平軸の倍率
	int					nScalingFactorY;	//プリンタの垂直軸の倍率
#if 1	
	int					nBltAlignment;		//平方向のアラインメント（整列単位）の優先値をピクセル単位で取得します
#endif
#if 0
	int					nShadeBlendCaps;	//デバイスのシェーディング（陰影）とブレンディング（混色）の能力を示す値です
#endif
	GDCRASTERCAPS		RasTerCaps;			//デバイスのラスタ能力を示します
	GDCCURVECAPS		CurVeCaps;			//デバイスの曲線描画能力を示します 
	GDCLINECAPS			LineCaps;			//デバイスの直線描画能力を示します
	GDCPOLYGONALCAPS	PolygonalCaps;		//デバイスの多角形描画能力を示します
	GDCTEXTCAPS			TextCaps;			//デバイスのテキスト表示能力を示します
#if 0
	GDCCOLORMGMTCAPS	ColorMGMTCaps;		//デバイスの色の管理（カラーマネジメント）能力を示します。
#endif
}DEVICEINFO, *PDEVICEINFO;

#ifdef __cplusplus
}
#endif

#endif