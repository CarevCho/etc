
// MFC_timer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_timerApp:
// �� Ŭ������ ������ ���ؼ��� MFC_timer.cpp�� �����Ͻʽÿ�.
//

class CMFC_timerApp : public CWinApp
{
public:
	CMFC_timerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_timerApp theApp;
