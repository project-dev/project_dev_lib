// StringEndode.cpp: CStringEncode クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "StringEncode.h"
#include "ByteArrayOutputStream.h"
#include "StringBuffer.h"
#include "DebugSupport.h"

//JISのエスケープシーケンス（開始）
static char startEcs[] = { 0x1b, 0x24, 0x40};

//JISのエスケープシーケンス（終了）
static char endEcs[] = { 0x1b, 0x28, 0x4a};

static const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
 
//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

/**
 * @brief コンストラクタ
 */
CStringEncode::CStringEncode(){
	m_nType = NaN;
	m_pszBuff = 0;
}

/**
 * @brief デストラクタ
 */
CStringEncode::~CStringEncode(){

}

/**
 * @brief 文字コードのチェック
 * @param  pszBuff チェックする文字列
 * @return 文字コード(CStringEncode::eCode)
 */
int CStringEncode::CheckCode(char *pszBuff){
	m_pszBuff = pszBuff;
	if(!m_pszBuff){
		return NaN;
	}

	byte byte1;
	byte byte2;
	int nLen = strlen(m_pszBuff);

	for (int i = 0; i < nLen - 1; i++){

		byte1 = (byte)((byte)0xff & (byte)m_pszBuff[i]);
		byte2 = (byte)((byte)0xff & (byte)m_pszBuff[i+1]);

		if ((byte1 == 0x1B) && ((byte2 ==0x24) || (byte2 ==0x26))){
			m_nType = JIS;
			break;

		}else if (((byte1 == 0xFE) && (byte2 == 0xFF)) ||
				  ((byte1 == 0xFF) && (byte2 == 0xFE))){
			m_nType = UNICODE;
			break;

		}else if ((((byte1 >= 0xC0) && (byte1 <= 0xDF)) ||
				   ((byte1 >= 0xE0) && (byte1 <= 0xEF)) ||
				   ((byte1 >= 0xF0) && (byte1 <= 0xF7))) &&
				   ((byte2 >= 0x80) && (byte2 <= 0xBF))){
			m_nType = UTF8;
			break;

		}else if ((((byte1 >= 0x81) && (byte1 <= 0x9F)) ||
				   ((byte1 >= 0xE0) && (byte1 <= 0xEF))) &&
				  (((byte2 >= 0x40) && (byte2 <= 0x7E)) ||
				   ((byte2 >= 0x80) && (byte2 <= 0xFC)))){
			m_nType = SJIS;
			break;

		}else if (((byte1 >= 0xA1) && (byte1 <= 0xFE)) &&
				  ((byte2 >= 0xA1) && (byte2 <= 0xFE))){
			m_nType = EUC;
			break;
		}
	}

	return m_nType;
}

/**
 * @brief EUCをJISに変換<BR>
 * @param  eucchars 文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::euc2jis(char* eucchars){
	ByteArrayOutputStream baos;
	baos.open();
	char* chs = eucchars;
	bool escin = false;
	byte byte1,byte2;
	int i = 0;
	int nLen = strlen(chs);
	while((nLen - 1) > i){
		byte1 = (byte)(0xff & (byte)chs[i]);
		byte2 = (byte)(0xff & (byte)chs[i+1]);

		if (((byte1 >= 0xA1) && (byte1 <= 0xFE)) &&
			((byte2 >= 0xA1) && (byte2 <= 0xFE))){

			if (!escin){
				//開始のエスケープシーケンスを入れておく
				baos.write(startEcs);
				escin = true;
			}
			baos.write((byte)(0x7F & byte1));
			baos.write((byte)(0x7F & byte2));
			i++;
		}else{
			if(escin){
				//終了のエスケープシーケンスを入れておく
				baos.write(endEcs);
				escin = false;
			}
			baos.write(byte1);
		}
		i++;
	}
	char *b = baos.toByteArray();
	char *pszRet = new char[strlen(b) + 1];
	memset(pszRet, 0, strlen(b) + 1);
	strcpy(pszRet, b);
	baos.close();
	return pszRet;

}

/**
 * @brief EUCをShift-JISに変換<br>
 * @param eucchars 文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
*/
char* CStringEncode::euc2sjis(char* eucchars){
	char *pszBuff = euc2jis(eucchars);
	char *pszRet = jis2sjis(pszBuff);
	delete[] pszBuff;
	return pszRet;
}

