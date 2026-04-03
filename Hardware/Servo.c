#include "stm32f10x.h"                  
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();									
}

void Servo4_SetAngle2(float Angle)
{
	PWM4_SetCompare2(Angle / 180 * 2000 + 500);
}

void Servo3_SetAngle1(float Angle)
{
	PWM3_SetCompare1(Angle / 180 * 2000 + 500);
}

void Servo4_SetAngle1(float Angle)
{
	PWM4_SetCompare1(Angle / 180 * 2000 + 500);
}
