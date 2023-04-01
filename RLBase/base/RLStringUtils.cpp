#include "RLStringUtils.h"
#include <algorithm>
#include <ctype.h>
#include <errno.h>
#include <strsafe.h>

namespace RL
{

enum
{
    RET_FAILED  = -1 ,
    RET_OK      = 0  ,
    RET_RETRY   = 1
};

void RLStringUtils::TrimLeft(std::wstring& str, const wchar_t* value)
{
    if (str.empty() || (value == nullptr) || (value[0] == L'\0'))
    {
        return;
    }
    auto pos = str.find_first_not_of(value);
    if (pos != std::wstring::npos) 
    {
        str.erase(0, pos);
    }
    else
    {
        str.clear();
    }
}

void RLStringUtils::TrimRight(std::wstring& str, const wchar_t* value)
{
    if (str.empty() || (value == nullptr) || (value[0] == L'\0'))
    {
        return;
    }
    auto pos = str.find_last_not_of(value);
    if (pos != std::wstring::npos) 
    {
        str.erase(pos + 1);
    }
    else 
    {
        str.clear();
    }
}

void RLStringUtils::Trim(std::wstring& str, const wchar_t* value)
{
    if (str.empty() || (value == nullptr) || (value[0] == L'\0'))
    {
        return;
    }
    // 去除前导空格、制表符、换行符、回车符、换页符和垂直制表符
    size_t start = str.find_first_not_of(value);
    if (start != std::wstring::npos)
    {
        str.erase(0, start);
    }
    else
    {
        str.clear();
        return;
    }

    // 去除尾部空格、制表符、换行符、回车符、换页符和垂直制表符等
    size_t end = str.find_last_not_of(value);
    if (end != std::wstring::npos)
    {
        str.erase(end + 1);
    }
}

void RLStringUtils::Format(std::wstring& str, const wchar_t* fmt , ...)
{
    std::wstring& result = str;
    int32_t retValue = 0;
    const int32_t BUF_SIZE = 1024;
    wchar_t buf[BUF_SIZE];
    int32_t size = BUF_SIZE;
    if(fmt != nullptr && *fmt != 0)
    {
        va_list args;
        va_start(args, fmt);
        int32_t nRet  = FormatToBuffer(buf,size,fmt,args);
        if(RET_OK == nRet)
        {
            result = buf;
        }
        else if(RET_FAILED == nRet)
        {
            result = L"";
            retValue = RET_FAILED;
        }
        else if(RET_RETRY == nRet)
        {
           //retry util the buffer is enough          
           const int32_t MAX_TIME = 1024;
           int32_t nTimes = 0;
           for(nTimes = 0; nTimes < MAX_TIME; nTimes++)
           {
                size *= 2;
                wchar_t* pNewBuf = new wchar_t[size];
                bool isOK = true;
                nRet  = FormatToBuffer(pNewBuf,size,fmt,args);
                if(RET_OK == nRet)
                {
                    result = pNewBuf;                    
                }
                else if(RET_FAILED == nRet)
                {
                    result = L"";
                    retValue = RET_FAILED;
                }
                else if(RET_RETRY == nRet)
                {
                    isOK = false;
                }
                delete [] pNewBuf;
                pNewBuf = nullptr;
                if(isOK)
                {
                    break;
                }
            }
            if(nTimes == MAX_TIME)
            {
                retValue = RET_RETRY;
            }
        }                
        va_end(args);
    }
    if(retValue != RET_OK)
    {
        result.clear();
    }
}

int32_t RLStringUtils::FormatToBuffer(wchar_t* buf, int32_t size ,const wchar_t* format, va_list args)
{
#ifdef _WIN32
    HRESULT hResult = ::StringCchVPrintf(buf, size, format, args);
    if (hResult == S_OK)
    {
        return RET_OK;
    }
    else if (hResult == STRSAFE_E_INVALID_PARAMETER)
    {
        return RET_FAILED;
    }
    else if (hResult == STRSAFE_E_INSUFFICIENT_BUFFER)
    {
        return RET_RETRY;
    }
    else
    {
        return RET_FAILED;
    }
#else
    errno = 0;
    int32_t n = _vsnwprintf(buf,size,format,args);
    if(( n >= 0) && (n < size))
    {
        return RET_OK;
    }
    else if(n >= 0)
    {
        return RET_RETRY;
    }
    else
    {
        return RET_FAILED;
    }
#endif
}


void RLStringUtils::Replace(std::wstring& str ,const wchar_t* from, const wchar_t* to)
{
    if( (from == nullptr) || (to == nullptr) ){
        return;
    }
    std::wstring::size_type fromLen = RLStringUtils::StringLen(from);
    std::wstring::size_type toLen = RLStringUtils::StringLen(to);
    std::wstring::size_type beginPos = 0;
    std::wstring::size_type pos = str.find(from,beginPos);
    while(std::wstring::npos != pos)
    {
        str.replace(pos,fromLen,to);
        beginPos = pos + toLen;
        pos = str.find(from,beginPos);
    }
}

void RLStringUtils::Replace(std::wstring& str ,const wchar_t from, const wchar_t to)
{
    std::wstring::size_type count = str.size();
    for(std::wstring::size_type pos = 0; pos < count; ++pos )
    {
        if(from == str[pos])
        {
            str[pos] = to;
        }
    }
}

void RLStringUtils::UInt64ToString(uint64_t value, wchar_t *s)
{
    wchar_t temp[32] = {0};
    int pos = 0;
    do
    {
        temp[pos++] = (wchar_t)(L'0' + (int)(value % 10));
        value /= 10;
    }while (value != 0);
    
    do
    {
        *s++ = temp[--pos];
    }while (pos > 0);
    *s = L'\0';
}

void RLStringUtils::Int64ToString(int64_t value, wchar_t *s)
{
    if (value < 0)
    {
        *s++ = L'-';
        value = -value;
    }
    UInt64ToString(value, s);
}

uint64_t RLStringUtils::StringToUInt64(const wchar_t *s, const wchar_t **end)
{
    uint64_t result = 0;
    for (;;)
    {
        wchar_t c = *s;
        if (c < '0' || c > '9')
        {
            if (end != nullptr)
            {
                *end = s;
            }
            return result;
        }
        result *= 10;
        result += (c - '0');
        s++;
    }
}

uint32_t RLStringUtils::StringToUInt32(const wchar_t* s, const wchar_t** end)
{
    return (uint32_t)StringToUInt64(s, end);
}

std::wstring RLStringUtils::Int64ToString(int64_t value)
{
    wchar_t str[64] = {0};
    Int64ToString(value,str);
    return std::wstring(str);
}

std::wstring RLStringUtils::UInt64ToString(uint64_t value )
{
    wchar_t str[64] = {0};
    UInt64ToString(value,str);
    return std::wstring(str);
}

std::wstring RLStringUtils::Int32ToString(int32_t value )
{
    return RLStringUtils::Int64ToString(int64_t(value));
}

std::wstring RLStringUtils::UInt32ToString(uint32_t value )
{
    return RLStringUtils::UInt64ToString( uint64_t(value) );
}

std::wstring RLStringUtils::UInt32ToHex(uint32_t value )
{
    wchar_t s[9] = {0};
    for (int32_t i = 0; i < 8; ++i)
    {
        int32_t t = value & 0xF;
        value >>= 4;
        s[7 - i] = (wchar_t)((t < 10) ? (L'0' + t) : (L'A' + (t - 10)));
    }
    s[8] = L'\0';
    return std::wstring(s);
}

std::wstring RLStringUtils::BooleanToString(bool value) 
{
    uint32_t integer = value ? 1 : 0;
    return UInt32ToString(integer);
}

bool RLStringUtils::StringToBoolean(const wchar_t* s)
{
    uint32_t integer = StringToUInt32(s, nullptr);
    return integer != 0 ? true : false;
}


int32_t RLStringUtils::CompareNoCase(const std::wstring& lhs, const std::wstring& rhs)
{
    return RLStringUtils::CompareNoCase(lhs.c_str(),rhs.c_str(),std::max(lhs.size(),rhs.size()));
}

int32_t RLStringUtils::CompareNoCase(const wchar_t* cs, const wchar_t* ct, size_t count)
{
    if (count == 0)
    {
        return 0;
    }
    if (cs == ct)
    {
        return 0;
    }
    do
    {
        if (towupper(*cs) != towupper(*ct++))
        {
            return towupper(*cs) - towupper(*--ct);
        }
        if (*cs++ == 0)
        {
            break;
        }
    }while (--count != 0);
    return 0;
}

bool RLStringUtils::IsEqualNoCase(const std::wstring& lhs, const std::wstring& rhs)
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }
    return IsEqualNoCasePrivate(lhs.c_str(), rhs.c_str());
}

