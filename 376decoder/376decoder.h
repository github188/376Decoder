
// 376decoder.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy376decoderApp:
// �йش����ʵ�֣������ 376decoder.cpp
//

class CMy376decoderApp : public CWinApp
{
public:
	CMy376decoderApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy376decoderApp theApp;