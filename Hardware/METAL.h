#ifndef __METAL_H
#define __METAL_H

#include "stm32f10x.h"
#include "delay.h"
#include "math.h"

#define METAL_GPIO_CLK      RCC_APB2Periph_GPIOB
#define METAL_DO_PORT GPIOA
#define METAL_DO_PIN  GPIO_Pin_2

void METAL_Init(void);

uint8_t METAL_Sensor_Read_Detection_State(void);

#endif
