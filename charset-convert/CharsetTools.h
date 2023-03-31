#pragma once

#include "base/RLCharsetString.h"
#include <string>
#include <thread>

struct TCharsetToolsParam
{
	bool isDirChecked = true;
	std::wstring fileName;
	std::wstring filePath;
	std::wstring fileExt;

	RL::RLCharsetType srcFileCharset = RL::RLCharsetType::UNKNOWN;
	RL::RLCharsetType destFileCharset = RL::RLCharsetType::UNKNOWN;
	bool destFileWriteBOM = false;
};

//进度相关数据
struct TProgressData
{
	//是否为检测模式：true为检测模式，false为转换模式
	bool isCheckedMode = true;
	//文件总数
	uint32_t totalFiles = 0;
	//当前文件索引值，从0开始
	uint32_t currentFileIndex = 0;
	//当前文件路径
	const std::wstring fileName;
	//当前文件编码
	RL::RLCharsetType srcFileCharset = RL::RLCharsetType::UNKNOWN;
	//目标文件编码
	RL::RLCharsetType destFileCharset = RL::RLCharsetType::UNKNOWN;
	//操作结果: 0 转换模式：转换成功，
	//         1 检测模式：成功，无操作
	//         10 源文件编码检测失败
	//         11 源文件读取失败
	//         12 目标文件写入失败
	uint32_t result = 0;
};

class CharsetToolsCallback
{
public:
	//如果回调函数返回false，则终止执行
	virtual bool OnConvertBegin() = 0;
	virtual bool OnConvertProgress(const TProgressData& progressData) = 0;
	virtual bool OnConvertEnd() = 0;
};

class CharsetTools
{
public:
	CharsetTools();

public:
	//开始转换
	bool StartConvert(const TCharsetToolsParam& convertParam, CharsetToolsCallback* callback);

	//结束并清理资源
	void Terminate();

public:
	//获取错误信息
	static std::wstring GetErrMsg(const TProgressData& progressData);

	//获取文件编码信息
	static std::wstring GetCharsetMsg(const TProgressData& progressData);

	//获取编码显示信息
	static std::wstring GetCharsetTypeMsg(RL::RLCharsetType charsetType);

private:
	void RunConvertThread();

private:
	TCharsetToolsParam m_convertParam;
	CharsetToolsCallback* m_callback;
	std::thread m_convertThread;
};

