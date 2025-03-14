#ifndef _MOTOR_CONFIG_H
#define _MOTOR_CONFIG_H

/*
M2006-C610:
电调ID=1
反馈:
    ID:0x201
    DATA[0]:角度高8位
    DATA[1]:角度低8位
    DATA[2]:转速高8位       0-8191对应0-360
    DATA[3]:转速低8位
    DATA[4]:实际转矩高8位
    DATA[5]:实际转矩低8位
发送：
    ID:0x200
    DLC：八字节
    DATA[0]:控制电流高8位
    DATA[1]:控制电流低8位
    电流范围[-10000,10000]


*/

// 测试电机宏定义
/************/
#define MOTOR_NUM 3

// 测试电机1-----C610------G2006
#define MOTOR1_CAN CAN1
#define MOTOR1_CAN_ID 0x201
// 测试电机2
#define MOTOR2_CAN CAN1
#define MOTOR2_CAN_ID 0x202
// 测试电机3
#define MOTOR3_CAN CAN1
#define MOTOR3_CAN_ID 0x203
/************/

// FIFO 0 接收ID
#define CAN1_FIFO0_ID0 0x201
#define CAN1_FIFO0_ID1 0x202
#define CAN1_FIFO0_ID2 0x203
#define CAN1_FIFO0_ID3 0x204

// FIFO 1 接收ID
#define CAN1_FIFO1_ID0 0x205
#define CAN1_FIFO1_ID1 0x206
#define CAN1_FIFO1_ID2 0x207
#define CAN1_FIFO1_ID3 0x208

// FIFO 0 接收ID
#define CAN2_FIFO0_ID0 0x201
#define CAN2_FIFO0_ID1 0x202
#define CAN2_FIFO0_ID2 0x203
#define CAN2_FIFO0_ID3 0x204

// FIFO 1 接收ID
#define CAN2_FIFO1_ID0 0x205
#define CAN2_FIFO1_ID1 0x206
#define CAN2_FIFO1_ID2 0x207
#define CAN2_FIFO1_ID3 0x208

#endif
