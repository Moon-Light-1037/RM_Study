#include "bsp_can.h"
#include "can_config.h"
#include "main.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

void can_filter_init(void)
{
	CAN_FilterTypeDef can_filter_st;
	// CAN 1 FIFO0 接收中断
	can_filter_st.FilterBank = 0;
	can_filter_st.FilterActivation = ENABLE;
	can_filter_st.FilterMode = CAN_FILTERMODE_IDLIST;
	can_filter_st.FilterScale = CAN_FILTERSCALE_16BIT;
	can_filter_st.FilterIdHigh = CAN1_FIFO0_ID0 << 5;
	can_filter_st.FilterIdLow = CAN1_FIFO0_ID1 << 5;
	can_filter_st.FilterMaskIdHigh = CAN1_FIFO0_ID2 << 5;
	can_filter_st.FilterMaskIdLow = CAN1_FIFO0_ID3 << 5;
	can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
	can_filter_st.SlaveStartFilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	// CAN 1 FIFO1 接收中断
	can_filter_st.FilterBank = 1;
	can_filter_st.FilterActivation = ENABLE;
	can_filter_st.FilterMode = CAN_FILTERMODE_IDLIST;
	can_filter_st.FilterScale = CAN_FILTERSCALE_16BIT;
	can_filter_st.FilterIdHigh = CAN1_FIFO1_ID0 << 5;
	can_filter_st.FilterIdLow = CAN1_FIFO1_ID1 << 5;
	can_filter_st.FilterMaskIdHigh = CAN1_FIFO1_ID2 << 5;
	can_filter_st.FilterMaskIdLow = CAN1_FIFO1_ID3 << 5;
	can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO1;
	can_filter_st.SlaveStartFilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);
	// CAN 2 FIFO0 接收中断
	can_filter_st.FilterBank = 15;
	can_filter_st.FilterActivation = ENABLE;
	can_filter_st.FilterMode = CAN_FILTERMODE_IDLIST;
	can_filter_st.FilterScale = CAN_FILTERSCALE_16BIT;
	can_filter_st.FilterIdHigh = CAN2_FIFO0_ID0 << 5;
	can_filter_st.FilterIdLow = CAN2_FIFO0_ID1 << 5;
	can_filter_st.FilterMaskIdHigh = CAN2_FIFO0_ID2 << 5;
	can_filter_st.FilterMaskIdLow = CAN2_FIFO0_ID3 << 5;
	can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
	can_filter_st.SlaveStartFilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
	HAL_CAN_Start(&hcan2);
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
	// CAN 2 FIFO1 接收中断
	can_filter_st.FilterBank = 16;
	can_filter_st.FilterActivation = ENABLE;
	can_filter_st.FilterMode = CAN_FILTERMODE_IDLIST;
	can_filter_st.FilterScale = CAN_FILTERSCALE_16BIT;
	can_filter_st.FilterIdHigh = CAN2_FIFO1_ID0 << 5;
	can_filter_st.FilterIdLow = CAN2_FIFO1_ID1 << 5;
	can_filter_st.FilterMaskIdHigh = CAN2_FIFO1_ID2 << 5;
	can_filter_st.FilterMaskIdLow = CAN2_FIFO1_ID3 << 5;
	can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO1;
	can_filter_st.SlaveStartFilterBank = 14;
	HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
	HAL_CAN_Start(&hcan2);
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO1_MSG_PENDING);
	// CAN 1 发送中断
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_TX_MAILBOX_EMPTY);
	// CAN 2 发送中断
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_TX_MAILBOX_EMPTY);
}




