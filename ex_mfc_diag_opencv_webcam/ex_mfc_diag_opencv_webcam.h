
// ex_mfc_diag_opencv_webcam.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// Cex_mfc_diag_opencv_webcamApp:
// �� Ŭ������ ������ ���ؼ��� ex_mfc_diag_opencv_webcam.cpp�� �����Ͻʽÿ�.
//

class Cex_mfc_diag_opencv_webcamApp : public CWinApp
{
public:
	Cex_mfc_diag_opencv_webcamApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern Cex_mfc_diag_opencv_webcamApp theApp;