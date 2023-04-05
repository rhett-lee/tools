
// charset-convertDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "charset-convert.h"
#include "charset-convertDlg.h"
#include "base/StringUtils.h"

#include "afxdialogex.h"
#include <string>
#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CHARSET_AUTO		L"自动检测"
#define CHARSET_ANSI		L"ANSI"
#define CHARSET_UTF8		L"UTF-8"
#define CHARSET_UNICODE		L"Unicode"

//自定义消息，用于更新界面
#define WM_CONVERT_MSG		(WM_USER + 10)

typedef enum
{
	MSG_CONVERT_Begin = 1,
	MSG_CONVERT_Progress,
	MSG_CONVERT_End,
}TConvertMessageWParam;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcharsetconvertDlg dialog



CcharsetconvertDlg::CcharsetconvertDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHARSETCONVERT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcharsetconvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
}

BEGIN_MESSAGE_MAP(CcharsetconvertDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_DEST, &CcharsetconvertDlg::OnCbnSelchangeComboDest)
	ON_BN_CLICKED(IDC_BUTTON_SEL_DIR, &CcharsetconvertDlg::OnBnClickedButtonSelDir)
	ON_BN_CLICKED(IDC_BUTTON_SEL_FILE, &CcharsetconvertDlg::OnBnClickedButtonSelFile)
	ON_BN_CLICKED(IDC_RADIO_DIR, &CcharsetconvertDlg::OnBnClickedRadioDir)
	ON_BN_CLICKED(IDC_RADIO_FILE, &CcharsetconvertDlg::OnBnClickedRadioFile)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CcharsetconvertDlg::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_CONVERT, &CcharsetconvertDlg::OnBnClickedButtonConvert)

	ON_MESSAGE(WM_CONVERT_MSG, OnConvertMessage)
	
END_MESSAGE_MAP()


// CcharsetconvertDlg message handlers

BOOL CcharsetconvertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	CComboBox srcCharset;
	srcCharset.Attach(GetDlgItem(IDC_COMBO_SRC)->m_hWnd);
	srcCharset.AddString(CHARSET_AUTO);
	srcCharset.AddString(CHARSET_ANSI);
	srcCharset.AddString(CHARSET_UTF8);	
	srcCharset.AddString(CHARSET_UNICODE);
	srcCharset.SetCurSel(0);
	srcCharset.Detach();

	CComboBox destCharset;
	destCharset.Attach(GetDlgItem(IDC_COMBO_DEST)->m_hWnd);
	destCharset.AddString(CHARSET_ANSI);
	destCharset.AddString(CHARSET_UTF8);
	destCharset.AddString(CHARSET_UNICODE);
	destCharset.SetCurSel(0);
	destCharset.Detach();

	((CButton*)GetDlgItem(IDC_RADIO_FILE))->SetCheck(FALSE); //不选
	((CButton*)GetDlgItem(IDC_RADIO_DIR))->SetCheck(TRUE); //选上
	((CEdit*)GetDlgItem(IDC_EDIT_FILE_EXT))->SetWindowText(L"*.h;*.cpp");
	UpdateEditConstrolStatus();

	((CStatic*)GetDlgItem(IDC_STATIC_RESULT))->SetWindowText(L"");
	((CButton*)GetDlgItem(IDC_CHECK_BOM))->EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CcharsetconvertDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CcharsetconvertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CcharsetconvertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcharsetconvertDlg::UpdateEditConstrolStatus()
{
	BOOL isDirChecked = ((CButton*)GetDlgItem(IDC_RADIO_DIR))->GetCheck();
	
	((CEdit*)GetDlgItem(IDC_EDIT_FILE))->EnableWindow(!isDirChecked);
	((CEdit*)GetDlgItem(IDC_EDIT_DIR))->EnableWindow(isDirChecked);
	((CEdit*)GetDlgItem(IDC_EDIT_FILE_EXT))->EnableWindow(isDirChecked);

	((CButton*)GetDlgItem(IDC_BUTTON_SEL_FILE))->EnableWindow(!isDirChecked);
	((CButton*)GetDlgItem(IDC_BUTTON_SEL_DIR))->EnableWindow(isDirChecked);
}