bool RLStringUtils::IsEqualNoCase(const wchar_t* lhs, const std::wstring& rhs)
{
    if (lhs == nullptr)
    {
        return false;
    }
    return IsEqualNoCasePrivate(lhs, rhs.c_str());
}

bool RLStringUtils::IsEqualNoCase(const std::wstring& lhs, const wchar_t* rhs)
{
    if (rhs == nullptr)
    {
        return false;
    }
    return IsEqualNoCasePrivate(lhs.c_str(), rhs);
}

bool RLStringUtils::IsEqualNoCase(const wchar_t* lhs, const wchar_t* rhs)
{
    if(lhs == nullptr)
    {
        return (rhs == nullptr) ? true : false;
    }
    else if(rhs == nullptr)
    {
        return (lhs == nullptr) ? true : false;
    }
    return IsEqualNoCasePrivate(lhs, rhs);
}

bool RLStringUtils::IsEqualNoCasePrivate(const wchar_t* lhs, const wchar_t* rhs)
{
    if (lhs == rhs)
    {
        return true;
    }
    for (;;)
    {
        if (*lhs == *rhs)
        {
            if (*lhs++ == 0)
            {
                return true;
            }
            rhs++;
            continue;
        }
        if (towupper(*lhs++) == towupper(*rhs++))
        {
            continue;
        }
        return false;
    }
}

