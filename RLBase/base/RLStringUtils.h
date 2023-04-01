#ifndef __RLStringUtils_h_
#define __RLStringUtils_h_ 1

#include <string>
#include <stdarg.h>

namespace RL
{

/** �ַ���ת��������
*/
class RLStringUtils
{
public:
    /** ȥ�����ָ���ַ�
    @param [in,out] str ��Ҫ�������ַ���
    @param [in] value ��ҪTrim���ַ��б�
    */
    static void TrimLeft(std::wstring& str, const wchar_t* value = L" \r\t\n");
        
    /** ȥ���Ҳ�ָ���ַ�
    @param [in,out] str ��Ҫ�������ַ���
    @param [in] value ��ҪTrim���ַ��б�
    */
    static void TrimRight(std::wstring& str, const wchar_t* value = L" \r\t\n");
        
    /** ȥ����������ָ���ַ�
    @param [in,out] str ��Ҫ�������ַ���
    @param [in] value ��ҪTrim���ַ��б�
    */
    static void Trim(std::wstring& str, const wchar_t* value = L" \r\t\n");
        
        /** ��ʽ���ַ���
    @param [in,out] str ����ַ���
    @param [in] fmt ��ʽ���ַ�
    @param [in] ... �ɱ�����б�
    */
    static void Format(std::wstring& str, const wchar_t* fmt , ...);
        
    /** ��ʽ���ַ���
    @param [out] buf ���������
    @param [in] size ��������С
    @param [in] format ��ʽ���ַ�
    @param [in] args �ɱ�����б�
    @return ת������� 0 ��ʾ�ɹ�, -1 ��ʾʧ�ܣ�1 ��ʾ����������
    */
    static int32_t FormatToBuffer(wchar_t* buf, int32_t size ,const wchar_t* format, va_list args);
    
    /** ���ַ������滻���ַ���
    @param [in,out] str ��Ҫ�������ַ���
    @param [in] from ���滻���ַ���
    @param [in] to   �滻�ɵ��ַ���
    */
    static void Replace(std::wstring& str ,const wchar_t* from, const wchar_t* to);
        
    /** ���ַ������滻���ַ�
    @param [in,out] str ��Ҫ�������ַ���
    @param [in] from ���滻���ַ���
    @param [in] to   �滻�ɵ��ַ���
    */
    static void Replace(std::wstring& str ,const wchar_t from, const wchar_t to);
        
public:    
    /** 32λ�з�������ת���ַ���
    @param [in] value ����ֵ
    @return ����ת������ַ���ֵ
    */
    static std::wstring Int32ToString(int32_t value );
    
    /** 32λ�޷�������ת���ַ���
    @param [in] value ����ֵ
    @return ����ת������ַ���ֵ
    */
    static std::wstring UInt32ToString(uint32_t value );
    
    /** 32λ�޷�������ת��ʮ�������ַ���
    @param [in] value ����?
    @return ����ת������ַ���ֵ
    */
    static std::wstring UInt32ToHex(uint32_t value );
    
    /** 64λ�޷�������ת�ɿ��ֽ��ַ���
    @param [in] value ����ֵ
    @param [out] s ����ת������ַ�������������С�ڲ������
    */
    static void UInt64ToString(uint64_t value, wchar_t* s);
    
    /** 64λ�з�������ת�ɿ��ֽ��ַ���
    @param [in] value ����ֵ
    @param [out] s ����ת������ַ�������������С�ڲ������
    */
    static void Int64ToString(int64_t value, wchar_t *s);
    
    /** 64λ�з�������ת���ַ���
    @param [in] value ����ֵ
    @return ����ת������ַ���ֵ
    */
    static std::wstring Int64ToString(int64_t value );
    
    /** 64λ�޷�������ת���ַ���
    @param [in] value ����ֵ
    @return ����ת������ַ���ֵ
    */
    static std::wstring UInt64ToString(uint64_t value );
    
