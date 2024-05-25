#include "pch.h"
#include "base/StringCharset.h"
#include "base/WindowsDefs.h"
#include "filesystem/TextFile.h"
#include <vector>
#include <fstream>
#include <filesystem>

//读取文件到容器中，注意如果是文本文件，调用方需要自己处理字符串的尾零问题。
void ReadBinaryFileToVector(const std::string& filename, std::vector<char>& container) 
{
    // 打开文件
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    // 获取文件大小
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // 读取文件内容并存储到容器中
    container.resize((size_t)fileSize);
    file.read(container.data(), fileSize);

    // 关闭文件
    file.close();
}

TEST(StringCharset, TextFile)
{
    UINT acp = ::GetACP();
    std::wstring file_data_check;

    std::wstring file_data_string;
    RL::CharsetType charsetType;
    std::vector<char> file_data;
    ReadBinaryFileToVector("test-GBK.txt", file_data);
    EXPECT_TRUE(RL::StringCharset::IsValidateGBKStream(&file_data[0], file_data.size()));
    EXPECT_FALSE(RL::StringCharset::IsValidateUTF8Stream(&file_data[0], file_data.size()));
    EXPECT_TRUE(RL::StringCharset::GetDataAsString(&file_data[0], file_data.size(), file_data_string));
    if (file_data_check.empty())
    {
        file_data_check = file_data_string;
    }
    file_data_string.clear();

    ReadBinaryFileToVector("test-UTF8-BOM.txt", file_data);
    charsetType = RL::StringCharset::GetDataCharsetByBOM(&file_data[0], file_data.size());
    EXPECT_TRUE(charsetType == RL::CharsetType::UTF8);
    EXPECT_TRUE(RL::StringCharset::GetBOMSize(charsetType) == 3);
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF8Stream(&file_data[0] + 3, file_data.size() - 3));
    charsetType = RL::StringCharset::GetDataCharset(&file_data[0] + 3, file_data.size() - 3);
    EXPECT_TRUE(charsetType == RL::CharsetType::UTF8);
    EXPECT_TRUE(RL::StringCharset::GetDataAsString(&file_data[0] + 3, file_data.size() - 3, file_data_string));
    EXPECT_TRUE(file_data_check == file_data_string);
    file_data_string.clear();

    ReadBinaryFileToVector("test-UTF8-noBOM.txt", file_data);
    charsetType = RL::StringCharset::GetDataCharsetByBOM(&file_data[0], file_data.size());
    EXPECT_TRUE(charsetType == RL::CharsetType::UNKNOWN);
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF8Stream(&file_data[0], file_data.size()));
    charsetType = RL::StringCharset::GetDataCharset(&file_data[0], file_data.size());
    EXPECT_TRUE(charsetType == RL::CharsetType::UTF8);
    EXPECT_TRUE(RL::StringCharset::GetDataAsString(&file_data[0], file_data.size(), file_data_string));
    EXPECT_TRUE(file_data_check == file_data_string);
    file_data_string.clear();

    ReadBinaryFileToVector("test-UTF16LE-BOM.txt", file_data);
    charsetType = RL::StringCharset::GetDataCharsetByBOM(&file_data[0], file_data.size());
    EXPECT_TRUE(charsetType == RL::CharsetType::UTF16_LE);
    EXPECT_TRUE(RL::StringCharset::GetBOMSize(charsetType) == 2);
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF16LEStream(&file_data[0] + 2, file_data.size() - 2));
    charsetType = RL::StringCharset::GetDataCharset(&file_data[0] + 2, file_data.size() - 2);
    EXPECT_TRUE(charsetType == RL::CharsetType::UTF16_LE);
    EXPECT_TRUE(RL::StringCharset::GetDataAsString(&file_data[0] + 2, file_data.size() - 2, file_data_string));
    EXPECT_TRUE(file_data_check == file_data_string);
    file_data_string.clear();

    ReadBinaryFileToVector("test-UTF16LE-noBOM.txt", file_data);
    charsetType = RL::StringCharset::GetDataCharsetByBOM(&file_data[0], file_data.size());
    EXPECT_TRUE(charsetType == RL::CharsetType::UNKNOWN);
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF16LEStream(&file_data[0], file_data.size()));
    charsetType = RL::StringCharset::GetDataCharset(&file_data[0], file_data.size());
    EXPECT_TRUE(charsetType == RL::CharsetType::UTF16_LE);
    EXPECT_TRUE(RL::StringCharset::GetDataAsString(&file_data[0], file_data.size(), file_data_string));
    EXPECT_TRUE(file_data_check == file_data_string);
    file_data_string.clear();

    ReadBinaryFileToVector("test-UTF16BE-BOM.txt", file_data);
    charsetType = RL::StringCharset::GetDataCharsetByBOM(&file_data[0], file_data.size());
    EXPECT_TRUE(charsetType == RL::CharsetType::UTF16_BE);
    EXPECT_TRUE(RL::StringCharset::GetBOMSize(charsetType) == 2);
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF16BEStream(&file_data[0] + 2, file_data.size() - 2));
    charsetType = RL::StringCharset::GetDataCharset(&file_data[0] + 2, file_data.size() - 2);
    EXPECT_TRUE(charsetType == RL::CharsetType::UTF16_BE);
    EXPECT_TRUE(RL::StringCharset::GetDataAsString(&file_data[0] + 2, file_data.size() - 2, file_data_string));
    EXPECT_TRUE(file_data_check == file_data_string);
    file_data_string.clear();

    ReadBinaryFileToVector("test-UTF16BE-noBOM.txt", file_data);
    charsetType = RL::StringCharset::GetDataCharsetByBOM(&file_data[0], file_data.size());
    EXPECT_TRUE(charsetType == RL::CharsetType::UNKNOWN);
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF16BEStream(&file_data[0], file_data.size()));
    charsetType = RL::StringCharset::GetDataCharset(&file_data[0], file_data.size());
    EXPECT_TRUE(charsetType == RL::CharsetType::UTF16_BE);
    EXPECT_TRUE(RL::StringCharset::GetDataAsString(&file_data[0], file_data.size(), file_data_string));
    EXPECT_TRUE(file_data_check == file_data_string);
    file_data_string.clear();
}