//////////////////////// jis ///////////////////////////////////
/**
 * @brief JISをEUCに変換に変換
 * @param jischars 文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::jis2euc(char* jischars){
	ByteArrayOutputStream baos;
	baos.open();
	char* chs = jischars;
	int nLen = strlen(chs);
	int i = 0;
	int skip;

	while(nLen > i){
		skip = 0;
		//エスケープシーケンスを検索し削除せよ！
		if((chs[i] == 0x1b) && (chs[i+1] == 0x24) &&
		   ((chs[i+2] == 0x40) || (chs[i+2] == 0x42))){
			skip = 3;
		}else if((chs[i] == 0x1b) && (chs[i+1] == 0x24) &&
				 ((chs[i+2] == 0x28) && (chs[i+3] == 0x44))){
			skip = 4;
		}else if((chs[i] == 0x1b) && (chs[i+1] == 0x26) &&
				 (chs[i+2] == 0x40) && (chs[i+3] == 0x1b) &&
				 (chs[i+4] == 0x24) && (chs[i+5] == 0x42)){
			skip = 6;
		}

		if (skip > 0){
			i += skip;
			while(true){

				//リーダーバイトとトレーラーバイトのチェック
				if (((chs[i] >=0x21)   && (chs[i] <= 0x7e)) &&
					((chs[i+1] >=0x21) && (chs[i+1] <= 0x7e))){
						baos.write(0x80 | chs[i]);
						baos.write(0x80 | chs[i+1]);
					i+=2;
				}else if((chs[i] ==0x1b) && (chs[i+1] ==0x28) &&
					((chs[i+2] ==0x4a) || (chs[i+2] <=0x48) ||
					 (chs[i+2] ==0x42) || (chs[i+2] <=0x49))){

					 //終了のエスケープシーケンスがあった場合
					i += 2;
					break;

				}else{
					baos.write(chs[i]);
					break;
				}
			}
		}else{
			baos.write(chs[i]);
		}
		i++;
	}
	char *b = baos.toByteArray();
	char *pszRet = new char[strlen(b)];
	strcpy(pszRet, b);
	baos.close();
	return pszRet;
}

/**
 * @brief JISをShift-JISに変換します<br>
 * @param jischars 文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::jis2sjis(char* jischars){
	ByteArrayOutputStream baos;
	baos.open();
	char *chs = jischars;
	int i = 0;
	int nLen = strlen(chs);
	int skip;
	byte byte1,byte2;

	while((nLen-1) > i){
		skip = 0;
		//エスケープシーケンスを検索し削除せよ！
		if((chs[i] == 0x1b) && (chs[i+1] == 0x24) &&
		   ((chs[i+2] == 0x40) || (chs[i+2] == 0x42))){
			skip = 3;
		}else if((chs[i] == 0x1b) && (chs[i+1] == 0x24) &&
				 ((chs[i+2] == 0x28) && (chs[i+3] == 0x44))){
			skip = 4;
		}else if((chs[i] == 0x1b) && (chs[i+1] == 0x26) &&
				 (chs[i+2] == 0x40) && (chs[i+3] == 0x1b) &&
				 (chs[i+4] == 0x24) && (chs[i+5] == 0x42)){
			skip = 6;
		}

		if (skip > 0){
			i += skip;
			while(true){

				//リーダーバイトとトレーラーバイトのチェック
				if (((chs[i] >=0x21) && (chs[i] <= 0x7e)) &&
					((chs[i+1] >=0x21) && (chs[i+1] <= 0x7e))){

					byte1 = (byte)((byte)0xff & (byte)((chs[i] + 1) / 2));
					byte2 = (byte)((byte)0xff & (byte)chs[i+1]);

					//第１バイト
					if (chs[i] < 0x5f){
						byte1 += 0x70;
					}else{
						byte1 += 0xb0;
					}

					baos.write(byte1);

					//第２バイト
					if (!(chs[i] % 2 == 0)){
						//奇数の時
						byte2 = (byte)(0xff & (byte2 + 0x1f));
						if(byte2 > 0x00007e){
							byte2 ++;
						}
					}else{
						//偶数の時
						byte2 = (byte)(0xff & (byte2 + 0x7e));
					}
					baos.write(byte2);
					i+=2;

				}else if((chs[i] ==0x1b) && (chs[i+1] ==0x28) &&
					((chs[i+2] ==0x4a) || (chs[i+2] <=0x48) ||
					 (chs[i+2] ==0x42) || (chs[i+2] <=0x49))){

					 //終了のエスケープシーケンスがあった場合
					i += 2;
					break;

				}else{
					baos.write(chs[i]);
					break;
				}
			}
		}else{
			baos.write(chs[i]);
		}
		i++;
	}
	char *b = baos.toByteArray();
	char *pszRet = new char[strlen(b) + 1];
	memset(pszRet, 0, strlen(b) + 1);
	strcpy(pszRet, b);
	baos.close();
	return pszRet;
}

//////////////////////// sjis ///////////////////////////////////
// 
/**
 * @brief Shift-JISをJISに変換します<br>
 * @param sjischars 文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::sjis2jis(char* sjischars){
	ByteArrayOutputStream baos;
	baos.open();
	char* chs = sjischars;
	int nLen = strlen(chs);
	byte byte1,byte2;
	bool escin = false;
	int i = 0;

	while((nLen-1) > i){
		byte1 = (byte)((byte)0xff & (byte)chs[i]);
		byte2 = (byte)((byte)0xff & (byte)chs[i+1]);

		if ((((byte1 >= 0x81) && (byte1 <= 0x9F)) ||
			 ((byte1 >= 0xE0) && (byte1 <= 0xEF))) &&
			((byte2 >= 0x40) && (byte2 <= 0xFC))){

			if (!escin){
				//開始のエスケープシーケンスを入れておく
				baos.write(startEcs);
				escin = true;
			}

			//変換作業
			if(byte1 <= 0x9f){
				byte1 -= 0x71;
			}else{
				byte1 -= 0xb1;
			}
			byte1 = (byte)((byte1 << 1) + 1);

			if(byte2 > 0x7f){
				byte2--;
			}
			if (byte2 >= 0x9e){
				byte2 -= 0x7d;
				byte1 ++;
			}else{
				byte2 -= 0x1f;
			}
			baos.write(byte1);
			baos.write(byte2);
			i++;
		}else{
			if(escin){
				//終了のエスケープシーケンスを入れておく
				baos.write(endEcs);
				escin = false;
			}
			baos.write(chs[i]);
		}
		i++;
	}
	char *b = baos.toByteArray();
	char *pszRet = new char[strlen(b) + 1];
	memset(pszRet, 0, strlen(b) + 1);
	strcpy(pszRet, b);
	baos.close();
	return pszRet;
}

/**
 * @brief Shift-JISをEUCに変換します
 * @param sjischars 文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::sjis2euc(char* sjischars){
	char *pszBuff = sjis2jis(sjischars);
	char *pszRet = jis2euc(pszBuff);
	delete[] pszBuff;
	return pszRet;
}

/**
 * @brief xx2yyで取得したバッファの解放
 * @param pszBuff 文字列
 * @return なし
 */
