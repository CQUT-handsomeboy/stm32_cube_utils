#include "pid.h"

void PID_Init(PID_s * pid)
{
	pid->Kp = 0;
	pid->Ki = 0;
	pid->Kd = 0;
	pid->target = 0;
	PID_Reset(pid);
}

void PID_Reset(PID_s * pid)
{
	pid->input = 0;
	pid->output = 0;
	pid->error = 0;
	pid->prev_error = 0;
	pid->prev_prev_error = 0;
	pid->error_sum = 0;
}

void PID_Calculate(PID_s * pid) {
	float P,I,D;
	switch (pid->mode) 
	{
	case INCREASEMENT:
		pid->error = pid->target - pid->input;
		P = (pid->error - pid->prev_error) * pid->Kp;
		I = pid->error * pid->Ki;
		D = ((pid->error - pid->prev_error) - 
			(pid->prev_error - pid->prev_prev_error)) * pid->Kd;
		pid->prev_prev_error = pid->prev_error;
		pid->prev_error = pid->error;
		break;
	case POSITIONAL:
		pid->error = pid->target - pid->input;
		pid->error_sum += pid->error;
		P = pid->Kp * pid->error;
		I = pid->Ki * pid->error_sum;
		D = pid->Kd * (pid->error - pid->prev_error);
		pid->prev_error = pid->error;
		break;
	}
	pid->output = P + I + D;
}
