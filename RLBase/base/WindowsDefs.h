#ifndef __RL_WindowsDefs_h_
#define __RL_WindowsDefs_h_ 1

//֧����Ͱ汾��Windows XP
#ifndef WINVER
    #define WINVER 0x0501
#endif

#ifndef _WIN32_WINNT          
    #define _WIN32_WINNT 0x0501
#endif                                                

//�ú�ֻ��Win9xϵ�в�ʹ��
#ifndef _WIN32_WINDOWS
    #define _WIN32_WINDOWS 0x0501
#endif

//֧��IE��Ͱ汾��6.0 SP2
#ifndef _WIN32_IE
    #define _WIN32_IE 0x0603
#endif

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#ifndef VC_EXTRALEAN
    #define VC_EXTRALEAN
#endif

#ifndef NOMINMAX
    #define NOMINMAX 1
#endif

#include <windows.h>

#endif //__RL_WindowsDefs_h_