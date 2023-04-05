#include "TextFile.h"
#include "base/UnicodeConvert.h"
#include <fstream>
#include <cassert>

namespace RL
{

bool TextFile::ReadData(const std::wstring& fileName, 
                        CharsetType inCharsetType, 
                        std::wstring& fileText,
                        CharsetType& outCharsetType,
                        uint32_t& bomSize)
{
    fileText.clear();
    outCharsetType = CharsetType::UNKNOWN;
    bomSize = 0;
    std::vector<char> fileData;
    if (!ReadBinaryFile(fileName, fileData) || fileData.empty())
    {
        return false;
    }
    return StringCharset::GetDataAsString(fileData.data(), (uint32_t)fileData.size(), inCharsetType, fileText, outCharsetType, bomSize);
}

bool TextFile::WriteData(const std::wstring& fileName, const std::wstring& fileText, CharsetType charsetType, bool writeBOM)
{
    if ((charsetType == CharsetType::UNKNOWN) || fileText.empty() || fileName.empty())
    {
        return false;
    }
    
    std::vector<char> fileData;
    if (charsetType == CharsetType::ANSI)
    {
        std::string data = UnicodeConvert::UnicodeToMultiByte(fileText);
        fileData.reserve(fileData.size() + data.size());
        std::copy(data.begin(), data.end(), std::back_inserter(fileData));
    }
    else if (charsetType == CharsetType::UTF8)
    {
        if (writeBOM)
        {
            fileData.push_back('\xEF');
            fileData.push_back('\xBB');
            fileData.push_back('\xBF');
        }
        std::string data = UnicodeConvert::UnicodeToUTF8(fileText);
        const char* newData = data.c_str();
        size_t newDataSize = data.size();
        size_t oldSize = fileData.size();
        fileData.resize(oldSize + newDataSize, 0);
        ::memcpy_s(fileData.data() + oldSize, newDataSize, newData, newDataSize);
    }
    else if (charsetType == CharsetType::UTF16_LE)
    {
        if (writeBOM)
        {
            fileData.push_back('\xFF');
            fileData.push_back('\xFE');
        }
        const char* newData = (const char*)fileText.c_str();
        size_t newDataSize = fileText.size() * sizeof(wchar_t);
        size_t oldSize = fileData.size();
        fileData.resize(oldSize + newDataSize, 0);
        ::memcpy_s(fileData.data() + oldSize, newDataSize, newData, newDataSize);
    }
    else if (charsetType == CharsetType::UTF16_BE)
    {
        if (writeBOM)
        {
            fileData.push_back('\xFE');
            fileData.push_back('\xFF');            
        }
        //�����ֽ���
        uint32_t dataSize = fileText.size();
        std::wstring resultBE;
        resultBE.reserve(dataSize + 1);
        for (size_t i = 0; i < fileText.size(); i++)
        {
            // ����ǰ�ַ����ֽ���ת��������洢������ַ�����
            resultBE.push_back((fileText[i] >> 8) | (fileText[i] << 8));
        }
        const char* newData = (const char*)resultBE.c_str();
        size_t newDataSize = resultBE.size() * sizeof(wchar_t);
        size_t oldSize = fileData.size();
        fileData.resize(oldSize + newDataSize, 0);
        ::memcpy_s(fileData.data() + oldSize, newDataSize, newData, newDataSize);
    }
    else
    {
        return false;
    }
    return WriteBinaryFile(fileName, fileData);
}

bool TextFile::ReadBinaryFile(const std::wstring& fileName, std::vector<char>& container)
{
    container.clear();
    // ���ļ�
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) 
    {
        return false;
    }

    // ��ȡ�ļ���С
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    bool isOk = false;
    //�ļ���С�޶���10MB��
    assert(fileSize < 1024 * 1024 * 10);
    if ((fileSize > 0) && (fileSize < 1024*1024*10))
    {
        // ��ȡ�ļ����ݲ��洢��������
        container.resize((size_t)fileSize);
        file.read(container.data(), fileSize);
        if (!file.fail())
        {
            isOk = true;
        }
    }
    // �ر��ļ�
    file.close();
    return isOk;
}

bool TextFile::WriteBinaryFile(const std::wstring& fileName, const std::vector<char>& container)
{
    // ���ļ�
    std::ofstream file(fileName, std::ios::binary);
    if (!file.is_open()) 
    {
        return false;
    }

    // �������е�����д���ļ�
    file.write(container.data(), container.size());

    // ���д���Ƿ�ɹ�
    bool isOk = file.good();
    // �ر��ļ�
    file.close();
    return isOk;
}

}//namespace RL