#ifndef __RLUnicodeConvert_h_
#define __RLUnicodeConvert_h_ 1

#include <string>

namespace RL
{
/** ����ҳ����Windows API�Ķ�����ͬ
*/
typedef enum
{
    RL_CP_ACP   = 0 ,   //CP_ACP��ANSI����ҳ
    RL_CP_OEMCP = 1 ,   //CP_OEMCP��OEM����ҳ
    RL_CP_UTF8  = 65001 //CP_UTF8��ʹ��UTF-8ת��
}RCCodePage;

/** �ַ����ַ���ת���ࣺĿ�궨λ��ANSI/UTF8/Unicode�����ַ���֮���໥ת��
*/
class RLUnicodeConvert
{   
public:
    /** ���ֽ�ת���ɿ��ֽ�
    @param [in] src Դ�ַ�������
    */
    static std::wstring MultiByteToUnicode(const std::string& src);

    /** ���ֽ�ת���ɿ��ֽڣ���Ĭ�ϴ���ҳת��
    @param [in] src Դ�ַ�������
    @return ת����Ŀ��ֽڱ����ַ���
    */
    static std::wstring MultiByteToUnicode(const char* src);
    
    /** ���ֽ�ת���ɿ��ֽ�
    @param [in] src Դ�ַ�������
    @param [in] len �ַ����ĳ��ȣ����Ϊ-1����Ϊsrc����0��β���ַ���
    @param [in] codePage �ַ�������Ĵ���ҳ���ɲ��գ�https://learn.microsoft.com/zh-cn/windows/win32/intl/code-page-identifiers
    */
    static std::wstring MultiByteToUnicode(const char* src, int32_t len, uint32_t codePage);
                                                 
public:    
    /** ���ֽ�ת���ɶ��ֽ�
    @param [in] src Դ�ַ�������
    */                                 
    static std::string UnicodeToMultiByte(const std::wstring& src);

    /** ���ֽ�ת���ɶ��ֽ�, ������Ĭ��CodePageת��
    @param [in] src Դ�ַ�������
    */
    static std::string UnicodeToMultiByte(const wchar_t* src);

    /** ���ֽ�ת���ɶ��ֽ�
    @param [in] src Դ�ַ�������
    @param [in] srcLen Դ�ַ����ĳ��ȣ���Ϊ-1���Զ�����
    @param [in] codePage �ַ�������Ĵ���ҳ���ɲ��գ�https://learn.microsoft.com/zh-cn/windows/win32/intl/code-page-identifiers
    */
    static std::string UnicodeToMultiByte(const wchar_t* src, int32_t srcLen,  uint32_t codePage);
                                                
    /** ���ֽ�ת���ɶ��ֽ�
    @param [in] src Դ�ַ�������
    @param [in] codePage �ַ�������Ĵ���ҳ
    @param [in] defaultChar ���޷�ת��ʱ���滻��Ĭ���ַ�
    @param [out] defaultCharWasUsed Ĭ���ַ��Ƿ�ʹ��
    */
    static std::string UnicodeToMultiByte(const std::wstring& src,
                                          uint32_t codePage, 
                                          char defaultChar, 
                                          bool& defaultCharWasUsed);   

public:
    /** UTF8����ת��Unicode����
    @param [in] inBuf �����ַ���
    @param [in] inBufLen �������ݳ��ȣ� ���Ϊ-1���Զ����㳤��
    */
    static std::wstring ConvertUTF8ToUnicode(const char* inBuf, int32_t inBufLen);

    /** UTF8����ת��Unicode����
    */
    static std::wstring ConvertUTF8ToUnicode(const std::string& inBuf);

    /** UTF8����ת��Unicode����
    @param [in] inBuf �����ַ���
    @param [in] inBufLen �������ݳ��ȣ� ���Ϊ-1���Զ����㳤��
    */
    static std::string ConvertUnicodeToUTF8(const wchar_t* inBuf, int32_t inBufLen);

    /** UTF8����ת��Unicode����
    */
    static std::string ConvertUnicodeToUTF8(const std::wstring& inBuf);

public:
    
    /** ����Ĭ�ϵĴ���ҳ
    */
    static void SetDefaultCodePage(uint32_t codePage);

private:    
    /** ���ֽ�ת���ɶ��ֽ�
    @param [in] src Դ�ַ�������
    @param [in] srcLen Դ�ַ����ĳ��ȣ����Ϊ-1��ʾ�Զ�����
    @param [in] codePage �ַ�������Ĵ���ҳ
    @param [in] defaultChar ���޷�ת��ʱ���滻��Ĭ���ַ�
    @param [out] defaultCharWasUsed Ĭ���ַ��Ƿ�ʹ��
    @param [out] result �����Ƿ�ɹ�
    @return ת����Ķ��ֽڱ����ַ���
    */
    static std::string DoUnicodeToMultiByte(const wchar_t* src,
                                            int32_t srcLen,
                                            uint32_t codePage, 
                                            char defaultChar, 
                                            bool& defaultCharWasUsed,
                                            bool& result);
    
    /** ���ֽ�ת���ɿ��ֽ�
    @param [in] src Դ�ַ�������
    @param [in] len �ַ����ĳ��ȣ����Ϊ-1����Ϊsrc����0��β���ַ���
    @param [in] codePage �ַ�������Ĵ���ҳ
    @param [out] result �����Ƿ�ɹ�
    @return ת����Ŀ��ֽڱ����ַ���
    */
    static std::wstring DoMultiByteToUnicode(const char* src, 
                                             int32_t len, 
                                             uint32_t codePage, 
                                             bool& result);
    
private:
    
    /** Ĭ�ϵĴ���ҳ
    */
    static uint32_t s_defaultCodePage;
};

}//namespace RL

#endif //__RLUnicodeConvert_h_
