/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
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
#include "can.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t Txdata[8] = {1};
uint8_t Rxdata[8] = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void CAN_FilterConfig_Scale16_IDMask(void);
void CAN_Txdata(uint16_t StdID, uint8_t *data, uint8_t length);
void CAN_ENANBLE(void);


void Delay_us_simple(uint32_t us);


void Delay_ms_simple(uint32_t ms);

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
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */
  CAN_FilterConfig_Scale16_IDMask();
  CAN_ENANBLE();
  CAN_Txdata(0x201, Txdata, 1);
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
 * @brief  过滤器初始化
 * @retval None
 */
void CAN_FilterConfig_Scale16_IDMask(void)
{
  CAN_FilterTypeDef can_filter_initstruct;
  can_filter_initstruct.FilterScale = CAN_FILTERSCALE_32BIT;
  can_filter_initstruct.SlaveStartFilterBank = 0;
  can_filter_initstruct.FilterActivation = CAN_FILTER_ENABLE;
  can_filter_initstruct.FilterBank = 0;
  can_filter_initstruct.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  can_filter_initstruct.FilterMode = CAN_FILTERMODE_IDMASK;
 
   
    can_filter_initstruct.FilterIdHigh = 0;
    can_filter_initstruct.FilterIdLow = 0x201;

    can_filter_initstruct.FilterMaskIdHigh = 0;
    can_filter_initstruct.FilterMaskIdLow = 0xFFFC;
  HAL_CAN_ConfigFilter(&hcan, &can_filter_initstruct);
};
/**
 * @brief  发送标准ID的数据帧
 * @param StdID 标准格式的ID
 * @param data 数据
 * @param length 字节长度，范围为0-8
 * @retval None
 */
void CAN_Txdata(uint16_t StdID, uint8_t *data, uint8_t length)
{
  static CAN_TxHeaderTypeDef TxHeader;
  TxHeader.DLC = length;
  TxHeader.ExtId = 0;
  TxHeader.StdId = StdID;
  TxHeader.IDE = CAN_ID_STD;
  TxHeader.RTR = CAN_RTR_DATA;
  TxHeader.TransmitGlobalTime = DISABLE;

  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, data, (uint32_t *)CAN_TX_MAILBOX0) != HAL_OK)
  {
    if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, data, (uint32_t *)CAN_TX_MAILBOX1) != HAL_OK)
    {
      HAL_CAN_AddTxMessage(&hcan, &TxHeader, data, (uint32_t *)CAN_TX_MAILBOX2);
    }
  }
};
/**
 * @brief  接收FIFO0邮箱的信息，并传到CAN_Rxdata
 * @retval None
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef RxHeader;
  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, Rxdata);
  Txdata[0] = Rxdata[0];
	Txdata[0]++;
	Delay_ms_simple(500);
	CAN_Txdata(0x201, Txdata, 1);
}
/**
 * @brief  使CAN工作
 * @retval None
 */
void CAN_ENANBLE(void)
{
  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
  HAL_CAN_Start(&hcan);
}

void Delay_us_simple(uint32_t us)
{
    volatile uint32_t i;
    for (i = 0; i < us * 72 / 5; i++)
    {
        // 空循环，根据实际情况调整系数
    }
}

void Delay_ms_simple(uint32_t ms)
{
    volatile uint32_t i;
    for (i = 0; i < ms; i++)
    {
        Delay_us_simple(1000);
    }
}
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

#ifdef USE_FULL_ASSERT
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