    /** ����ֵתΪ�ַ���
    @param [in] value ����ֵ
    @return ����ת������ַ���ֵ
    */
    static std::wstring BooleanToString(bool value);
    
    /** ���ֽ��ַ���ת��64λ�޷�������
    @param [in] s �ַ�����ʼ��ַ
    @param [out] end ת����ֹ���ַ�����ַ����ѡ����
    @return ����ת��������ֵ
    */
    static uint64_t StringToUInt64(const wchar_t* s, const wchar_t** end);
    
    /** ���ֽ��ַ���ת��32λ�޷�������
    @param [in] s �ַ�����ʼ��ַ
    @param [out] end ת����ֹ���ַ�����ַ����ѡ����
    @return ����ת��������ֵ
    */
    static uint32_t StringToUInt32(const wchar_t* s, const wchar_t** end);
    
    /** �ַ���תΪ����ֵ
    @param [in] s �ַ�����ʼ��ַ
    @return ����ת������ַ���ֵ
    */
    static bool StringToBoolean(const wchar_t* s);
    
public:
        /** �Ƚ��ַ����������ִ�Сд
    @param [in] lhs ��ֵ�ַ���
    @param [in] rhs ��ֵ�ַ���
    @return ����ֵ�������£�
            0  - ���
         >= 1  - lhs > rhs
         <=-1  - lhs < rhs
    */
    static int32_t CompareNoCase(const std::wstring& lhs, const std::wstring& rhs);

    /** �Ƚ��ַ����������ִ�Сд
    @param [in] lhs ��ֵ�ַ���
    @param [in] rhs ��ֵ�ַ���
    @return true ��� false �����
    */
    static bool IsEqualNoCase(const std::wstring& lhs, const std::wstring& rhs);
    
    /** �Ƚ��ַ����������ִ�Сд
    @param [in] lhs ��ֵ�ַ���
    @param [in] rhs ��ֵ�ַ���
    @return true ��� false �����
    */
    static bool IsEqualNoCase(const wchar_t* lhs, const std::wstring& rhs);

    /** �Ƚ��ַ����������ִ�Сд
    @param [in] lhs ��ֵ�ַ���
    @param [in] rhs ��ֵ�ַ���
    @return true ��� false �����
    */
    static bool IsEqualNoCase(const std::wstring& lhs, const wchar_t* rhs);

    /** �Ƚ��ַ����������ִ�Сд
    @param [in] lhs ��ֵ�ַ������ڲ����ж�lhs�Ƿ�Ϊ��
    @param [in] rhs ��ֵ�ַ������ڲ����ж�rhs�Ƿ�Ϊ��
    @return true ��� false �����
    */
    static bool IsEqualNoCase(const wchar_t* lhs, const wchar_t* rhs);

    /** �Ƚ��ַ��������ִ�Сд
    @param [in] lhs ��ֵ�ַ���
    @param [in] rhs ��ֵ�ַ���
    @return ����ֵ�������£�
            0  - ���
            1  - lhs > rhs
            -1 - lhs < rhs
    */
    static int32_t Compare(const std::wstring& lhs, const std::wstring& rhs);
        
        /** �ַ�����ͨ����Ƚ�, ͨ���Ϊ * �� ?
    @param [in] sPattern ����ͨ������ַ���
    @param [in] sFileName ��Ҫ����ƥ��Ƚϵ��ַ���
    @param [in] bNoCase �Ƿ����ִ�Сд��true ��ʾ�����ִ�Сд, false��ʾ���ִ�Сд
    @return ����true��ʾƥ��ɹ�������ƥ��ʧ��
    */
    static bool WildcardCompare(const wchar_t* sPattern,
                                const wchar_t* sFileName,
                                bool bNoCase);    
       
