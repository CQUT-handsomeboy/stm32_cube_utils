```C

#include "pid.h"

PID_s positional_pid; /* 声明一个PID_s结构体 */
PID_Reset(&positional_pid); /* 重置结构体内的成员 */

/* 设置PID计算模式 */
positional_pid.mode = POSITIONAL; // 位置式PID

/* 设置参数 */
positional_pid.Ki = 0.4;
positional_pid.Kp = 0.2;
positional_pid.Kd = 0.2;
positional_pid.target = 60;
positional_pid.input = 0;

/* 计算PID */
PID_Calculate(&positional_pid);

/* 运用计算结果 */
update_like_this(positional_pid.output);

```