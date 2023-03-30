#include "time.h"

unsigned step=0;

void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx
}


void jishi(unsigned char sj1,unsigned char  sj2)//�������ϱ�ͨ��ʱ��   ����ͨ��ʱ��
{
	switch (step)
	{
		case 0://�ϱ��̣�������
			nanbei_dis=sj1;
		  dongxi_dis =sj1+huang;
		  led_kz(1,0);
		  step=1;
			break;
		case 1:
			if(nanbei_dis>0)
			{
				nanbei_dis--;
				dongxi_dis--;
			}
			else //�ϱ��ƣ�������
			{
				nanbei_dis=huang-1;
				dongxi_dis--;
				led_kz(2,0);
				step=2;flag=1;
			}		
			break;
		case 2:
			if(nanbei_dis>0)
			{
				if(flag==1)//�����ϱ��Ƶ���˸
				{
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
		      GPIO_SetBits(GPIOA,GPIO_Pin_1);	
		      GPIO_ResetBits(GPIOA,GPIO_Pin_2);	
        }
				else
				{
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
		      GPIO_ResetBits(GPIOA,GPIO_Pin_1);	
		      GPIO_ResetBits(GPIOA,GPIO_Pin_2);	
        }
				nanbei_dis--;
				dongxi_dis--;
			}
			else//�ϱ��죬������
			{
				nanbei_dis=sj2+huang;
				dongxi_dis=sj2;
				led_kz(0,1);
				step=3;
			}
			break;
		case 3:
			if(dongxi_dis>0)
			{
				nanbei_dis--;
				dongxi_dis--;
			}
			else//�ϱ��죬������
			{
				nanbei_dis--;
				dongxi_dis=huang-1;
				led_kz(0,2);
				step=4;flag=1;
			}
			break;
		case 4:
			if(nanbei_dis>0)
			{
				if(flag==1)//���ƶ����Ƶ���˸
				{
						GPIO_ResetBits(GPIOA,GPIO_Pin_3);	
		        GPIO_SetBits(GPIOA,GPIO_Pin_4);	
		        GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
        }
				else
				{
						GPIO_ResetBits(GPIOA,GPIO_Pin_3);	
	        	GPIO_ResetBits(GPIOA,GPIO_Pin_4);	
		        GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
        }
				nanbei_dis--;
				dongxi_dis--;
			}
			else
			{
				step=0;
			}
			break;
	}
}


//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
  static unsigned int a=0;
	
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ��
		a++;
    if(a>50)
		{
			if(mode==0)//�Զ�����
			{
			  jishi(nanbei,dongxi);
			}
			else if(mode==4)//�ֶ�����ͨ��ʱ��
			{
				 jishi(nanbei_set,dongxi_set);
			}
			a=0;
			
				if(flag==0)
				{
						flag=1;
				}
				else 
				{
						flag=0;
				}
		}
   		

		
			
	}
}
