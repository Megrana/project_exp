#include "stm32f10x.h"
#include "delay.h"
#include "OLED.h"
#include "OELD_Data.h"
#include "Servo.h"
#include "PWM.h"
#include "METAL.h"
#include "HX711.h"



int32_t rawValue; 											// HX711传感器读取的原始称重数据
float weight;														// 计算后的实际重量值
int32_t tareValue;											// 空载时的传感器原始数据
float calibrationWeight = 100.0;  			// 校准用标准重量（已知质量，此处为100g）
int32_t calibrationRawValue = 8084000;  // 标准重量对应的传感器原始数据（100g重物放置时的rawValue）
#define EMPTY_WEIGHT_TOLERANCE 2
float angle1;
float angle2;
float angle3;
	
int main(void)
{
    HX711_Init();
    OLED_Init();
    METAL_Init();
		Servo_Init();
	
    OLED_ShowString(0,0, "bottle:", OLED_8X16);
    OLED_Update();
    
    tareValue = HX711_ReadData(); // 将当前无重物时的rawValue存储为tareValue，后续测量值减去此基准即得到净重量
   
    while(1)
    {

					if (METAL_Sensor_Read_Detection_State()==0)  // 检测到易拉罐
						{
            OLED_ShowString(0, 16, "can bottle",OLED_8X16);
									angle2+=90;
									Servo3_SetAngle1(angle2);
									Delay_s(1);
									angle2-=90;
									Servo3_SetAngle1(angle2);	
						}
			else
			{
				rawValue = HX711_ReadData();
        // 重量计算公式：(当前原始值 - 去皮值) * 校准重量 / (校准原始值 - 去皮值)
					weight = (rawValue - tareValue) * calibrationWeight / (calibrationRawValue - tareValue);
				 OLED_ShowNum(58, 0, weight, 4, OLED_8X16);
				if (fabs(weight) <= EMPTY_WEIGHT_TOLERANCE)
							{
									OLED_ShowString(0, 16, "empty               ", OLED_8X16); 
							}
				else if (fabs(weight) >= EMPTY_WEIGHT_TOLERANCE && fabs(weight) <= 60)
								{
									
							OLED_ShowString(0, 16, "plastic bottle", OLED_8X16);
									angle2+=90;
									Servo4_SetAngle2(angle2);
									Delay_s(1);
									angle2-=90;
									Servo4_SetAngle2(angle2);	
								}			
				else
				{
					OLED_ShowString(0, 16, "glass bottle    ", OLED_8X16);
									
									angle3+=90;
									Servo4_SetAngle1(angle3);	
									Delay_s(1);
									angle3-=90;
									Servo4_SetAngle1(angle3);
				}
			}
				OLED_Update();
				Delay_ms(500);
		}  
}
