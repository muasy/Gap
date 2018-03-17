/*
*********************************************************************************************************
* @file    	Gap.h
* @author  	SY
* @version 	V1.0.0
* @date    	2017-8-22 09:45:41
* @IDE	 	Keil V5.22.0.0
* @Chip    	STM32F407VE
* @brief   	General Abstract Package Head
*********************************************************************************************************
* @attention
*
* 
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Define to prevent recursive inclusion
*********************************************************************************************************
*/
#ifndef __GAP_H
#define __GAP_H

/*
*********************************************************************************************************
*                              				Exported Includes
*********************************************************************************************************
*/
#include <stdbool.h>
#include <string.h>
#include "stm32f10x.h"



/*
*********************************************************************************************************
*                              				Exported define
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Exported types
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                              				��������
*********************************************************************************************************
*/
typedef enum
{
	STATUS_PERIOD_TASK_IDLE = 0,
	STATUS_PERIOD_TASK_ON,
	STATUS_PERIOD_TASK_OFF,
	STATUS_PERIOD_TASK_DONE,
}PERIOD_TASK_STATUS_TypeDef;

typedef struct
{
	/* ����������ʵ�� */
	PERIOD_TASK_STATUS_TypeDef status;					//״̬
	uint32_t runPeriod;									//������������(��λ��ms)
	void *devicePtr;									//�豸ָ��
	
	/* �ص����� */
	void (*taskStartNotify_CallBack)( void *devicePrt );//��ʼ֪ͨ
	void (*onDevice_CallBack)( void *devicePrt );		//���豸
	void (*offDevice_CallBack)( void *devicePrt );		//�ر��豸
	void (*taskDoneNotify_CallBack)( void *devicePrt );	//���֪ͨ
	
	/* �ɱ�������ʵ�� */
	bool enableFlag;							//ʹ�ܿ���
	bool disableFlag;							//ʧ�ܿ���
	bool done;									//��ɱ�ʶ
	uint32_t executeNums;						//ִ�д���
	uint32_t onTime;							//��ʱ��
	uint32_t offTime;							//�ر�ʱ��
	uint32_t executeCount;						//ִ�ж��������
	uint32_t onCount;							//�򿪼�����
	uint32_t offCount;							//�رռ�����
}PERIOD_TASK_TypeDef;	

/*
*********************************************************************************************************
*                              				IOģ��PWM����
*********************************************************************************************************
*/
typedef enum
{
	PWM_IO_STATUS_IDLE = 0,
	PWM_IO_STATUS_OPEN,
	PWM_IO_STATUS_CLOSE,
	PWM_IO_STATUS_DONE,
}PWM_IO_STATUS_TypeDef;

typedef struct
{
	/* ����������ʵ�� */
	PWM_IO_STATUS_TypeDef status;					//״̬
	float runPeriod;								//��������
	float outputPeriod;								//�������
	uint16_t maxControlDegree;						//��������
	void *devicePrt;								//�豸ָ��
	
	/* �ص����� */
	void (*taskStartNotify_CallBack)( void *devicePrt );//��ʼ֪ͨ
	void (*onDevice_CallBack)( void *devicePrt );		//���豸
	void (*offDevice_CallBack)( void *devicePrt );		//�ر��豸
	void (*taskDoneNotify_CallBack)( void *devicePrt );	//���֪ͨ
	
	/* �ɱ�������ʵ�� */
	bool enableFlag;								//ʹ�ܿ���
	bool disableFlag;								//ʧ�ܿ���
	bool continueRunFlag;							//�������п���
	uint16_t dutyCycle;								//ռ�ձ�
	uint32_t PWM_Count;								//PWM������
	uint32_t sumCount;								//��ִ�д���
	uint32_t Reg_CCR;								//�Ƚϼ�����
}PWM_IO_TypeDef;

/*
*********************************************************************************************************
*                              				��������
*********************************************************************************************************
*/
typedef enum
{
	SWITCH_TASK_IDLE = 0,
	SWITCH_TASK_OPEN,
	SWITCH_TASK_OPEN_NOTIFY,
	SWITCH_TASK_CLOSE,
	SWITCH_TASK_CLOSE_NOTIFY,
}SWITCH_TASK_STATUS_TypeDef;

