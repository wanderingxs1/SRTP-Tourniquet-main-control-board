#include "key.h"
#include "display.h"
#include "main.h"
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
	static uint8_t key_up; //按键按松开标志
	key_up=1;
	if(mode)key_up=1; //模式选择
	if(key_up&&(KEY_Pi==0||KEY_Pd==0||KEY_Ti==0||KEY_Td==0||KEY_PMODE==0||KEY_INFLATE==0||KEY_DEFLATE==0))
	{
		delay_ms(40); //消抖
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
	return 0; //无按键按下
}
