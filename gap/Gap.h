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
*                              				周期任务
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
	/* 由主调函数实现 */
	PERIOD_TASK_STATUS_TypeDef status;					//状态
	uint32_t runPeriod;									//函数运行周期(单位：ms)
	void *devicePtr;									//设备指针
	
	/* 回调函数 */
	void (*taskStartNotify_CallBack)( void *devicePrt );//开始通知
	void (*onDevice_CallBack)( void *devicePrt );		//打开设备
	void (*offDevice_CallBack)( void *devicePrt );		//关闭设备
	void (*taskDoneNotify_CallBack)( void *devicePrt );	//完成通知
	
	/* 由被调函数实现 */
	bool enableFlag;							//使能开关
	bool disableFlag;							//失能开关
	bool done;									//完成标识
	uint32_t executeNums;						//执行次数
	uint32_t onTime;							//打开时间
	uint32_t offTime;							//关闭时间
	uint32_t executeCount;						//执行对象计数器
	uint32_t onCount;							//打开计数器
	uint32_t offCount;							//关闭计数器
}PERIOD_TASK_TypeDef;	

/*
*********************************************************************************************************
*                              				IO模拟PWM任务
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
	/* 由主调函数实现 */
	PWM_IO_STATUS_TypeDef status;					//状态
	float runPeriod;								//运行周期
	float outputPeriod;								//输出周期
	uint16_t maxControlDegree;						//最大控制量
	void *devicePrt;								//设备指针
	
	/* 回调函数 */
	void (*taskStartNotify_CallBack)( void *devicePrt );//开始通知
	void (*onDevice_CallBack)( void *devicePrt );		//打开设备
	void (*offDevice_CallBack)( void *devicePrt );		//关闭设备
	void (*taskDoneNotify_CallBack)( void *devicePrt );	//完成通知
	
	/* 由被调函数实现 */
	bool enableFlag;								//使能开关
	bool disableFlag;								//失能开关
	bool continueRunFlag;							//连续运行开关
	uint16_t dutyCycle;								//占空比
	uint32_t PWM_Count;								//PWM计数器
	uint32_t sumCount;								//总执行次数
	uint32_t Reg_CCR;								//比较计数器
}PWM_IO_TypeDef;

/*
*********************************************************************************************************
*                              				开关任务
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
	/* 由主调函数实现 */
	SWITCH_TASK_STATUS_TypeDef status;					//状态
	void *devicePrt;									//设备指针
	
	/* 回调函数 */
	bool (*isSwitchOn_CallBack)( void *devicePrt );		//开关是否打开
	void (*onDevice_CallBack)( void *devicePrt );		//打开开关通知
	void (*offDevice_CallBack)( void *devicePrt );		//关闭开关通知
	
	/* 由被调函数实现 */	
}SWITCH_TASK_TypeDef;

/*
*********************************************************************************************************
*                              				定时器任务
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
	/* 由主调函数实现 */
	TIMER_TASK_STATUS_TypeDef status;				//状态
	uint32_t runPeriod;								//运行周期
	void *devicePrt;								//设备指针
	
	/* 回调函数 */
	void (*timeUpNotify_CallBack)( void *devicePrt );//时间到达通知
	
	/* 由被调函数实现 */
	bool enableFlag;								//使能开关
	bool disableFlag;								//失能开关
	uint32_t decreaseCount;							//递减计数器
	uint32_t countTimeMS;							//计数时间
}TIMER_TASK_TypeDef;

/*
*********************************************************************************************************
*                              				心跳
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
	/* 内部变量 */
	HEARTBEAT_ENUM status;
	uint32_t time;
	
	/* 外部变量 */
	void *private;
	uint32_t runPeriod;
	uint32_t beatCnt;
	uint32_t beatPeriod;
	uint32_t period;
	PERIOD_TASK_TypeDef cycle;
	
	/* 由被调函数实现 */
	bool enable;										//使能开关
	bool disable;										//失能开关
	
	/* 回调函数 */
	void (*notify_Start)( void *private );				//开始通知
	void (*notify_Open)( void *private );				//打开设备
	void (*notify_Close)( void *private );				//关闭设备
	void (*notify_Done)( void *private );				//完成通知
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
*                              				周期任务
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
*                              				IO模拟PWM任务
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
*                              				开关任务
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
*                              				定时器任务
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
*                              				心跳
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
