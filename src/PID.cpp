#include "PID.h"
#include <Arduino.h>

PID::PID(float setPoint, float kp, float ki, float kd)
    : setPoint(setPoint), kp(kp), ki(ki), kd(kd), previousTime(0.0),previousError(0.0) {}

float PID::Compute(float measuredValue)
{
    float error = setPoint - measuredValue;
    float dt = (millis() - previousTime) / 1000.0f; // Convert milliseconds to seconds
    previousTime = millis();

    float proportional = kp * error;
    integral = integral + (ki * error * dt);
    float derivative = kd * ((error - previousError) / dt);
    previousError = error;

    return proportional + integral + derivative;
}