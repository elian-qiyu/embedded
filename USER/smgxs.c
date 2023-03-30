#include "stm32f10x.h"
#include "Delay.h"
#include "smg.h"
#include "time.h"


#define k1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define k2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)
#define k3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define k4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)

//����0��9ʮ�����ֵ��������
unsigned int table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0xff};   
unsigned int wei[]={0x0fe,0x0fd,0x0fb,0x0f7,0x0ef,0x0df,0xff,0xff}; //λ��;

unsigned char mode=0;  //0�����Զ�  1��������   2�������ɵ�  3����֧·  4�����ֶ�   5�������

//ʱ����ʾ
unsigned char  nanbei_dis=20;   //�ϱ������ʱ��(ʵʱ��ʾ)
unsigned char  dongxi_dis=15;   //���������ʱ��(ʵʱ��ʾ)

//�ֶ����õ�ʱ��
unsigned char  nanbei_set=40;   //�ϱ������ʱ��
unsigned char  dongxi_set=40;   //���������ʱ��

//�Զ�ģʽ��ͨ��ʱ��
unsigned char  nanbei=20;   //�ϱ������ʱ��
unsigned char  dongxi=15;   //���������ʱ��

unsigned char  huang=3;     //�Ƶ�ʱ��
extern unsigned step;
unsigned char  flag=0;//�Ƶ���˸

//�������ʾ����
void display(unsigned char a,unsigned char b)
{
	GPIO_Write(GPIOB,wei[0]);
	GPIO_Write(GPIOC,table[a/10]);
	Delay(23);
	GPIO_Write(GPIOB,0x0ff);
	Delay(23);
	
	GPIO_Write(GPIOB,wei[1]);
	GPIO_Write(GPIOC,table[a%10]);
	Delay(23);
	GPIO_Write(GPIOB,0x0ff);
	Delay(23);
	
	GPIO_Write(GPIOB,wei[2]);
	GPIO_Write(GPIOC,table[b/10]);
	Delay(23);
	GPIO_Write(GPIOB,0x0ff);
	Delay(23);
	
	GPIO_Write(GPIOB,wei[3]);
	GPIO_Write(GPIOC,table[b%10]);
	Delay(23);
	GPIO_Write(GPIOB,0x0ff);
	Delay(23);
}

//���̵���ɫ����  0���  1�̵�  2�Ƶ�
void led_kz(unsigned char c1,unsigned char c2)
{
	if(c1==0)//�ϱ����
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);	
		GPIO_SetBits(GPIOA,GPIO_Pin_2);	
	}
  else if(c1==1)//�ϱ��̵�
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);	
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);	
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);	
	}
	else if(c1==2)//�ϱ��Ƶ�
	{

		 GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
		 GPIO_SetBits(GPIOA,GPIO_Pin_1);	
		 GPIO_ResetBits(GPIOA,GPIO_Pin_2);	

	}
	
	if(c2==0)//�ϱ����
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_3);	
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);	
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
	}
  else if(c2==1)//�ϱ��̵�
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_3);	
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);	
		GPIO_SetBits(GPIOA,GPIO_Pin_5);	
	}
	else if(c2==2)//�ϱ��Ƶ�
	{

		GPIO_ResetBits(GPIOA,GPIO_Pin_3);	
		GPIO_SetBits(GPIOA,GPIO_Pin_4);	
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);	

	}
	
}




void key()
{
	if(k1==0)	
	{	
		if(mode==0)
		{
			nanbei_dis=nanbei_set;
			dongxi_dis=dongxi_set;
			mode=1;//��������
    }
		else if(mode==1)
		{
			nanbei_dis=nanbei_set;
			dongxi_dis=dongxi_set;
			mode=2;//�������ɵ�
    }
		else if(mode==2)
		{
			nanbei_dis=nanbei_set;
			dongxi_dis=dongxi_set;
			mode=3;//����֧·
    }
		else if(mode==3)
		{
			nanbei_dis=nanbei_set;
			dongxi_dis=dongxi_set;
			mode=4;//�������õ�ʱ��
    }
		else if(mode==4)
		{
			nanbei_dis=nanbei;
			dongxi_dis=dongxi;
			mode=0;//�����Զ�ѭ��
    }
		else 
		{
			nanbei_dis=nanbei;
			dongxi_dis=dongxi;
			mode=0;
    }
		step=0;
		while(!k1);	 
	}	
	
		if(k2==0)	//jia
		{
			if(mode==2)
			{
				if(nanbei_set<60)
				nanbei_set++;
      }
			else if(mode==3)
			{
				if(dongxi_set<60)
				dongxi_set++;
      }
			while(!k2);	
    }
		
		if(k3==0)	//jian
		{
			if(mode==2)
			{
				if(nanbei_set>10)
				{
					nanbei_set--;
        }
      }
			else if(mode==3)
			{
				if(dongxi_set>10)
				{
					dongxi_set--;
        }
      }
			while(!k3);	
    }
		
		if(k4==0)	
		{
			mode=5;
			while(!k4);	
    }
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM3_Int_Init(799,99);
	SMG_Init();
	nanbei_dis=nanbei;//��ʼ��ʾ��ֵ
	dongxi_dis=dongxi;
	while(1)
	{
		key();
		if((mode==0)||(mode==4))//��ʾ����ʱ(����ʱ)
		{
			 display(nanbei_dis,dongxi_dis);
    }
		else if((mode==1)||(mode==2)||(mode==3))//��ʾ���õ�ʱ�䣨����ʱ��
		{	 
			display(nanbei_set,dongxi_set);			 
    }
		else//��������
		{
			GPIO_Write(GPIOB,0x0ff);//�ر��������ʾ
			led_kz(0,0);//ȫ�����
    }
		
	}
}
