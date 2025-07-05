
#pragma once


class PID {
    float kp, ki, kd;
    float setPoint;
    float previousTime;
    float previousError;
    float integral;

    public:
        PID(float setPoint, float kp, float ki, float kd);
        float Compute(float measuredValue);
};