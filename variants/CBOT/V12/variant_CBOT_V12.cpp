/*
 *******************************************************************************
 * Copyright (c) 2020, STMicroelectronics
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#if defined(ARDUINO_CBOT_V12)
#include "pins_arduino.h"

// Digital PinName array
const PinName digitalPin[] = {
  PC_13,  // HAT_CS
  PC_0,   // AD5941_CS
  PC_1,   // DRDY (LIS3MDL Data Ready)
  PB_2,   // SD_DET
  PB_10,  // SCL
  PB_11,  // SDA
  PB_12,  // SD_CS
  PB_13,  // SCK
  PB_14,  // MISO
  PB_15,  // MOSI
  PC_6,   // USER_LED_GREEN
  PC_7,   // USER_LED_RED
  PB_1,   // USER_LED_BLUE (moved from V11)
  PC_9,   // BAT_CH
  PA_8,   // BAT_CON
  PA_10,  // HAT_IO4
  PA_9,   // USB_VBUS
  PA_11,  // USB_DM
  PA_12,  // USB_DP
  PA_13,  // SWDIO
  PA_14,  // SWCLK
  PA_15,  // DONE (TPL5110 power timer)
  PA_3,   // HAT_EN  (SARA_ON)
  PA_2,   // HAT_RST (SARA_RESET)
  PA_0,   // HAT_TXD (SARA_TXD)
  PA_1,   // HAT_RXD (SARA_RXD)
  PB_3,   // SWO
  PB_4,   // HAT_IO1 (SARA_RTS)
  PB_5,   // HAT_IO2 (SARA_CTS)
  PA_6,   // HAT_IO3
  PB_6,   // Button_LED
  PB_8,   // AVCC_EN (AD5941 power)
  PB_9,   // DETECT (AD5941 electrode)
  PC_2,   // HAT_POWER_ON
};

// Analog (Ax) pin number array
const uint32_t analogInputPin[] = {
  // No analog pins
};

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

WEAK void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {};

  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE0) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSI
                              |RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 2;
  RCC_OscInitStruct.PLL.PLLN = 55;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV4;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_SDMMC1  
                                      | RCC_PERIPHCLK_UART4 | RCC_PERIPHCLK_USB 
                                      | RCC_PERIPHCLK_I2C2;
  // RCC_PERIPHCLK_I2C2;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_PLLP;
  PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_SYSCLK;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;
  PeriphClkInit.I2c2ClockSelection = RCC_I2C2CLKSOURCE_SYSCLK;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

}

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_CBOT_V12 */