int32_t RLStringUtils::Compare(const std::wstring& lhs, const std::wstring& rhs)
{
    return lhs.compare(rhs);
}

bool RLStringUtils::WildcardCompare(const wchar_t* sPattern,
                                    const wchar_t* sFileName,
                                    bool bNoCase)
{
    if( (sPattern == nullptr) || (sFileName == nullptr) )
    {
        return false;
    }
    const wchar_t* pStar  = 0;
    const wchar_t* pName  = 0;

    while(*sFileName)
    {
        switch (*sPattern)
        {
        case L'?':
            ++sFileName; 
            ++sPattern;
            continue;
        case L'*':
            if (!*++sPattern)
            {
                return true;
            }
            pStar = sPattern;
            pName = sFileName + 1;
            continue;
        default:
            if(bNoCase) 
            {
                if (RLStringUtils::CharToLower(*sFileName) == RLStringUtils::CharToLower(*sPattern))     // if equal
                {
                    ++sFileName; 
                    ++sPattern; 
                    continue;
                }
            }
            else if (*sFileName == *sPattern)    // bNoCase == false, 
            {                                    // compare chars directly
                ++sFileName; 
                ++sPattern; 
                continue;
            }

            // chars are NOT equal, 
            // if there was no '*' thus far, strings don't match
            if(!pStar)
            {
                return false;
            }

            // go back to last '*' character
            sPattern = pStar;
            sFileName = pName++;
            continue;
        }
    }
    // check is there anything left after last '*'
    while (*sPattern == L'*') ++sPattern;
    return (!*sPattern);
}

size_t RLStringUtils::StringLen(const wchar_t* s)
{
    if(s == nullptr)
    {
        return 0;
    }
    size_t i = 0;
    for (i = 0; s[i] != L'\0'; ++i);
    {
        return i;
    }
    return 0;
}