TEST(StringCharset, IsValidateUTF8Stream)
{
    // 测试空流
    EXPECT_FALSE(RL::StringCharset::IsValidateUTF8Stream("", 0));

    // 测试 ASCII 字符
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF8Stream("Hello, world!", 13));

    // 测试 UTF-8 的多字节字符
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF8Stream((const char*)u8"你好，世界！", 18));

    // 测试不符合规范的 UTF-8 字符
    EXPECT_FALSE(RL::StringCharset::IsValidateUTF8Stream("\xF0\x80\x80\xC0", 4));
}

TEST(StringCharset, IsValidateUTF16LEStream)
{
    // 测试空流
    EXPECT_FALSE(RL::StringCharset::IsValidateUTF16LEStream("", 0));

    // 测试 BMP 中的字符
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF16LEStream((const char*)u"Hello, world!", 26));

    // 测试字符
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF16LEStream((const char*)u"详", 4));
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF16LEStream((const char*)u"Unicode编码详解(四)：UTF-16编码", 46));

    // 测试代理对
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF16LEStream("\x34\x12\xDC\x00\x56\x34\xDE\x00", 8));

    // 测试不符合规范的 UTF-16LE 字符
    EXPECT_TRUE(RL::StringCharset::IsValidateUTF16LEStream("\x34\x12\xDC\x00\x56\x34\xDC\x00", 8));
}

TEST(StringCharset, IsValidateUTF16BEStream)
{
    // 测试空流
    ASSERT_FALSE(RL::StringCharset::IsValidateUTF16BEStream("", 0));

    // 测试 BMP 中的字符
    ASSERT_TRUE(RL::StringCharset::IsValidateUTF16BEStream((const char*)u"Hello, world!", 26));

    // 测试代理对
    ASSERT_TRUE(RL::StringCharset::IsValidateUTF16BEStream("\x12\x34\x00\xDC\x34\x56\x00\xDE", 8));

    // 测试不符合规范的 UTF-16BE 字符
    //ASSERT_FALSE(RL::StringCharset::IsValidateUTF16BEStream("\x12\x34\x00\xDC\x34\x56\x00\xDC", 8));
}

