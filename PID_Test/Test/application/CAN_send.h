#ifndef _CAN_SEND_H
#define _CAN_SEND_H

#define MOTOR_STD_ID_0x200 0x200
#define MOTOR_STD_ID_0x1FF 0x1FF
#define MOTOR_STD_ID_0x1FE 0x1FE
#define MOTOR_STD_ID_0x2FE 0x2FE

void CAN_Test(void);
void autoReverse(void);
void ToggleAddGrid(float *set_point, float N);
void CAN_Motor_Send1(short a);
void CAN_Motor_Send1(short a);
#endif
