#ifndef BSP_CAN_H
#define BSP_CAN_H
#include "struct_typedef.h"
#include "pid.h"

#define TOGGLE_START_CURRENT 4.0f // 拨弹开始时电流,超过此值但拨盘转不动即为堵转

// #define ONE_GRID_ANGLE 164.0f // 度
#define ONE_GRID_ANGLE 78.0f // 度
#define SIGN_ROTATE -1.0f    // 拨盘正转动方向 1.0f表示逆时针为正拨  -1.0表示逆时针为反拨

#define M3508_ANGLE_RATIO 0.04394531f // 将机械角度转为度
#define M3508_SPEED_RATIO 6.0f        // 度/s
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
  MOTOR_TYPE motor_type; // 电机类型
  MOTOR_ID motor_id;     // 电机id
  MOTOR_CAN_TYPE can_type;
  int8_t __;
} MOTOR_Typedef;

/*拨弹电机状态*/
typedef enum ToggleState
{
  TOGGLE_NORMAL,  // 正常
  TOGGLE_ERROR,   // 拨弹错误
  TOGGLE_REVERSE, // 反拨
} ToggleState;

/* 拨弹控制器 */
typedef struct ToggleController
{
  Pid_Typedef toggle_pos_pid;
  Pid_Typedef toggle_speed_pid; // 拨弹速度
  MOTOR_Receive_Typedef toggle_info;

  float set_pos;
  float set_speed;
  int8_t is_shoot; // 发射指令

  float shoot_freq_speed; // 根据机器人等级设置的拨盘速度

  //	反拨部分
  ToggleState toggle_state;
  uint8_t rev_shoot; // 速度环反拨指令
  int32_t reverse_counter;
  int32_t error_counter; // 拨弹错误计数
} ToggleController;

extern void can_filter_init(void);

#endif
