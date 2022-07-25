#include "key.h"
#include "display.h"
#include "main.h"
/*******************************************************************************
* �� �� ��         : KEY_Scan
* ��������		   : ����ɨ����
* ��    ��         : mode=0:���ΰ��°���
										mode=1���������°���
* ��    ��         : 0��δ�а�������
					 KEYx_VALUE��KEYx������
*******************************************************************************/


uint8_t KEY_Scan(uint8_t mode)
{
	static uint8_t key_up; //�������ɿ���־
	key_up=1;
	if(mode)key_up=1; //ģʽѡ��
	if(key_up&&(KEY_Pi==0||KEY_Pd==0||KEY_Ti==0||KEY_Td==0||KEY_PMODE==0||KEY_INFLATE==0||KEY_DEFLATE==0))
	{
		delay_ms(40); //����
		key_up=0;				
		if(KEY_Pi==0)return KEY_Pinc;
		else if(KEY_Pd==0)return KEY_Pdec;
		else if(KEY_Ti==0)return KEY_Tinc;
		else if(KEY_Td==0)return KEY_Tdec;
		else if(KEY_PMODE==0)return KEY_Pmode;
		else if(KEY_INFLATE==0)return KEY_Inflate;
		else if(KEY_DEFLATE==0)return KEY_Deflate;
	}
	else if(KEY_Pi==0&&KEY_Pd==0&&KEY_Ti==0&&KEY_Td==0&&KEY_PMODE==0&&KEY_INFLATE==0&&KEY_DEFLATE==0)key_up=1; 
	return 0; //�ް�������
}
