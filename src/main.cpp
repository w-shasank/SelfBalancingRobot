#include <WiFi.h>
#include <Arduino.h>
#include <MPU6050.h>
#include "MotorDriver.h"
#include "PID.h"

MPU6050 mpu;
PID pitch_pid(0.0, 1.0, 0.01, 0.1); // SetPoint, Kp, Ki, Kd

MotorDriver rightMotor(16, 17, 4); // Motor pins for right motor
MotorDriver leftMotor(5, 18, 19); // Motor pins for left motor

void setup() {
    Serial.begin(115200);    
    Wire.begin();

    mpu.initialize();
    rightMotor.Initialize();
    leftMotor.Initialize();

    if (mpu.testConnection()) {
        Serial.println("MPU6050 connection successful");
    } else {
        Serial.println("MPU6050 connection failed");
    }
    
    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);

    // mpu.CalibrateAccel();
    // mpu.CalibrateGyro();
    // mpu.PrintActiveOffsets();

    mpu.setXAccelOffset(-1150);
    mpu.setYAccelOffset(493);
    mpu.setZAccelOffset(2776);

    mpu.setXGyroOffset(0.00);
    mpu.setYGyroOffset(0.00);
    mpu.setZGyroOffset(0.00);
}



void loop() {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    float roll = atan2(ay, az) * 180 / PI; 
    float pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180 / PI; 

    float control_signal = pitch_pid.Compute(pitch);

    if (control_signal > 0) {
        rightMotor.Forward();
        leftMotor.Forward();
        control_signal = constrain(control_signal, 0, 255); 
        rightMotor.SetSpeed(control_signal);
        leftMotor.SetSpeed(control_signal);
    } else if (control_signal < 0) {
        control_signal = constrain(control_signal, -255, 0);
        rightMotor.Backward();
        leftMotor.Backward();
        rightMotor.SetSpeed(-control_signal);
        leftMotor.SetSpeed(-control_signal);
    } else {
        rightMotor.Stop();
        leftMotor.Stop();
    }

    Serial.printf("Response: %.2f\n", control_signal);


    delay(100); 
}
