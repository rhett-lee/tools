#ifndef __RL_StringToken_h_
#define __RL_StringToken_h_ 1

#include <string>
#include <vector>

namespace RL
{

/** 字符串Token工具类
*/
class StringToken
{
public:
    
    /** 根据分隔符，对字符串进行切分
        举例：
            输入："1;2;;"，输出： "1","2",""共3个元素
            输入: "1;2;"，输出： "1","2"共2个元素
            输入: "1;2"，输出： "1","2"共2个元素
    @param [in] str 需要切分的字符串, 如果是以分隔符结束，最后一个分隔符会被忽略
    @param [in] sepChar 分割字符
    @param [out] arrayValue 切分的结果
    */
    static void StringToArray(const std::wstring& str, 
                              const wchar_t sepChar, 
                              std::vector<std::wstring>& arrayValue) ;
    
    /** 根据分隔符，对字符串进行切分
        举例：
            输入："1;2;;"，输出： "1","2",""共3个元素
            输入: "1;2;"，输出： "1","2"共2个元素
            输入: "1;2"，输出： "1","2"共2个元素
    @param [in] str 需要切分的字符串, 如果是以分隔符结束，最后一个分隔符会被忽略
    @param [in] sepChar 分割字符
    @param [out] arrayValue 切分的结果
    */
    static void StringToArrayA(const std::string& str, 
                               const char sepChar, 
                               std::vector<std::string>& arrayValue) ;

    /** 根据空格作为分隔符，对字符串进行切分
    @param [in] str 需要切分的字符串，空格分隔符，如果文件名中有空格，用引号括起来，格式为 "D B" A E 
    @param [out] arrayValue 切分的结果
    @param [in] skipBlank 是否跳过空白符，默认跳过
    */
    static void StringToFileNameArray(const std::wstring& str, 
                                      std::vector<std::wstring>& arrayValue,
                                      bool skipBlank = true) ;

    /** 将文件名转换成空格分隔的字符串
    @param [in] arrayValue 文件名数组
    @return 文件名字符串，用空格分隔，文件名用引号括起来
    */
    static std::wstring FileNameArrayToString(const std::vector<std::wstring>& arrayValue) ;
};

}//namespace RL

#endif //__RLStringToken_h_
