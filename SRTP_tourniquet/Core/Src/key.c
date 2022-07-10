#include "key.h"

/*******************************************************************************
* 函 数 名         : KEY_Scan
* 函数功能		   : 按键扫描检测
* 输    入         : mode=0:单次按下按键
										mode=1：连续按下按键
* 输    出         : 0：未有按键按下
					 KEYx_VALUE：KEYx键按下
*******************************************************************************/


uint8_t KEY_Scan(uint8_t mode)
{
	static uint8_t key_up=1; //按键按松开标志
	if(mode)key_up=1; //模式选择
	if(key_up&&(P1_inc_Pin==0||P1_dec_Pin==0||T1_inc_Pin==0||T1_dec_Pin==0))
	{
		HAL_Delay(10); //消抖
		key_up=0;				
		if(P1_inc_Pin==0)return KEY_Pinc;
		else if(P1_dec_Pin==0)return KEY_Pdec;
		else if(T1_inc_Pin==0)return KEY_Tinc;
		else if(T1_dec_Pin==0)return KEY_Tdec;
	}
	else if(P1_inc_Pin==0&&P1_dec_Pin==0&&T1_inc_Pin==0&&T1_dec_Pin==0)key_up=1; 
	return 0; //无按键按下
}