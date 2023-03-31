
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

	//更新编辑框的状态
	void UpdateEditConstrolStatus();

	//检查界面选项
	bool CheckInput(bool& isDirChecked, std::wstring& fileName, std::wstring& filePath, std::wstring& fileExt);

	//进行转换操作
	void OnBnClickedButton(bool isCheckMode);

	//自定义消息响应
	LRESULT OnConvertMessage(WPARAM wParam, LPARAM lParam);

	//获取显示消息
	std::wstring GetDisplayMsg(WPARAM wParam);

protected:
	//如果回调函数返回false，则终止执行
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

	//数据同步锁
	std::mutex m_mutex;

	//转换实现对象
	CharsetTools m_convertTools;
};