void CStringEncode::ReleaseBuff(char *pszBuff){
	delete[] pszBuff;
}

/**
 * @brief JISに変換します
 * @param なし
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::toJIS(){
	switch(m_nType){
	case JIS:
		return m_pszBuff;
	case SJIS:
		return sjis2jis(m_pszBuff);
	case EUC:
		return euc2jis(m_pszBuff);
	case UTF8:
//		return utf2jis(m_pszBuff);
	case UNICODE:
	case NaN:
	default:
		return NULL;
	}
}

/**
 * @brief SJISに変換します
 * @param なし
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::toSJIS(){
	switch(m_nType){
	case JIS:
		return jis2sjis(m_pszBuff);
	case SJIS:
		return m_pszBuff;
	case EUC:
		return euc2sjis(m_pszBuff);
	case UTF8:
		return utf82sjis(m_pszBuff);
	case UNICODE:
	case NaN:
	default:
		return NULL;
	}
}

/**
 * @brief EUCに変換します
 * @param なし
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::toEUC(){
	switch(m_nType){
	case JIS:
		return jis2euc(m_pszBuff);
	case SJIS:
		return sjis2euc(m_pszBuff);
	case EUC:
		return m_pszBuff;
	case UTF8:
//		return utf82sjis(m_pszBuff);
	case UNICODE:
	case NaN:
	default:
		return NULL;
	}
}

/**
 * @brief UTF-8に変換します
 * @param なし
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::toUTF8(){
	switch(m_nType){
	case JIS:
//		return jis2euc(m_pszBuff);
		return NULL;
	case SJIS:
		return sjis2utf8(m_pszBuff);
	case EUC:
//		return m_pszBuff;
		return NULL;
	case UTF8:
//		return utf82sjis(m_pszBuff);
	case UNICODE:
	case NaN:
	default:
		return NULL;
	}
}



/**
 * @brief URL文字列に変換します
 *
 * 現在のバイト配列をURL(%の付いたあれね)にエンコードします。<BR>
 * エンコードできない場合はnullを返します。<BR>
 * 半角スペースは "+" に変換します。<BR>
 * '半角英数字 [A-Za-z0-9] および *-.@_ の記号は変換しません。
 * @param なし
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::toURL(){
	StringBuffer code;
	int nLen = strlen(m_pszBuff);
	for (int i = 0; i < nLen; i++){
		int codeInt = 0xff & m_pszBuff[i];
		if (((codeInt >= 0x30) && (codeInt <= 0x39)) ||
			((codeInt >= 0x40) && (codeInt <= 0x5a)) ||
			((codeInt >= 0x61) && (codeInt <= 0x7a)) ||
			 (codeInt == 0x2a) || (codeInt == 0x2d) ||
			 (codeInt == 0x2e) || (codeInt == 0x5f)){
			code.append((char)codeInt);
		}else if (codeInt == 0x20){
			code.append("+");
		}else{
			code.append("%");
			char hex[MAXTEXT];
			itoa(codeInt, hex, 10);
			
			if (strlen(hex) == 1){
				code.append("0");
			}
			code.append(hex);
		}
	}

	//エンコードした物を出力
	return code.toByte();
}

/**
 * @brief URL文字をデコードします
 * @param chars URL文字にエンコードされた文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::decodeURL(char* chars){
	ByteArrayOutputStream baos;
	baos.open();
	StringBuffer sb;
	bool key = false;
	int nLen = strlen(chars);

	for (int i = 0; i < nLen; i++){
		int codeInt = 0xff & chars[i];
		if(codeInt != '%'){
			if(codeInt == '+'){
				baos.write(' ');
			}else if((((codeInt >= 0x30) && (codeInt <= 0x39)) ||
					 ((codeInt >= 0x40) && (codeInt <= 0x5a)) ||
					 ((codeInt >= 0x61) && (codeInt <= 0x7a)) ||
					 (codeInt == 0x2a) || (codeInt == 0x2d) ||
					 (codeInt == 0x2e) || (codeInt == 0x5f)) &&
					 (!key)){
				char szValue[MAXTEXT];
				itoa(codeInt, szValue, 10);
				baos.write(szValue);
			}else{
				sb.append((char)codeInt);
				if (sb.length() == 2){
					int nVal = atoi(sb.toByte());
					char szHex[MAXTEXT];
					itoa(nVal, szHex, 16);
					baos.write(szHex);
					sb.Empty();
					key = false;
				}
			}
		}else{
			key = true;
		}
	}
	char *b = baos.toByteArray();
	char *pszRet = new char[strlen(b) + 1];
	memset(pszRet, 0, strlen(b) + 1);
	strcpy(pszRet, b);
	baos.close();
	return pszRet;
}

/**
 * @brief BASE64にエンコード
 * @param chars エンコードされた文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::toBASE64(){
	ByteArrayOutputStream baos;
	baos.open();
	int i = 0;
	char bit6[5];
	int b1,b2;
	int code1,code2;
	int pos;
	//char *retbyte;
	// 12345678 12345678 12345678
	// 00000000 00000000 00000000
	//      ↓以下のように↓
	// 123456 123456 123456 123456
	// 000000 000000 000000 000000
	int nLen = 0;
	while(true){

		//テーブル初期化
		memset(bit6, 0, 5);
		nLen = strlen(m_pszBuff);
		if (nLen > i){
			code1 = 0xff & m_pszBuff[i];
			// aabbccdd -> 00aabbcc
			pos = code1 >> 2;
			//System.out.print(pos + "/");
			bit6[0] = getBasebyte(pos);
		}else{
			bit6[0] = '=';
			break;
		}

		nLen = strlen(m_pszBuff);
		if (nLen > (i+1)){
			code2 = 0xff & m_pszBuff[i+1];
			// aabbccdd -> dd000000
			b1 = code1 <<6;

			// aabbccdd -> 00dd0000
			b1 = b1 >> 2;

			// aabbccdd -> 0000aabb
			b2 = code2 >> 4;

			pos = 0x3f & (b1 | b2);
			bit6[1] = getBasebyte(pos);
		}else{
			bit6[1] = '=';
			baos.write(bit6);
			break;
		}

		nLen = strlen(m_pszBuff);
		if (nLen > (i+2)){
			code1 = 0xff & m_pszBuff[i+1];
			code2 = 0xff & m_pszBuff[i+2];

			// aabbccdd -> ccdd0000
			b1 = 0xff & (code1 << 4);

			// ccdd0000 -> 00ccdd00
			b1 = b1 >> 2;

			// aabbccdd -> 000000aa
			b2 = code2 >> 6;

			pos = b1 + b2;
			bit6[2] = getBasebyte(pos);
		}else{
			bit6[2] = '=';
			baos.write(bit6);
			break;
		}

		nLen = strlen(m_pszBuff);
		if (nLen > (i+2)){
			pos = 0x3f & code2;
			bit6[3] = getBasebyte(pos);

		}else{
			bit6[3] = '=';
			baos.write(bit6);
			break;
		}

		baos.write(bit6);
		i += 3;
		if ((i % 60) == 0){
			baos.write('\n');
		}
	}
	char *b = baos.toByteArray();
	char *pszRet = new char[strlen(b) + 1];
	memset(pszRet, 0, strlen(b) + 1);
	strcpy(pszRet, b);
	baos.close();
	return pszRet;
}

/**
 * @brief BASE64形式の文字列をデコード
 *
 * 問題があるときはnullを返します。現在、最後にゴミが入ります。
 * @param base64s エンコードされた文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::decodeBASE64(const char* base64s){
	ByteArrayOutputStream baos;
	baos.open();
	char bit8[3];
	int bit6[4];
	int b1,b2;
	int i = 0;
	int nBaseLen = strlen(base64s);

	while(true){
		//テーブル初期化
		int nLen = strlen(bit8);
		for(int j = 0; j < nLen; j++){
			bit8[j] = 0x00;
		}

		//改行チェック
		nLen = sizeof(bit6);
		for(int j = 0; j < nLen; j++){
			if ((i+j) < nBaseLen){
				if (base64s[i+j] != '\n'){
					bit6[j] = strcspn(&base[0], &base64s[i+j]);
					//bit6[j] = base.indexOf((char)base64s[i+j]);
				}else{
					i++;
					if ((i+j) < nBaseLen){
						bit6[j] = strcspn(&base[0], &base64s[i+j]);
						//bit6[j] = base.indexOf((char)base64s[i+j]);
					}else{
						bit6[j] = -1;
					}
				}
			}else{
				bit6[j] = -1;
			}
		}

		if(i < nBaseLen){
			// 00aabbcc 00ddeeff -> aabbccdd
			if ((bit6[0] != 65) || (bit6[0] != -1)){
				b1 = bit6[0] << 2;
				if ((bit6[1] != 65) || (bit6[1] != -1)){
					b2 = bit6[1] >> 4;
				}else{
					b2 = 0;
				}
				bit8[0] = (char)(b1 + b2);
			}else{
				break;
			}
		}else{
			break;
		}

		if((i+1) < nBaseLen){
			// 00ddeeff 00gghhii -> eeffgghh
			if ((bit6[1] != 65) || (bit6[1] != -1)){
				b1 = bit6[1] << 4;
				if ((bit6[2] != 65) || (bit6[2] != -1)){
					b2 = bit6[2] >> 2;
				}else{
					b2 = 0;
				}
				bit8[1] = (char)(b1 + b2);
			}else{
				baos.write(bit8);
				break;
			}
		}else{
			baos.write(bit8);
			break;
		}

		if((i+2) < nBaseLen){
			// 00gghhii 00jjkkll -> iijjkkll
			if ((bit6[2] != 65) || (bit6[2] != -1)){
				b1 = bit6[2] << 6;
				if ((bit6[3] != 65) || (bit6[3] != -1)){
					bit8[2] = (char)(b1 + bit6[3]);
				}else{
					bit8[2] = (char)(b1);
				}
			}else{
				baos.write(bit8);
				break;
			}
		}else{
			baos.write(bit8);
			break;
		}
	
		baos.write(bit8);
		i += 4;
	}
	char *b = baos.toByteArray();
	char *pszRet = new char[strlen(b) + 1];
	memset(pszRet, 0, strlen(b) + 1);
	strcpy(pszRet, b);
	baos.close();
	return pszRet;
}

/**
 * @brief 変換テーブル内に一致する場所を取得
 *
 * 問題があるときはnullを返します。現在、最後にゴミが入ります。
 * @param pos 位置
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
*/
char CStringEncode::getBasebyte(int pos){
	//return (char)(base.substring(pos, pos+1).charAt(0));
	return base[pos];
}

