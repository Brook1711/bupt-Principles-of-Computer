/*****************************************************************
实验名称：BCD码实验

硬件模块：计算机原理应用实验箱

硬件接线：ARM P12接口---------拨码开关 P1接口  
					 PF0~PF3-----------SW1~SW4
				ARM P11接口---------数码管 P4接口 
				   PC0--------SI
					 PC1--------RCK
					 PC2--------SCK
					 PC3--------A
					 PC4--------B
					 PC5--------C
		    注：可用20P排线直连P12、P1接口，20P排线直连P11、P4接口
				 
实验现象：数码管显示拨码开关(SW1~SW5)的数据（以8421码转换）。

更新时间：2018-10-11
*****************************************************************/
#include "stm32f4xx.h"
#include "delay.h"
#include "smg.h"
#include "exti.h"
uint8_t flag = 0;
/*******************************
功  能：拨码开关端口初始化
参  数：无
返回值：无
*******************************/

void Sw_Init(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //开启GPIOF的时钟
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;           //输入模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      
		GPIO_Init(GPIOF, &GPIO_InitStructure);
}


/*******************************
功  能：数据提取
参  数：无
返回值：无
*******************************/
void Draw_Data(void)
{
   smg_data[0] = 0x10;
	smg_data[1] = 0x10;
	 smg_data[2] = 0x10;
	smg_data[3] = 0x10;
	   smg_data[4] = 0x10;
	smg_data[5] = 0x10;
	 smg_data[6] = 0x10;
	smg_data[7] = 0x10;
}
void Draw_Data1(void)
{
   smg_data[0] = 0x00;
	smg_data[1] = 0x01;
	 smg_data[2] = 0x04;
	smg_data[3] = 0x00;
	   smg_data[4] = 0x00;
	smg_data[5] = 0x01;
	 smg_data[6] = 0x04;
	smg_data[7] = 0x00;
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	EXTI_Configure();
		Delay_Init();   //延时初始化
		//Sw_Init();     	//拨码开关初始化
		SMG_Init();  	  //数码管初始化
		
		while(1)
    {
							SMG_Display();
			//	Draw_Data(); 
			if(flag == 1)
			{
				Draw_Data1();

			}
			else
			{
				flag = 0;
			}
			if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1) == 1 || GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0) == 1)
			{flag = 0;
			Draw_Data();}
    }
}



//end file

