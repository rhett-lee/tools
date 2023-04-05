#ifndef __RL_FileTimeUtils_h_
#define __RL_FileTimeUtils_h_ 1

#include "FileTime.h"
#include <string>

namespace RL
{
/** 文件时间操作辅助类
*/
class FileTimeUtils
{
public:    
    /** 判断文件时间是否为有效值
    @param [in] fileTime 文件时间值
    */
    static bool IsValidFileTime(const FileTime& fileTime);
    
    /**  本地时间转换成UTC时间
    @param [in] fileTime 本地文件时间
    @param [out] utcFileTime 返回UTC 文件时间
    */
    static bool LocalFileTimeToFileTime(const FileTime& fileTime, FileTime& utcFileTime);
    
    /**  UTC时间转换成本地时间
    @param [in] utcFileTime UTC 文件时间
    @param [out] fileTime 返回本地文件时间
    */
    static bool FileTimeToLocalFileTime(const FileTime& utcFileTime, FileTime& fileTime);
    
    /** 比较文件时间
    @param [in] time1 第一个文件时间
    @param [in] time2 第二个文件时间
    @return 如果相等返回0, 如果 time1 > time2 返回1，如果time1 < time2 返回 -1
    */
    static int32_t CompareFileTime(const FileTime* time1, const FileTime* time2);

    /** 将Dos文件时间转换为本地文件时间
    @param [in] dosTime Unix文件时间
    @param [out] fileTime 返回本地文件时间
    */
    static bool DosTimeToFileTime(uint32_t dosTime, FileTime& fileTime);
    
    /** 将本地文件时间转换为Dos文件时间
    @param [in] fileTime 本地文件时间
    @param [out] dosTime Dos文件时间
    */
    static bool FileTimeToDosTime(const FileTime& fileTime, uint32_t& dosTime);
    
    /** 将Unix文件时间转换为本地文件时间
    @param [in] unixTime Unix文件时间
    @param [out] fileTime 返回本地文件时间
    */
    static void UnixTimeToFileTime(uint32_t unixTime, FileTime& fileTime);
    
    /** 将本地文件时间转换为Unix文件时间
    @param [in] fileTime 本地文件时间
    @param [out] unixTime Unix文件时间
    */
    static bool FileTimeToUnixTime(const FileTime& fileTime, uint32_t& unixTime);

    /** 将Unix文件时间转换为本地文件时间
    @param [in] unixTime Unix文件时间
    @param [out] fileTime 返回本地文件时间
    */
    static bool UnixTime64ToFileTime(int64_t unixTime, FileTime& fileTime);

    /** 将本地文件时间转换为Unix文件时间
    @param [in] fileTime 本地文件时间
    @param [out] unixTime Unix文件时间
    */
    static bool FileTimeToUnixTime64(const FileTime& fileTime, int64_t& unixTime);
    
    /** 获取从1601年起的秒数
    @param [in] year 年
    @param [in] month 月
    @param [in] day 日
    @param [in] hour 时
    @param [in] min 分
    @param [in] sec 秒
    @param [out] resSeconds 返回UTC文件时间
    */
    static bool GetSecondsSince1601(uint32_t year, 
                                    uint32_t month, 
                                    uint32_t day,
                                    uint32_t hour, 
                                    uint32_t min, 
                                    uint32_t sec, 
                                    uint64_t& resSeconds);
    
    /** 获取本地UTC文件时间
    @param [out] fileTime 返回UTC文件时间
    */
    static void GetCurrentUtcFileTime(FileTime& fileTime);
    
    /** 将文件时间转换成64位无符号整型表示
    @param [in] fileTime 文件时间
    @return 返回转换结果
    */
    static uint64_t ConvertFromFileTime(const FileTime& fileTime);
    
    /** 将64位无符号整型表示转换成文件时间
    @param [in] time 64位无符号整型表示的文件时间
    @param [out] fileTime 返回文件时间
    */
    static void ConvertToFileTime(uint64_t time, FileTime& fileTime);
    
    /** 将文件时间转换为字符串形式: 不做时区转换
    @param [in] fileTime 文件时间， 默认是UTC时间
    @param [in] includeTime 是否包含时间（指时分）
    @param [in] includeSeconds 是否包含秒
    @return 返回显示的字符串，如果失败返回空串
    */
    static std::wstring FileTimeToString(const FileTime& fileTime, 
                                         bool includeTime, 
                                         bool includeSeconds);


    /** 将文件时间转换为字符串形式， 并将区转换为本地时间
    @param [in] fileTime 文件时间， UTC时间
    @param [in] includeTime 是否包含时间（指时分）
    @param [in] includeSeconds 是否包含秒
    @return 返回显示的字符串，如果失败返回空串
    */
    static std::wstring FileTimeToLocalTimeString(const FileTime& fileTime, 
                                                  bool includeTime, 
                                                  bool includeSeconds);
};

}//namespace RL

#endif //__RL_FileTimeUtils_h_