void CcharsetconvertDlg::OnCbnSelchangeComboDest()
{
	CComboBox* destBox = ((CComboBox*)GetDlgItem(IDC_COMBO_DEST));
	int nSel = destBox->GetCurSel();
	bool isEnable = true;
	if (nSel ==0)
	{
		isEnable = 0;
	}
	((CButton*)GetDlgItem(IDC_CHECK_BOM))->EnableWindow(isEnable ? TRUE : FALSE);
}

void CcharsetconvertDlg::OnBnClickedButtonSelDir()
{
	TCHAR szFolderPath[MAX_PATH] = { 0 };
	BROWSEINFO sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = L"请选择一个文件夹：";
	sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn = NULL;
	// 显示文件夹选择对话框
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名
		if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			((CEdit*)GetDlgItem(IDC_EDIT_DIR))->SetWindowText(szFolderPath);
		}
	}
	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}
}

void CcharsetconvertDlg::OnBnClickedButtonSelFile()
{
	OPENFILENAME l = { sizeof(l), };
	TCHAR buf[MAX_PATH] = { 0 };
	l.hwndOwner = m_hWnd;
	l.lpstrFilter = _T("所有文件\0*.*\0\0");
	l.lpstrFile = buf;
	l.nMaxFile = MAX_PATH - 1;
	l.lpstrTitle = _T("选择文件");
	l.lpstrDefExt = NULL;
	l.lpstrInitialDir = NULL;
	l.Flags = OFN_HIDEREADONLY | OFN_EXPLORER | OFN_PATHMUSTEXIST;
	buf[0] = 0;
	if (GetOpenFileName(&l))
	{
		((CEdit*)GetDlgItem(IDC_EDIT_FILE))->SetWindowText(buf);
	}
}


void CcharsetconvertDlg::OnBnClickedRadioDir()
{
	UpdateEditConstrolStatus();
}


void CcharsetconvertDlg::OnBnClickedRadioFile()
{
	UpdateEditConstrolStatus();
}


void CcharsetconvertDlg::OnBnClickedButtonCheck()
{	
	OnBnClickedButton(true);
}

void CcharsetconvertDlg::OnBnClickedButtonConvert()
{
	OnBnClickedButton(false);
}

