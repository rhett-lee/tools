#ifndef __RLCharsetString_h_
#define __RLCharsetString_h_ 1

#include <string>

namespace RL
{

/** ֧�ֵ��ַ�������
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

/** �ַ����ַ���������
*/
class RLCharsetString
{   
    /** ��ȡָ�������BOMͷ����
    @param [in] charsetType ��������
    */
    static uint32_t GetBOMSize(RLCharsetType charsetType);
    
    /** ������ݵ��ַ�������, ����BOMͷ���м��
    @param [in] bytes ������ʼ��ַ
    @param [in] dataLen ���ݳ���
    @return �����ַ�������
    */
    static RLCharsetType GetDataCharset(const unsigned char* bytes, uint32_t dataLen);

    /** ��������ת��Ϊ�ַ���, ����BOMͷ���м�����ͣ�������ʧ����ANSI�ַ�������ת��
    @param [in] bytes ������ʼ��ַ, ����Ϊδ֪��������
    @param [in] dataLen ���ݳ���
    @return ����Unicode�ַ���ֵ
    */
    static std::wstring GetDataString(const unsigned char* bytes, uint32_t dataLen);
};

}//namespace RL

#endif //__RLCharsetString_h_
