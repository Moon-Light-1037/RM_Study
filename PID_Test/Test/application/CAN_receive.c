#include "bsp_can.h"
#include "can_config.h"
#include "main.h"
#include "CAN_send.h"
#include "PID.h"

extern Motor MOTOR_M2006;
extern Motor MOTOR_GM6020;
extern Motor MOTOR_M3508;
extern Motor MOTOR_J4310;
extern uint8_t can_send_data[8];

uint16_t flag = 0;
void MotorPosCal(Motor *motor);
float MotorPIDcal(Motor *motor);

/**********************************************************************************************************
 *函 数 名: MotorReceive
 *功能说明: 电机数据接收函数
 *形    参:
 *返 回 值: 无
 **********************************************************************************************************/
void MotorReceive(CAN_RxHeaderTypeDef *rx_header, uint8_t *data)
{
	if (rx_header->StdId == 0x202)
	{
		MOTOR_M2006.motor_info.Angle = (data[0] << 8) | (data[1]);
		MOTOR_M2006.motor_info.RealSpeed = (data[2] << 8) | (data[3]);
		MOTOR_M2006.motor_info.Current = (data[4] << 8) | (data[5]);
		MOTOR_M2006.motor_info.temp = data[6];
	}
	// MOTOR_M2006.motor_info.Angle = (data[0] << 8) | (data[1]);
	// MOTOR_M2006.motor_info.RealSpeed = (data[2] << 8) | (data[3]);
	// MOTOR_M2006.motor_info.Current = (data[4] << 8) | (data[5]);
	// MOTOR_M2006.motor_info.temp = data[6];

	else if (rx_header->StdId == 0x201)
	{
		MOTOR_M3508.motor_info.Angle = (data[0] << 8) | (data[1]);
		MOTOR_M3508.motor_info.RealSpeed = (data[2] << 8) | (data[3]);
		MOTOR_M3508.motor_info.Current = (data[4] << 8) | (data[5]);
		MOTOR_M3508.motor_info.temp = data[6];
	}
	// else if (rx_header->StdId == 0x204 + 1)
	// {
	// 	MOTOR_GM6020.motor_info.Angle = (data[0] << 8) | (data[1]);
	// 	MOTOR_GM6020.motor_info.RealSpeed = (data[2] << 8) | (data[3]);
	// 	MOTOR_GM6020.motor_info.Current = (data[4] << 8) | (data[5]);
	// 	MOTOR_GM6020.motor_info.temp = data[6];
	// }
	else if (rx_header->StdId == 0)
	{
		MOTOR_J4310.motor_info.Angle = (data[1] << 8) | (data[2]);
		MOTOR_J4310.motor_info.RealSpeed = (data[3] << 8) | (data[4] >> 4);
		MOTOR_J4310.motor_info.Current = (data[5] << 8) | (data[6]);
		MOTOR_J4310.motor_info.temp = data[7];
	}

	MotorPosCal(&MOTOR_M2006);
}

/**********************************************************************************************************
 *函 数 名: HAL_CAN_RxFifo0MsgPendingCallback
 *功能说明:FIFO 0邮箱中断回调函数
 *形    参:
 *返 回 值: 无
 **********************************************************************************************************/
uint8_t rx_data1[8];
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	flag = 1;
	//	short a;
	CAN_RxHeaderTypeDef rx_header;
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data1);

	MotorReceive(&rx_header, rx_data1);

	__HAL_CAN_CLEAR_FLAG(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

int16_t pos_count = 0;

void MotorPosCal(Motor *motor)
{
	motor->motor_info.AngleErr = (motor->motor_info.Angle - motor->motor_info.LastAngle);

	// 0-->8191,负角度
	if (motor->motor_info.AngleErr > 0.7f * 8191)
	{
		pos_count--;
	}
	// 8191-->0,正角度
	else if (motor->motor_info.AngleErr < 0.7f * (-8191))
	{
		pos_count++;
	}
	motor->motor_info.LastAngle = motor->motor_info.Angle;

	if (pos_count >= 36)
	{
		motor->real_pos++;
		pos_count -= 36;
	}
	else if (pos_count <= -36)
	{
		motor->real_pos--;
		pos_count += 36;
	}
}
float speed_ref;
float current_ref;
float MotorPIDcal(Motor *motor)
{

	speed_ref = PID_Calc(&motor->motor_pos_pid, motor->motor_info.Angle);
	motor->real_speed = motor->motor_info.RealSpeed;
	// motor->motor_speed_pid.SetPoint = speed_ref;
	current_ref = PID_Calc(&motor->motor_speed_pid, motor->real_speed);
	return current_ref;
}
