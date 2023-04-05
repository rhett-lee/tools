#pragma once

#include "base/StringCharset.h"
#include <string>
#include <thread>

struct TCharsetToolsParam
{
	bool isCheckMode = true; //���ģʽ��������ʵ��ת��
	bool isDirChecked = true;
	std::wstring fileName;
	std::wstring filePath;
	std::wstring fileExt;

	RL::CharsetType srcFileCharset = RL::CharsetType::UNKNOWN;
	RL::CharsetType destFileCharset = RL::CharsetType::UNKNOWN;
	bool destFileWriteBOM = false;
};

//�����������
struct TProgressData
{
	//�Ƿ�Ϊ���ģʽ��trueΪ���ģʽ��falseΪת��ģʽ
	bool isCheckMode = true;
	//�ļ�����
	uint32_t totalFiles = 0;
	//��ǰ�ļ�����ֵ����0��ʼ
	uint32_t currentFileIndex = 0;
	//��ǰ�ļ�·��
	std::wstring fileName;
	//��ǰ�ļ�����
	RL::CharsetType srcFileCharset = RL::CharsetType::UNKNOWN;
	//Ŀ���ļ�����
	RL::CharsetType destFileCharset = RL::CharsetType::UNKNOWN;
	//�������: 0 ת��ģʽ��ת���ɹ���
	//         1 ���ģʽ���ɹ����޲���
	//         10 ��ȡԴ�ļ�ʧ��
	//         20 д��Ŀ���ļ�ʧ��
	uint32_t result = 1;
};

class CharsetToolsCallback
{
public:
	//����ص���������false������ִֹ��
	virtual bool OnConvertBegin() = 0;
	virtual bool OnConvertProgress(const TProgressData& progressData) = 0;
	virtual bool OnConvertEnd() = 0;
};

class CharsetTools
{
public:
	CharsetTools();

public:
	//��ʼת��
	bool StartConvert(const TCharsetToolsParam& convertParam, CharsetToolsCallback* callback);

	//������������Դ
	void Terminate();

public:
	//��ȡ������Ϣ
	static std::wstring GetErrMsg(const TProgressData& progressData);

	//��ȡ�ļ�������Ϣ
	static std::wstring GetCharsetMsg(const TProgressData& progressData);

	//��ȡ������ʾ��Ϣ
	static std::wstring GetCharsetTypeMsg(RL::CharsetType charsetType);

private:
	void RunConvertThread();

private:
	TCharsetToolsParam m_convertParam;
	CharsetToolsCallback* m_callback;
	std::thread m_convertThread;
};

