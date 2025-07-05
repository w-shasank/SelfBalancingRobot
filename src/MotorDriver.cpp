#include "MotorDriver.h"
#include <Arduino.h>

MotorDriver::MotorDriver(int motorPin1, int motorPin2, int pwmPin)
    : motorPin1(motorPin1), motorPin2(motorPin2), pwmPin(pwmPin) {
}

void MotorDriver::Initialize() {
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(pwmPin, OUTPUT);
    
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    analogWrite(pwmPin, 0); 
}

void MotorDriver::SetSpeed(int speed) {
    analogWrite(pwmPin, speed);
}

void MotorDriver::Stop() {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
}

void MotorDriver::Forward() {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
}

void MotorDriver::Backward() {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
}