typedef struct
{
	/* ����������ʵ�� */
	SWITCH_TASK_STATUS_TypeDef status;					//״̬
	void *devicePrt;									//�豸ָ��
	
	/* �ص����� */
	bool (*isSwitchOn_CallBack)( void *devicePrt );		//�����Ƿ��
	void (*onDevice_CallBack)( void *devicePrt );		//�򿪿���֪ͨ
	void (*offDevice_CallBack)( void *devicePrt );		//�رտ���֪ͨ
	
	/* �ɱ�������ʵ�� */	
}SWITCH_TASK_TypeDef;

/*
*********************************************************************************************************
*                              				��ʱ������
*********************************************************************************************************
*/
typedef enum
{
	TIMER_TASK_IDLE = 0,
	TIMER_TASK_WORKING,
	TIMER_TASK_DONE,
}TIMER_TASK_STATUS_TypeDef;

typedef struct
{
	/* ����������ʵ�� */
	TIMER_TASK_STATUS_TypeDef status;				//״̬
	uint32_t runPeriod;								//��������
	void *devicePrt;								//�豸ָ��
	
	/* �ص����� */
	void (*timeUpNotify_CallBack)( void *devicePrt );//ʱ�䵽��֪ͨ
	
	/* �ɱ�������ʵ�� */
	bool enableFlag;								//ʹ�ܿ���
	bool disableFlag;								//ʧ�ܿ���
	uint32_t decreaseCount;							//�ݼ�������
	uint32_t countTimeMS;							//����ʱ��
}TIMER_TASK_TypeDef;

/*
*********************************************************************************************************
*                              				����
*********************************************************************************************************
*/
typedef enum {
	HEARTBEAT_STATUS_IDLE = 0,
	HEARTBEAT_STATUS_LOAD,
	HEARTBEAT_STATUS_BEAT,
	HEARTBEAT_STATUS_SLEEP,
	HEARTBEAT_STATUS_DONE,
	HEARTBEAT_STATUS_STOP,
}HEARTBEAT_ENUM;

typedef struct {
	/* �ڲ����� */
	HEARTBEAT_ENUM status;
	uint32_t time;
	
	/* �ⲿ���� */
	void *private;
	uint32_t runPeriod;
	uint32_t beatCnt;
	uint32_t beatPeriod;
	uint32_t period;
	PERIOD_TASK_TypeDef cycle;
	
	/* �ɱ�������ʵ�� */
	bool enable;										//ʹ�ܿ���
	bool disable;										//ʧ�ܿ���
	
	/* �ص����� */
	void (*notify_Start)( void *private );				//��ʼ֪ͨ
	void (*notify_Open)( void *private );				//���豸
	void (*notify_Close)( void *private );				//�ر��豸
	void (*notify_Done)( void *private );				//���֪ͨ
}HEARTBEAT_TypeDef;

/*
*********************************************************************************************************
*                              				Exported constants
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Exported macro
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Exported variables
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Exported functions
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                              				��������
*********************************************************************************************************
*/
void PeriodTaskInit( PERIOD_TASK_TypeDef *this, uint32_t runPeriod, \
		uint32_t executeNums, uint32_t onTimeMS, uint32_t offTimeMS, void *devicePtr );
void PeriodTaskDeInit( PERIOD_TASK_TypeDef *this );
void SetPeriodTaskExecuteTime( PERIOD_TASK_TypeDef *this,\
		uint32_t executeNums, uint32_t onTimeMS, uint32_t offTimeMS );
void OpenPeriodExecuteTask( PERIOD_TASK_TypeDef *this );
void ClosePeriodExecuteTask( PERIOD_TASK_TypeDef *this );	
void PeriodTaskCycle( PERIOD_TASK_TypeDef *this );
void RegisterPeriodTaskStartNotify_CallBack( PERIOD_TASK_TypeDef *this,\
		void (*taskStartNotify_CallBack)( void *devicePrt ) );
void RegisterPeriodTaskOnDevice_CallBack( PERIOD_TASK_TypeDef *this,\
		void (*onDevice_CallBack)( void *devicePrt ) );
void RegisterPeriodTaskOffDevice_CallBack( PERIOD_TASK_TypeDef *this,\
		void (*offDevice_CallBack)( void *devicePrt ) );
