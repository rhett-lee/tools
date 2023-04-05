#include "StringCharset.h"
#include "UnicodeConvert.h"
#include "WindowsDefs.h"

#include <memory>
#include <cassert>

/////////////////////////////////////////////////////////////////
//RLStringCharset class implementation

namespace RL
{

uint32_t StringCharset::GetBOMSize(CharsetType charsetType)
{
    switch (charsetType)
    {
    case CharsetType::UTF8:
        return 3;
    case CharsetType::UTF16_BE:
    case CharsetType::UTF16_LE:
        return 2;
    default:
        return 0;
    }
    return 0;
}

CharsetType StringCharset::GetDataCharsetByBOM(const char* data, uint32_t length)
{
    CharsetType charsetType = CharsetType::UNKNOWN;
    if ((length < 2) || (data == nullptr))
    {
        return charsetType;
    }
    if (length >= 4 && data[0] == '\x00' && data[1] == '\x00' && data[2] == '\xFE' && data[3] == '\xFF')
    {
        //"UTF-32BE";
        charsetType = CharsetType::UNKNOWN;
    }
    else if (length >= 4 && data[0] == '\xFF' && data[1] == '\xFE' && data[2] == '\x00' && data[3] == '\x00')
    {        
        if (length == 4)
        {
            charsetType = CharsetType::UTF16_LE;
        }
        else
        {
            //"UTF-32LE";
            charsetType = CharsetType::UNKNOWN;
        }
    }
    else if (length >= 3 && data[0] == '\xEF' && data[1] == '\xBB' && data[2] == '\xBF') 
    {
        charsetType = CharsetType::UTF8;
    }
    else if (length >= 2 && data[0] == '\xFF' && data[1] == '\xFE') 
    {
        charsetType = CharsetType::UTF16_LE;
    }
    else if (length >= 2 && data[0] == '\xFE' && data[1] == '\xFF') 
    {
        charsetType = CharsetType::UTF16_BE;
    }
    return charsetType;
}

CharsetType StringCharset::GetDataCharset(const char* data, uint32_t length)
{
    CharsetType charsetType = CharsetType::UNKNOWN;
    if ((length < 1) || (data == nullptr))
    {
        return charsetType;
    }
    if (IsValidateGBKStream(data, length))
    {
        charsetType = CharsetType::ANSI;
    }
    else if (IsValidateUTF8Stream(data, length))
    {
        charsetType = CharsetType::UTF8;
    }
    else if (IsValidateUTF16LEStream(data, length))
    {
        charsetType = CharsetType::UTF16_LE;
    }
    else if (IsValidateUTF16BEStream(data, length))
    {
        charsetType = CharsetType::UTF16_BE;
    }
    return charsetType;
}

bool StringCharset::GetDataAsString(const char* data, uint32_t length, std::wstring& result)
{
    CharsetType inCharsetType = CharsetType::UNKNOWN;
    CharsetType outCharsetType = CharsetType::UNKNOWN;
    uint32_t bomSize = 0;
    return GetDataAsString(data, length, inCharsetType, result, outCharsetType, bomSize);
}

bool StringCharset::GetDataAsString(const char* data, uint32_t length, CharsetType inCharsetType, std::wstring& result)
{
    CharsetType outCharsetType = CharsetType::UNKNOWN;
    uint32_t bomSize = 0;
    return GetDataAsString(data, length, inCharsetType, result, outCharsetType, bomSize);
}

bool StringCharset::GetDataAsString(const char* data, uint32_t length,
                                    std::wstring& result, CharsetType& outCharsetType, uint32_t& bomSize)
{
    CharsetType inCharsetType = CharsetType::UNKNOWN;
    return GetDataAsString(data, length, inCharsetType, result, outCharsetType, bomSize);
}

bool StringCharset::GetDataAsString(const char* data, uint32_t length, CharsetType inCharsetType,
                                    std::wstring& result, CharsetType& outCharsetType, uint32_t& bomSize)
{
    result.clear();
    outCharsetType = CharsetType::UNKNOWN;
    bomSize = 0;
    if ((length < 1) || (data == nullptr))
    {
        return false;
    }
    outCharsetType = GetDataCharsetByBOM(data, length);
    bomSize = GetBOMSize(outCharsetType);
    if (inCharsetType != CharsetType::UNKNOWN)
    {
        if (inCharsetType != outCharsetType)
        {            
            if (bomSize > 0)
            {
                //���ݰ���BOMͷǩ��������ָ����ʽ��ʵ�ʸ�ʽ��ͬ������
                return false;
            }
            else
            {
                //�����BOMͷǩ������ǿ����inCharsetType�����������                
                CharsetType checkCharsetType = GetDataCharset(data, length);
                if (inCharsetType != checkCharsetType)
                {
                    //ָ����������������ʵ���ļ����ݼ�⵽�ı��벻ͬ
                    return false;
                }
                outCharsetType = inCharsetType;
            }
        }
    }    

    assert(bomSize <= length);
    if (outCharsetType == CharsetType::UNKNOWN)
    {
        //�����BOMͷ���ʧ�ܣ�����������
        outCharsetType = GetDataCharset(data, length);
    }
    const char* realData = data + bomSize;
    uint32_t realLen = length - bomSize;

    if (outCharsetType == CharsetType::ANSI)
    {
        result = UnicodeConvert::MultiByteToUnicode(realData, realLen);
    }
    else if (outCharsetType == CharsetType::UTF8)
    {
        result = UnicodeConvert::UTF8ToUnicode(realData, realLen);
    }
    else if (outCharsetType == CharsetType::UTF16_LE)
    {
        result.assign((const wchar_t*)realData, realLen / sizeof(wchar_t));
    }
    else if (outCharsetType == CharsetType::UTF16_BE)
    {
        // ����ǰ�ַ����ֽ���ת��������洢�����LE������ַ�����
        uint32_t dataSize = realLen / sizeof(wchar_t);
        result.reserve(dataSize + 1);
        const wchar_t* dataBE = (const wchar_t*)realData;
        for (uint32_t i = 0; i < dataSize; i++)
        {
            result.push_back((dataBE[i] >> 8) | (dataBE[i] << 8));
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool StringCharset::IsValidateGBKStream(const char* stream, uint32_t length)
{
    if ((length < 1) || (stream == nullptr))
    {
        return false;
    }
    unsigned char* s = (unsigned char*)stream;
    unsigned char* e = s + length;

    for (; s < e; s++)
    {
        if (*s < 0x80)
        {
            continue;
        }
        if (*s < 0x81 || 0xFE < *s)
        {
            break;
        }
        if (++s == e)
        {
            return false;
        }
        if (*s < 0x40 || 0xFE < *s)
        {
            break;
        }
    }
    return s == e;
}

bool StringCharset::IsValidateUTF8Stream(const char* stream, uint32_t length)
{
    if ((length < 1) || (stream == nullptr))
    {
        return false;
    }
    // �������е�ÿ���ֽ�
    for (uint32_t i = 0; i < length; i++)
    {
        // �����ǰ�ֽ��� ASCII �ַ��������������һ���ֽ�
        if ((stream[i] & 0x80) == 0x00)
        {
            continue;
        }
        // �����ǰ�ֽ��� UTF-8 ����Ķ��ֽ��ַ��ĵ�һ���ֽڣ��������ַ����ֽ���
        else if ((stream[i] & 0xE0) == 0xC0)
        {
            uint32_t numBytes = 2;
            // �������ֽ��Ƿ��Ǹ��ַ�����Ч�ֽ�
            for (uint32_t j = 1; j < numBytes; j++)
            {
                if ((i + j >= length) || ((stream[i + j] & 0xC0) != 0x80))
                {
                    return false;
                }
            }
            // ��������ֽڶ��Ǹ��ַ�����Ч�ֽڣ������������һ���ַ�
            i += numBytes - 1;
            continue;
        }
        else if ((stream[i] & 0xF0) == 0xE0)
        {
            uint32_t numBytes = 3;
            // �������ֽ��Ƿ��Ǹ��ַ�����Ч�ֽ�
            for (uint32_t j = 1; j < numBytes; ++j)
            {
                if ((i + j >= length) || ((stream[i + j] & 0xC0) != 0x80))
                {
                    return false;
                }
            }
            // ��������ֽڶ��Ǹ��ַ�����Ч�ֽڣ������������һ���ַ�
            i += numBytes - 1;
            continue;
        }
        else if ((stream[i] & 0xF8) == 0xF0)
        {
            uint32_t numBytes = 4;
            // �������ֽ��Ƿ��Ǹ��ַ�����Ч�ֽ�
            for (uint32_t j = 1; j < numBytes; ++j)
            {
                if ((i + j >= length) || ((stream[i + j] & 0xC0) != 0x80))
                {
                    return false;
                }
            }
            // ��������ֽڶ��Ǹ��ַ�����Ч�ֽڣ������������һ���ַ�
            i += numBytes - 1;
            continue;
        }
        // �����ǰ�ֽ��� UTF-8 ����Ķ��ֽ��ַ��ĵ�һ���ֽڣ��������ַ����ֽ���
        else
        {
            return false;
        }
    }
    // ��������ֽڶ�����Ч�� UTF-8 ���룬�򷵻� true
    return true;
}

bool StringCharset::IsValidateUTF16LEStream(const char* stream, uint32_t length)
{
    if ((length < 1) || (stream == nullptr))
    {
        return false;
    }
    // �� UTF-16LE �����У�ÿ���ַ�ռ�� 2 ���ֽ�
    // ��ˣ����ĳ��ȱ����� 2 �ı���
    if (length % 2 != 0) 
    {
        return false;
    }

    // �������е�ÿ���ַ�
    for (uint32_t i = 0; i < length; i += 2)
    {
        // �����ǰ�ַ��Ǵ���Եĵ�һ���ַ���������һ���ַ��Ƿ�Ϊ����Եĵڶ����ַ�
        if ((stream[i + 1] & 0xFC) == 0xD8)
        {
            if (((i + 3) < length) && ((stream[i + 3] & 0xFC) == 0xDC)) 
            {
                // ����Ǵ���ԣ������������һ���ַ�
                i += 2;
                continue;
            }
            else 
            {
                // ������Ǵ���ԣ��򷵻� false
                return false;
            }
        }
        // �����ǰ�ַ��Ǵ���Եĵڶ����ַ����򷵻� false
        else if ((stream[i + 1] & 0xFC) == 0xDC) 
        {
            return false;
        }
    }
    // ��������ַ�������Ч�� UTF-16LE ���룬�򷵻� true
    return true;
}

bool StringCharset::IsValidateUTF16BEStream(const char* stream, uint32_t length)
{
    if ((length < 1) || (stream == nullptr))
    {
        return false;
    }
    // �� UTF-16BE �����У�ÿ���ַ�ռ�� 2 ���ֽ�
    // ��ˣ����ĳ��ȱ����� 2 �ı���
    if (length % 2 != 0) 
    {
        return false;
    }
    // �������е�ÿ���ַ�
    for (uint32_t i = 0; i < length; i += 2)
    {
        if ((stream[i] & 0xFC) == 0xD8) 
        {
            if (((i + 2) < length) && ((stream[i + 2] & 0xFC) == 0xDC)) 
            {
                // ����Ǵ���ԣ������������һ���ַ�
                i += 2;
                continue;
            }
            else 
            {
                // ������Ǵ���ԣ��򷵻� false
                return false;
            }
        }
        // �����ǰ�ַ��Ǵ���Եĵڶ����ַ����򷵻� false
        else if ((stream[i] & 0xFC) == 0xDC) 
        {
            return false;
        }
    }
    // ��������ַ�������Ч�� UTF-16BE ���룬�򷵻� true
    return true;
}

}//namespace RL