void CcharsetconvertDlg::OnBnClickedButton(bool isCheckMode)
{
	bool isDirChecked = true;
	std::wstring fileName;
	std::wstring filePath;
	std::wstring fileExt;
	if (!CheckInput(isDirChecked, fileName, filePath, fileExt))
	{
		return;
	}
	if (isDirChecked)
	{
		fileName.clear();
	}
	std::wstring srcFileCharset;
	std::wstring destFileCharset;
	bool destFileWriteBOM = false;

	CComboBox* srcBox = ((CComboBox*)GetDlgItem(IDC_COMBO_SRC));
	int nSel = srcBox->GetCurSel();
	if (nSel != -1)
	{
		TCHAR szText[MAX_PATH] = { 0 };
		srcBox->GetLBText(nSel, szText);
		srcFileCharset = szText;
	}

	CComboBox* destBox = ((CComboBox*)GetDlgItem(IDC_COMBO_DEST));
	nSel = destBox->GetCurSel();
	if (nSel != -1)
	{
		TCHAR szText[MAX_PATH] = { 0 };
		destBox->GetLBText(nSel, szText);
		destFileCharset = szText;
	}

	destFileWriteBOM = ((CButton*)GetDlgItem(IDC_CHECK_BOM))->GetCheck() != FALSE;

	RL::CharsetType srcCharset = RL::CharsetType::UNKNOWN;
	RL::CharsetType destCharset = RL::CharsetType::UNKNOWN;
	if (srcFileCharset == CHARSET_ANSI)
	{
		srcCharset = RL::CharsetType::ANSI;
	}
	else if(srcFileCharset == CHARSET_UTF8)
	{
		srcCharset = RL::CharsetType::UTF8;
	}
	else if (srcFileCharset == CHARSET_UNICODE)
	{
		srcCharset = RL::CharsetType::UTF16_LE;
	}

	if (destFileCharset == CHARSET_ANSI)
	{
		destCharset = RL::CharsetType::ANSI;
	}
	else if (destFileCharset == CHARSET_UTF8)
	{
		destCharset = RL::CharsetType::UTF8;
	}
	else if (destFileCharset == CHARSET_UNICODE)
	{
		destCharset = RL::CharsetType::UTF16_LE;
	}

	//开始转换
	TCharsetToolsParam convertParam;
	convertParam.isCheckMode = isCheckMode;
	convertParam.isDirChecked = isDirChecked;
	convertParam.fileName = fileName;
	convertParam.filePath = filePath;
	convertParam.fileExt = fileExt;

	convertParam.srcFileCharset = srcCharset;
	convertParam.destFileCharset = destCharset;
	convertParam.destFileWriteBOM = destFileWriteBOM;

	if (m_convertTools.StartConvert(convertParam, this))
	{
		((CButton*)GetDlgItem(IDC_BUTTON_CHECK))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BUTTON_CONVERT))->EnableWindow(FALSE);
	}
}

bool CcharsetconvertDlg::CheckInput(bool& isDirChecked, std::wstring& fileName, std::wstring& filePath, std::wstring& fileExt)
{
	isDirChecked = ((CButton*)GetDlgItem(IDC_RADIO_DIR))->GetCheck() != FALSE;

	TCHAR buffer[MAX_PATH] = {0};
	((CEdit*)GetDlgItem(IDC_EDIT_FILE))->GetWindowText(buffer, MAX_PATH - 1);
	fileName = buffer;

	((CEdit*)GetDlgItem(IDC_EDIT_DIR))->GetWindowText(buffer, MAX_PATH - 1);
	filePath = buffer;

	((CEdit*)GetDlgItem(IDC_EDIT_FILE_EXT))->GetWindowText(buffer, MAX_PATH - 1);
	fileExt = buffer;

	RL::StringUtils::Trim(fileName);
	RL::StringUtils::Trim(filePath);
	RL::StringUtils::Trim(fileExt);

	if (isDirChecked)
	{
		if (filePath.empty())
		{
			MessageBox(L"所在文件夹为空，请输入文件所在的文件夹！");
			return false;
		}
		if (fileExt.empty())
		{
			MessageBox(L"文件类型为空，请输入文件类型！");
			return false;
		}
	}
	else
	{
		if (fileName.empty())
		{
			MessageBox(L"单文件的路径为空，请输入单文件的路径！");
			return false;
		}
	}
	return true;
}

bool CcharsetconvertDlg::OnConvertBegin()
{
	if (!::IsWindow(m_hWnd))
	{
		return false;
	}
	std::lock_guard<std::mutex> lock(m_mutex);
	m_progressData.clear();

	PostMessage(WM_CONVERT_MSG, MSG_CONVERT_Begin, 0);
	return true;
}

bool CcharsetconvertDlg::OnConvertProgress(const TProgressData& progressData)
{
	if (!::IsWindow(m_hWnd))
	{
		return false;
	}
	std::lock_guard<std::mutex> lock(m_mutex);
	m_progressData.push_back(progressData);

	PostMessage(WM_CONVERT_MSG, MSG_CONVERT_Progress, 0);
	return true;
}

bool CcharsetconvertDlg::OnConvertEnd()
{
	if (!::IsWindow(m_hWnd))
	{
		return false;
	}
	std::lock_guard<std::mutex> lock(m_mutex);

	PostMessage(WM_CONVERT_MSG, MSG_CONVERT_End, 0);
	return true;
}

