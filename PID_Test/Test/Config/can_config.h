#ifndef _MOTOR_CONFIG_H
#define _MOTOR_CONFIG_H

/*
M2006-C610:
���ID=1
����:
    ID:0x201
    DATA[0]:�Ƕȸ�8λ
    DATA[1]:�Ƕȵ�8λ
    DATA[2]:ת�ٸ�8λ       0-8191��Ӧ0-360
    DATA[3]:ת�ٵ�8λ
    DATA[4]:ʵ��ת�ظ�8λ
    DATA[5]:ʵ��ת�ص�8λ
���ͣ�
    ID:0x200
    DLC�����ֽ�
    DATA[0]:���Ƶ�����8λ
    DATA[1]:���Ƶ�����8λ
    ������Χ[-10000,10000]


*/

// ���Ե���궨��
/************/
#define MOTOR_NUM 3

// ���Ե��1-----C610------G2006
#define MOTOR1_CAN CAN1
#define MOTOR1_CAN_ID 0x201
// ���Ե��2
#define MOTOR2_CAN CAN1
#define MOTOR2_CAN_ID 0x202
// ���Ե��3
#define MOTOR3_CAN CAN1
#define MOTOR3_CAN_ID 0x203
/************/

// FIFO 0 ����ID
#define CAN1_FIFO0_ID0 0x201
#define CAN1_FIFO0_ID1 0x202
#define CAN1_FIFO0_ID2 0x203
#define CAN1_FIFO0_ID3 0x204

// FIFO 1 ����ID
#define CAN1_FIFO1_ID0 0x205
#define CAN1_FIFO1_ID1 0x206
#define CAN1_FIFO1_ID2 0x207
#define CAN1_FIFO1_ID3 0x208

// FIFO 0 ����ID
#define CAN2_FIFO0_ID0 0x201
#define CAN2_FIFO0_ID1 0x202
#define CAN2_FIFO0_ID2 0x203
#define CAN2_FIFO0_ID3 0x204

// FIFO 1 ����ID
#define CAN2_FIFO1_ID0 0x205
#define CAN2_FIFO1_ID1 0x206
#define CAN2_FIFO1_ID2 0x207
#define CAN2_FIFO1_ID3 0x208

#endif
