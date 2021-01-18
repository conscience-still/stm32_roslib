#include "pid.h"

float GetPid(PID_typedef* pid,float m,float ep)
{
    float err  =  ep -m;

    if(pid->_ki >0){
        pid->_iter = pid->_iter+ pid->_ki*err; 
    }
    if(pid->_iter>pid->_imax){
        pid->_iter = pid->_imax;
    }
    if(pid->_iter<pid->_imin){
        pid->_iter = pid->_imin;
    }

    float out  = pid->_iter+pid->_kp*err;


    if(pid->_kd >0){
        pid->_lastd[2] +=pid->_alph*(err - pid->_lastd[1]);
        pid->_lastd[1] = err;
        out += pid->_kd*pid->_lastd[2];
    }

    if(out > pid->_omax )out = pid->_omax;
    if(out < pid->_omin )out = pid->_omin;
    return out;
}

void SetPidPra(PID_typedef* pid, float kp,float ki,float kd)
{
    pid->_kp = kp;
    pid->_ki = ki;
    pid->_kd = kd;
}
