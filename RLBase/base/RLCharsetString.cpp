#include "RLCharsetString.h"
#include "RLWindowsDefs.h"
#include <memory>
#include <cassert>

/////////////////////////////////////////////////////////////////
//RLCharsetString class implementation

namespace RL
{

uint32_t RLCharsetString::GetBOMSize(RLCharsetType charsetType)
{
    switch (charsetType)
    {
    case RLCharsetType::UNICODE_UTF8:
        return 3;
    case RLCharsetType::UNICODE_UTF16:
    case RLCharsetType::UNICODE_UTF16_BE:
    case RLCharsetType::UNICODE_UTF16_LE:
        return 2;
    case RLCharsetType::UNICODE_UTF32:
    case RLCharsetType::UNICODE_UTF32_BE:
    case RLCharsetType::UNICODE_UTF32_LE:
        return 4;
    default:
        return 0;
    }
    return 0;
}

RLCharsetType RLCharsetString::GetDataCharset(const unsigned char* bytes, uint32_t dataLen)
{
    RLCharsetType charsetType = RLCharsetType::UNKNOWN;
    if ((dataLen < 2) || (bytes == NULL))
    {
        return charsetType;
    }

    if ((bytes[0] == 0xFF) && (bytes[1] == 0xFE))
    {
        if ((dataLen >= 4) && (bytes[2] == 0x00) && (bytes[3] == 0x00))
        {
            charsetType = RLCharsetType::UNICODE_UTF32_LE;
        }
        else
        {
            charsetType = RLCharsetType::UNICODE_UTF16_LE;
        }
    }
    else if (bytes[0] == 0xFE && bytes[1] == 0xFF)
    {
        charsetType = RLCharsetType::UNICODE_UTF16_BE;
    }
    else if ((bytes[0] == 0xEF) && (bytes[1] == 0xBB))
    {
        if ((dataLen >= 3) && (bytes[2] == 0xBF))
        {
            charsetType = RLCharsetType::UNICODE_UTF8;
        }
    }
    else if ((dataLen >= 4) &&
             (bytes[0] == 0x00) && (bytes[1] == 0x00) &&
             (bytes[2] == 0xFE) && (bytes[3] == 0xFF))
    {
        charsetType = RLCharsetType::UNICODE_UTF32_BE;
    }
    return charsetType;
}

std::wstring RLCharsetString::GetDataString(const unsigned char* bytes, uint32_t dataLen)
{
    std::wstring result;
    if ((dataLen < 1) || (bytes == NULL))
    {
        return result;
    }
    return result;
}

}//namespace RL
