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
/*
 * Automatically generated from STM32L562RET6Q
 * CubeMX DB release 6.0.140
 */
#if defined(ARDUINO_CBOT_V12)
#include "Arduino.h"
#include "PeripheralPins.h"

/* =====
 * Notes:
 * - The pins mentioned Px_y_ALTz are alternative possibilities which use other
 *   HW peripheral instances. You can use them the same way as any other "normal"
 *   pin (i.e. analogWrite(PA7_ALT1, 128);).
 *
 * - Commented lines are alternative possibilities which are not used per default.
 *   If you change them, you will have to know what you do
 * =====
 */

//*** ADC ***

#ifdef HAL_ADC_MODULE_ENABLED
WEAK const PinMap PinMap_ADC[] = {
  // No analog pins configured for this board
  {NC,        NP,   0}
};
#endif

//*** DAC ***

#ifdef HAL_DAC_MODULE_ENABLED
WEAK const PinMap PinMap_DAC[] = {
  {PA_4, DAC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 1, 0)}, // DAC1_OUT1
  {PA_5, DAC1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 2, 0)}, // DAC1_OUT2
  {NC,   NP,   0}
};
#endif

//*** I2C ***

#ifdef HAL_I2C_MODULE_ENABLED
WEAK const PinMap PinMap_I2C_SDA[] = {
  {PB_11,      I2C2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)},
  {NC,         NP,   0}
};

WEAK const PinMap PinMap_I2C_SCL[] = {
  {PB_10,      I2C2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)},
  {NC,         NP,   0}
};
#endif

//*** PWM ***

#ifdef HAL_TIM_MODULE_ENABLED
WEAK const PinMap PinMap_PWM[] = {
  {PB_3,       TIM2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF1_TIM2, 2, 0)}, // TIM2_CH2
  {PB_4,       TIM3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 1, 0)}, // TIM3_CH1
  {PB_5,       TIM3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 2, 0)}, // TIM3_CH2
  {PB_6,       TIM4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM4, 1, 0)}, // TIM4_CH1
  {PB_7,       TIM4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM4, 2, 0)}, // TIM4_CH2
  {PB_8,       TIM4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM4, 3, 0)}, // TIM4_CH3
  {PB_9,       TIM4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM4, 4, 0)}, // TIM4_CH4
  {PC_6,       TIM3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 1, 0)}, // TIM3_CH1
  {PC_7,       TIM3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 2, 0)}, // TIM3_CH2
  {PC_8,       TIM3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 3, 0)}, // TIM3_CH3
  {PC_9,       TIM3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF2_TIM3, 4, 0)}, // TIM3_CH4
  {NC,         NP,    0}
};
#endif

//*** SERIAL ***

#ifdef HAL_UART_MODULE_ENABLED
WEAK const PinMap PinMap_UART_TX[] = {
  {PA_9,       USART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
  {PC_12,      UART5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)},
  {NC,         NP,     0}
};

WEAK const PinMap PinMap_UART_RX[] = {
  {PA_10,      USART1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},
  {PD_2,       UART5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)},
  {NC,         NP,     0}
};

WEAK const PinMap PinMap_UART_RTS[] = {
  {PB_4,       UART5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)},
  {NC,         NP,     0}
};

WEAK const PinMap PinMap_UART_CTS[] = {
  {PB_5,       UART5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)},
  {NC,         NP,     0}
};
#endif

//*** SPI ***

#ifdef HAL_SPI_MODULE_ENABLED
WEAK const PinMap PinMap_SPI_MOSI[] = {
  {PB_15,      SPI2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI2)},
  {NC,         NP,   0}
};

WEAK const PinMap PinMap_SPI_MISO[] = {
  {PB_14,      SPI2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI2)},
  {NC,         NP,   0}
};

WEAK const PinMap PinMap_SPI_SCLK[] = {
  {PB_13,      SPI2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI2)},
  {NC,         NP,   0}
};

WEAK const PinMap PinMap_SPI_SSEL[] = {
  {PB_12,      SPI2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF5_SPI2)},
  {NC,         NP,   0}
};
#endif

//*** OSPI ***

#ifdef HAL_OSPI_MODULE_ENABLED
WEAK const PinMap PinMap_OSPI_DATA0[] = {
  {PB_1,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_IO0
  {NC,         NP,       0}
};

WEAK const PinMap PinMap_OSPI_DATA1[] = {
  {PB_0,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_IO1
  {NC,         NP,       0}
};

WEAK const PinMap PinMap_OSPI_DATA2[] = {
  {PA_7,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_IO2
  {NC,         NP,       0}
};

WEAK const PinMap PinMap_OSPI_DATA3[] = {
  {PA_6,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_IO3
  {NC,         NP,       0}
};

WEAK const PinMap PinMap_OSPI_DATA4[] = {
  {PC_1,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_IO4
  {NC,         NP,       0}
};

WEAK const PinMap PinMap_OSPI_DATA5[] = {
  {PC_2,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_IO5
  {NC,         NP,       0}
};

WEAK const PinMap PinMap_OSPI_DATA6[] = {
  {PC_3,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_IO6
  {NC,         NP,       0}
};

WEAK const PinMap PinMap_OSPI_DATA7[] = {
  {PC_0,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_IO7
  {NC,         NP,       0}
};

WEAK const PinMap PinMap_OSPI_SCLK[] = {
  {PA_3,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_CLK
  {NC,         NP,       0}
};

WEAK const PinMap PinMap_OSPI_SSEL[] = {
  {PA_2,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_NCS
  {NC,         NP,       0}
};

WEAK const PinMap PinMap_OSPI_DQS[] = {
  {PB_2,       OCTOSPI1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_OCTOSPI1)}, // OCTOSPI1_DQS
  {NC,         NP,       0}
};
#endif

//*** USB ***

#ifdef HAL_PCD_MODULE_ENABLED
WEAK const PinMap PinMap_USB_OTG_FS[] = {
  {PA_11,      USB_OTG_FS, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_DM
  {PA_12,      USB_OTG_FS, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF10_OTG_FS)}, // USB_OTG_FS_DP
  {NC,         NP,         0}
};
#endif

//*** SD ***

#ifdef HAL_SD_MODULE_ENABLED
WEAK const PinMap PinMap_SD[] = {
  {PC_8,       SDMMC1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF12_SDIO1)}, // SDMMC1_D0
  {PC_9,       SDMMC1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF12_SDIO1)}, // SDMMC1_D1
  {PC_10,      SDMMC1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF12_SDIO1)}, // SDMMC1_D2
  {PC_11,      SDMMC1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF12_SDIO1)}, // SDMMC1_D3
  {PC_12,      SDMMC1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF12_SDIO1)}, // SDMMC1_CK
  {PD_2,       SDMMC1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF12_SDIO1)}, // SDMMC1_CMD
  {NC,         NP,     0}
};
#endif

#endif /* ARDUINO_CBOT_V12 */