/**
 * @brief UTF-8をSJISに変換します
 * @param utfchars 文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */
char* CStringEncode::utf82sjis(char *utfchars){
	//Unicodeに変更
	char szDebgMsg[1024];
	CDebugSupport::OutputDebugLog("utf82sjis Step1\n");
	int nSize = ::MultiByteToWideChar(CP_UTF8,
									  0,
									  utfchars,
									  -1,
									  NULL,
									  0);
	if(nSize == 0){
		DWORD dwErr = GetLastError();
		char szMsg[1024];
		switch(dwErr){
		case ERROR_INSUFFICIENT_BUFFER:
			CDebugSupport::OutputDebugLog("ERROR_INSUFFICIENT_BUFFER\n");
			break;
		case ERROR_INVALID_FLAGS:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_FLAGS\n");
			break;
		case ERROR_INVALID_PARAMETER:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_PARAMETER\n");
			break;
		case ERROR_NO_UNICODE_TRANSLATION:
			CDebugSupport::OutputDebugLog("ERROR_NO_UNICODE_TRANSLATION\n");
			break;
		default:
			sprintf(szMsg, "%s\n", CDebugSupport::GetLastErrorText(dwErr));
			CDebugSupport::OutputDebugLog(szMsg);
			break;
		}
		return 0;
	}

	sprintf(szDebgMsg, "utf82sjis Step2\nbuff size %d\n", nSize);
	CDebugSupport::OutputDebugLog(szDebgMsg);
	wchar_t  *pszWBuff = new wchar_t [nSize+1];
	memset(pszWBuff, 0, nSize);
	nSize = ::MultiByteToWideChar(CP_UTF8,
								  0,
								  utfchars,
								  -1,
								  pszWBuff,
								  nSize);
	if((int)wcslen(pszWBuff) < nSize){
		CDebugSupport::OutputDebugLog("サイズオーバー\n");
	}
	if(nSize == 0){
		delete[] pszWBuff;
		DWORD dwErr = GetLastError();
		char szMsg[1024];
		switch(dwErr){
		case ERROR_INSUFFICIENT_BUFFER:
			CDebugSupport::OutputDebugLog("ERROR_INSUFFICIENT_BUFFER\n");
			break;
		case ERROR_INVALID_FLAGS:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_FLAGS\n");
			break;
		case ERROR_INVALID_PARAMETER:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_PARAMETER\n");
			break;
		case ERROR_NO_UNICODE_TRANSLATION:
			CDebugSupport::OutputDebugLog("ERROR_NO_UNICODE_TRANSLATION\n");
			break;
		default:
			sprintf(szMsg, "%s\n", CDebugSupport::GetLastErrorText(dwErr));
			CDebugSupport::OutputDebugLog(szMsg);
			break;
		}

		return 0;
	}


	//UnicodeからShift-JISへ
	CDebugSupport::OutputDebugLog("utf82sjis Step3\n");
	nSize = ::WideCharToMultiByte(CP_ACP,
								  0,
								  pszWBuff,
								  -1,
								  NULL,
								  0,
								  NULL,
								  NULL);
	if(nSize == 0){
		delete[] pszWBuff;
		DWORD dwErr = GetLastError();
		char szMsg[1024];
		switch(dwErr){
		case ERROR_INSUFFICIENT_BUFFER:
			CDebugSupport::OutputDebugLog("ERROR_INSUFFICIENT_BUFFER\n");
			break;
		case ERROR_INVALID_FLAGS:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_FLAGS\n");
			break;
		case ERROR_INVALID_PARAMETER:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_PARAMETER\n");
			break;
		default:
			sprintf(szMsg, "%s\n", CDebugSupport::GetLastErrorText(dwErr));
			CDebugSupport::OutputDebugLog(szMsg);
			break;
		}
		return 0;
	}

	sprintf(szDebgMsg, "utf82sjis Step4\nbuff size %d\n", nSize);
	CDebugSupport::OutputDebugLog(szDebgMsg);
	char *pszMBuff = new char[nSize+1];
	memset(pszMBuff, 0, nSize);
	
	nSize = ::WideCharToMultiByte(CP_ACP,
								  0,
								  pszWBuff,
								  -1,
								  pszMBuff,
								  nSize,
								  NULL,
								  NULL);
	if((int)strlen(pszMBuff) < nSize){
		CDebugSupport::OutputDebugLog("サイズオーバー\n");
	}
	if(nSize == 0){
		delete[] pszWBuff;
		delete[] pszMBuff;
		DWORD dwErr = GetLastError();
		char szMsg[1024];
		switch(dwErr){
		case ERROR_INSUFFICIENT_BUFFER:
			CDebugSupport::OutputDebugLog("ERROR_INSUFFICIENT_BUFFER\n");
			break;
		case ERROR_INVALID_FLAGS:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_FLAGS\n");
			break;
		case ERROR_INVALID_PARAMETER:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_PARAMETER\n");
			break;
		default:
			sprintf(szMsg, "%s\n", CDebugSupport::GetLastErrorText(dwErr));
			CDebugSupport::OutputDebugLog(szMsg);
			break;
		}
		return 0;
	}
	delete[] pszWBuff;
	return pszMBuff;
}

