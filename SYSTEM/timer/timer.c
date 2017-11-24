#include "timer.h"

void TIM3_OC_Init(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef       TIM_OCInitStructure;
//////////////////////////////////////ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3,ENABLE);	    //TIM3ʱ��ʹ��
//////////////////////////////////////���ų�ʼ��////////////////////////	
  //PB0
  //PB1	
	//���Ÿ���
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource0,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource1,GPIO_AF_TIM3);	

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
//////////////////////////////////////TIM3��ʱ���ʼ��
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=20000-1;                    //Ƶ��50hz
	TIM_TimeBaseInitStructure.TIM_Prescaler=84-1;
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
//////////////////////////////////////TIM3�Ƚ�ͨ����ʼ��
//CH3  CH4
//���ϼ�����PWM1ģʽ,ռ�ձȳ�ʼ��Ϊ5%,Ƶ��50hz
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;	
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;	
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;	
	TIM_OCInitStructure.TIM_Pulse=1000;                                    //ռ�ձ�5%��
//CH3	
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);	
//CH4
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
//ʹ��
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	
  TIM_CtrlPWMOutputs(TIM3,ENABLE);
	TIM_Cmd(TIM3, ENABLE);

}


void TIM3_OCH3_PLUSE(u32 pluse)
{
	TIM_SetCompare3(TIM3, pluse);
}

void TIM3_OCH4_PLUSE(u32 pluse)
{
	TIM_SetCompare4(TIM3, pluse);
}

