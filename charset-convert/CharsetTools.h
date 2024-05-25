#pragma once

#include "base/StringCharset.h"
#include <string>
#include <thread>

struct TCharsetToolsParam
{
    bool isCheckMode = true; //检测模式，不进行实际转换
    bool isDirChecked = true;
    std::wstring fileName;
    std::wstring filePath;
    std::wstring fileExt;

    RL::CharsetType srcFileCharset = RL::CharsetType::UNKNOWN;
    RL::CharsetType destFileCharset = RL::CharsetType::UNKNOWN;
    bool destFileWriteBOM = false;
};

//进度相关数据
struct TProgressData
{
    //是否为检测模式：true为检测模式，false为转换模式
    bool isCheckMode = true;
    //文件总数
    uint32_t totalFiles = 0;
    //当前文件索引值，从0开始
    uint32_t currentFileIndex = 0;
    //当前文件路径
    std::wstring fileName;
    //当前文件编码
    RL::CharsetType srcFileCharset = RL::CharsetType::UNKNOWN;
    //目标文件编码
    RL::CharsetType destFileCharset = RL::CharsetType::UNKNOWN;
    //操作结果: 0 转换模式：转换成功，
    //         1 检测模式：成功，无操作
    //         10 读取源文件失败
    //         20 写入目标文件失败
    uint32_t result = 1;
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
    static std::wstring GetCharsetTypeMsg(RL::CharsetType charsetType);

private:
    void RunConvertThread();

private:
    TCharsetToolsParam m_convertParam;
    CharsetToolsCallback* m_callback;
    std::thread m_convertThread;
};

