#include "exti.h"

/*******************************
��  �ܣ��ⲿ�ж�����
��  ������
����ֵ����
*******************************/
void EXTI_Configure(void)
{
		GPIO_InitTypeDef GPIO_TypeDefStructure;
		EXTI_InitTypeDef EXTI_TypeDefStructure;
		NVIC_InitTypeDef NVIC_TypeDefStructure;
		
		//�����ж�����˿�ʱ��
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		
		//�����ⲿ�ж�ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		
		GPIO_TypeDefStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_TypeDefStructure.GPIO_Mode = GPIO_Mode_IN;     //ͨ������ģʽ
		GPIO_TypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP; 	  //����
		GPIO_Init(GPIOF, &GPIO_TypeDefStructure);

		//�ж��߹���
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource0);
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource1);
	
		EXTI_TypeDefStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;
		EXTI_TypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_TypeDefStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
		EXTI_TypeDefStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_TypeDefStructure);
		
		//EXT9_5_IRQn�ж��������ȼ�����
		NVIC_TypeDefStructure.NVIC_IRQChannel = EXTI0_IRQn | EXTI1_IRQn;
		NVIC_TypeDefStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_TypeDefStructure.NVIC_IRQChannelSubPriority = 7;
		NVIC_TypeDefStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_TypeDefStructure);
}



/*******************************
��  �ܣ��ⲿ�жϷ�����
��  ������
����ֵ����
*******************************/
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line8))
    {
        if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
        {
          //  LED1(!LED1_DATA());
            EXTI_ClearITPendingBit(EXTI_Line8);
        }
    }
}
void EXTI0_IRQHandler(void)
{
		if(EXTI_GetITStatus(EXTI_Line0))
		{
				if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1) == 0)
				{
					flag = 1; 
					EXTI_ClearITPendingBit(EXTI_Line0);
				}
		}
}

void EXTI1_IRQHandler(void)
{
		if(EXTI_GetITStatus(EXTI_Line1))
		{
				if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_0) == 0)
				{
						flag = 1;
					EXTI_ClearITPendingBit(EXTI_Line1);
				}
		}
}


