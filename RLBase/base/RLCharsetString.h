#ifndef __RLCharsetString_h_
#define __RLCharsetString_h_ 1

#include <string>

namespace RL
{

/** 支持的字符集定义
*/
enum class RLCharsetType
{
    UNKNOWN,
    ANSI,
    UNICODE_UTF7,
    UNICODE_UTF8,
    UNICODE_UTF16,
    UNICODE_UTF16_BE,
    UNICODE_UTF16_LE,
    UNICODE_UTF32,
    UNICODE_UTF32_BE,
    UNICODE_UTF32_LE
};

/** 字符串字符集辅助类
*/
class RLCharsetString
{   
    /** 获取指定编码的BOM头长度
    @param [in] charsetType 编码类型
    */
    static uint32_t GetBOMSize(RLCharsetType charsetType);
    
    /** 检测数据的字符集类型, 根据BOM头进行检测
    @param [in] bytes 数据起始地址
    @param [in] dataLen 数据长度
    @return 返回字符集类型
    */
    static RLCharsetType GetDataCharset(const unsigned char* bytes, uint32_t dataLen);

    /** 将流数据转换为字符串, 根据BOM头进行检测类型，如果检测失败则按ANSI字符集进行转码
    @param [in] bytes 数据起始地址, 数据为未知编码数据
    @param [in] dataLen 数据长度
    @return 返回Unicode字符串值
    */
    static std::wstring GetDataString(const unsigned char* bytes, uint32_t dataLen);
};

}//namespace RL

#endif //__RLCharsetString_h_
