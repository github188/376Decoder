#include "afx.h"
#include <sstream>
#include <string>
#include <regex>
#include "DateFrameDefine.h"

using namespace std;

void addrrev(addrcode* addr)
{
	BYTE temp;
	BYTE *t = (BYTE *)addr;
	BYTE *p = (BYTE *)addr + 5;

	temp = *t;
	*t++ = *p;
	*p-- = temp;

	temp = *t;
	*t++ = *p;
	*p-- = temp;

	temp = *t;
	*t++ = *p;
	*p-- = temp;
}

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
	int i,j;
	string msg_s = msg;
	regex ilegalchar("[^A-Fa-f0-9]+");
	string sparator = " ";
	msg_s = regex_replace(msg_s, ilegalchar, sparator);

	hexmsg = new BYTE[(MsgLen + 1) / 3];

	for(i = 0, j = 0; i < MsgLen; i++, j++)
	{
		if((msg[i] != ' ') && (msg[i + 1] != ' '))
		{
			hexmsg[j] = (ConvHEXChar(msg[i]) << 4) + (ConvHEXChar(msg[i+1]));
			i += 2;
		}
	}

}

void MsgFrame_3762::Decode()
{

	length = (hexmsg[2] << 8) + hexmsg[1];

	DIR = (0x80 & hexmsg[3]) >> 7;
	PRM = (0x40 & hexmsg[3]) >> 6;
	transmethod = 0x3F & hexmsg[3];

	relaylevel = (0xC0 & hexmsg[4]) >> 5;
	conflict = (0x08 & hexmsg[4]) >> 3;
	module = (0x04 & hexmsg[4]) >> 2;

	routing = 0x01 & hexmsg[4];
	channel = 0x0F & hexmsg[5];

	if(module)
	{
		AddrZone = new addrcode[relaylevel + 2];
		memcpy(AddrZone, hexmsg+10, (relaylevel + 2)*6);
		for(int i=0; i < relaylevel + 2; i++)
		{
			addrrev(AddrZone + i);
		}
	}

	
}