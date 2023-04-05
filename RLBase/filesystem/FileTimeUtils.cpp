#include "FileTimeUtils.h"
#include "base/WindowsDefs.h"

namespace RL
{

bool FileTimeUtils::IsValidFileTime(const FileTime& fileTime)
{
    return (fileTime.highDateTime != 0) || (fileTime.lowDateTime != 0);
}

bool FileTimeUtils::LocalFileTimeToFileTime(const FileTime& fileTime, FileTime& utcFileTime)
{
    FILETIME src = { 0 };
    src.dwHighDateTime = fileTime.highDateTime ;
    src.dwLowDateTime  = fileTime.lowDateTime ;
    FILETIME dst = { 0 };
    BOOL ret = ::LocalFileTimeToFileTime(&src,&dst);
    if(ret)
    {
        utcFileTime.highDateTime = dst.dwHighDateTime ;
        utcFileTime.lowDateTime  = dst.dwLowDateTime ;
        return true ;
    }
    return false ;
}
   
bool FileTimeUtils::FileTimeToLocalFileTime(const FileTime& utcFileTime, FileTime& fileTime)
{
    FILETIME src = { 0 };
    src.dwHighDateTime = utcFileTime.highDateTime ;
    src.dwLowDateTime  = utcFileTime.lowDateTime ;
    FILETIME dst = { 0 };
    BOOL ret = ::FileTimeToLocalFileTime(&src, &dst);
    if(ret)
    {
        fileTime.highDateTime = dst.dwHighDateTime ;
        fileTime.lowDateTime  = dst.dwLowDateTime ;
        return true ;
    }
    return false ;
}

int32_t FileTimeUtils::CompareFileTime(const FileTime* time1, const FileTime* time2)
{
    if( (time1 == NULL) && (time2 == NULL) )
    {
        return 0 ;
    }
    if(time1 == NULL)
    {
        return -1 ;
    }
    if(time2 == NULL)
    {
        return 1 ;
    }
    if (time1->highDateTime < time2->highDateTime)
    {
        return -1;
    }
    if (time1->highDateTime > time2->highDateTime)
    {
        return 1;
    }
    if (time1->lowDateTime < time2->lowDateTime)
    {
        return -1;
    }
    if (time1->lowDateTime > time2->lowDateTime)
    {
        return 1;
    }
    return 0;
}

bool FileTimeUtils::DosTimeToFileTime(uint32_t dosTime, FileTime& fileTime)
{
    FILETIME time = {0};
    if(::DosDateTimeToFileTime((uint16_t)(dosTime >> 16), (uint16_t)(dosTime & 0xFFFF), &time) != FALSE)
    {
        fileTime.lowDateTime  = time.dwLowDateTime ;
        fileTime.highDateTime = time.dwHighDateTime ;
        return true ;
    }
    else
    {
        return false ;
    }
}

bool FileTimeUtils::FileTimeToDosTime(const FileTime& fileTime, uint32_t &dosTime)
{ 
    FILETIME time = { 0 };
    time.dwLowDateTime = fileTime.lowDateTime ;
    time.dwHighDateTime = fileTime.highDateTime ;
    WORD datePart = 0 ;
    WORD timePart = 0 ;
    if (!::FileTimeToDosDateTime(&time, &datePart, &timePart))
    {
        const uint32_t kHighDosTime = 0xFF9FBF7D ;
        const uint32_t kLowDosTime = 0x210000 ;
        dosTime = (time.dwHighDateTime >= 0x01C00000) ? kHighDosTime : kLowDosTime;
        return false;
    }
    dosTime = (((uint32_t)datePart) << 16) + timePart;
    return true ;   
}

static const uint32_t kNumTimeQuantumsInSecond = 10000000;
static const uint32_t kFileTimeStartYear       = 1601;
static const uint32_t kUnixTimeStartYear       = 1970;
static const uint64_t kUnixTimeOffset          = (uint64_t)60 * 60 * 24 * (89 + 365 * (kUnixTimeStartYear - kFileTimeStartYear));
static const uint64_t kNumSecondsInFileTime    = (uint64_t)(int64_t)-1 / kNumTimeQuantumsInSecond;

void FileTimeUtils::UnixTimeToFileTime(uint32_t unixTime, FileTime& fileTime)
{
    uint64_t v = (kUnixTimeOffset + (uint64_t)unixTime) * kNumTimeQuantumsInSecond;
    fileTime.lowDateTime  = (uint32_t)v;
    fileTime.highDateTime = (uint32_t)(v >> 32);
}

bool FileTimeUtils::FileTimeToUnixTime(const FileTime& fileTime, uint32_t& unixTime)
{
    uint64_t winTime = (((uint64_t)fileTime.highDateTime) << 32) + fileTime.lowDateTime;
    winTime /= kNumTimeQuantumsInSecond;
    if (winTime < kUnixTimeOffset)
    {
        unixTime = 0;
        return false;
    }
    winTime -= kUnixTimeOffset;
    if (winTime > 0xFFFFFFFF)
    {
        unixTime = 0xFFFFFFFF;
        return false;
    }
    unixTime = (uint32_t)winTime;
    return true;
}

bool FileTimeUtils::UnixTime64ToFileTime(int64_t unixTime, FileTime& fileTime)
{
    int64_t v = (int64_t)kUnixTimeOffset + unixTime;
    if (unixTime < 0)
    {
        if (v < 0)
        {
            fileTime.lowDateTime = fileTime.highDateTime = 0;
            return false;
        }
    }
    else
    {
        if (v < unixTime || v > kNumSecondsInFileTime)
        {
            fileTime.lowDateTime = fileTime.highDateTime = (uint32_t)(int32_t)-1;
            return false;
        }
    }
    uint64_t v2 = (uint64_t)v * kNumTimeQuantumsInSecond;
    fileTime.lowDateTime =  (uint32_t)v2;
    fileTime.highDateTime = (uint32_t)(v2 >> 32);
    return true;
}

bool FileTimeUtils::FileTimeToUnixTime64(const FileTime& fileTime, int64_t& unixTime)
{
    uint64_t winTime = (((uint64_t)fileTime.highDateTime) << 32) + fileTime.lowDateTime;
    unixTime = (int64_t)(winTime / kNumTimeQuantumsInSecond) - kUnixTimeOffset;
    return true ;
}

bool FileTimeUtils::GetSecondsSince1601(uint32_t year,
                                          uint32_t month, 
                                          uint32_t day,
                                          uint32_t hour, 
                                          uint32_t min, 
                                          uint32_t sec, 
                                          uint64_t& resSeconds)
{
    resSeconds = 0;
    if ( year < 1601 || year >= 10000 || month < 1 || month > 12 ||
         day < 1 || day > 31 || hour > 23 || min > 59 || sec > 59)
    {
        return false;
    }
    uint32_t numYears = year - 1601;
    uint32_t numDays = numYears * 365 + numYears / 4 - numYears / 100 + numYears / 400;
    uint8_t ms[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        ms[1] = 29;
    }
    month--;
    for (unsigned i = 0; i < month; i++)
    {
        numDays += ms[i];
    }
    numDays += day - 1;
    resSeconds = ((uint64_t)(numDays * 24 + hour) * 60 + min) * 60 + sec;
    return true;
}

void FileTimeUtils::GetCurrentUtcFileTime(FileTime& fileTime)
{
    SYSTEMTIME st = { 0 };
    ::GetSystemTime(&st);
    FILETIME time = { 0 };
    ::SystemTimeToFileTime(&st, &time);
    fileTime.lowDateTime  = time.dwLowDateTime ;
    fileTime.highDateTime = time.dwHighDateTime ;
}

uint64_t FileTimeUtils::ConvertFromFileTime(const FileTime& fileTime)
{
    uint64_t value = (uint64_t)fileTime.highDateTime ;
    value = (value << 32) + fileTime.lowDateTime ;
    return value ;
}

void FileTimeUtils::ConvertToFileTime(uint64_t time, FileTime& fileTime)
{
    fileTime.highDateTime = (uint32_t)(time >> 32);
    fileTime.lowDateTime  = (uint32_t)((time << 32) >> 32);
}

static wchar_t* UIntToStringSpec(wchar_t c, uint32_t value, wchar_t* s, int32_t numPos)
{
    if (c != 0)
    {
        *s++ = c;
    }
    wchar_t temp[16];
    int32_t pos = 0;
    do
    {
        temp[pos++] = (wchar_t)(L'0' + value % 10);
        value /= 10 ;
    } while (value != 0);
    int32_t i = 0 ;
    for (i = 0; i < numPos - pos; i++)
    {
        *s++ = L'0';
    }
    do
    {
        *s++ = temp[--pos];
    }
    while (pos > 0);
    *s = L'\0';
    return s;
}

std::wstring FileTimeUtils::FileTimeToString(const FileTime& fileTime,
                                             bool includeTime, 
                                             bool includeSeconds)
{
    wchar_t result[64] = {0};
    wchar_t* s = result ;
    FILETIME time = { 0 };
    time.dwLowDateTime  = fileTime.lowDateTime ;
    time.dwHighDateTime = fileTime.highDateTime ;
    SYSTEMTIME st = { 0 };
    if(::FileTimeToSystemTime(&time, &st) == FALSE)
    {
        return std::wstring();
    }
    s = UIntToStringSpec(0, st.wYear, s, 4);
    s = UIntToStringSpec(L'-', st.wMonth, s, 2);
    s = UIntToStringSpec(L'-', st.wDay, s, 2);
    if (includeTime)
    {
        s = UIntToStringSpec(L' ', st.wHour, s, 2);
        s = UIntToStringSpec(L':', st.wMinute, s, 2);
        if (includeSeconds)
        {
            UIntToStringSpec(L':', st.wSecond, s, 2);
        }
    }
    return std::wstring(result);
}

std::wstring FileTimeUtils::FileTimeToLocalTimeString(const FileTime& fileTime,
                                                      bool includeTime,
                                                      bool includeSeconds)
{
    wchar_t result[64] = { 0 };
    wchar_t* s = result;

    DWORD64 ddwUniversalTime = fileTime.highDateTime;
    ddwUniversalTime = ddwUniversalTime << 32;
    ddwUniversalTime += fileTime.lowDateTime;

    //因为FILETIME的时间单位是100个亿分之一秒，然后TIME_ZONE_INFORMATION的时间单位是分，所以这里需要乘以600000000
    TIME_ZONE_INFORMATION defaultTimeZone = { 0 };
    DWORD dwResult = ::GetTimeZoneInformation(&defaultTimeZone);
    if (dwResult == TIME_ZONE_ID_INVALID)
    {
        return std::wstring();
    }

    DWORD64 ddwBias = std::abs(defaultTimeZone.Bias);
    ddwBias *= 600000000;

    //转换公式为：LOCAL_TIME = UTC - BIAS  
    DWORD64 ddwLocalTime = 0;
    if (defaultTimeZone.Bias > 0)
    {
        ddwLocalTime = ddwUniversalTime - ddwBias;
    }
    else if (defaultTimeZone.Bias < 0)
    {
        ddwLocalTime = ddwUniversalTime + ddwBias;
    }

    //将DWORD64数值转换为FILETIME格式  
    FILETIME ftLocalTime = { 0 };
    ftLocalTime.dwLowDateTime = static_cast<DWORD>(ddwLocalTime);
    ftLocalTime.dwHighDateTime = static_cast<DWORD>(ddwLocalTime >> 32);

    SYSTEMTIME st = {0};
    if (::FileTimeToSystemTime(&ftLocalTime, &st) == FALSE)
    {
        return std::wstring();
    }
    s = UIntToStringSpec(0, st.wYear, s, 4);
    s = UIntToStringSpec(L'-', st.wMonth, s, 2);
    s = UIntToStringSpec(L'-', st.wDay, s, 2);
    if (includeTime)
    {
        s = UIntToStringSpec(L' ', st.wHour, s, 2);
        s = UIntToStringSpec(L':', st.wMinute, s, 2);
        if (includeSeconds)
        {
            UIntToStringSpec(L':', st.wSecond, s, 2);
        }
    }
    return std::wstring(result);
}

}//namespace RL