LRESULT CcharsetconvertDlg::OnConvertMessage(WPARAM wParam, LPARAM lParam)
{
	std::wstring msg = GetDisplayMsg(wParam);
	((CStatic*)GetDlgItem(IDC_STATIC_RESULT))->SetWindowText(msg.c_str());

	if (wParam == MSG_CONVERT_End)
	{
		m_convertTools.Terminate();
		((CButton*)GetDlgItem(IDC_BUTTON_CHECK))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BUTTON_CONVERT))->EnableWindow(TRUE);
	}
    return 0;
}

std::wstring CcharsetconvertDlg::GetDisplayMsg(WPARAM wParam)
{
	std::wstring dispalyMsg;
	switch (wParam)
	{
	case MSG_CONVERT_Begin:
	{
		dispalyMsg = L"操作开始 ...";
	}
	break;
	case MSG_CONVERT_Progress:
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (!m_progressData.empty() && (m_progressData.back().totalFiles > 0))
		{
			const TProgressData& data = m_progressData.back();
			if (data.isCheckMode)
			{
				dispalyMsg = L"正在检测 ... ，";
			}
			else
			{
				dispalyMsg = L"正在转换 ... ，";
			}
			std::wstring msg;
			RL::StringUtils::Format(msg, L"总体进度：%u%%（%u/%u）", (data.currentFileIndex + 1)*100/data.totalFiles, data.currentFileIndex + 1, data.totalFiles);
			dispalyMsg += msg;

			RL::StringUtils::Format(msg, L"当前文件：%s", data.fileName.c_str());
			dispalyMsg += L"\n";
			dispalyMsg += msg;

			RL::StringUtils::Format(msg, L"编码信息：%s", CharsetTools::GetCharsetMsg(data).c_str());
			dispalyMsg += L"\n";
			dispalyMsg += msg;

			std::wstring errMsg = CharsetTools::GetErrMsg(data);
			if (!errMsg.empty())
			{
				RL::StringUtils::Format(msg, L"错误信息：%s", errMsg.c_str());
				dispalyMsg += L"\n";
				dispalyMsg += msg;
			}
		}
	}
	break;
	case MSG_CONVERT_End:
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if (!m_progressData.empty() && (m_progressData.back().totalFiles > 0))
		{
			const TProgressData& data = m_progressData.back();
			if (data.isCheckMode)
			{
				dispalyMsg = L"检测结果：";
			}
			else
			{
				dispalyMsg = L"转换结果：";
			}

			uint32_t successCount = 0;
			for (const auto& progress : m_progressData)
			{
				if ((progress.result == 0) || (progress.result == 1))
				{
					++successCount;
				}
			}

			std::wstring msg;
			RL::StringUtils::Format(msg, L"总文件数：%u，成功文件数：%u，成功率：%u%%", data.totalFiles, successCount, successCount*100 / data.totalFiles);
			dispalyMsg += msg;

			std::map<std::wstring, int> charsetMap;
			for (const auto& progress : m_progressData)
			{
				std::wstring charsetMsg = CharsetTools::GetCharsetTypeMsg(progress.srcFileCharset);
				auto iter = charsetMap.find(charsetMsg);
				if (iter == charsetMap.end())
				{
					charsetMap[charsetMsg] = 1;
				}
				else
				{
					++iter->second;
				}
			}

			if (!charsetMap.empty())
			{
				dispalyMsg += L"\n源文件编码信息：";
			}			
			for (const auto& charsetIter : charsetMap)
			{
				RL::StringUtils::Format(msg, L"%s(%d) ", charsetIter.first.c_str(), charsetIter.second);
				dispalyMsg += msg;				
			}
		}
	}
	break;
	default:
		break;
	}
	return dispalyMsg;
}