/**
 * @brief SJISをUTF-8に変換します
 * @param sjischars 文字列
 * @return 変換後の文字列
 * @attention 不要になったら戻り値で返ってきたポインタをCStringEncode::ReleaseBuff関数で破棄する必要がある
 * @see CStringEncode::ReleaseBuff(char *pszBuff)
 */          
char* CStringEncode::sjis2utf8(char *sjischars){
	//Unicodeに変更
	char szDebgMsg[1024];
	CDebugSupport::OutputDebugLog("sjis2utf8 Step1\n");
	int nSize = ::MultiByteToWideChar(CP_ACP,
									  0,
									  sjischars,
									  -1,
									  NULL,
									  0);
	if(nSize == 0){
		DWORD dwErr = GetLastError();
		char szMsg[1024];
		switch(dwErr){
		case ERROR_INSUFFICIENT_BUFFER:
			CDebugSupport::OutputDebugLog("ERROR_INSUFFICIENT_BUFFER\n");
			break;
		case ERROR_INVALID_FLAGS:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_FLAGS\n");
			break;
		case ERROR_INVALID_PARAMETER:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_PARAMETER\n");
			break;
		case ERROR_NO_UNICODE_TRANSLATION:
			CDebugSupport::OutputDebugLog("ERROR_NO_UNICODE_TRANSLATION\n");
			break;
		default:
			sprintf(szMsg, "%s\n", CDebugSupport::GetLastErrorText(dwErr));
			CDebugSupport::OutputDebugLog(szMsg);
			break;
		}
		return 0;
	}

	sprintf(szDebgMsg, "sjis2utf8 Step2\nbuff size %d\n", nSize);
	CDebugSupport::OutputDebugLog(szDebgMsg);
	wchar_t  *pszWBuff = new wchar_t [nSize+1];
	memset(pszWBuff, 0, nSize);
	nSize = ::MultiByteToWideChar(CP_ACP,
								  0,
								  sjischars,
								  -1,
								  pszWBuff,
								  nSize);
	if(nSize == 0){
		delete[] pszWBuff;
		DWORD dwErr = GetLastError();
		char szMsg[1024];
		switch(dwErr){
		case ERROR_INSUFFICIENT_BUFFER:
			CDebugSupport::OutputDebugLog("ERROR_INSUFFICIENT_BUFFER\n");
			break;
		case ERROR_INVALID_FLAGS:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_FLAGS\n");
			break;
		case ERROR_INVALID_PARAMETER:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_PARAMETER\n");
			break;
		case ERROR_NO_UNICODE_TRANSLATION:
			CDebugSupport::OutputDebugLog("ERROR_NO_UNICODE_TRANSLATION\n");
			break;
		default:
			sprintf(szMsg, "%s\n", CDebugSupport::GetLastErrorText(dwErr));
			CDebugSupport::OutputDebugLog(szMsg);
			break;
		}

		return 0;
	}


	//UnicodeからUTF-8へ
	CDebugSupport::OutputDebugLog("sjis2utf8 Step3\n");
	nSize = ::WideCharToMultiByte(CP_UTF8,
								  0,
								  pszWBuff,
								  -1,
								  NULL,
								  0,
								  NULL,
								  NULL);
	if(nSize == 0){
		delete[] pszWBuff;
		DWORD dwErr = GetLastError();
		char szMsg[1024];
		switch(dwErr){
		case ERROR_INSUFFICIENT_BUFFER:
			CDebugSupport::OutputDebugLog("ERROR_INSUFFICIENT_BUFFER\n");
			break;
		case ERROR_INVALID_FLAGS:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_FLAGS\n");
			break;
		case ERROR_INVALID_PARAMETER:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_PARAMETER\n");
			break;
		default:
			sprintf(szMsg, "%s\n", CDebugSupport::GetLastErrorText(dwErr));
			CDebugSupport::OutputDebugLog(szMsg);
			break;
		}
		return 0;
	}

	sprintf(szDebgMsg, "sjis2utf8 Step4\nbuff size %d\n", nSize);
	CDebugSupport::OutputDebugLog(szDebgMsg);
	char *pszMBuff = new char[nSize+1];					
	memset(pszMBuff, 0, nSize);
	nSize = ::WideCharToMultiByte(CP_UTF8,
								  0,
								  pszWBuff,
								  -1,
								  pszMBuff,
								  nSize,
								  NULL,
								  NULL);
	if(nSize == 0){
		delete[] pszWBuff;
		delete[] pszMBuff;
		DWORD dwErr = GetLastError();
		char szMsg[1024];
		switch(dwErr){
		case ERROR_INSUFFICIENT_BUFFER:
			CDebugSupport::OutputDebugLog("ERROR_INSUFFICIENT_BUFFER\n");
			break;
		case ERROR_INVALID_FLAGS:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_FLAGS\n");
			break;
		case ERROR_INVALID_PARAMETER:
			CDebugSupport::OutputDebugLog("ERROR_INVALID_PARAMETER\n");
			break;
		default:
			sprintf(szMsg, "%s\n", CDebugSupport::GetLastErrorText(dwErr));
			CDebugSupport::OutputDebugLog(szMsg);
			break;
		}
		return 0;
	}
	delete[] pszWBuff;
	return pszMBuff;

}