TEST(TextFile, ReadData)
{
    std::wstring fileName;
    std::wstring fileText;
    RL::CharsetType outCharsetType = RL::CharsetType::UNKNOWN;
    uint32_t bomSize = 0;


    fileName = L"test-GBK.txt";
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UNKNOWN, fileText, outCharsetType, bomSize));
    ASSERT_TRUE(!fileText.empty());
    ASSERT_TRUE(bomSize == 0);
    ASSERT_TRUE(outCharsetType == RL::CharsetType::ANSI);
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_LE, fileText, outCharsetType, bomSize));
    fileText.clear();

    fileName = L"test-UTF8-BOM.txt";
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UNKNOWN, fileText, outCharsetType, bomSize));
    ASSERT_TRUE(!fileText.empty());
    ASSERT_TRUE(bomSize == 3);
    ASSERT_TRUE(outCharsetType == RL::CharsetType::UTF8);
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF8, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::ANSI, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_LE, fileText, outCharsetType, bomSize));
    fileText.clear();

    fileName = L"test-UTF8-noBOM.txt";
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UNKNOWN, fileText, outCharsetType, bomSize));
    ASSERT_TRUE(!fileText.empty());
    ASSERT_TRUE(bomSize == 0);
    ASSERT_TRUE(outCharsetType == RL::CharsetType::UTF8);
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF8, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::ANSI, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_LE, fileText, outCharsetType, bomSize));
    fileText.clear();

    fileName = L"test-UTF16BE-BOM.txt";
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UNKNOWN, fileText, outCharsetType, bomSize));
    ASSERT_TRUE(!fileText.empty());
    ASSERT_TRUE(bomSize == 2);
    ASSERT_TRUE(outCharsetType == RL::CharsetType::UTF16_BE);
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_BE, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF8, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::ANSI, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_LE, fileText, outCharsetType, bomSize));
    fileText.clear();

    fileName = L"test-UTF16BE-noBOM.txt";
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UNKNOWN, fileText, outCharsetType, bomSize));
    ASSERT_TRUE(!fileText.empty());
    ASSERT_TRUE(bomSize == 0);
    ASSERT_TRUE(outCharsetType == RL::CharsetType::UTF16_BE);
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_BE, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF8, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::ANSI, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_LE, fileText, outCharsetType, bomSize));
    fileText.clear();

    fileName = L"test-UTF16LE-BOM.txt";
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UNKNOWN, fileText, outCharsetType, bomSize));
    ASSERT_TRUE(!fileText.empty());
    ASSERT_TRUE(bomSize == 2);
    ASSERT_TRUE(outCharsetType == RL::CharsetType::UTF16_LE);
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_LE, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF8, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::ANSI, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_BE, fileText, outCharsetType, bomSize));
    fileText.clear();

    fileName = L"test-UTF16LE-noBOM.txt";
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UNKNOWN, fileText, outCharsetType, bomSize));
    ASSERT_TRUE(!fileText.empty());
    ASSERT_TRUE(bomSize == 0);
    ASSERT_TRUE(outCharsetType == RL::CharsetType::UTF16_LE);
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_LE, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF8, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::ANSI, fileText, outCharsetType, bomSize));
    ASSERT_FALSE(RL::TextFile::ReadData(fileName, RL::CharsetType::UTF16_BE, fileText, outCharsetType, bomSize));
    fileText.clear();
}

