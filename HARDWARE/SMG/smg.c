#include "smg.h"
#include "delay.h"

uint8_t digivalue[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07           //显示的数字数组，依次为0~F  0x00全灭
                       , 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00};  
uint8_t smg_data[8] = {0x00, 0x01, 0x04, 0x00, 0x00, 0x01, 0x04, 0x00};


/*******************************
功  能：数码管端口初始化
参  数：无
返回值：无
*******************************/
void SMG_Init(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //开启GPIOF的时钟
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 
																| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //推挽输出 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //速度50MHz
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*******************************
功  能：HC595发送数据
参  数：dat    数据
返回值：无
*******************************/
void HC595_Send(uint8_t dat)
{
		uint8_t dat_buf = 0, i;
		for(i=0; i<8; i++)
		{
			dat_buf = dat & 0x80;
			if (dat_buf) //输出1bit数据
			{
				SI = 1;    //将74HC595串行数据输入引脚设置为高电平
			}
			else
			{
				SI = 0;    //将74HC595串行数据输入引脚设置为低电平
			}
			SCK = 0;
			Delay_Us(1);
			SCK = 1;
			Delay_Us(1);
			dat <<= 1;
		}
		RCK = 0;
		Delay_Us(3);
		RCK = 1;
}


/*******************************
功  能：数码管位段控制
参  数：index   对应的数码管
返回值：无
*******************************/
void SMG_Sele(uint8_t index)
{
   HC595_Send(digivalue[smg_data[index]]);  	 
   switch(index)
   {
	   case 0: 
		    HC138_C = 0;  HC138_B = 0;  HC138_A = 0;
		    break;
	   case 1: 
		    HC138_C = 0;  HC138_B = 0;  HC138_A = 1;
		    break;
	   case 2: 
		    HC138_C = 0;  HC138_B = 1;  HC138_A = 0;
		    break;
       case 3:
          HC138_C = 0;  HC138_B = 1;  HC138_A = 1;	   
		    break;
	   case 4: 
		    HC138_C = 1;  HC138_B = 0;  HC138_A = 0;
		    break;
	   case 5: 
		    HC138_C = 1;  HC138_B = 0;  HC138_A = 1;
		    break;
	   case 6: 
		    HC138_C = 1;  HC138_B = 1;  HC138_A = 0;
		    break;
	   case 7: 
		    HC138_C = 1;  HC138_B = 1;  HC138_A = 1;
		    break;
	   default:
	        break;
   }  
}


/*******************************
功  能：数码管显示函数
参  数：无
返回值：无
*******************************/
void SMG_Display(void)
{
   static uint8_t i = 0;	
   SMG_Sele(i);  //数码管显示数据
   i++;
   i &= 0x07;
}


