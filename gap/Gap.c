/*
*********************************************************************************************************
* @file    	Gap.c
* @author  	SY
* @version 	V1.0.1
* @date    	2017-9-17 10:21:52
* @IDE	 	Keil V5.22.0.0
* @Chip    	STM32F407VE
* @brief   	General Abstract Package Source
*********************************************************************************************************
* @attention
* =======================================================================================================
*	�汾 		ʱ��					����					˵��
* -------------------------------------------------------------------------------------------------------
*	Ver1.0.1 	2018-3-17 10:22:19 		SY			1. �޸�ѭ������Ϊ��������
*													2. ���Ź������޸�Ϊ��ʱ������
*													3. ɾ����ʱֹͣ�����ɶ�ʱ���������
*
* 
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Private Includes
*********************************************************************************************************
*/
#include "Gap.h"


/*
*********************************************************************************************************
*                              				Private define
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                              				Private typedef
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Private constants
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Private macro
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Private variables
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Private function prototypes
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              				Private functions
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                              				��������
*********************************************************************************************************
*/
/*
*********************************************************************************************************
* Function Name : PeriodTaskInit
* Description	: ���������ʼ��
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void PeriodTaskInit( PERIOD_TASK_TypeDef *this, uint32_t runPeriod, \
		uint32_t executeNums, uint32_t onTimeMS, uint32_t offTimeMS, void *devicePtr )
{
	PeriodTaskDeInit(this);	
	this->status = STATUS_PERIOD_TASK_IDLE;
	this->runPeriod = runPeriod;
	this->executeNums = executeNums;
	this->onTime = onTimeMS;
	this->offTime = offTimeMS;
	this->devicePtr = devicePtr;
}
	
/*
*********************************************************************************************************
* Function Name : PeriodTaskDeInit
* Description	: ��������ָ�Ĭ��ֵ
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void PeriodTaskDeInit( PERIOD_TASK_TypeDef *this )
{
	memset(this,NULL,sizeof(PERIOD_TASK_TypeDef));
}

/*
*********************************************************************************************************
* Function Name : SetPeriodTaskExecuteTime
* Description	: ������������ִ��ʱ��
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void SetPeriodTaskExecuteTime( PERIOD_TASK_TypeDef *this,\
		uint32_t executeNums, uint32_t onTimeMS, uint32_t offTimeMS )
{
	//�ȴ��ϴ�ִ�н���
	if (this->status == STATUS_PERIOD_TASK_IDLE)
	{
		this->enableFlag = true;
		this->executeNums = executeNums;
		this->onTime = onTimeMS;
		this->offTime = offTimeMS;
	}
}

/*
*********************************************************************************************************
* Function Name : OpenPeriodExecuteTask
* Description	: ����������
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void OpenPeriodExecuteTask( PERIOD_TASK_TypeDef *this )
{
	//�ȴ��ϴ�ִ�н���
	if (this->status == STATUS_PERIOD_TASK_IDLE)
	{
		this->enableFlag = true;
	}
}

/*
*********************************************************************************************************
* Function Name : ClosePeriodExecuteTask
* Description	: �ر�����ִ������
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void ClosePeriodExecuteTask( PERIOD_TASK_TypeDef *this )
{
	this->disableFlag = true;
	if (this->disableFlag == true)
	{
		this->disableFlag = false;
		this->enableFlag = false;
		this->status = STATUS_PERIOD_TASK_IDLE;
		if (this->offDevice_CallBack)
		{
			this->offDevice_CallBack(this->devicePtr);
		}
		if (this->taskDoneNotify_CallBack)
		{
			this->taskDoneNotify_CallBack(this->devicePtr);
		}
	}
}

/*
*********************************************************************************************************
* Function Name : RegisterPeriodTaskStartNotify_CallBack
* Description	: ע����������ʼ֪ͨ�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterPeriodTaskStartNotify_CallBack( PERIOD_TASK_TypeDef *this,\
		void (*taskStartNotify_CallBack)( void *devicePrt ) )
{
	this->taskStartNotify_CallBack = taskStartNotify_CallBack;
}

/*
*********************************************************************************************************
* Function Name : RegisterPeriodTaskOnDevice_CallBack
* Description	: ע��ѭ��ִ��������豸�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterPeriodTaskOnDevice_CallBack( PERIOD_TASK_TypeDef *this,\
		void (*onDevice_CallBack)( void *devicePrt ) )
{
	this->onDevice_CallBack = onDevice_CallBack;
}

/*
*********************************************************************************************************
* Function Name : RegisterPeriodTaskOffDevice_CallBack
* Description	: ע��ѭ��ִ������ر��豸�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterPeriodTaskOffDevice_CallBack( PERIOD_TASK_TypeDef *this,\
		void (*offDevice_CallBack)( void *devicePrt ) )
{
	this->offDevice_CallBack = offDevice_CallBack;
}

/*
*********************************************************************************************************
* Function Name : RegisterPeriodTaskDoneNotify_CallBack
* Description	: ע���ظ�ִ���������֪ͨ�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterPeriodTaskDoneNotify_CallBack( PERIOD_TASK_TypeDef *this,\
		void (*taskDoneNotify_CallBack)( void *devicePrt ) )
{
	this->taskDoneNotify_CallBack = taskDoneNotify_CallBack;
}

/*
*********************************************************************************************************
* Function Name : PeriodTaskCycle
* Description	: �ظ�ִ������ѭ����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void PeriodTaskCycle( PERIOD_TASK_TypeDef *this )
{	
	switch ( this->status )
	{
		case STATUS_PERIOD_TASK_IDLE:
		{
			if (this->enableFlag == true)			
			{
				this->enableFlag = false;
				
				if (this->runPeriod != 0)
				{
					if (this->executeNums != 0)
					{
						this->executeCount = 0;
						this->onCount = 0;
						this->offCount = 0;
						this->done = false;
						this->status = STATUS_PERIOD_TASK_ON;
						
						if (this->taskStartNotify_CallBack)
						{
							this->taskStartNotify_CallBack(this->devicePtr);
						}
					}
				}
			}
			break;
		}
		case STATUS_PERIOD_TASK_ON:
		{
			if (this->onCount == 0)
			{
				if (this->onDevice_CallBack)
				{
					this->onDevice_CallBack(this->devicePtr);
				}
			}
			
			this->onCount++;
			if (this->onCount >= this->onTime / this->runPeriod)
			{
				this->onCount = 0;
				this->status = STATUS_PERIOD_TASK_OFF;
			}
			break;
		}
		case STATUS_PERIOD_TASK_OFF:
		{
			if (this->offCount == 0)
			{
				if (this->offDevice_CallBack)
				{
					this->offDevice_CallBack(this->devicePtr);
				}
			}
			
			this->offCount++;
			if (this->offCount >= this->offTime / this->runPeriod)
			{
				this->offCount = 0;			
				
				this->executeCount++;
				if (this->executeCount >= this->executeNums)
				{
					this->executeCount = 0;

					this->status = STATUS_PERIOD_TASK_DONE;
				}
				else
				{
					this->status = STATUS_PERIOD_TASK_ON;
				}
			}
			break;
		}
		case STATUS_PERIOD_TASK_DONE:
		{
			if (this->offDevice_CallBack)
			{
				this->offDevice_CallBack(this->devicePtr);
			}
			if (this->taskDoneNotify_CallBack)
			{
				this->taskDoneNotify_CallBack(this->devicePtr);
			}
			this->done = true;
			this->status = STATUS_PERIOD_TASK_IDLE;
			break;
		}
		default:
			this->status = STATUS_PERIOD_TASK_IDLE;
			break;
	}
}

/*
*********************************************************************************************************
*                              				IOģ��PWM����
*********************************************************************************************************
*/
/*
*********************************************************************************************************
* Function Name : PWM_IO_OutputInit
* Description	: IOģ��PWM�����ʼ��
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void PWM_IO_OutputInit( PWM_IO_TypeDef *this, float runPeriod, float outputPeriod, 
						uint16_t maxControlDegree, void *devicePrt )
{
	PWM_IO_OutputDeInit(this);	
	this->runPeriod = runPeriod;
	this->outputPeriod = outputPeriod;
	this->maxControlDegree = maxControlDegree;
	this->devicePrt = devicePrt;
}	

/*
*********************************************************************************************************
* Function Name : PWM_IO_OutputDeInit
* Description	: IOģ��PWM����ָ�Ĭ��ֵ
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void PWM_IO_OutputDeInit( PWM_IO_TypeDef *this )
{
	memset(this,NULL,sizeof(PWM_IO_TypeDef));
}

/*
*********************************************************************************************************
* Function Name : PWM_IO_SetOutput
* Description	: IOģ��PWM���
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void PWM_IO_SetOutput( PWM_IO_TypeDef *this, uint16_t dutyCycle )
{
	this->status = PWM_IO_STATUS_IDLE;
	this->dutyCycle = dutyCycle;
	this->enableFlag = true;
}

/*
*********************************************************************************************************
* Function Name : this
* Description	: �ر�IOģ��PWM���
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void PWM_IO_CloseOutput( PWM_IO_TypeDef *this )
{	
	this->disableFlag = true;
	if (this->disableFlag == true)
	{
		this->disableFlag = false;
		this->enableFlag = false;		
		this->continueRunFlag = false;
		this->status = PWM_IO_STATUS_IDLE;	
	
		if (this->offDevice_CallBack)
		{
			this->offDevice_CallBack(this->devicePrt);
		}	
		if (this->taskDoneNotify_CallBack)
		{
			this->taskDoneNotify_CallBack(this->devicePrt);
		}
	}
}

/*
*********************************************************************************************************
* Function Name : RegisterPWM_IO_TaskStartNotify_CallBack
* Description	: ע��IOģ��PWM����ʼ֪ͨ�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterPWM_IO_TaskStartNotify_CallBack( PWM_IO_TypeDef *this,\
		void (*taskStartNotify_CallBack)( void *devicePrt ) )
{
	this->taskStartNotify_CallBack = taskStartNotify_CallBack;
}

/*
*********************************************************************************************************
* Function Name : RegisterPWM_IO_TaskOnDevice_CallBack
* Description	: ע��IOģ��PWM������豸�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterPWM_IO_TaskOnDevice_CallBack( PWM_IO_TypeDef *this,\
		void (*onDevice_CallBack)( void *devicePrt ) )
{
	this->onDevice_CallBack = onDevice_CallBack;
}

/*
*********************************************************************************************************
* Function Name : RegisterPWM_IO_TaskOffDevice_CallBack
* Description	: ע��IOģ��PWM����ر��豸�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterPWM_IO_TaskOffDevice_CallBack( PWM_IO_TypeDef *this,\
		void (*offDevice_CallBack)( void *devicePrt ) )
{
	this->offDevice_CallBack = offDevice_CallBack;
}

/*
*********************************************************************************************************
* Function Name : RegisterPWM_IO_TaskDoneNotify_CallBack
* Description	: ע��IOģ��PWM�������֪ͨ�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterPWM_IO_TaskDoneNotify_CallBack( PWM_IO_TypeDef *this,\
		void (*taskDoneNotify_CallBack)( void *devicePrt ) )
{
	this->taskDoneNotify_CallBack = taskDoneNotify_CallBack;
}

/*
*********************************************************************************************************
* Function Name : PWM_IO_Output
* Description	: IOģ��PWM���ѭ���壨�����ڵ�����Ƶ�ʣ�
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void PWM_IO_OutputCycle( PWM_IO_TypeDef *this )
{
	switch ( this->status )
	{
		case PWM_IO_STATUS_IDLE:
		{				
			if ((this->enableFlag==true) || (this->continueRunFlag==true))
			{
				this->enableFlag = false;
				this->continueRunFlag = false;
				this->PWM_Count = 0;
				this->sumCount = 0;
				this->Reg_CCR = 0;
				
				if (this->runPeriod)
				{
					this->sumCount = this->outputPeriod / this->runPeriod;
				}
				
				if (this->maxControlDegree)
				{
					this->Reg_CCR = (float)(this->dutyCycle) / this->maxControlDegree * this->sumCount;
				}
				
				if (this->Reg_CCR != 0)
				{
					this->status = PWM_IO_STATUS_OPEN;
				}
				else
				{
					this->status = PWM_IO_STATUS_CLOSE;
				}
			}
			
			if (this->status == PWM_IO_STATUS_OPEN)
			{
				if (this->taskStartNotify_CallBack)
				{
					this->taskStartNotify_CallBack(this->devicePrt);
				}
			}
			else if (this->status == PWM_IO_STATUS_CLOSE)
			{
				if (this->taskDoneNotify_CallBack)
				{
					this->taskDoneNotify_CallBack(this->devicePrt);
				}
			}
			break;
		}
		case PWM_IO_STATUS_OPEN:
		{		
			if (this->onDevice_CallBack)
			{
				this->onDevice_CallBack(this->devicePrt);
			}
			
			this->PWM_Count++;
			if (this->PWM_Count >= this->Reg_CCR)
			{
				if (this->PWM_Count >= this->sumCount)
				{
					this->status = PWM_IO_STATUS_DONE;
				}
				else
				{
					this->status = PWM_IO_STATUS_CLOSE;
				}
			}		
			break;
		}
		case PWM_IO_STATUS_CLOSE:
		{
			if (this->offDevice_CallBack)
			{
				this->offDevice_CallBack(this->devicePrt);
			}
			
			this->PWM_Count++;
			if (this->PWM_Count >= this->sumCount)
			{
				this->status = PWM_IO_STATUS_DONE;
			}
			break;
		}
		case PWM_IO_STATUS_DONE:
		{
			//ģ�¶�ʱ���������ظ�ִ�У�ֱ���յ�ָֹͣ�
			this->continueRunFlag = true;		
			this->status = PWM_IO_STATUS_IDLE;
			break;
		}
		default:
			this->status = PWM_IO_STATUS_IDLE;
			break;
	}
}

/*
*********************************************************************************************************
*                              				��������
*********************************************************************************************************
*/
/*
*********************************************************************************************************
* Function Name : SwitchTaskInit
* Description	: ���������ʼ��
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void SwitchTaskInit( SWITCH_TASK_TypeDef *this, void *devicePrt )
{
	SwitchTaskDeInit(this);
	this->devicePrt = devicePrt;
}

/*
*********************************************************************************************************
* Function Name : SwitchTaskDeInit
* Description	: ��������ָ�Ĭ��ֵ
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void SwitchTaskDeInit( SWITCH_TASK_TypeDef *this )
{
	memset(this,NULL,sizeof(SWITCH_TASK_TypeDef));
}

/*
*********************************************************************************************************
* Function Name : RegisterSwitchTaskIsSwitchOn_CallBack
* Description	: ע�Ὺ�������Ƿ�򿪻ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterSwitchTaskIsSwitchOn_CallBack( SWITCH_TASK_TypeDef *this,\
		bool (*isSwitchOn_CallBack)( void *devicePrt ) )
{
	this->isSwitchOn_CallBack = isSwitchOn_CallBack;
}

/*
*********************************************************************************************************
* Function Name : RegisterSwitchTaskOnDevice_CallBack
* Description	: ע�Ὺ��������豸�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterSwitchTaskOnDevice_CallBack( SWITCH_TASK_TypeDef *this,\
		void (*onDevice_CallBack)( void *devicePrt ) )
{
	this->onDevice_CallBack = onDevice_CallBack;
}

/*
*********************************************************************************************************
* Function Name : RegisterSwitchTaskOffDevice_CallBack
* Description	: ע�Ὺ������ر��豸�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterSwitchTaskOffDevice_CallBack( SWITCH_TASK_TypeDef *this,\
		void (*offDevice_CallBack)( void *devicePrt ) )
{
	this->offDevice_CallBack = offDevice_CallBack;
}

/*
*********************************************************************************************************
* Function Name : SwitchTask
* Description	: ��������
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void SwitchTask( SWITCH_TASK_TypeDef *this )
{
	switch ( this->status )
	{
		case SWITCH_TASK_IDLE:
		{
			if (this->isSwitchOn_CallBack)
			{
				if (this->isSwitchOn_CallBack(this->devicePrt) == true)
				{
					this->status = SWITCH_TASK_OPEN_NOTIFY;
				}
				else
				{
					this->status = SWITCH_TASK_CLOSE_NOTIFY;
				}
			}		
			break;
		}	
		case SWITCH_TASK_OPEN:
		{
			if (this->isSwitchOn_CallBack(this->devicePrt) == false)
			{
				this->status = SWITCH_TASK_CLOSE_NOTIFY;
			}
			break;
		}
		case SWITCH_TASK_OPEN_NOTIFY:
		{
			if (this->onDevice_CallBack)
			{
				this->onDevice_CallBack(this->devicePrt);
			}
			this->status = SWITCH_TASK_OPEN;
			break;
		}	
		case SWITCH_TASK_CLOSE:
		{
			if (this->isSwitchOn_CallBack(this->devicePrt) == true)
			{
				this->status = SWITCH_TASK_OPEN_NOTIFY;
			}
			break;
		}	
		case SWITCH_TASK_CLOSE_NOTIFY:
		{
			if (this->offDevice_CallBack)
			{
				this->offDevice_CallBack(this->devicePrt);
			}
			this->status = SWITCH_TASK_CLOSE;
			break;
		}
		default:
			this->status = SWITCH_TASK_IDLE;
			break;
	}
}

/*
*********************************************************************************************************
*                              				��ʱ������
*********************************************************************************************************
*/
/*
*********************************************************************************************************
* Function Name : TimerTaskInit
* Description	: ��ʱ�������ʼ��
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void TimerTaskInit(TIMER_TASK_TypeDef *this, uint32_t runPeriod, 
						void *devicePrt)
{
	TimerTaskDeInit(this);
	this->status = TIMER_TASK_IDLE;
	this->runPeriod = runPeriod;
	this->devicePrt = devicePrt;
}

/*
*********************************************************************************************************
* Function Name : TimerTaskDeInit
* Description	: ��ʱ������ָ�Ĭ��ֵ
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void TimerTaskDeInit( TIMER_TASK_TypeDef *this )
{
	memset(this,NULL,sizeof(TIMER_TASK_TypeDef));
}

/*
*********************************************************************************************************
* Function Name : SetTimerCounter
* Description	: ���ö�ʱ��������ֵ
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void SetTimerCounter( TIMER_TASK_TypeDef *this,\
		uint32_t countTimeMS )
{
	this->enableFlag = true;
	this->status = TIMER_TASK_IDLE;
	this->countTimeMS = countTimeMS;
}

/*
*********************************************************************************************************
* Function Name : CloseTimerTask
* Description	: �رն�ʱ������
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void CloseTimerTask( TIMER_TASK_TypeDef *this )
{
	this->disableFlag = true;
	if (this->disableFlag == true)
	{
		this->disableFlag = false;
		this->enableFlag = false;
		
		this->status = TIMER_TASK_IDLE;		
	}
}

/*
*********************************************************************************************************
* Function Name : RegisterTimerTaskTimeUpNotify_CallBack
* Description	: ע�ᶨʱ��ʱ�䵽�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterTimerTaskTimeUpNotify_CallBack( TIMER_TASK_TypeDef *this,\
		void (*timeUpNotify_CallBack)( void *devicePrt ) )
{
	this->timeUpNotify_CallBack = timeUpNotify_CallBack;
}

/*
*********************************************************************************************************
* Function Name : TimerTaskCycle
* Description	: ��ʱ������ѭ��
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void TimerTaskCycle( TIMER_TASK_TypeDef *this )
{
	switch ( this->status )
	{
		case TIMER_TASK_IDLE:
		{
			if (this->enableFlag == true) 
			{
				this->enableFlag = false;
				
				if (this->runPeriod)
				{
					this->decreaseCount = this->countTimeMS / this->runPeriod;
					this->status = TIMER_TASK_WORKING;
				}
			}
			break;
		}
		case TIMER_TASK_WORKING:
		{	
			if (this->decreaseCount)
			{
				this->decreaseCount--;
			}
			else
			{
				this->status = TIMER_TASK_DONE;
			}
			break;
		}
		case TIMER_TASK_DONE:
		{	
			if (this->timeUpNotify_CallBack)
			{
				this->timeUpNotify_CallBack(this->devicePrt);
			}
			this->status = TIMER_TASK_IDLE;
			break;
		}
		default:
			this->status = TIMER_TASK_IDLE;
			break;
	}
}

/*
*********************************************************************************************************
*                              				����
*********************************************************************************************************
*/
/*
*********************************************************************************************************
* Function Name : HeartBeat_Init
* Description	: ������ʼ��
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void HeartBeat_Init(HEARTBEAT_TypeDef *this, uint32_t runPeriod, uint32_t beatPeriod,\
		uint32_t beatCnt, uint32_t period, void *private)
{
	memset(this, NULL, sizeof(HEARTBEAT_TypeDef));
	
	this->status = HEARTBEAT_STATUS_IDLE;
	this->runPeriod = runPeriod;
	this->beatPeriod = beatPeriod;
	this->beatCnt = beatCnt;
	this->period = period;
	this->private = private;
}

/*
*********************************************************************************************************
* Function Name : HeartBeat_Start
* Description	: ������ʼ
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void HeartBeat_Start(HEARTBEAT_TypeDef *this)
{
	this->enable = true;
	this->status = HEARTBEAT_STATUS_IDLE;
}

/*
*********************************************************************************************************
* Function Name : HeartBeat_Stop
* Description	: ����ֹͣ
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void HeartBeat_Stop(HEARTBEAT_TypeDef *this)
{
	this->disable = true;
	this->status = HEARTBEAT_STATUS_STOP;
}

/*
*********************************************************************************************************
* Function Name : RegisterHeartbeatOnDevice_CallBack
* Description	: ע���������豸�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterHeartbeatOpenDevice_CallBack(HEARTBEAT_TypeDef *this,\
		void (*notify_Open)( void *private ))
{
	this->notify_Open = notify_Open;
}

/*
*********************************************************************************************************
* Function Name : RegisterHeartbeatCloseDevice_CallBack
* Description	: ע�������ر��豸�ص�����
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void RegisterHeartbeatCloseDevice_CallBack(HEARTBEAT_TypeDef *this,\
		void (*notify_Close)( void *private ))
{
	this->notify_Close = notify_Close;
}

/*
*********************************************************************************************************
* Function Name : HeartBeat_Exec
* Description	: ����ִ��
* Input			: None
* Output		: None
* Return		: None
*********************************************************************************************************
*/
void HeartBeat_Exec(HEARTBEAT_TypeDef *this)
{
	switch (this->status)
	{
		case HEARTBEAT_STATUS_IDLE:
			if (this->enable == true)
			{
				this->enable = false;
				
				if ((this->runPeriod == 0) || (this->beatPeriod == 0) || \
					(this->period == 0))
				{
					return;
				}
				
				if (this->notify_Start)
				{
					this->notify_Start(this->private);
				}			
				this->status = HEARTBEAT_STATUS_LOAD;
			}
			break;
		case HEARTBEAT_STATUS_LOAD:
			PeriodTaskInit(&this->cycle, this->runPeriod, this->beatCnt, this->beatPeriod*0.2, this->beatPeriod*0.8, this->private);
			OpenPeriodExecuteTask(&this->cycle);
			RegisterPeriodTaskOnDevice_CallBack(&this->cycle, this->notify_Open);
			RegisterPeriodTaskOffDevice_CallBack(&this->cycle, this->notify_Close);
		
			this->status = HEARTBEAT_STATUS_BEAT;
			break;
		case HEARTBEAT_STATUS_BEAT:
			PeriodTaskCycle(&this->cycle);			
			if (this->cycle.done == true)
			{
				this->cycle.done = false;
				
				this->time = 0;
				this->status = HEARTBEAT_STATUS_SLEEP;
			}
			break;
		case HEARTBEAT_STATUS_SLEEP:
			this->time += this->runPeriod;
			if (this->time >= this->period - this->beatCnt * this->beatPeriod)
			{
				this->status = HEARTBEAT_STATUS_DONE;
			}
			break;
		case HEARTBEAT_STATUS_DONE:
			if (this->notify_Done)
			{
				this->notify_Done(this->private);
			}
			this->status = HEARTBEAT_STATUS_LOAD;
			break;
		case HEARTBEAT_STATUS_STOP:
			this->status = HEARTBEAT_STATUS_IDLE;	
			break;
		default:
			this->status = HEARTBEAT_STATUS_IDLE;
			break;
	}
}



/************************ (C) COPYRIGHT STMicroelectronics **********END OF FILE*************************/
