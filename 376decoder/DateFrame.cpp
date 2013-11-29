#include "stdafx.h"
#include "string.h"
#include "DateFrameDefine.h"

using namespace std;

MsgFrame_3762::MsgFrame_3762(CString data)
{
	msg = data;
}

BYTE MsgFrame_3762::ConvHEXChar(BYTE ch)
{
	if((ch >= '0') && (ch <= '9'))
		return ch - '0';
	else if(( ch>= 'a' ) && (ch <= 'f'))
		return ch - 'a' + 10;
	else if((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else
		return -1;
}

void MsgFrame_3762::StringToHex()
{
	int MsgLen = msg.GetLength();
	hexmsg = new BYTE[MsgLen];
	for(int i = 0, j = 0; i < MsgLen, j < MsgLen; i++, j++)
	{
		if((msg[i] != ' ') && (msg[i+1] != ' '))
		{
			hexmsg[j] = (ConvHEXChar(msg[i]) << 4) + (ConvHEXChar(msg[i+1]));
			i += 3;
			j++;
		}
	}
}
void MsgFrame_3762::Decode()
{

	length = (hexmsg[2] << 8) + hexmsg[1];

	DIR = 0x80 & hexmsg[3];
	PRM = 0x40 & hexmsg[3];
	transmethod = 0x3F & hexmsg[3];

	relaylevel = (0xC0 & hexmsg[4]) >> 5;
	conflict = 0x08 & hexmsg[4];
	module = 0x04 & hexmsg[4];

	routing = 0x01 & hexmsg[4];
	channel = 0x0F & hexmsg[5];

	if(module)
	{
		AddrZone = new addrcode[relaylevel + 2];
		for(int i=0; i < (relaylevel + 2); i++)
		{
			AddrZone[i] = hexmsg + (i * 6) + 10;
			strrev(AddrZone[i]);
		}
	}

	
}