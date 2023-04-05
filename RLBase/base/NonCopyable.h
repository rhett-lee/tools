#ifndef __RC_NonCopyable_h_
#define __RC_NonCopyable_h_ 1

namespace RL
{

/** 禁止对象复制，作为基类使用
*/
class NonCopyable
{    
protected:    
    /** 默认构造函数与析构函数
    */
    NonCopyable() = default;
    ~NonCopyable() = default;

private:
    /** 拷贝构造函数和赋值操作符
    */
    NonCopyable(const NonCopyable&);
    const NonCopyable& operator= (const NonCopyable&);
};

}//namespace RL

#endif //__RL_NonCopyable_h_
