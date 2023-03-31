#include "pch.h"
#include "CharsetTools.h"

CharsetTools::CharsetTools():
    m_callback(NULL)
{

}

bool CharsetTools::StartConvert(const TCharsetToolsParam& convertParam, CharsetToolsCallback* callback)
{
    if (convertParam.isDirChecked)
    {
        if (convertParam.filePath.empty() || convertParam.fileExt.empty())
        {
            return false;
        }
    }
    else if (convertParam.fileName.empty())
    {
        return false;
    }
    if (callback == nullptr)
    {
        return false;
    }
    m_convertParam = convertParam;
    m_callback = callback;

    assert(!m_convertThread.joinable());

    std::thread convertThread = std::thread([this]() {
            this->RunConvertThread();
        });
    m_convertThread.swap(convertThread);
    return true;
}

void CharsetTools::RunConvertThread()
{
    //扫描磁盘文件
    CharsetToolsCallback* callback = m_callback;
    if (!callback->OnConvertBegin())
    {
        return;
    }

    TProgressData data;
    data.totalFiles = 20;
    data.result = 1;
    for (size_t index = 0; index < data.totalFiles; ++index)
    {        
        Sleep(1000);
        if (!callback->OnConvertProgress(data))
        {
            return;
        }

        data.currentFileIndex += 1;
    }    

    if (!callback->OnConvertEnd())
    {
        return;
    }
}

void CharsetTools::Terminate()
{
    if (m_convertThread.joinable())
    {
        m_convertThread.detach();
    }
    m_callback = nullptr;
}

std::wstring CharsetTools::GetErrMsg(const TProgressData& progressData)
{
    std::wstring errMsg;
    switch (progressData.result)
    {
    case 10:
        errMsg = L"源文件编码检测失败";
        break;
    case 11:
        errMsg = L"源文件读取失败";
        break;
    case 20:
        errMsg = L"目标文件写入失败";
        break;
    default:
        break;
    }
    return errMsg;
}

std::wstring CharsetTools::GetCharsetMsg(const TProgressData& progressData)
{
    std::wstring charsetSrc = GetCharsetTypeMsg(progressData.srcFileCharset);
    std::wstring charsetDest = GetCharsetTypeMsg(progressData.destFileCharset);

    std::wstring msg = L"（";
    msg += charsetSrc;
    msg += L" -> ";
    msg += charsetDest;
    msg += L"）";
    return msg;
}

std::wstring CharsetTools::GetCharsetTypeMsg(RL::RLCharsetType charsetType)
{
    std::wstring msg;
    switch (charsetType)
    {
    case RL::RLCharsetType::ANSI:
        msg = L"ANSI";
        break;
    case RL::RLCharsetType::UNICODE_UTF7:
        msg = L"UTF7";
        break;
    case RL::RLCharsetType::UNICODE_UTF8:
        msg = L"UTF8";
        break;
    case RL::RLCharsetType::UNICODE_UTF16:
    case RL::RLCharsetType::UNICODE_UTF16_LE:
        msg = L"UTF16";
        break;
    case RL::RLCharsetType::UNICODE_UTF16_BE:    
        msg = L"UTF16-BE";
        break;
    case RL::RLCharsetType::UNICODE_UTF32:    
    case RL::RLCharsetType::UNICODE_UTF32_LE:
        msg = L"UTF32";
        break;
    case RL::RLCharsetType::UNICODE_UTF32_BE:
        msg = L"UTF32-BE";
        break;
    default:
        msg = L"UNKNOWN";
        break;
    }
    return msg;
}
