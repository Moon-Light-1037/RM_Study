#ifndef BSP_CAN_H
#define BSP_CAN_H
#include "struct_typedef.h"
#include "pid.h"

#define TOGGLE_START_CURRENT 4.0f // ������ʼʱ����,������ֵ������ת������Ϊ��ת

// #define ONE_GRID_ANGLE 164.0f // ��
#define ONE_GRID_ANGLE 78.0f // ��
#define SIGN_ROTATE -1.0f    // ������ת������ 1.0f��ʾ��ʱ��Ϊ����  -1.0��ʾ��ʱ��Ϊ����

#define M3508_ANGLE_RATIO 0.04394531f // ����е�Ƕ�תΪ��
#define M3508_SPEED_RATIO 6.0f        // ��/s
#define C620_CURRENT_SEND_TRANS 819.2f

#define M3508_REDUCTION_RATIO 19.0f

typedef struct
{
  short Angle;
  short RealSpeed;
  short Current;
  char temp;

  short LastAngle;
  short AngleErr;
  int16_t Sum_AngleErr;

} MOTOR_Receive_Typedef;

typedef enum MOTOR_TYPE
{
  GM6020,
  M3508,
  M2006,
  DM_MOTOR
} MOTOR_TYPE;

typedef enum MOTOR_ID
{
  ID_201,
  ID_202,
  ID_203,
  ID_204,
  ID_205,
  ID_206,
  ID_207,
  ID_208
} MOTOR_ID;

typedef enum MOTOR_CAN_TYPE
{
  CAN_1,
  CAN_2
} MOTOR_CAN_TYPE;

typedef struct
{
  MOTOR_TYPE motor_type; // �������
  MOTOR_ID motor_id;     // ���id
  MOTOR_CAN_TYPE can_type;
  int8_t __;
} MOTOR_Typedef;

/*�������״̬*/
typedef enum ToggleState
{
  TOGGLE_NORMAL,  // ����
  TOGGLE_ERROR,   // ��������
  TOGGLE_REVERSE, // ����
} ToggleState;

/* ���������� */
typedef struct ToggleController
{
  Pid_Typedef toggle_pos_pid;
  Pid_Typedef toggle_speed_pid; // �����ٶ�
  MOTOR_Receive_Typedef toggle_info;

  float set_pos;
  float set_speed;
  int8_t is_shoot; // ����ָ��

  float shoot_freq_speed; // ���ݻ����˵ȼ����õĲ����ٶ�

  //	��������
  ToggleState toggle_state;
  uint8_t rev_shoot; // �ٶȻ�����ָ��
  int32_t reverse_counter;
  int32_t error_counter; // �����������
} ToggleController;

extern void can_filter_init(void);

#endif
