
// OpenGLwithMFCDlg.h : ��� ����
//

#pragma once

// including OpenGL header
#include "GL\glew.h"
#include "GL\wglew.h"
//#include "freeglut.h"
//#include "freeglut_ext.h"
#include "afxwin.h"

// add to be used library
//#pragma comment(lib, "freeglut.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glew32.lib")

// COpenGLwithMFCDlg ��ȭ ����
class COpenGLwithMFCDlg : public CDialogEx
{
// �����Դϴ�.
public:
	COpenGLwithMFCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGLWITHMFC_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	// You will add the following stuff!!!

	virtual BOOL GetOldStyleRenderingContext(void);
	virtual BOOL SetupPixelFormat(void);


private:
	//OpenGL Setup
	BOOL GetRenderingContext();
	//Rendering Context and Device Context Pointers
	HGLRC     m_hRC;
	CDC*      m_pDC;

	//float angle;
	GLuint vao;
	void defineVAO(GLuint &vao, GLuint &shaderProgram);
	GLuint create_program();

public:
	// control variable about IDC_PICTURE, to draw OpenGL
	CStatic m_picture;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};