size_t RLStringUtils::StringLen(const char* s)
{
    if(s == nullptr)
    {
        return 0;
    }
    size_t i = 0;
    for (i = 0; s[i] != '\0'; ++i);
    {
        return i;
    }
    return 0;
}

wchar_t* RLStringUtils::StringCopy(wchar_t* dest, const wchar_t* src)
{
    if( (dest == nullptr) || (src == nullptr) )
    {
        return nullptr;
    }
    wchar_t* destStart = dest;
    while ((*dest++ = *src++) != 0);
    return destStart;
}

wchar_t RLStringUtils::CharToUpper(wchar_t ch)
{
    return ::towupper(ch);
}

wchar_t RLStringUtils::CharToLower(wchar_t ch)
{
    return ::towlower(ch);
}

void RLStringUtils::MakeUpper(std::wstring& str)
{
    std::wstring::size_type size = str.size();
    std::wstring::size_type index = 0;
    for(; index < size; ++index)
    {
        str[index] = RLStringUtils::CharToUpper(str[index]);
    }
}

void RLStringUtils::MakeLower(std::wstring& str)
{
    std::wstring::size_type size = str.size();
    std::wstring::size_type index = 0;
    for(; index < size; ++index)
    {
        str[index] = RLStringUtils::CharToLower(str[index]);
    }
}

std::wstring RLStringUtils::Left(const std::wstring& str, int32_t count)
{
    if(count < 0)
    {
        return std::wstring();
    }
    return str.substr(0,count);
}

std::wstring RLStringUtils::Right(const std::wstring& str, int32_t count)
{
    if(count < 0)
    {
        return std::wstring();
    }
    std::wstring::size_type size = str.size();
    if(count > (int32_t)size)
    {
        count = (int32_t)size;
    }
    return str.substr(str.size() - count,count);
}
    
std::wstring RLStringUtils::Mid(const std::wstring& str, int32_t startIndex, std::wstring::size_type count)
{
    if(startIndex < 0)
    {
        return std::wstring();
    }    
    std::wstring::size_type size = str.size();
    if(startIndex > (int32_t)size - 1)
    {
        return std::wstring();
    }
    if(count == std::wstring::npos)
    {
        return str.substr(startIndex,std::wstring::npos);
    }
    else
    {
        if((startIndex + count) > size)
        {
            count = std::wstring::npos;
        }
        return str.substr(startIndex,count);
    }
}

const wchar_t* RLStringUtils::FindStr(const wchar_t* str, const wchar_t* searchStr)
{
    const wchar_t* ret = nullptr;
    if (str == nullptr || searchStr == nullptr)
    {
        return nullptr;
    }
    ret = wcsstr(str, searchStr);
    return ret;
}

const wchar_t* RLStringUtils::FindChr(const wchar_t* data, wchar_t ch)
{
    return ::wcschr(data,ch);
}

std::wstring RLStringUtils::CoverSbcToDbc(const std::wstring& sbcStr)
{
    std::wstring dbcStr;
    int32_t nLength = (int32_t)sbcStr.size();
    if (nLength <= 0 || nLength >= 65536)
    {
        return dbcStr;
    }
    wchar_t* dbc = new wchar_t[sizeof(wchar_t) * nLength + 1];
    if (dbc == nullptr)
    {
        return dbcStr;
    }
    memset(dbc, 0, sizeof(wchar_t) * nLength + 1);
    ::StringCchCopy(dbc, sizeof(wchar_t) * nLength + 1, sbcStr.c_str());
    for (int32_t i = 0; i < nLength; i++)
    {
        if (dbc[i] == 12288)
        {
            dbc[i] = (wchar_t)32;
            continue;
        }
        if (dbc[i] > 65280 && dbc[i] < 65375)
        {
            dbc[i] = (wchar_t)(dbc[i] - 65248);
        }
    }
    Format(dbcStr, L"%s", dbc);
    delete[] dbc;
    dbc = nullptr;
    return dbcStr;
}

}//namespace RL
