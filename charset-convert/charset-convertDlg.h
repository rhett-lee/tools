
// charset-convertDlg.h : header file
//

#pragma once

#include "CharsetTools.h"
#include <string>
#include <vector>
#include <mutex>

// CcharsetconvertDlg dialog
class CcharsetconvertDlg : 
	public CDialogEx,
	public CharsetToolsCallback
{
// Construction
public:
	CcharsetconvertDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHARSETCONVERT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	//���±༭���״̬
	void UpdateEditConstrolStatus();

	//������ѡ��
	bool CheckInput(bool& isDirChecked, std::wstring& fileName, std::wstring& filePath, std::wstring& fileExt);

	//����ת������
	void OnBnClickedButton(bool isCheckMode);

	//�Զ�����Ϣ��Ӧ
	LRESULT OnConvertMessage(WPARAM wParam, LPARAM lParam);

	//��ȡ��ʾ��Ϣ
	std::wstring GetDisplayMsg(WPARAM wParam);

protected:
	//����ص���������false������ִֹ��
	virtual bool OnConvertBegin();
	virtual bool OnConvertProgress(const TProgressData& progressData);
	virtual bool OnConvertEnd();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCbnSelchangeComboDest();
	afx_msg void OnBnClickedButtonSelDir();
	afx_msg void OnBnClickedButtonSelFile();
	afx_msg void OnBnClickedRadioDir();
	afx_msg void OnBnClickedRadioFile();
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonConvert();

private:

	std::vector<TProgressData> m_progressData;

	//����ͬ����
	std::mutex m_mutex;

	//ת��ʵ�ֶ���
	CharsetTools m_convertTools;
};
