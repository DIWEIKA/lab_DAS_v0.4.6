#ifndef _CyUSB300_H
#define _CyUSB300_H

const int CyUSB3000_MAX_DEV_COUNT = 64;
///read flag /////
const UINT damShallowRead = 0x0001;
///write flag 
const UINT damShallowWrite = 0x0001;
///param index
const int  DPI_ReadSumSize = 0, DPI_ReadSumErrorCount = 1, DPI_BufSizeOfRead=2, DPI_FastBufSizeOfRead=3;
typedef TCHAR CyUSB3000_DevID[128];
#define CYUAPI _stdcall
//�õ�������Ϣ
extern "C" int CYUAPI CyUSB3000_GetLastError(HANDLE hDev, TCHAR* strError, int nSize);
//�о��豸
extern "C" int CYUAPI CyUSB3000_EnumDevices(CyUSB3000_DevID *strDevIDs, int nCount);
//�����豸���, ʧ�ܷ���NULL
extern "C" HANDLE CYUAPI CyUSB3000_CreateDevice(DWORD dwReserve);
//�����豸���
extern "C" bool  CYUAPI CyUSB3000_DestroyDevice(HANDLE hDev);
//��ȡ�豸����
extern "C" int  CYUAPI CyUSB3000_GetParam(HANDLE hDev, int index, void* buffer, int len);
//�����豸����
extern "C" bool  CYUAPI CyUSB3000_SetParam(HANDLE hDev, int index, const void* buffer, int len);
//���豸
extern "C" bool  CYUAPI CyUSB3000_OpenDevice(HANDLE hDev, LPCTSTR strDevID, DWORD dwMode);
//�ر��豸
extern "C" bool CYUAPI CyUSB3000_CloseDevice(HANDLE hDev);
//���豸�ж�ȡ����
extern "C" int CYUAPI CyUSB3000_Read(HANDLE hDev, void* buffer, int len, UINT uFlag);
//���豸��д������
extern "C" int CYUAPI CyUSB3000_Write(HANDLE hDev, const void* buffer, int len, UINT uFlag);

#endif