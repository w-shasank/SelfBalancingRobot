#pragma once


class MotorDriver {
    public:
        MotorDriver(int motorPin1, int motorPin2, int pwmPin);
        void Initialize();
        void SetSpeed(int speed);
        void Stop();
        void Forward();
        void Backward();
    private:
        int motorPin1;
        int motorPin2;
        int pwmPin;
};