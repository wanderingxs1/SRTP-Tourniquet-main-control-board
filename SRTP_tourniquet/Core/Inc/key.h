#ifndef _key_H
#define _key_H

#include "main.h"
#include "stm32f0xx_it.h"


//定义各个按键值 
#define KEY_Pinc 1 //P1+ 按下
#define KEY_Pdec 2 //P1- 按下
#define KEY_Tinc 3 //T1+ 按下
#define KEY_Tdec 4 //T1- 按下  


uint8_t KEY_Scan(uint8_t mode);
#endif
