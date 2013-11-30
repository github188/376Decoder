#include <iostream>
#include "DateFrameDefine.h"
using namespace std;

int main()
{
	MsgFrame_3762 test = "68.2D.00.4A.04.00..00 00 00 00 43 60 05 02 64 00 11 68 61 02 00 00 02 01 00 02 10 68 11 68 61 02 00 00 68 11 04 33 32 34 33 8D 16 7D 16";
	test.StringToHex();
	test.Decode();
	return(0);
}