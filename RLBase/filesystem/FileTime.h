#ifndef __RL_FileTime_h_
#define __RL_FileTime_h_ 1

#include <stdint.h>

namespace RL
{

/** 文件时间
*/
class FileTime
{
public:    
    /** 低位值
    */
    uint32_t lowDateTime = 0;
    
    /** 高位值
    */
    uint32_t highDateTime = 0;
};

}//namespace RL

#endif //__RL_FileTime_h_
