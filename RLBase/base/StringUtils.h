#ifndef __RL_StringUtils_h_
#define __RL_StringUtils_h_ 1

#include <string>
#include <stdarg.h>

namespace RL
{

/** 字符串转换辅助类
*/
class StringUtils
{
public:
    /** 去除左侧指定字符
    @param [in,out] str 需要操作的字符串
    @param [in] value 需要Trim的字符列表
    */
    static void TrimLeft(std::wstring& str, const wchar_t* value = L" \r\t\n");
        
    /** 去除右侧指定字符
    @param [in,out] str 需要操作的字符串
    @param [in] value 需要Trim的字符列表
    */
    static void TrimRight(std::wstring& str, const wchar_t* value = L" \r\t\n");
        
    /** 去除左右两侧指定字符
    @param [in,out] str 需要操作的字符串
    @param [in] value 需要Trim的字符列表
    */
    static void Trim(std::wstring& str, const wchar_t* value = L" \r\t\n");
        
        /** 格式化字符串
    @param [in,out] str 结果字符串
    @param [in] fmt 格式化字符
    @param [in] ... 可变参数列表
    */
    static void Format(std::wstring& str, const wchar_t* fmt , ...);
        
    /** 格式化字符串
    @param [out] buf 结果缓冲区
    @param [in] size 缓冲区大小
    @param [in] format 格式化字符
    @param [in] args 可变参数列表
    @return 转换结果： 0 表示成功, -1 表示失败，1 表示缓冲区不够
    */
    static int32_t FormatToBuffer(wchar_t* buf, int32_t size ,const wchar_t* format, va_list args);
    
    /** 在字符串中替换子字符串
    @param [in,out] str 需要操作的字符串
    @param [in] from 被替换的字符串
    @param [in] to   替换成的字符串
    */
    static void Replace(std::wstring& str ,const wchar_t* from, const wchar_t* to);
        
    /** 在字符串中替换子字符
    @param [in,out] str 需要操作的字符串
    @param [in] from 被替换的字符串
    @param [in] to   替换成的字符串
    */
    static void Replace(std::wstring& str ,const wchar_t from, const wchar_t to);
        
public:    
    /** 32位有符号整型转成字符串
    @param [in] value 整型值
    @return 返回转换后的字符串值
    */
    static std::wstring Int32ToString(int32_t value );
    
    /** 32位无符号整型转成字符串
    @param [in] value 整型值
    @return 返回转换后的字符串值
    */
    static std::wstring UInt32ToString(uint32_t value );
    
    /** 32位无符号整型转成十六进制字符串
    @param [in] value 整型?
    @return 返回转换后的字符串值
    */
    static std::wstring UInt32ToHex(uint32_t value );
    
    /** 64位无符号整型转成宽字节字符串
    @param [in] value 整型值
    @param [out] s 返回转换后的字符串，缓冲区大小内部不检查
    */
    static void UInt64ToString(uint64_t value, wchar_t* s);
    
    /** 64位有符号整型转成宽字节字符串
    @param [in] value 整型值
    @param [out] s 返回转换后的字符串，缓冲区大小内部不检查
    */
    static void Int64ToString(int64_t value, wchar_t *s);
    
    /** 64位有符号整型转成字符串
    @param [in] value 整型值
    @return 返回转换后的字符串值
    */
    static std::wstring Int64ToString(int64_t value );
    
    /** 64位无符号整型转成字符串
    @param [in] value 整型值
    @return 返回转换后的字符串值
    */
    static std::wstring UInt64ToString(uint64_t value );
    
    /** 布尔值转为字符串
    @param [in] value 布尔值
    @return 返回转换后的字符串值
    */
    static std::wstring BooleanToString(bool value);
    
    /** 宽字节字符串转成64位无符号整型
    @param [in] s 字符串起始地址
    @param [out] end 转换截止的字符串地址，可选参数
    @return 返回转换后整型值
    */
    static uint64_t StringToUInt64(const wchar_t* s, const wchar_t** end);
    
    /** 宽字节字符串转成32位无符号整型
    @param [in] s 字符串起始地址
    @param [out] end 转换截止的字符串地址，可选参数
    @return 返回转换后整型值
    */
    static uint32_t StringToUInt32(const wchar_t* s, const wchar_t** end);
    
    /** 字符串转为布尔值
    @param [in] s 字符串起始地址
    @return 返回转换后的字符串值
    */
    static bool StringToBoolean(const wchar_t* s);
    
public:
        /** 比较字符串，不区分大小写
    @param [in] lhs 左值字符串
    @param [in] rhs 右值字符串
    @return 返回值定义如下：
            0  - 相等
         >= 1  - lhs > rhs
         <=-1  - lhs < rhs
    */
    static int32_t CompareNoCase(const std::wstring& lhs, const std::wstring& rhs);

    /** 比较字符串，不区分大小写
    @param [in] lhs 左值字符串
    @param [in] rhs 右值字符串
    @return true 相等 false 不相等
    */
    static bool IsEqualNoCase(const std::wstring& lhs, const std::wstring& rhs);
    