TEST(TextFile, WriteData)
{
    std::wstring fileName;
    std::wstring fileText;
    RL::CharsetType outCharsetType = RL::CharsetType::UNKNOWN;
    uint32_t bomSize = 0;

    fileName = L"test-UTF8-BOM.txt";
    ASSERT_TRUE(RL::TextFile::ReadData(fileName, RL::CharsetType::UNKNOWN, fileText, outCharsetType, bomSize));
    ASSERT_TRUE(!fileText.empty());
    ASSERT_TRUE(bomSize == 3);
    ASSERT_TRUE(outCharsetType == RL::CharsetType::UTF8);
    
    const std::wstring tempFileName = L"test-temp.txt";
    if (std::filesystem::exists(tempFileName))
    {
        std::filesystem::remove(tempFileName);
    }
    ASSERT_FALSE(std::filesystem::exists(tempFileName));    
    ASSERT_FALSE(RL::TextFile::WriteData(tempFileName, fileText, RL::CharsetType::UNKNOWN, false));

    RL::CharsetType charsetType = RL::CharsetType::UNKNOWN;
    std::wstring readFileText;

    charsetType = RL::CharsetType::ANSI;
    ASSERT_TRUE(RL::TextFile::WriteData(tempFileName, fileText, charsetType, false));
    ASSERT_TRUE(RL::TextFile::ReadData(tempFileName, RL::CharsetType::UNKNOWN, readFileText, outCharsetType, bomSize));
    ASSERT_TRUE(outCharsetType == charsetType);
    ASSERT_TRUE(bomSize == 0);
    ASSERT_TRUE(readFileText == fileText);
    std::filesystem::remove(tempFileName);
    ASSERT_FALSE(std::filesystem::exists(tempFileName));

    charsetType = RL::CharsetType::UTF8;
    ASSERT_TRUE(RL::TextFile::WriteData(tempFileName, fileText, charsetType, false));
    ASSERT_TRUE(RL::TextFile::ReadData(tempFileName, RL::CharsetType::UNKNOWN, readFileText, outCharsetType, bomSize));
    ASSERT_TRUE(outCharsetType == charsetType);
    ASSERT_TRUE(bomSize == 0);
    ASSERT_TRUE(readFileText == fileText);
    std::filesystem::remove(tempFileName);
    ASSERT_FALSE(std::filesystem::exists(tempFileName));

    charsetType = RL::CharsetType::UTF8;
    ASSERT_TRUE(RL::TextFile::WriteData(tempFileName, fileText, charsetType, true));
    ASSERT_TRUE(RL::TextFile::ReadData(tempFileName, RL::CharsetType::UNKNOWN, readFileText, outCharsetType, bomSize));
    ASSERT_TRUE(outCharsetType == charsetType);
    ASSERT_TRUE(bomSize == 3);
    ASSERT_TRUE(readFileText == fileText);
    std::filesystem::remove(tempFileName);
    ASSERT_FALSE(std::filesystem::exists(tempFileName));

    charsetType = RL::CharsetType::UTF16_LE;
    ASSERT_TRUE(RL::TextFile::WriteData(tempFileName, fileText, charsetType, false));
    ASSERT_TRUE(RL::TextFile::ReadData(tempFileName, RL::CharsetType::UNKNOWN, readFileText, outCharsetType, bomSize));
    ASSERT_TRUE(outCharsetType == charsetType);
    ASSERT_TRUE(bomSize == 0);
    ASSERT_TRUE(readFileText == fileText);
    std::filesystem::remove(tempFileName);
    ASSERT_FALSE(std::filesystem::exists(tempFileName));

    charsetType = RL::CharsetType::UTF16_LE;
    ASSERT_TRUE(RL::TextFile::WriteData(tempFileName, fileText, charsetType, true));
    ASSERT_TRUE(RL::TextFile::ReadData(tempFileName, RL::CharsetType::UNKNOWN, readFileText, outCharsetType, bomSize));
    ASSERT_TRUE(outCharsetType == charsetType);
    ASSERT_TRUE(bomSize == 2);
    ASSERT_TRUE(readFileText == fileText);
    std::filesystem::remove(tempFileName);
    ASSERT_FALSE(std::filesystem::exists(tempFileName));

    charsetType = RL::CharsetType::UTF16_BE;
    ASSERT_TRUE(RL::TextFile::WriteData(tempFileName, fileText, charsetType, false));
    ASSERT_TRUE(RL::TextFile::ReadData(tempFileName, RL::CharsetType::UNKNOWN, readFileText, outCharsetType, bomSize));
    ASSERT_TRUE(outCharsetType == charsetType);
    ASSERT_TRUE(bomSize == 0);
    ASSERT_TRUE(readFileText == fileText);
    std::filesystem::remove(tempFileName);
    ASSERT_FALSE(std::filesystem::exists(tempFileName));

    charsetType = RL::CharsetType::UTF16_BE;
    ASSERT_TRUE(RL::TextFile::WriteData(tempFileName, fileText, charsetType, true));
    ASSERT_TRUE(RL::TextFile::ReadData(tempFileName, RL::CharsetType::UNKNOWN, readFileText, outCharsetType, bomSize));
    ASSERT_TRUE(outCharsetType == charsetType);
    ASSERT_TRUE(bomSize == 2);
    ASSERT_TRUE(readFileText == fileText);
    std::filesystem::remove(tempFileName);
    ASSERT_FALSE(std::filesystem::exists(tempFileName));
}