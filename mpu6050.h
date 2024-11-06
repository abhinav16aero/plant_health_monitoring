#ifndef MPU_SENSOR_H
#define MPU_SENSOR_H
#include <Wire.h>
#include <MPU6050.h>

class MPUSensor {
  private:
    MPU6050 mpu;      
    char reading[256]; 

  public:
    void begin() {
      Wire.begin();
      mpu.initialize();
      if (!mpu.testConnection()) {
        Serial.println("MPU6050 connection failed");
        while (1);
      }
    }

    struct MotionData {
      int16_t ax, ay, az; 
      int16_t gx, gy, gz; 
    };

    MotionData readMotionData() {
      MotionData data;
      mpu.getMotion6(&data.ax, &data.ay, &data.az, &data.gx, &data.gy, &data.gz);
      return data;
    }

    void WriteToBuff() {
      MotionData data = readMotionData();
      sprintf(reading,
              "{\"Accel\":{\"X\":%d,\"Y\":%d,\"Z\":%d},\"Gyro\":{\"X\":%d,\"Y\":%d,\"Z\":%d}}",
              data.ax, data.ay, data.az, data.gx, data.gy, data.gz);
    }

    const char* getReading() {
      return reading;
    }
};

#endif
