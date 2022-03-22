#ifndef _CU3AD_H
#define _CU3AD_H
/*��SDK�ڲ����� unicode�ַ��� ʹ�ô�SDK�Ļ�������(���ǹ̶�����)
  1.CU3_Init(...);//����ʹ��SDKʱ����ʼ��SDK�ڲ���Դ
  2.CU3_OpenDev(...);//���豸
  3.CU3_SetSamParam(...);//���ò�������
  4.CU3_StartAD(...);//��ʼ����
  5.CU3_ReadADRecords(...);
  6.CU3_StopAD(...);
  7.CU3_CloseDev(...);
  8.CU3_Release(...);//����ʹ��SDKʱ���ͷ�SDK�ڲ���Դ
  ����:���ƹ��̿��ԺͲɼ����̿����������߳�
*/

#define CU3API _stdcall

const int CU3_MAX_CHAN_COUNT = 16;
struct CU3_RECORD_META
{
    WORD nSwitchNum;//����                4
    DWORD iRecordSn;//���ڼ�¼��(��1��ʼ) 2
    int nChannelCount;                   // 4
    int nRecordLenOfChans[CU3_MAX_CHAN_COUNT];   //64
};

//��������
struct CU3_SAM_PARA
{
	int nBitCount;
	double nFreq;
	int nChannelCount;
	int nRecordLenOfChans[CU3_MAX_CHAN_COUNT];
};

const int DPI_RAW_ReadSumSize = 0, DPI_RAW_ReadSumErrorCount = 1;
const int DPI_ADSumErrorCount = 0x100;

//��ʼ��SDK�ڲ���Դ
extern "C" bool CU3API CU3_Init();

//�ͷ�SDK�ڲ���Դ
extern "C" void CU3API CU3_Release();

/*���ش�����Ϣ
  hDev:�豸���������豸�����Ч������-1.
  strError:������Ϣ������
  nSize:������Ϣ�������������ɵ��ַ�������������С��
  ����ֵ:��strError=NULLʱ��������Ҫ�Ļ�������С��
  ����������㹻��, �򷵻�ʵ�ʴ�С;��������������󷵻�-1*/
extern "C" int CU3API CU3_GetLastError(HANDLE hDev, TCHAR* strError, int nSize);

/*���豸
  strDevID:�豸ID
  ����ֵ:�ɹ�ʱ���طǿ�(NULL), ʧ�ܷ���NULL*/
extern "C" HANDLE CU3API CU3_OpenDev(LPCTSTR strDevID);

//�رղɼ���
extern "C" bool CU3API CU3_CloseDev(HANDLE hDev);

//��ȡ����
extern "C" int CU3API CU3_GetParam(HANDLE hDev, int nIndex, void* buffer, int len);

//���ò���
extern "C" bool CU3API CU3_SetParam(HANDLE hDev, int nIndex, const void* buffer, int len);

//���òɼ�����
extern "C" bool CU3API CU3_SetSamParam(HANDLE hDev, const CU3_SAM_PARA *pSamParam);

//��ʼ��AD����(�˺���������,�����˺�����Ϊ�ӿڼ���)
extern "C" bool CU3API CU3_InitAD(HANDLE hDev);

//����AD����
extern "C" bool CU3API CU3_StartAD(HANDLE hDev);

//ֹͣAD����
extern "C" bool CU3API CU3_StopAD(HANDLE hDev);

/*��ȡ������¼
  hDev:�豸���
  buffer: ��¼���ݻ�����   
  nRecordCount:ϣ����ȡ�ļ�¼��
  recordMetas:��¼Ԫ��Ϣ
  ����ֵ: >=0ʱ��ʾʵ�ʶ�ȡ���ļ�¼����<0 ��ʾʧ��*/
extern "C" int CU3API CU3_ReadADRecords(HANDLE hDev, BYTE* buffer, int nRecordCount, CU3_RECORD_META* recordMetas);

#endif
