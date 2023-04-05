#ifndef __RL_FileTimeUtils_h_
#define __RL_FileTimeUtils_h_ 1

#include "FileTime.h"
#include <string>

namespace RL
{
/** �ļ�ʱ�����������
*/
class FileTimeUtils
{
public:    
    /** �ж��ļ�ʱ���Ƿ�Ϊ��Чֵ
    @param [in] fileTime �ļ�ʱ��ֵ
    */
    static bool IsValidFileTime(const FileTime& fileTime);
    
    /**  ����ʱ��ת����UTCʱ��
    @param [in] fileTime �����ļ�ʱ��
    @param [out] utcFileTime ����UTC �ļ�ʱ��
    */
    static bool LocalFileTimeToFileTime(const FileTime& fileTime, FileTime& utcFileTime);
    
    /**  UTCʱ��ת���ɱ���ʱ��
    @param [in] utcFileTime UTC �ļ�ʱ��
    @param [out] fileTime ���ر����ļ�ʱ��
    */
    static bool FileTimeToLocalFileTime(const FileTime& utcFileTime, FileTime& fileTime);
    
    /** �Ƚ��ļ�ʱ��
    @param [in] time1 ��һ���ļ�ʱ��
    @param [in] time2 �ڶ����ļ�ʱ��
    @return �����ȷ���0, ��� time1 > time2 ����1�����time1 < time2 ���� -1
    */
    static int32_t CompareFileTime(const FileTime* time1, const FileTime* time2);

    /** ��Dos�ļ�ʱ��ת��Ϊ�����ļ�ʱ��
    @param [in] dosTime Unix�ļ�ʱ��
    @param [out] fileTime ���ر����ļ�ʱ��
    */
    static bool DosTimeToFileTime(uint32_t dosTime, FileTime& fileTime);
    
    /** �������ļ�ʱ��ת��ΪDos�ļ�ʱ��
    @param [in] fileTime �����ļ�ʱ��
    @param [out] dosTime Dos�ļ�ʱ��
    */
    static bool FileTimeToDosTime(const FileTime& fileTime, uint32_t& dosTime);
    
    /** ��Unix�ļ�ʱ��ת��Ϊ�����ļ�ʱ��
    @param [in] unixTime Unix�ļ�ʱ��
    @param [out] fileTime ���ر����ļ�ʱ��
    */
    static void UnixTimeToFileTime(uint32_t unixTime, FileTime& fileTime);
    
    /** �������ļ�ʱ��ת��ΪUnix�ļ�ʱ��
    @param [in] fileTime �����ļ�ʱ��
    @param [out] unixTime Unix�ļ�ʱ��
    */
    static bool FileTimeToUnixTime(const FileTime& fileTime, uint32_t& unixTime);

    /** ��Unix�ļ�ʱ��ת��Ϊ�����ļ�ʱ��
    @param [in] unixTime Unix�ļ�ʱ��
    @param [out] fileTime ���ر����ļ�ʱ��
    */
    static bool UnixTime64ToFileTime(int64_t unixTime, FileTime& fileTime);

    /** �������ļ�ʱ��ת��ΪUnix�ļ�ʱ��
    @param [in] fileTime �����ļ�ʱ��
    @param [out] unixTime Unix�ļ�ʱ��
    */
    static bool FileTimeToUnixTime64(const FileTime& fileTime, int64_t& unixTime);
    
    /** ��ȡ��1601���������
    @param [in] year ��
    @param [in] month ��
    @param [in] day ��
    @param [in] hour ʱ
    @param [in] min ��
    @param [in] sec ��
    @param [out] resSeconds ����UTC�ļ�ʱ��
    */
    static bool GetSecondsSince1601(uint32_t year, 
                                    uint32_t month, 
                                    uint32_t day,
                                    uint32_t hour, 
                                    uint32_t min, 
                                    uint32_t sec, 
                                    uint64_t& resSeconds);
    
    /** ��ȡ����UTC�ļ�ʱ��
    @param [out] fileTime ����UTC�ļ�ʱ��
    */
    static void GetCurrentUtcFileTime(FileTime& fileTime);
    
    /** ���ļ�ʱ��ת����64λ�޷������ͱ�ʾ
    @param [in] fileTime �ļ�ʱ��
    @return ����ת�����
    */
    static uint64_t ConvertFromFileTime(const FileTime& fileTime);
    
    /** ��64λ�޷������ͱ�ʾת�����ļ�ʱ��
    @param [in] time 64λ�޷������ͱ�ʾ���ļ�ʱ��
    @param [out] fileTime �����ļ�ʱ��
    */
    static void ConvertToFileTime(uint64_t time, FileTime& fileTime);
    
    /** ���ļ�ʱ��ת��Ϊ�ַ�����ʽ: ����ʱ��ת��
    @param [in] fileTime �ļ�ʱ�䣬 Ĭ����UTCʱ��
    @param [in] includeTime �Ƿ����ʱ�䣨ָʱ�֣�
    @param [in] includeSeconds �Ƿ������
    @return ������ʾ���ַ��������ʧ�ܷ��ؿմ�
    */
    static std::wstring FileTimeToString(const FileTime& fileTime, 
                                         bool includeTime, 
                                         bool includeSeconds);


    /** ���ļ�ʱ��ת��Ϊ�ַ�����ʽ�� ������ת��Ϊ����ʱ��
    @param [in] fileTime �ļ�ʱ�䣬 UTCʱ��
    @param [in] includeTime �Ƿ����ʱ�䣨ָʱ�֣�
    @param [in] includeSeconds �Ƿ������
    @return ������ʾ���ַ��������ʧ�ܷ��ؿմ�
    */
    static std::wstring FileTimeToLocalTimeString(const FileTime& fileTime, 
                                                  bool includeTime, 
                                                  bool includeSeconds);
};

}//namespace RL

#endif //__RL_FileTimeUtils_h_

