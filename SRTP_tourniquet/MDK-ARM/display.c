#include "display.h"

#define DEL  1   //�궨�� ͨ�����ʣ�Ĭ��Ϊ1���粻��ͨ�ſɼӴ���ֵ��

//��ַģʽ������
//#define TM1640MEDO_ADD  0x40   //�궨��	�Զ���һģʽ
#define TM1640MEDO_ADD  0x44   //�궨�� �̶���ַģʽ���Ƽ���

//��ʾ���ȵ�����
//#define TM1640MEDO_DISPLAY  0x88   //�궨�� ����  ��С
//#define TM1640MEDO_DISPLAY  0x89   //�궨�� ����
//#define TM1640MEDO_DISPLAY  0x8a   //�궨�� ����
//#define TM1640MEDO_DISPLAY  0x8b   //�궨�� ����
#define TM1640MEDO_DISPLAY  0x8c   //�궨�� ���ȣ��Ƽ���
//#define TM1640MEDO_DISPLAY  0x8d   //�궨�� ����
//#define TM1640MEDO_DISPLAY  0x8f   //�궨�� ���� ���

#define TM1640MEDO_DISPLAY_OFF  0x80   //�궨�� ���� ��



//ͨ��ʱ�� ��ʼ������GPIO���������Ͳ㣩
void TM1640_start()
{ 
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_14,GPIO_PIN_SET ); //�ӿ�����ߵ�ƽ1	
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_13,GPIO_PIN_SET ); //�ӿ�����ߵ�ƽ1	
	HAL_Delay(DEL);
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_14,GPIO_PIN_RESET ); //�ӿ����0	
	HAL_Delay(DEL);
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_13,GPIO_PIN_RESET ); //�ӿ����0	
	HAL_Delay(DEL);
}

void TM1640_stop()
{
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_14,GPIO_PIN_RESET );
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_13,GPIO_PIN_SET );
	HAL_Delay(DEL);
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_14,GPIO_PIN_SET ); 
	HAL_Delay(DEL);
}

void TM1640_writeInt(u8 data)
{
	u8 i;
	u8 temp;
	temp=data;
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_14,GPIO_PIN_RESET ); //�ӿ����0	
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_13,GPIO_PIN_RESET ); //�ӿ����0	
	for(i=0;i<8;i++)
	{
		HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_13,GPIO_PIN_RESET );//�ӿ����0	
		HAL_Delay(DEL);

		if(temp&0x01)
		{
			HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_14,GPIO_PIN_SET );  //�ӿ�����ߵ�ƽ1	
			HAL_Delay(DEL);
		}
		else
		{
			HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_14,GPIO_PIN_RESET ); //�ӿ����0	
			HAL_Delay(DEL);
		}
		HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_13,GPIO_PIN_SET ); //�ӿ�����ߵ�ƽ1	
		HAL_Delay(DEL);
		temp=temp>>1;
   }
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_14,GPIO_PIN_RESET ); //�ӿ����0	
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_13,GPIO_PIN_RESET ); //�ӿ����0	
}

void TM1640_writeFloat(float data)
{
	
}

void TM1640_Init()
{
//��gpio.c�Աȿɵã��ⲿ�ִ����ʱ�Ӷ˿ڣ�ѡ��˿ںŲ������乤����ʽ��Ӧ�ò���Ҫ��дһ��
//		GPIO_InitTypeDef  GPIO_InitStructure; 	
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);       
//    GPIO_InitStructure.Pin = GPIO_PIN_14 | GPIO_PIN_13;//ѡ��˿ںţ�0~15��all��                        
//    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; //ѡ��IO�ӿڹ�����ʽ       
//    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; //����IO�ӿ��ٶȣ�2/10/50MHz��    
//		HAL_GPIO_Init(TM1640_GPIOPORT, &GPIO_InitStructure);

	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_14,GPIO_PIN_SET ); //�ӿ�����ߵ�ƽ1	
	HAL_GPIO_WritePin(TM1640_GPIOPORT,GPIO_PIN_13,GPIO_PIN_SET ); //�ӿ�����ߵ�ƽ1	
	TM1640_start();
	TM1640_writeInt(TM1640MEDO_ADD); //�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
	TM1640_stop();
	TM1640_start();
	TM1640_writeInt(TM1640MEDO_DISPLAY); //������ʾ������ʾ��0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f�ֱ��Ӧ������Ϊ:
					 				  //------------------1/16,  2/16,  4/16,  10/16, 11/16, 12/16, 13/16, 14/16	 //0x80����ʾ
	TM1640_stop();	

}


void TM1640_display(u8 address,u8 data)
{
	const u8 buff[21]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x00};//����0~9��0~9�ӵ���ʾ�����
    //---------------   0    1    2    3    4    5    6    7    8    9    0.   1.   2.   3.   4.   5.   6.   7.   8.   9.   ��   
   TM1640_start();
   TM1640_writeInt(0xC0+address);	         //����ʾ���ݶ�Ӧ�ĵ�ַ
   TM1640_writeInt(buff[data]);				 //��1BYTE��ʾ����
   TM1640_stop();
}

//�̶���ַģʽ����ʾ���8��LED����
//void TM1640_led(u8 date)
//{ 
//   TM1640_start();
//   TM1640_write(TM1640_LEDPORT);	        //����ʾ���ݶ�Ӧ�ĵ�ַ
//   TM1640_write(date);	//��1BYTE��ʾ����
//   TM1640_stop();
//}


