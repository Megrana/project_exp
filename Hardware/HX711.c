#include "HX711.h"
#include "delay.h"

void HX711_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(HX711_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = HX711_SCK_GPIO_PIN;
    GPIO_Init(HX711_SCK_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = HX711_DOUT_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(HX711_DOUT_GPIO_PORT, &GPIO_InitStructure);
}

uint32_t HX711_ReadData(void)
{
    uint32_t count = 0;  				// 存储读取到的24位数据
    uint8_t i;           				// 循环计数器
    
    HX711_SCK_LOW();     				// SCK置低电平，开始通信
    Delay_us(1);         				// 延时1us等待稳定
    
    while(HX711_DOUT_READ());		// 等待DOUT引脚变为低电平，表示HX711已准备好输出数据
    
    for (i = 0; i < 24; i++)		// 循环读取24位数据(MSB先行)
    {
        HX711_SCK_HIGH();       // SCK置高，驱动HX711输出下一位数据
        Delay_us(1);
        count = count << 1;     // 数据左移1位，腾出最低位空间
        HX711_SCK_LOW();        // SCK置低，完成当前位读取
        Delay_us(1);
        if(HX711_DOUT_READ())   // 读取DOUT引脚状态，若为高则最低位置1
            count++;
    }
    
    HX711_SCK_HIGH();						// 发送第25个SCK脉冲(用于设置增益/通道，此处默认配置)
    Delay_us(1);
    
    count = count ^ 0x800000;		// 将24位二进制补码转换为无符号数(最高位符号位取反)
    
    HX711_SCK_LOW();     				// 结束通信，SCK恢复低电平
    Delay_us(1);
    
    return count;       			  // 返回读取到的原始数据
}
