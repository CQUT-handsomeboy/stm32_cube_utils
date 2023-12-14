#ifndef PID_H
#define PID_H

typedef enum PID_Mode_e {
	INCREASEMENT,
	POSITIONAL
} PID_Mode_e;

typedef volatile struct PID_s {
	volatile float Kp,Ki,Kd;
	volatile float input;
	volatile float output;
	volatile float target;
	volatile float error;
	volatile float prev_error;
	volatile float error_sum;
	volatile float prev_prev_error;
	volatile PID_Mode_e mode;
} PID_s;

void PID_Init(PID_s * pid);
void PID_Reset(PID_s * pid);
void PID_Calculate(PID_s * pid);

#endif