    /** 比较字符串，不区分大小写
    @param [in] lhs 左值字符串
    @param [in] rhs 右值字符串
    @return true 相等 false 不相等
    */
    static bool IsEqualNoCase(const wchar_t* lhs, const std::wstring& rhs);

    /** 比较字符串，不区分大小写
    @param [in] lhs 左值字符串
    @param [in] rhs 右值字符串
    @return true 相等 false 不相等
    */
    static bool IsEqualNoCase(const std::wstring& lhs, const wchar_t* rhs);

    /** 比较字符串，不区分大小写
    @param [in] lhs 左值字符串，内部不判断lhs是否为空
    @param [in] rhs 右值字符串，内部不判断rhs是否为空
    @return true 相等 false 不相等
    */
    static bool IsEqualNoCase(const wchar_t* lhs, const wchar_t* rhs);

    /** 比较字符串，区分大小写
    @param [in] lhs 左值字符串
    @param [in] rhs 右值字符串
    @return 返回值定义如下：
            0  - 相等
            1  - lhs > rhs
            -1 - lhs < rhs
    */
    static int32_t Compare(const std::wstring& lhs, const std::wstring& rhs);
        
        /** 字符串的通配符比较, 通配符为 * 与 ?
    @param [in] sPattern 含有通配符的字符串
    @param [in] sFileName 需要进行匹配比较的字符串
    @param [in] bNoCase 是否区分大小写，true 表示不区分大小写, false表示区分大小写
    @return 返回true表示匹配成功，否则匹配失败
    */
    static bool WildcardCompare(const wchar_t* sPattern,
                                const wchar_t* sFileName,
                                bool bNoCase);    
       
    /** 比较字符串，不区分大小写
    @param [in] cs 左值字符串
    @param [in] ct 右值字符串
    @param [in] count 最多比较的字符数
    @return 返回值定义如下：
            0  - 相等
          >= 1  - lhs > rhs
          <= -1 - lhs < rhs
    */
    static int32_t CompareNoCase(const wchar_t* cs, const wchar_t* ct, size_t count);

public:  
    /** 获取字符串长度
    @param [in] s 字符串起始地址
    @return 返回字符串长度
    */
    static size_t StringLen(const wchar_t* s);
    
    /** 获取字符串长度
    @param [in] s 字符串起始地址
    @return 返回字符串长度
    */
    static size_t StringLen(const char* s);
    
    /** 字符串复制, 不做缓冲区长度检查
    @param [in] src 源字符串地址
    @param [out] dest 目标缓冲区地址
    @return 返回dest
    */
    static wchar_t* StringCopy(wchar_t* dest, const wchar_t* src);
    
    /** 字符转换成大写
    @param [in] ch 需要转换的字符串
    @return 转换结果字符
    */
    static wchar_t CharToUpper(wchar_t ch);
    
    /** 字符转换成小写
    @param [in] ch 需要转换的字符串
    @return 转换结果字符
    */
    static wchar_t CharToLower(wchar_t ch);
                 
    /** 转换为大写
    @param [in,out] str 需要操作的字符串
    */
    static void MakeUpper(std::wstring& str);
    
    /** 转换为小写
    @param [in,out] str 需要操作的字符串
    */
    static void MakeLower(std::wstring& str);
    
    /** 取左侧子串
    @param [in] str 需要操作的字符串
    @param [in] count 需要取的字符个数
    @return 返回子串
    */
    static std::wstring Left(const std::wstring& str, int32_t count);
    
    /** 取右侧子串
    @param [in] str 需要操作的字符串
    @param [in] count 需要取的字符个数
    @return 返回子串
    */
    static std::wstring Right(const std::wstring& str, int32_t count);
    
    /** 取子串
    @param [in] str 需要操作的字符串
    @param [in] startIndex 起始下标值
    @param [in] count 字符个数，如果为std::wstring::npos，则表示从startIndex到字符串结束
    @return 返回子串
    */
    static std::wstring Mid(const std::wstring& str, int32_t startIndex, std::wstring::size_type count = std::wstring::npos);

    /** 在字符串中查找子串 大小写敏感
    @param [in] str         代查找串
    @param [in] searchStr   要查找的子串
    @return 返回找到的子串未知,如果未找到,返回NULL
    */
    static const wchar_t* FindStr(const wchar_t* str, const wchar_t* searchStr);
    
    /** 在字符串中查找字符
    @param [in] data 字符串起始地址
    @param [in] ch 需要查找的字符
    @return 查找到的字符串地址，找不到则返回NULL
    */
    static const wchar_t* FindChr(const wchar_t* data, wchar_t ch);

    /** 将字符串全角转换为半角
    @param [in] sbc 全角字符串
    */
    static std::wstring CoverSbcToDbc(const std::wstring &sbc);

private:

    /** 比较字符串，不区分大小写
    @param [in] lhs 左值字符串，内部不判断lhs是否为空
    @param [in] rhs 右值字符串，内部不判断rhs是否为空
    @return true 相等 false 不相等
    */
    static bool IsEqualNoCasePrivate(const wchar_t* lhs, const wchar_t* rhs);

};

}//namespace RL

#endif //__RL_StringUtils_h_
