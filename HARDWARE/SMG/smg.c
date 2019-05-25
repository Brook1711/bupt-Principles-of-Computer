#include "smg.h"
#include "delay.h"

uint8_t digivalue[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07           //��ʾ���������飬����Ϊ0~F  0x00ȫ��
                       , 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, 0x00};  
uint8_t smg_data[8] = {0x00, 0x01, 0x04, 0x00, 0x00, 0x01, 0x04, 0x00};


/*******************************
��  �ܣ�����ܶ˿ڳ�ʼ��
��  ������
����ֵ����
*******************************/
void SMG_Init(void)
{
    GPIO_InitTypeDef   GPIO_InitStructure;
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //����GPIOF��ʱ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 
																| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //������� 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //�ٶ�50MHz
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*******************************
��  �ܣ�HC595��������
��  ����dat    ����
����ֵ����
*******************************/
void HC595_Send(uint8_t dat)
{
		uint8_t dat_buf = 0, i;
		for(i=0; i<8; i++)
		{
			dat_buf = dat & 0x80;
			if (dat_buf) //���1bit����
			{
				SI = 1;    //��74HC595��������������������Ϊ�ߵ�ƽ
			}
			else
			{
				SI = 0;    //��74HC595��������������������Ϊ�͵�ƽ
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
��  �ܣ������λ�ο���
��  ����index   ��Ӧ�������
����ֵ����
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
��  �ܣ��������ʾ����
��  ������
����ֵ����
*******************************/
void SMG_Display(void)
{
   static uint8_t i = 0;	
   SMG_Sele(i);  //�������ʾ����
   i++;
   i &= 0x07;
}


