#ifndef __HX711_H
#define __HX711_H

#include "stm32f10x.h"
#include "delay.h"
#include "math.h"

#define HX711_GPIO_CLK                  RCC_APB2Periph_GPIOA
#define HX711_SCK_GPIO_PORT             GPIOA
#define HX711_SCK_GPIO_PIN              GPIO_Pin_0
#define HX711_DOUT_GPIO_PORT            GPIOA
#define HX711_DOUT_GPIO_PIN             GPIO_Pin_1

#define HX711_SCK_HIGH()                GPIO_SetBits(HX711_SCK_GPIO_PORT, HX711_SCK_GPIO_PIN)           // 设置SCK引脚为高电平（用于驱动HX711时钟信号）
#define HX711_SCK_LOW()                 GPIO_ResetBits(HX711_SCK_GPIO_PORT, HX711_SCK_GPIO_PIN)         // 设置SCK引脚为低电平（用于结束当前时钟周期）
#define HX711_DOUT_READ()               GPIO_ReadInputDataBit(HX711_DOUT_GPIO_PORT, HX711_DOUT_GPIO_PIN)

void HX711_Init(void);
uint32_t HX711_ReadData(void);

#endif