    /** �Ƚ��ַ����������ִ�Сд
    @param [in] cs ��ֵ�ַ���
    @param [in] ct ��ֵ�ַ���
    @param [in] count ���Ƚϵ��ַ���
    @return ����ֵ�������£�
            0  - ���
          >= 1  - lhs > rhs
          <= -1 - lhs < rhs
    */
    static int32_t CompareNoCase(const wchar_t* cs, const wchar_t* ct, size_t count);

public:  
    /** ��ȡ�ַ�������
    @param [in] s �ַ�����ʼ��ַ
    @return �����ַ�������
    */
    static size_t StringLen(const wchar_t* s);
    
    /** ��ȡ�ַ�������
    @param [in] s �ַ�����ʼ��ַ
    @return �����ַ�������
    */
    static size_t StringLen(const char* s);
    
    /** �ַ�������, �������������ȼ��
    @param [in] src Դ�ַ�����ַ
    @param [out] dest Ŀ�껺������ַ
    @return ����dest
    */
    static wchar_t* StringCopy(wchar_t* dest, const wchar_t* src);
    
    /** �ַ�ת���ɴ�д
    @param [in] ch ��Ҫת�����ַ���
    @return ת������ַ�
    */
    static wchar_t CharToUpper(wchar_t ch);
    
    /** �ַ�ת����Сд
    @param [in] ch ��Ҫת�����ַ���
    @return ת������ַ�
    */
    static wchar_t CharToLower(wchar_t ch);
                 
    /** ת��Ϊ��д
    @param [in,out] str ��Ҫ�������ַ���
    */
    static void MakeUpper(std::wstring& str);
    
    /** ת��ΪСд
    @param [in,out] str ��Ҫ�������ַ���
    */
    static void MakeLower(std::wstring& str);
    
    /** ȡ����Ӵ�
    @param [in] str ��Ҫ�������ַ���
    @param [in] count ��Ҫȡ���ַ�����
    @return �����Ӵ�
    */
    static std::wstring Left(const std::wstring& str, int32_t count);
    
    /** ȡ�Ҳ��Ӵ�
    @param [in] str ��Ҫ�������ַ���
    @param [in] count ��Ҫȡ���ַ�����
    @return �����Ӵ�
    */
    static std::wstring Right(const std::wstring& str, int32_t count);
    
    /** ȡ�Ӵ�
    @param [in] str ��Ҫ�������ַ���
    @param [in] startIndex ��ʼ�±�ֵ
    @param [in] count �ַ����������Ϊstd::wstring::npos�����ʾ��startIndex���ַ�������
    @return �����Ӵ�
    */
    static std::wstring Mid(const std::wstring& str, int32_t startIndex, std::wstring::size_type count = std::wstring::npos);

    /** ���ַ����в����Ӵ� ��Сд����
    @param [in] str         �����Ҵ�
    @param [in] searchStr   Ҫ���ҵ��Ӵ�
    @return �����ҵ����Ӵ�δ֪,���δ�ҵ�,����NULL
    */
    static const wchar_t* FindStr(const wchar_t* str, const wchar_t* searchStr);
    
    /** ���ַ����в����ַ�
    @param [in] data �ַ�����ʼ��ַ
    @param [in] ch ��Ҫ���ҵ��ַ�
    @return ���ҵ����ַ�����ַ���Ҳ����򷵻�NULL
    */
    static const wchar_t* FindChr(const wchar_t* data, wchar_t ch);

    /** ���ַ���ȫ��ת��Ϊ���
    @param [in] sbc ȫ���ַ���
    */
    static std::wstring CoverSbcToDbc(const std::wstring &sbc);

private:

    /** �Ƚ��ַ����������ִ�Сд
    @param [in] lhs ��ֵ�ַ������ڲ����ж�lhs�Ƿ�Ϊ��
    @param [in] rhs ��ֵ�ַ������ڲ����ж�rhs�Ƿ�Ϊ��
    @return true ��� false �����
    */
    static bool IsEqualNoCasePrivate(const wchar_t* lhs, const wchar_t* rhs);

};

}//namespace RL

#endif //__RLStringUtils_h_
