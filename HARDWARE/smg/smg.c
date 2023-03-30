#include "stm32f10x.h"
#include "smg.h"
void SMG_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
//ʹ��GPIOCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = 0x00ff;					//PC0-PC7��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //GPIOC�ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				//��ʼ��PC0-PC7
	
  GPIO_InitStructure.GPIO_Pin = 0x003f;					//PB0-PC5��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //GPIOB�ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);				//��ʼ��PB0-PB5
	
	//��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //GPIOB�ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);	

	
	//����
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6| GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9; 			
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;  //��������
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;      //�ٶ�
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}
