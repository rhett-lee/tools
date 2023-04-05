#ifndef __RL_TextFile_h_
#define __RL_TextFile_h_ 1

#include "base/StringCharset.h"
#include <vector>

namespace RL
{

//�ı��ļ������֧࣬��ANSI��Unicode����
class TextFile
{
public:
    /** ��ȡ�ļ�����
    @param [in] fileName �ļ�·��
    @param [in] inCharsetType ��ȡ�ļ������õı��룬���ΪUNKNOWN���Զ�����ı���������
    @parma [out] fileText ���ض�ȡ�����ļ������ַ���
    @param [out] outCharsetType ��ȡ�ļ������õı�������
    @param [out] bomSize ��ȡ�ļ�ʱ����⵽��Unicode BOMͷ��С
    */
    static bool ReadData(const std::wstring& fileName, 
                         CharsetType inCharsetType, 
                         std::wstring& fileText,
                         CharsetType& outCharsetType,
                         uint32_t& bomSize);
                  
                  
    /** д���ļ�
    @param [in] fileName �ļ�·��
    @parma [in] fileText �ļ������ַ���
    @param [in] charsetType �����ļ����õı�������
    @param [in] writeBOM ����Unicode���룬�Ƿ�д��BOMǩ��ͷ����
    */
    static bool WriteData(const std::wstring& fileName, const std::wstring& fileText, CharsetType charsetType, bool writeBOM);

private:
    //��ȡ�ļ��������У��ļ���С�޶���10MB�ڣ����÷���Ҫ�Լ������ַ�����β�����⡣
    static bool ReadBinaryFile(const std::wstring& fileName, std::vector<char>& container);

    //�������еĶ���������д���ļ�
    static bool WriteBinaryFile(const std::wstring& fileName, const std::vector<char>& container);
};

}//namespace RL

#endif //__RL_TextFile_h_
