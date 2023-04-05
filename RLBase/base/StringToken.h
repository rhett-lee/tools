#ifndef __RL_StringToken_h_
#define __RL_StringToken_h_ 1

#include <string>
#include <vector>

namespace RL
{

/** �ַ���Token������
*/
class StringToken
{
public:
    
    /** ���ݷָ��������ַ��������з�
        ������
            ���룺"1;2;;"������� "1","2",""��3��Ԫ��
            ����: "1;2;"������� "1","2"��2��Ԫ��
            ����: "1;2"������� "1","2"��2��Ԫ��
    @param [in] str ��Ҫ�зֵ��ַ���, ������Էָ������������һ���ָ����ᱻ����
    @param [in] sepChar �ָ��ַ�
    @param [out] arrayValue �зֵĽ��
    */
    static void StringToArray(const std::wstring& str, 
                              const wchar_t sepChar, 
                              std::vector<std::wstring>& arrayValue) ;
    
    /** ���ݷָ��������ַ��������з�
        ������
            ���룺"1;2;;"������� "1","2",""��3��Ԫ��
            ����: "1;2;"������� "1","2"��2��Ԫ��
            ����: "1;2"������� "1","2"��2��Ԫ��
    @param [in] str ��Ҫ�зֵ��ַ���, ������Էָ������������һ���ָ����ᱻ����
    @param [in] sepChar �ָ��ַ�
    @param [out] arrayValue �зֵĽ��
    */
    static void StringToArrayA(const std::string& str, 
                               const char sepChar, 
                               std::vector<std::string>& arrayValue) ;

    /** ���ݿո���Ϊ�ָ��������ַ��������з�
    @param [in] str ��Ҫ�зֵ��ַ������ո�ָ���������ļ������пո�����������������ʽΪ "D B" A E 
    @param [out] arrayValue �зֵĽ��
    @param [in] skipBlank �Ƿ������հ׷���Ĭ������
    */
    static void StringToFileNameArray(const std::wstring& str, 
                                      std::vector<std::wstring>& arrayValue,
                                      bool skipBlank = true) ;

    /** ���ļ���ת���ɿո�ָ����ַ���
    @param [in] arrayValue �ļ�������
    @return �ļ����ַ������ÿո�ָ����ļ���������������
    */
    static std::wstring FileNameArrayToString(const std::vector<std::wstring>& arrayValue) ;
};

}//namespace RL

#endif //__RLStringToken_h_
