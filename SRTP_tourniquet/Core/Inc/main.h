/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SENSOR_Pin GPIO_PIN_1
#define SENSOR_GPIO_Port GPIOA
#define VALVE1ON_Pin GPIO_PIN_0
#define VALVE1ON_GPIO_Port GPIOB
#define VALVE2ON_Pin GPIO_PIN_1
#define VALVE2ON_GPIO_Port GPIOB
#define INFLATE2_Pin GPIO_PIN_10
#define INFLATE2_GPIO_Port GPIOB
#define DEFLATE2_Pin GPIO_PIN_11
#define DEFLATE2_GPIO_Port GPIOB
#define VALVE3ON_Pin GPIO_PIN_12
#define VALVE3ON_GPIO_Port GPIOB
#define VALVE4ON_Pin GPIO_PIN_13
#define VALVE4ON_GPIO_Port GPIOB
#define PUMPON_Pin GPIO_PIN_14
#define PUMPON_GPIO_Port GPIOB
#define INFLATE1_Pin GPIO_PIN_15
#define INFLATE1_GPIO_Port GPIOB
#define DEFLATE1_Pin GPIO_PIN_8
#define DEFLATE1_GPIO_Port GPIOA
#define DISPSCLK_Pin GPIO_PIN_11
#define DISPSCLK_GPIO_Port GPIOA
#define DISPDIN_Pin GPIO_PIN_12
#define DISPDIN_GPIO_Port GPIOA
#define P1_DEC_Pin GPIO_PIN_6
#define P1_DEC_GPIO_Port GPIOF
#define T1_INC_Pin GPIO_PIN_7
#define T1_INC_GPIO_Port GPIOF
#define PMODE_Pin GPIO_PIN_15
#define PMODE_GPIO_Port GPIOA
#define P1_DECB3_Pin GPIO_PIN_3
#define P1_DECB3_GPIO_Port GPIOB
#define Buzzer_Pin GPIO_PIN_4
#define Buzzer_GPIO_Port GPIOB
#define P1_INC_Pin GPIO_PIN_5
#define P1_INC_GPIO_Port GPIOB
#define T2_DEC_Pin GPIO_PIN_6
#define T2_DEC_GPIO_Port GPIOB
#define P2_INC_Pin GPIO_PIN_7
#define P2_INC_GPIO_Port GPIOB
#define P2_DEC_Pin GPIO_PIN_8
#define P2_DEC_GPIO_Port GPIOB
#define T2_INC_Pin GPIO_PIN_9
#define T2_INC_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define GAP 10 //充气放气压力差值
#define FLAW 3 //误差限
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
