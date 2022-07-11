/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "key.h"
#include "display.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
//时间变量
u8 setTime = 0;//设定时间
u8 curTime = 0;//当前时间
float curPres = 0.0;//当前压力
u8 setPres = 0;//设定压力
u8 key;
u8 workStatue =0;//工作状态，未定时为0，开始定时正常工作为1，溢出为2
u8 buzzerWork = 0;//蜂鸣器工作状态，0为不工作，1为工作
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	
	//显示板芯片初始化
	TM1640_Init();
	
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_USART1_UART_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    //扫描按键
		key = KEY_Scan(0);
		if(key) 
			{ 
				buzzerWork =0;
				workStatue=1;
				switch(key)
				{ case KEY_Tdec: //T1-,设定时间-1min
					HAL_TIM_Base_Stop_IT(&htim6);//关闭定时器中断	
						__HAL_TIM_CLEAR_FLAG(&htim6,TIM_FLAG_UPDATE);//清除标志位
						setTime--;
						curTime = setTime ;
						HAL_TIM_Base_Start_IT(&htim6);//打开定时器中断
						break;
					case KEY_Tinc: //T1+,设定时间+1min
						__HAL_TIM_CLEAR_FLAG(&htim6,TIM_FLAG_UPDATE);//清除标志位
						setTime++;
						curTime = setTime ;
						HAL_TIM_Base_Start_IT(&htim6);//打开定时器中断break;
					case KEY_Pdec: //P1-
						setPres--;break;
					case KEY_Pinc: //P1+
						setPres ++;break;
				}
				}
		else HAL_Delay(10);
//操纵蜂鸣器工作
		if(buzzerWork)
			HAL_GPIO_WritePin (GPIOB,GPIO_PIN_7,GPIO_PIN_SET);
//显示当前工作状态指示灯
		TM1640_lightLCD(13,workStatue);
		
//四个LCD显示数值（未完成）
//TM1640_display(0,curPres  );//浮点数从0.01到100+，表示方式待做
//每个LED组有3个LED，需查看对应地址
		u8 count=0;
		u8 tmp1,tmp2;
		
		if(curPres ==0){
		for(count=0;count<3;count++)
			TM1640_display (count,0);
		}		
				
		tmp1=setPres%10;
		tmp2 = setPres /10;
		for(count=5;count>2;count--){
			TM1640_display (count,tmp1);
			tmp1=tmp2%10;
			tmp2=tmp2/10;
		}

		tmp1=curTime %10;
		tmp2 = curTime  /10;
		for(count=8;count>5;count--){
			TM1640_display (count,tmp1);
			tmp1=tmp2%10;
			tmp2=tmp2/10;
		}
		
		tmp1=setTime %10;
		tmp2 = setTime  /10;
		for(count=11;count>8;count--){
			TM1640_display (count,tmp1);
			tmp1=tmp2%10;
			tmp2=tmp2/10;
		}

		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
