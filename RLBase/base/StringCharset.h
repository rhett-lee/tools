#ifndef __RL_StringCharset_h_
#define __RL_StringCharset_h_ 1

#include <string>

namespace RL
{

/** ֧�ֵ��ַ�������
*/
enum class CharsetType
{
    UNKNOWN,
    ANSI,
    UTF8,
    UTF16_LE,
    UTF16_BE
};

/** �ַ����ַ���������
*/
class StringCharset
{   
public:
    /** ��ȡָ�������BOMͷ����
    @param [in] charsetType ��������
    */
    static uint32_t GetBOMSize(CharsetType charsetType);
    
    /** ������ݵ��ַ�������, ���������ݵ�BOMͷ���м��
    @param [in] data ������ʼ��ַ
    @param [in] length ���ݳ���
    @return �����ַ������ͣ�������ʧ���򷵻�δ֪����
    */
    static CharsetType GetDataCharsetByBOM(const char* data, uint32_t length);

    /** ������ݵ��ַ�������, ���������ݵ����ͽ��м�⣬�����BOMͷ����
    @param [in] data ������ʼ��ַ
    @param [in] length ���ݳ���
    @return �����ַ������ͣ�������ʧ���򷵻�δ֪����
    */
    static CharsetType GetDataCharset(const char* data, uint32_t length);

    /** ��������ת��Ϊ�ַ���, ���ȸ���BOMͷ���м�����ͣ�������ʧ��������������������
    @param [in] data ������ʼ��ַ, ����Ϊδ֪��������
    @param [in] length ���ݳ���
    @param [out] result ����Unicode�ַ���ֵ
    */
    static bool GetDataAsString(const char* data, uint32_t length, std::wstring& result);

    /** ��������ת��Ϊ�ַ���, ���ȸ���BOMͷ���м�����ͣ�������ʧ��������������������
    @param [in] data ������ʼ��ַ, ����Ϊδ֪��������
    @param [in] length ���ݳ���
    @param [in] inCharsetType ��ȡ�ļ������õı��룬���ΪUNKNOWN���Զ�����ı���������
    @param [out] result ����Unicode�ַ���ֵ
    */
    static bool GetDataAsString(const char* data, uint32_t length, CharsetType inCharsetType, std::wstring& result);

    /** ��������ת��Ϊ�ַ���, ���ȸ���BOMͷ���м�����ͣ�������ʧ��������������������
    @param [in] data ������ʼ��ַ, ����Ϊδ֪��������
    @param [in] length ���ݳ���
    @param [out] result ����Unicode�ַ���ֵ
    @param [out] outCharsetType ��ȡ�ļ������õı�������
    @param [out] bomSize ��ȡ�ļ�ʱ����⵽��Unicode BOMͷ��С
    */
    static bool GetDataAsString(const char* data, uint32_t length, 
                                std::wstring& result, CharsetType& outCharsetType, uint32_t& bomSize);

     /** ��������ת��Ϊ�ַ���, ���ȸ���BOMͷ���м�����ͣ�������ʧ��������������������
    @param [in] data ������ʼ��ַ, ����Ϊδ֪��������
    @param [in] length ���ݳ���
    @param [in] inCharsetType ��ȡ�ļ������õı��룬���ΪUNKNOWN���Զ�����ı���������
    @param [out] result ����Unicode�ַ���ֵ
    @param [out] outCharsetType ��ȡ�ļ������õı�������
    @param [out] bomSize ��ȡ�ļ�ʱ����⵽��Unicode BOMͷ��С
    */
    static bool GetDataAsString(const char* data, uint32_t length, CharsetType inCharsetType,
                                std::wstring& result, CharsetType& outCharsetType, uint32_t& bomSize);

public:
    /** ������֤������ char ���Ƿ�Ϊ GBK ����
    @param [in] stream��ָ�� char ����ָ��
    #param [in] length�����ĳ��ȣ����ֽ�Ϊ��λ
    */
    static bool IsValidateGBKStream(const char* stream, uint32_t length);

    /** ������֤������ char ���Ƿ�Ϊ UTF-8 ����
    @param [in] stream��ָ�� char ����ָ��
    #param [in] length�����ĳ��ȣ����ֽ�Ϊ��λ
    */
    static bool IsValidateUTF8Stream(const char* stream, uint32_t length);

    /** ������֤������ char ���Ƿ�Ϊ UTF16-LE ����
    @param [in] stream��ָ�� char ����ָ��
    #param [in] length�����ĳ��ȣ����ֽ�Ϊ��λ
    */
    static bool IsValidateUTF16LEStream(const char* stream, uint32_t length);

    /** ������֤������ char ���Ƿ�Ϊ UTF16-BE ����
    @param [in] stream��ָ�� char ����ָ��
    #param [in] length�����ĳ��ȣ����ֽ�Ϊ��λ
    */
    static bool IsValidateUTF16BEStream(const char* stream, uint32_t length);
};

}//namespace RL

#endif //__RL_StringCharset_h_
