/*****************************************************************
ʵ�����ƣ�BCD��ʵ��

Ӳ��ģ�飺�����ԭ��Ӧ��ʵ����

Ӳ�����ߣ�ARM P12�ӿ�---------���뿪�� P1�ӿ�  
					 PF0~PF3-----------SW1~SW4
				ARM P11�ӿ�---------����� P4�ӿ� 
				   PC0--------SI
					 PC1--------RCK
					 PC2--------SCK
					 PC3--------A
					 PC4--------B
					 PC5--------C
		    ע������20P����ֱ��P12��P1�ӿڣ�20P����ֱ��P11��P4�ӿ�
				 
ʵ�������������ʾ���뿪��(SW1~SW5)�����ݣ���8421��ת������

����ʱ�䣺2018-10-11
*****************************************************************/
#include "stm32f4xx.h"
#include "delay.h"
#include "smg.h"
#include "exti.h"
uint8_t flag = 0;
/*******************************
��  �ܣ����뿪�ض˿ڳ�ʼ��
��  ������
����ֵ����
*******************************/

void Sw_Init(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //����GPIOF��ʱ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ;
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;           //����ģʽ
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;      
		GPIO_Init(GPIOF, &GPIO_InitStructure);
}


/*******************************
��  �ܣ�������ȡ
��  ������
����ֵ����
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
		Delay_Init();   //��ʱ��ʼ��
		//Sw_Init();     	//���뿪�س�ʼ��
		SMG_Init();  	  //����ܳ�ʼ��
		
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

