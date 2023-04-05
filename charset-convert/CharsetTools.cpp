#include "pch.h"
#include "CharsetTools.h"
#include "base/StringToken.h"
#include "base/StringUtils.h"
#include "base/StringCharset.h"
#include "filesystem/TextFile.h"
#include <filesystem>
#include <vector>

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
    if (convertParam.destFileCharset == RL::CharsetType::UNKNOWN)
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
    //ɨ������ļ�
    CharsetToolsCallback* callback = m_callback;
    if (!callback->OnConvertBegin())
    {
        return;
    }

    std::vector<std::wstring> allFiles;
    if (!m_convertParam.isDirChecked)
    {
        if (!m_convertParam.fileName.empty())
        {
            allFiles.push_back(m_convertParam.fileName);
        }
    }
    else
    {
        std::vector<std::wstring> extValues;
        RL::StringToken::StringToArray(m_convertParam.fileExt, L';', extValues);
        if (!extValues.empty())
        {
            //�ݹ�ɨ��Ŀ¼������ƥ����ļ�
            for (const auto& entry : std::filesystem::recursive_directory_iterator(m_convertParam.filePath))
            {
                if (entry.is_regular_file())
                {
                    for (const auto& ext : extValues)
                    {
                        if (RL::StringUtils::WildcardCompare(ext.c_str(), entry.path().filename().wstring().c_str(), true))
                        {
                            allFiles.push_back(entry.path().wstring());
                        }
                    }
                }
            }
        }
    }

    std::wstring fileText;
    TProgressData data;
    data.totalFiles = allFiles.size();
    data.result = 1;
    for (size_t index = 0; index < data.totalFiles; ++index)
    {
        data.currentFileIndex = index;
        data.fileName = allFiles[index];
        data.isCheckMode = m_convertParam.isCheckMode;
        data.destFileCharset = m_convertParam.destFileCharset;

        RL::CharsetType srcFileCharset = m_convertParam.srcFileCharset;

        fileText.clear();
        RL::CharsetType outCharsetType = RL::CharsetType::UNKNOWN;
        uint32_t bomSize = 0;        
        bool isOk = RL::TextFile::ReadData(data.fileName, srcFileCharset, fileText, outCharsetType, bomSize);
        if (!isOk || fileText.empty())
        {
            data.result = 10;
            data.srcFileCharset = RL::CharsetType::UNKNOWN;
        }
        else
        {
            data.result = data.isCheckMode ? 1 : 0;
            data.srcFileCharset = outCharsetType;
        }

        if (!m_convertParam.isCheckMode)
        {
            //����ת��
            RL::CharsetType destFileCharset = m_convertParam.destFileCharset;
            bool destFileWriteBOM = m_convertParam.destFileWriteBOM;
            assert(destFileCharset != RL::CharsetType::UNKNOWN);

            data.result = 20;
            if (destFileCharset != RL::CharsetType::UNKNOWN)
            {
                //��Ŀ����룬д���ļ�
                bool isOk = RL::TextFile::WriteData(data.fileName, fileText, destFileCharset, destFileWriteBOM);
                if (isOk)
                {
                    data.result = 0;
                }
            }
        }

        if (!callback->OnConvertProgress(data))
        {
            return;
        }        
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
        errMsg = L"��ȡԴ�ļ�ʧ��";
        break;
    case 20:
        errMsg = L"д��Ŀ���ļ�ʧ��";
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

    std::wstring msg = L"��";
    msg += charsetSrc;
    msg += L" -> ";
    msg += charsetDest;
    msg += L"��";
    return msg;
}

std::wstring CharsetTools::GetCharsetTypeMsg(RL::CharsetType charsetType)
{
    std::wstring msg;
    switch (charsetType)
    {
    case RL::CharsetType::ANSI:
        msg = L"ANSI";
        break;
    case RL::CharsetType::UTF8:
        msg = L"UTF8";
        break;
    case RL::CharsetType::UTF16_LE:
        msg = L"UTF16_LE";
        break;
    case RL::CharsetType::UTF16_BE:    
        msg = L"UTF16_BE";
        break;
    default:
        msg = L"UNKNOWN";
        break;
    }
    return msg;
}
