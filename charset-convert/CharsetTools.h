#pragma once

#include "base/RLCharsetString.h"
#include <string>
#include <thread>

struct TCharsetToolsParam
{
	bool isDirChecked = true;
	std::wstring fileName;
	std::wstring filePath;
	std::wstring fileExt;

	RL::RLCharsetType srcFileCharset = RL::RLCharsetType::UNKNOWN;
	RL::RLCharsetType destFileCharset = RL::RLCharsetType::UNKNOWN;
	bool destFileWriteBOM = false;
};

//�����������
struct TProgressData
{
	//�Ƿ�Ϊ���ģʽ��trueΪ���ģʽ��falseΪת��ģʽ
	bool isCheckedMode = true;
	//�ļ�����
	uint32_t totalFiles = 0;
	//��ǰ�ļ�����ֵ����0��ʼ
	uint32_t currentFileIndex = 0;
	//��ǰ�ļ�·��
	const std::wstring fileName;
	//��ǰ�ļ�����
	RL::RLCharsetType srcFileCharset = RL::RLCharsetType::UNKNOWN;
	//Ŀ���ļ�����
	RL::RLCharsetType destFileCharset = RL::RLCharsetType::UNKNOWN;
	//�������: 0 ת��ģʽ��ת���ɹ���
	//         1 ���ģʽ���ɹ����޲���
	//         10 Դ�ļ�������ʧ��
	//         11 Դ�ļ���ȡʧ��
	//         12 Ŀ���ļ�д��ʧ��
	uint32_t result = 0;
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
	static std::wstring GetCharsetTypeMsg(RL::RLCharsetType charsetType);

private:
	void RunConvertThread();

private:
	TCharsetToolsParam m_convertParam;
	CharsetToolsCallback* m_callback;
	std::thread m_convertThread;
};

