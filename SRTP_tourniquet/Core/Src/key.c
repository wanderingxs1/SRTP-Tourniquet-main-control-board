#include "key.h"

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
	if(key_up&&(P1_inc_Pin==0||P1_dec_Pin==0||T1_inc_Pin==0||T1_dec_Pin==0))
	{
		HAL_Delay(10); //����
		key_up=0;				
		if(P1_inc_Pin==0)return KEY_Pinc;
		else if(P1_dec_Pin==0)return KEY_Pdec;
		else if(T1_inc_Pin==0)return KEY_Tinc;
		else if(T1_dec_Pin==0)return KEY_Tdec;
	}
	else if(P1_inc_Pin==0&&P1_dec_Pin==0&&T1_inc_Pin==0&&T1_dec_Pin==0)key_up=1; 
	return 0; //�ް�������
}