void RegisterPeriodTaskDoneNotify_CallBack( PERIOD_TASK_TypeDef *this,\
		void (*taskDoneNotify_CallBack)( void *devicePrt ) );

/*
*********************************************************************************************************
*                              				IOģ��PWM����
*********************************************************************************************************
*/
void PWM_IO_OutputInit( PWM_IO_TypeDef *PWM, float runPeriod, float outputPeriod, 
						uint16_t maxControlDegree, void *devicePrt );
void PWM_IO_OutputDeInit( PWM_IO_TypeDef *PWM );
void PWM_IO_SetOutput( PWM_IO_TypeDef *PWM, uint16_t dutyCycle );
void PWM_IO_CloseOutput( PWM_IO_TypeDef *PWM );
void PWM_IO_OutputCycle( PWM_IO_TypeDef *PWM_ObjPtr );
void RegisterPWM_IO_TaskStartNotify_CallBack( PWM_IO_TypeDef *PWM_IO_Ptr,\
		void (*taskStartNotify_CallBack)( void *devicePrt ) );
void RegisterPWM_IO_TaskOnDevice_CallBack( PWM_IO_TypeDef *PWM_IO_Ptr,\
		void (*onDevice_CallBack)( void *devicePrt ) );
void RegisterPWM_IO_TaskOffDevice_CallBack( PWM_IO_TypeDef *PWM_IO_Ptr,\
		void (*offDevice_CallBack)( void *devicePrt ) );
void RegisterPWM_IO_TaskDoneNotify_CallBack( PWM_IO_TypeDef *PWM_IO_Ptr,\
		void (*taskDoneNotify_CallBack)( void *devicePrt ) );

/*
*********************************************************************************************************
*                              				��������
*********************************************************************************************************
*/
void SwitchTaskInit( SWITCH_TASK_TypeDef *switchPtr, void *devicePrt );
void SwitchTaskDeInit( SWITCH_TASK_TypeDef *switchPtr );
void SwitchTask( SWITCH_TASK_TypeDef *switchPtr );
void RegisterSwitchTaskIsSwitchOn_CallBack( SWITCH_TASK_TypeDef *switchPtr,\
		bool (*isSwitchOn_CallBack)( void *devicePrt ) );
void RegisterSwitchTaskOnDevice_CallBack( SWITCH_TASK_TypeDef *switchPtr,\
		void (*onDevice_CallBack)( void *devicePrt ) );
void RegisterSwitchTaskOffDevice_CallBack( SWITCH_TASK_TypeDef *switchPtr,\
		void (*offDevice_CallBack)( void *devicePrt ) );
		
/*
*********************************************************************************************************
*                              				��ʱ������
*********************************************************************************************************
*/
void TimerTaskInit( TIMER_TASK_TypeDef *wwdgPtr, uint32_t runPeriod, 
						void *devicePrt);
void TimerTaskDeInit( TIMER_TASK_TypeDef *wwdgPtr );
void SetTimerCounter( TIMER_TASK_TypeDef *wwdgPtr,\
		uint32_t countTimeMS );
void CloseTimerTask( TIMER_TASK_TypeDef *wwdgPtr );
void RegisterTimerTaskTimeUpNotify_CallBack( TIMER_TASK_TypeDef *wwdgPtr,\
		void (*timeUpNotify_CallBack)( void *devicePrt ) );
void TimerTaskCycle( TIMER_TASK_TypeDef *wwdgPtr );

/*
*********************************************************************************************************
*                              				����
*********************************************************************************************************
*/
void HeartBeat_Init(HEARTBEAT_TypeDef *this, uint32_t runPeriod, uint32_t beatPeriod,\
		uint32_t beatCnt, uint32_t period, void *private);
void HeartBeat_Start(HEARTBEAT_TypeDef *this);
void HeartBeat_Stop(HEARTBEAT_TypeDef *this);		
void RegisterHeartbeatOpenDevice_CallBack(HEARTBEAT_TypeDef *this,\
		void (*notify_Open)( void *private ));
void RegisterHeartbeatCloseDevice_CallBack(HEARTBEAT_TypeDef *this,\
		void (*notify_Close)( void *private ));
void HeartBeat_Exec(HEARTBEAT_TypeDef *this);	


#endif
/************************ (C) COPYRIGHT STMicroelectronics **********END OF FILE*************************/
