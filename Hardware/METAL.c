#include "metal.h"
#include "delay.h"

void METAL_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
    GPIO_InitStructure.GPIO_Pin = METAL_DO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(METAL_DO_PORT, &GPIO_InitStructure);
}

uint8_t METAL_Sensor_Read_Detection_State(void)
{
   
    if (GPIO_ReadInputDataBit(METAL_DO_PORT, METAL_DO_PIN) == Bit_RESET)
    {
        return 1;
    }
    else
    {
        return 0; 
    }
}
