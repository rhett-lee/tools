#ifndef __RL_FileTime_h_
#define __RL_FileTime_h_ 1

#include <stdint.h>

namespace RL
{

/** �ļ�ʱ��
*/
class FileTime
{
public:    
    /** ��λֵ
    */
    uint32_t lowDateTime = 0;
    
    /** ��λֵ
    */
    uint32_t highDateTime = 0;
};

}//namespace RL

#endif //__RL_FileTime_h_
