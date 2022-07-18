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
	static uint8_t key_up=1; //�������ɿ���־
	if(mode)key_up=1; //ģʽѡ��
	if(key_up&&(KEY_Pi==0||KEY_Pd==0||KEY_Ti==0||KEY_Td==0))
	{
		delay_ms(10); //����
		key_up=0;				
		if(KEY_Pi==0)return KEY_Pinc;
		else if(KEY_Pd==0)return KEY_Pdec;
		else if(KEY_Ti==0)return KEY_Tinc;
		else if(KEY_Td==0)return KEY_Tdec;
	}
	else if(KEY_Pi==0&&KEY_Pd==0&&KEY_Ti==0&&KEY_Td==0)key_up=1; 
	return 0; //�ް�������
}