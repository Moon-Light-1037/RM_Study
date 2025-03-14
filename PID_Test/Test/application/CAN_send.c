#include "main.h"
#include "bsp_can.h"

#define SINGLE 1

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

static CAN_TxHeaderTypeDef motor_can_tx_message;
static uint8_t can_send_data[8];
// M3508-C620-ID-1-0x201��
//  M2006-ID2
//  GM6020       ����SID 0x1FE		����0x204+ID
// 4310
/**********************************************************************************************************
 *�� �� ��: CAN_Motor_Send1
 *����˵��:	�����������		������ID 1-4
 *��    ��:
 *�� �� ֵ: ��
 **********************************************************************************************************/
void CAN_Motor_Send1(short a)
{
	uint32_t send_mail_box;

	motor_can_tx_message.StdId = 0x200;
	motor_can_tx_message.IDE = CAN_ID_STD;
	motor_can_tx_message.RTR = CAN_RTR_DATA;
	motor_can_tx_message.DLC = 0x08;

	a = LIMIT_MAX_MIN(a, 9500, -9500);

	can_send_data[0] = a >> 8;
	can_send_data[1] = a;

	HAL_CAN_AddTxMessage(&hcan1, &motor_can_tx_message, can_send_data, &send_mail_box);
}
