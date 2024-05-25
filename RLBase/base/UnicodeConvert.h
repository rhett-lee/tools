#ifndef __RL_UnicodeConvert_h_
#define __RL_UnicodeConvert_h_ 1

#include <string>

namespace RL
{
/** 代码页，与Windows API的定义相同
*/
typedef enum
{
    RL_CP_ACP   = 0 ,   //CP_ACP：ANSI代码页
    RL_CP_OEMCP = 1 ,   //CP_OEMCP：OEM代码页
    RL_CP_UTF8  = 65001 //CP_UTF8：使用UTF-8转换
}RLCodePage;

/** 字符串字符集转换类：目标定位于ANSI/UTF8/Unicode三个字符集之间相互转换
*/
class UnicodeConvert
{   
public:
    /** 多字节转换成宽字节，按默认代码页转换
    @param [in] src 源字符串编码
    */
    static std::wstring MultiByteToUnicode(const std::string& src);

    /** 多字节转换成宽字节，按默认代码页转换
    @param [in] src 源字符串编码
    @return 转换后的宽字节编码字符串
    */
    static std::wstring MultiByteToUnicode(const char* src);

    /** 多字节转换成宽字节，按默认代码页转换
    @param [in] src 源字符串编码
    @param [in] len 字符串的长度
    */
    static std::wstring MultiByteToUnicode(const char* src, int32_t len);
    
    /** 多字节转换成宽字节
    @param [in] src 源字符串编码
    @param [in] len 字符串的长度，如果为-1则认为src是以0结尾的字符串
    @param [in] codePage 字符串编码的代码页，用RL_CP_ACP代表本地默认编码
                可参照：https://learn.microsoft.com/zh-cn/windows/win32/intl/code-page-identifiers
    */
    static std::wstring MultiByteToUnicode(const char* src, int32_t len, uint32_t codePage);
                                                 
public:    
    /** 宽字节转换成多字节, 按本地默认编码转换
    @param [in] src 源字符串编码
    */                                 
    static std::string UnicodeToMultiByte(const std::wstring& src);

    /** 宽字节转换成多字节, 按本地默认编码转换
    @param [in] src 源字符串编码
    */
    static std::string UnicodeToMultiByte(const wchar_t* src);

    /** 宽字节转换成多字节, 按本地默认编码转换
    @param [in] src 源字符串编码
    @param [in] srcLen 源字符串的长度
    */
    static std::string UnicodeToMultiByte(const wchar_t* src, int32_t srcLen);

    /** 宽字节转换成多字节
    @param [in] src 源字符串编码
    @param [in] srcLen 源字符串的长度，若为-1则自动计算
    @param [in] codePage 字符串编码的代码页，可参照：https://learn.microsoft.com/zh-cn/windows/win32/intl/code-page-identifiers
    */
    static std::string UnicodeToMultiByte(const wchar_t* src, int32_t srcLen,  uint32_t codePage);
                                                
    /** 宽字节转换成多字节
    @param [in] src 源字符串编码
    @param [in] codePage 字符串编码的代码页
    @param [in] defaultChar 当无法转码时，替换的默认字符
    @param [out] defaultCharWasUsed 默认字符是否使用
    */
    static std::string UnicodeToMultiByte(const std::wstring& src,
                                          uint32_t codePage, 
                                          char defaultChar, 
                                          bool& defaultCharWasUsed);   

public:
    /** UTF8编码转成Unicode编码
    @param [in] inBuf 输入字符串
    @param [in] inBufLen 输入数据长度， 如果为-1则自动计算长度
    */
    static std::wstring UTF8ToUnicode(const char* inBuf, int32_t inBufLen);

    /** UTF8编码转成Unicode编码
    @param [in] inBuf 输入字符串, 自动计算长度
    */
    static std::wstring UTF8ToUnicode(const char* inBuf);

    /** UTF8编码转成Unicode编码
    */
    static std::wstring UTF8ToUnicode(const std::string& inBuf);

    /** UTF8编码转成Unicode编码
    @param [in] inBuf 输入字符串
    @param [in] inBufLen 输入数据长度， 如果为-1则自动计算长度
    */
    static std::string UnicodeToUTF8(const wchar_t* inBuf, int32_t inBufLen);

    /** UTF8编码转成Unicode编码
    @param [in] inBuf 输入字符串, 自动计算长度
    */
    static std::string UnicodeToUTF8(const wchar_t* inBuf);

    /** UTF8编码转成Unicode编码
    */
    static std::string UnicodeToUTF8(const std::wstring& inBuf);

public:
    
    /** 设置默认的代码页
    */
    static void SetDefaultCodePage(uint32_t codePage);

private:    
    /** 宽字节转换成多字节
    @param [in] src 源字符串编码
    @param [in] srcLen 源字符串的长度，如果为-1表示自动计算
    @param [in] codePage 字符串编码的代码页
    @param [in] defaultChar 当无法转码时，替换的默认字符
    @param [out] defaultCharWasUsed 默认字符是否使用
    @param [out] result 返回是否成功
    @return 转换后的多字节编码字符串
    */
    static std::string DoUnicodeToMultiByte(const wchar_t* src,
                                            int32_t srcLen,
                                            uint32_t codePage, 
                                            char defaultChar, 
                                            bool& defaultCharWasUsed,
                                            bool& result);
    
    /** 多字节转换成宽字节
    @param [in] src 源字符串编码
    @param [in] len 字符串的长度，如果为-1则认为src是以0结尾的字符串
    @param [in] codePage 字符串编码的代码页
    @param [out] result 返回是否成功
    @return 转换后的宽字节编码字符串
    */
    static std::wstring DoMultiByteToUnicode(const char* src, 
                                             int32_t len, 
                                             uint32_t codePage, 
                                             bool& result);
    
private:
    
    /** 默认的代码页
    */
    static uint32_t s_defaultCodePage;
};

}//namespace RL

#endif //__RL_UnicodeConvert_h_
