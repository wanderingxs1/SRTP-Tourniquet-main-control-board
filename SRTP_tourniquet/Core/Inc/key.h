#ifndef _key_H
#define _key_H

#include "main.h"
#include "stm32f0xx_it.h"


//定义各个按键值 
#define KEY_Pinc 1 //P1+ 按下
#define KEY_Pdec 2 //P1- 按下
#define KEY_Tinc 3 //T1+ 按下
#define KEY_Tdec 4 //T1- 按下
#define KEY_Pmode 5//PMODE按下，单位转换kpa-mmhg
#define KEY_Inflate 6//充气
#define KEY_Deflate 7//放气


#define KEY_Pi   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)
#define KEY_Pd   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)
#define KEY_Ti   HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_7)
#define KEY_Td   HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_6)
#define KEY_PMODE HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_15)
#define KEY_INFLATE HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)
#define KEY_DEFLATE HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)

uint8_t KEY_Scan(uint8_t mode);
#endif
