#pragma once

#include <afx.h>
#include <cstring>

using namespace std;

typedef BYTE addrcode[6];

class MsgFrame_3762
{
private:
	BYTE* hexmsg;
//	BYTE LengthZone[2];
	BYTE CtrlZone;
	BYTE InfoZone[6];
	addrcode *AddrZone;
	BYTE AFNZone;
	BYTE FnZone[2];

	CString DataUnit;
	BYTE CS;
public:
	CString msg;

	int length;
	BOOL DIR;
	BOOL PRM;
	int transmethod;

	int relaylevel;
	BOOL module;
	BOOL routing;
	int channel;

	//for downstream
	int expectlength;
	BOOL speedtag;
	BOOL speed;
	int cscode;

	//for upstream
	BOOL conflict;
	BOOL addnode;
	int channelspec;
	int phase;
	int ackqly;
	int comqly;

	int AFn;
	int Fn;

public:
	MsgFrame_3762(CString date);
	void StringToHex();
	void Decode();

private:
	BYTE ConvHEXChar(BYTE ch);
};