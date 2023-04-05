#ifndef __RC_NonCopyable_h_
#define __RC_NonCopyable_h_ 1

namespace RL
{

/** ��ֹ�����ƣ���Ϊ����ʹ��
*/
class NonCopyable
{    
protected:    
    /** Ĭ�Ϲ��캯������������
    */
    NonCopyable() = default;
    ~NonCopyable() = default;

private:
    /** �������캯���͸�ֵ������
    */
    NonCopyable(const NonCopyable&);
    const NonCopyable& operator= (const NonCopyable&);
};

}//namespace RL

#endif //__RL_NonCopyable_h_
