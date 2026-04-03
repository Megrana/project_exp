#include "stm32f10x.h"                 

void PWM_Init(void)
{
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_3| GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	/*配置时钟源*/
		TIM_InternalClockConfig(TIM2);
		TIM_InternalClockConfig(TIM3);
		TIM_InternalClockConfig(TIM4);
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1;				
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;				
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;           
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);            
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	/*输出比较初始化*/ 
	TIM_OCInitTypeDef TIM_OCInitStructure;							
	TIM_OCStructInit(&TIM_OCInitStructure);                        
	                                                                                                    
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   
	TIM_OCInitStructure.TIM_Pulse = 0;							
	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	/*TIM使能*/
	TIM_Cmd(TIM2, ENABLE);			
	TIM_Cmd(TIM3, ENABLE);
	TIM_Cmd(TIM4,ENABLE);
}


void PWM4_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM4, Compare);
}

void PWM3_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM3, Compare);
}

void PWM4_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM4, Compare);
}

