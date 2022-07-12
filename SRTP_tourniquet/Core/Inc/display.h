#ifndef __TM1640_H
#define __TM1640_H	 

#include "stm32f0xx_it.h"
#include "main.h"
#include "stm32f0xx_hal.h"

#define TM1640_GPIOPORT	GPIOA	//定义IO接口
#define TM1640_LEDPORT	0xC8	//定义IO接口

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

void TM1640_Init(void );

void TM1640_writeInt(u8 data);
void TM1640_display(u8 adress,u8 data);

void TM1640_lightLCD(u8 address,u8 workStatue);

void TM1640_start(void);
void TM1640_stop(void);

		 				    
#endif
