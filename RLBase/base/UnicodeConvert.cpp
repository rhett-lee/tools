#include "UnicodeConvert.h"
#include "WindowsDefs.h"
#include <memory>
#include <cassert>

/////////////////////////////////////////////////////////////////
//RLUnicodeConvert class implementation

namespace RL
{

uint32_t UnicodeConvert::s_defaultCodePage = 0;

std::wstring UnicodeConvert::MultiByteToUnicode(const std::string& src)
{
    return MultiByteToUnicode(src.c_str(), (int32_t)src.size(), RL_CP_ACP);
}

std::wstring UnicodeConvert::MultiByteToUnicode(const char* src)
{
    return MultiByteToUnicode(src, -1, RL_CP_ACP);
}

std::wstring UnicodeConvert::MultiByteToUnicode(const char* src, int32_t len)
{
    return MultiByteToUnicode(src, len, RL_CP_ACP);
}

std::wstring UnicodeConvert::MultiByteToUnicode(const char* src, int32_t len, uint32_t codePage)
{
    if (src == nullptr)
    {
        return std::wstring();
    }
#ifdef _DEBUG
    if ((len == RL_CP_ACP) || (len == RL_CP_OEMCP) || (len == RL_CP_UTF8))
    {
        assert(len == (int32_t)strlen(src));
    }
#endif
    bool result = true;
    uint32_t defaultCodePage = s_defaultCodePage;
    if (defaultCodePage > 0)
    {
        if( (codePage == RL_CP_ACP) || (codePage == RL_CP_OEMCP) )
        {
            std::wstring str = DoMultiByteToUnicode(src, len, defaultCodePage, result);
            if(result)
            {
                return str;
            }
        }           
    }
    return DoMultiByteToUnicode(src, len, codePage, result);
}

std::wstring UnicodeConvert::DoMultiByteToUnicode(const char* src, int32_t len,uint32_t codePage, bool& result)
{
    result = true;
    if(src == nullptr)
    {
        return std::wstring();
    }
    if(len < 0)
    {
        len = static_cast<int32_t>( strlen(src) );
    }
    if (len < 1)
    {
        return std::wstring();
    }
    //对小字符串进行特殊处理，以提高性能
    const uint32_t shortStrLen = 128;
    if (len < (shortStrLen - 8))
    {
        wchar_t szBuf[shortStrLen];
        int32_t bufLen = (int32_t)shortStrLen - 1;
        int32_t resultSize = ::MultiByteToWideChar(codePage, 0, src, len, szBuf, bufLen);
        if ((resultSize > 0) && (resultSize < bufLen))
        {
            szBuf[resultSize] = 0;
            return std::wstring(szBuf);
        }
    }
    int32_t minSize = ::MultiByteToWideChar(codePage, 0, src, len, NULL, 0);
    if(minSize > 0)
    {
        minSize += 1;
        wchar_t* buf = new wchar_t[minSize];
        std::unique_ptr<wchar_t[]> spBuf(buf);
        int32_t ret = ::MultiByteToWideChar(codePage, 0, src, len, buf, minSize);
        if( (ret > 0) && (ret < minSize) )
        {
            buf[ret] = 0;
        }
        else
        {
            result = false;
            buf[0] = 0;
        }
        return std::wstring(buf);
    }
    else
    {
        result = false;
        return std::wstring();
    }
}

std::string UnicodeConvert::UnicodeToMultiByte(const std::wstring& src,
                                                 uint32_t codePage, 
                                                 char defaultChar, 
                                                 bool& defaultCharWasUsed)
{
    bool result = true;
    
    if( (codePage == RL_CP_ACP) || (codePage == RL_CP_OEMCP) )
    {
        uint32_t defaultCodePage = s_defaultCodePage;
        if (defaultCodePage > 0)
        {
            std::string str = DoUnicodeToMultiByte(src.c_str(), (int32_t)src.size(), defaultCodePage, defaultChar, defaultCharWasUsed, result);
            if(result)
            {
                return str;
            }
        }
    }
    return DoUnicodeToMultiByte(src.c_str(), (int32_t)src.size(), codePage, defaultChar, defaultCharWasUsed, result);
}

std::string UnicodeConvert::DoUnicodeToMultiByte(const std::wstring::value_type* src,
                                                   int32_t srcLen,
                                                   uint32_t codePage, 
                                                   char defaultChar, 
                                                   bool& defaultCharWasUsed,
                                                   bool& result)
{
    result = true;
    defaultCharWasUsed = false;
    if ((src == nullptr) || (srcLen == 0) || (*src == '\0'))
    {
        return std::string();
    }
    if (srcLen < 0)
    {
        srcLen = (int32_t)wcslen(src);
    }
    if (srcLen < 1)
    {
        return std::string();
    }
    if ((codePage == CP_UTF7) || (codePage == CP_UTF8))
    {
        defaultChar = 0;
    }

    //对小字符串进行特殊处理，以提高性能
    const int32_t shortStrLen = 128;
    if (srcLen < (shortStrLen - 8))
    {
        char szBuf[shortStrLen * 2];
        int32_t minSize = (int32_t)shortStrLen * 2 - 1;
        int32_t len = 0;
        if (defaultChar != 0)
        {
            BOOL defUsed = FALSE;
            char defaultChars[2];
            defaultChars[0] = defaultChar;
            defaultChars[1] = 0;
            len = ::WideCharToMultiByte(codePage, 0, src, srcLen, szBuf, minSize, defaultChars, &defUsed);
            defaultCharWasUsed = (defUsed != FALSE);
        }
        else
        {
            len = ::WideCharToMultiByte(codePage, 0, src, srcLen, szBuf, minSize, NULL, NULL);
        }
        if ((len > 0) && (len < minSize))
        {
            szBuf[len] = 0;
            return std::string(szBuf);
        }
    }
    
    int32_t minSize = ::WideCharToMultiByte(codePage, 0, src, srcLen, NULL, 0, NULL, NULL);
    if(minSize > 0)
    {
        minSize += 8;
        char* buf = new char[minSize];
        std::unique_ptr<char[]> spBuf(buf);

        int32_t len = 0;
        if(defaultChar != 0)
        {
            BOOL defUsed = FALSE;
            char defaultChars[2];
            defaultChars[0] = defaultChar;
            defaultChars[1] = 0;
            len = ::WideCharToMultiByte(codePage, 0, src, srcLen, buf, minSize, defaultChars, &defUsed);
            defaultCharWasUsed = (defUsed != FALSE);
        }
        else
        {
            len = ::WideCharToMultiByte(codePage, 0, src, srcLen, buf, minSize, NULL, NULL);
        }
        if( (len > 0) && (len < minSize) )
        {
            buf[len] = 0;
        }
        else
        {
            result = false;
            buf[0] = 0;
        }        
        return std::string(buf);
    }
    else
    {
        result = false;
        return std::string();
    }
}

std::string UnicodeConvert::UnicodeToMultiByte(const std::wstring& src)
{
    return UnicodeToMultiByte(src.c_str(), (int32_t)src.size(), RL_CP_ACP);
}

std::string UnicodeConvert::UnicodeToMultiByte(const std::wstring::value_type* src)
{
    return UnicodeToMultiByte(src, -1, RL_CP_ACP);
}

std::string UnicodeConvert::UnicodeToMultiByte(const wchar_t* src, int32_t srcLen)
{
    return UnicodeToMultiByte(src, srcLen, RL_CP_ACP);
}

std::string UnicodeConvert::UnicodeToMultiByte(const std::wstring::value_type* src, int32_t srcLen, uint32_t codePage)
{
    if (src == nullptr)
    {
        return std::string();
    }
#ifdef _DEBUG
    if ((srcLen == RL_CP_ACP) || (srcLen == RL_CP_OEMCP) || (srcLen == RL_CP_UTF8))
    {
        assert(srcLen == (int32_t)wcslen(src));
    }
#endif
    bool defaultCharWasUsed = false;
    bool result = false;
    return DoUnicodeToMultiByte(src, srcLen, codePage, 0, defaultCharWasUsed, result);
}

std::wstring UnicodeConvert::UTF8ToUnicode(const char* inBuf, int32_t inBufLen)
{
    return MultiByteToUnicode(inBuf, inBufLen, RL_CP_UTF8);
}

std::wstring UnicodeConvert::UTF8ToUnicode(const char* inBuf)
{
    return MultiByteToUnicode(inBuf, -1, RL_CP_UTF8);
}

std::wstring UnicodeConvert::UTF8ToUnicode(const std::string& inBuf)
{
    return MultiByteToUnicode(inBuf.c_str(), (int32_t)inBuf.size(), RL_CP_UTF8);
}

std::string UnicodeConvert::UnicodeToUTF8(const wchar_t* inBuf, int32_t inBufLen)
{
    return UnicodeToMultiByte(inBuf, inBufLen, RL_CP_UTF8);
}

std::string UnicodeConvert::UnicodeToUTF8(const wchar_t* inBuf)
{
    return UnicodeToMultiByte(inBuf, -1, RL_CP_UTF8);
}

std::string UnicodeConvert::UnicodeToUTF8(const std::wstring& inBuf)
{
    return UnicodeToMultiByte(inBuf.c_str(), (int32_t)inBuf.size(), RL_CP_UTF8);
}

void UnicodeConvert::SetDefaultCodePage(uint32_t codePage)
{
    s_defaultCodePage = codePage;
}

}//namespace RL
