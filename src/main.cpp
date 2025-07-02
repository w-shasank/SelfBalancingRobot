#include <WiFi.h>
#include <Arduino.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
    Serial.begin(115200);    

    mpu.initialize();

    if (mpu.testConnection()) {
        Serial.println("MPU6050 connection successful");
    } else {
        Serial.println("MPU6050 connection failed");
    }

    mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_500);
    mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_8);
}


void loop() {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    float roll = atan2(ay, az) * 180 / PI; 
    float pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180 / PI; 

    Serial.print("Roll: "); Serial.print(roll);
    Serial.print(" | Pitch: "); Serial.println(pitch);

    delay(500); 
}
