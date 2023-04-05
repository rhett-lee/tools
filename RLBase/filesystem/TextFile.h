#ifndef __RL_TextFile_h_
#define __RL_TextFile_h_ 1

#include "base/StringCharset.h"
#include <vector>

namespace RL
{

//文本文件管理类，支持ANSI和Unicode编码
class TextFile
{
public:
    /** 读取文件内容
    @param [in] fileName 文件路径
    @param [in] inCharsetType 读取文件所采用的编码，如果为UNKNOWN则自动检测文本编码类型
    @parma [out] fileText 返回读取到的文件内容字符串
    @param [out] outCharsetType 读取文件所采用的编码类型
    @param [out] bomSize 读取文件时，检测到的Unicode BOM头大小
    */
    static bool ReadData(const std::wstring& fileName, 
                         CharsetType inCharsetType, 
                         std::wstring& fileText,
                         CharsetType& outCharsetType,
                         uint32_t& bomSize);
                  
                  
    /** 写入文件
    @param [in] fileName 文件路径
    @parma [in] fileText 文件内容字符串
    @param [in] charsetType 保存文件采用的编码类型
    @param [in] writeBOM 对于Unicode编码，是否写入BOM签名头数据
    */
    static bool WriteData(const std::wstring& fileName, const std::wstring& fileText, CharsetType charsetType, bool writeBOM);

private:
    //读取文件到容器中，文件大小限定在10MB内，调用方需要自己处理字符串的尾零问题。
    static bool ReadBinaryFile(const std::wstring& fileName, std::vector<char>& container);

    //将容器中的二进制数据写入文件
    static bool WriteBinaryFile(const std::wstring& fileName, const std::vector<char>& container);
};

}//namespace RL

#endif //__RL_TextFile_h_
