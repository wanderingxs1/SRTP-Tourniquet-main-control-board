#include "display.h"

#define DEL  1   //宏定义 通信速率

//地址模式的设置
//#define TM1640MEDO_ADD  0x40   //宏定义	自动加一模式
#define TM1640MEDO_ADD  0x44   //宏定义 固定地址模式（适配当前）

//显示亮度的设置
//#define TM1640MEDO_DISPLAY  0x88   //宏定义 亮度  最小
//#define TM1640MEDO_DISPLAY  0x89   //宏定义 亮度
//#define TM1640MEDO_DISPLAY  0x8a   //宏定义 亮度
//#define TM1640MEDO_DISPLAY  0x8b   //宏定义 亮度
#define TM1640MEDO_DISPLAY  0x8c   //宏定义 亮度（最适）
//#define TM1640MEDO_DISPLAY  0x8d   //宏定义 亮度
//#define TM1640MEDO_DISPLAY  0x8f   //宏定义 亮度 最大

#define TM1640MEDO_DISPLAY_OFF  0x80   //宏定义 亮度 关

void delay_ms(u16 time){    
 
   u16 i=0;  
 
   while(time--){
 
      i=12000;  //自己定义
      while(i--) ;    
   }
}

//通信时序 启始（基础GPIO操作）（低层）
void TM1640_start()
{ 
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_4,GPIO_PIN_SET ); //接口输出高电平1	
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_3,GPIO_PIN_SET ); //接口输出高电平1	
	delay_ms(DEL);
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_4,GPIO_PIN_RESET ); //接口输出0	
	delay_ms(DEL);
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_3,GPIO_PIN_RESET ); //接口输出0	
	delay_ms(DEL);
}

void TM1640_stop()
{
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_4,GPIO_PIN_RESET );
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_3,GPIO_PIN_SET );
	delay_ms(DEL);
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_4,GPIO_PIN_SET ); 
	delay_ms(DEL);
}

void TM1640_writeInt(u8 data)
{
	u8 i;
	u8 temp;
	temp=data;
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_4,GPIO_PIN_RESET ); //接口输出0	
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_3,GPIO_PIN_RESET ); //接口输出0	
	for(i=0;i<8;i++)
	{
		HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_3,GPIO_PIN_RESET );//接口输出0	
		delay_ms(DEL);

		if(temp&0x01)
		{
			HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_4,GPIO_PIN_SET );  //接口输出高电平1	
			delay_ms(DEL);
		}
		else
		{
			HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_4,GPIO_PIN_RESET ); //接口输出0	
			delay_ms(DEL);
		}
		HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_3,GPIO_PIN_SET ); //接口输出高电平1	
		delay_ms(DEL);
		temp=temp>>1;
   }
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_4,GPIO_PIN_RESET ); //接口输出0	
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_3,GPIO_PIN_RESET ); //接口输出0	
}


void TM1640_Init()
{
//和gpio.c对比可得，这部分打开输出时钟端口，选择端口号并配置其工作方式，应该不需要再写一次
//		GPIO_InitTypeDef  GPIO_InitStructure; 	
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);       
//    GPIO_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_13;//选择端口号（0~15或all）                        
//    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; //选择IO接口工作方式       
//    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; //设置IO接口速度（2/10/50MHz）    
//		HAL_GPIO_Init(TM1640_GPIOPORT, &GPIO_InitStructure);

	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_4,GPIO_PIN_SET ); //接口输出高电平1	
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_3,GPIO_PIN_SET ); //接口输出高电平1	
	TM1640_start();
	TM1640_writeInt(TM1640MEDO_ADD); //设置数据，0x40,0x44分别对应地址自动加一和固定地址模式
	TM1640_stop();
	TM1640_start();
	TM1640_writeInt(TM1640MEDO_DISPLAY); //控制显示，开显示，0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f分别对应脉冲宽度为:
					 				  //------------------1/16,  2/16,  4/16,  10/16, 11/16, 12/16, 13/16, 14/16	 //0x80关显示
	TM1640_stop();	

}


void TM1640_display(u8 address,u8 data)
{
	const u8 buff[21]={0xEB,0x88,0xB3,0xB9,0xD8,0x7A,0x7B,0xA8,0xFB,0xFA,0x00};//数字0~9及0~9加点显示段码表
    //---------------   0    1    2    3    4    5    6    7    8    9	无   
   TM1640_start();
   TM1640_writeInt(0xC0+address);	         //传显示数据对应的地址
   TM1640_writeInt(buff[data]);				 //传1BYTE显示数据
   TM1640_stop();
}

void TM1640_lightLCD(u8 address,u8 workStatue)
{
	TM1640_start();
	TM1640_writeInt (0xC0+address);
	switch(workStatue){
		case 0:
			TM1640_writeInt(0x80);break;
		case 1:
			TM1640_writeInt (0x40);break;
		case 2:
			TM1640_writeInt(0x20);break;
		default:
			TM1640_writeInt(0x00);break;
			break;
	}
	TM1640_stop();
}
//固定地址模式的显示输出8个LED控制
//void TM1640_led(u8 date)
//{ 
//   TM1640_start();
//   TM1640_write(TM1640_LEDPORT);	        //传显示数据对应的地址
//   TM1640_write(date);	//传1BYTE显示数据
//   TM1640_stop();
//}


