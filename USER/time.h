#ifndef _time_H
#define _time_H

#include "stm32f10x.h"


extern unsigned char mode;
extern unsigned char  flag;//�Ƶ���˸

//ʱ����ʾ
extern unsigned char  nanbei_dis;   //�ϱ������ʱ��(ʵʱ��ʾ)
extern unsigned char  dongxi_dis;   //���������ʱ��(ʵʱ��ʾ)

//�ֶ����õ�ʱ��
extern unsigned char  nanbei_set;   //�ϱ������ʱ��
extern unsigned char  dongxi_set;   //���������ʱ��

//�Զ�ģʽ��ͨ��ʱ��
extern unsigned char  nanbei;   //�ϱ������ʱ��
extern unsigned char  dongxi;   //���������ʱ��

extern unsigned char  huang;     //�Ƶ�ʱ��

extern void led_kz(unsigned char c1,unsigned char c2);
void TIM3_Int_Init(u16 arr,u16 psc);

#endif
