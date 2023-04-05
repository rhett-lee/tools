#include "StringToken.h"
#include "StringUtils.h"

namespace RL
{

void StringToken::StringToArray(const std::wstring& str,
                                const wchar_t sepChar, 
                                std::vector<std::wstring>& arrayValue)
{
    std::wstring tokenValue ;
    if(str.size() > 0)
    {
        tokenValue.reserve(str.size() > 128 ? 128 : str.size()) ;
    }
    else
    {
        return ;
    }
    size_t index = 0 ;
    for( ; index < str.size() ; ++index)
    {
        wchar_t ch = str[index] ;
        if(sepChar == ch)
        {
            arrayValue.push_back(tokenValue) ;
            tokenValue.clear() ;
        }
        else
        {
            tokenValue += ch ;
        }
    }
    if( (index > 0) && (index == str.size() ) )
    {
        --index ;
        if(str[index] != sepChar)
        {
            arrayValue.push_back(tokenValue) ;
        }
    }
}

void StringToken::StringToArrayA(const std::string& str,
                                 const char sepChar, 
                                 std::vector<std::string>& arrayValue)
{
    std::string tokenValue ;
    if(str.size() > 0)
    {
        tokenValue.reserve(str.size() > 128 ? 128 : str.size()) ;
    }
    else
    {
        return ;
    }
    size_t index = 0 ;
    for( ; index < str.size() ; ++index)
    {
        char ch = str[index] ;
        if(sepChar == ch)
        {
            arrayValue.push_back(tokenValue) ;
            tokenValue.clear() ;
        }
        else
        {
            tokenValue += ch ;
        }
    }
    if( (index > 0) && (index == str.size() ) )
    {
        --index ;
        if(str[index] != sepChar)
        {
            arrayValue.push_back(tokenValue) ;
        }
    }
}

void StringToken::StringToFileNameArray(const std::wstring& str,
                                        std::vector<std::wstring>& arrayValue,
                                        bool skipBlank)
{
    std::wstring tokenValue ;
    const wchar_t sepChar   = L' ' ;
    const wchar_t quoteChar = L'"' ;
    size_t index = 0 ;
    bool isInQuote = false ;
    for( ; index < str.size() ; ++index)
    {
        wchar_t ch = str[index] ;
        if(quoteChar == ch)
        {
            isInQuote = !isInQuote ;
            continue ;
        }
        if( (sepChar == ch) && !isInQuote)
        {
            if (skipBlank)
            {
                StringUtils::Trim(tokenValue) ;
            }
            if(!tokenValue.empty())
            {
                arrayValue.push_back(tokenValue) ;
            }
            tokenValue.clear() ;
        }
        else
        {
            tokenValue += ch ;
        }
    }
    if (skipBlank)
    {
        StringUtils::Trim(tokenValue) ;
    }
    if(!str.empty())
    {
        arrayValue.push_back(tokenValue) ;
    }
}

std::wstring StringToken::FileNameArrayToString(const std::vector<std::wstring>& arrayValue)
{
    const wchar_t sepChar   = L' ' ;
    const wchar_t quoteChar = L'"' ;
    std::wstring str ;
    size_t index = 0 ;
    for( ; index < arrayValue.size() ; ++index)
    {
        const std::wstring& fileName = arrayValue[index] ;
        if(!fileName.empty())
        {
            if(!str.empty())
            {
                str += sepChar ;
            }
            str += quoteChar ;
            str += fileName ;
            str += quoteChar ;
        }
    }
    return str ;
}

}//namespace RL
