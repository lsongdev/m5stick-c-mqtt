#include <M5StickC.h>

float gyroX, gyroY, gyroZ;

void setup()
{
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setRotation(3);
  M5.Lcd.setTextSize(1);
  M5.Lcd.println("Hello world!");
}


void loop()
{
  M5.Lcd.setCursor(0, 10, 2);
  M5.Rtc.GetBm8563Time();
  M5.Lcd.printf("%02d:%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute, M5.Rtc.Second);
  M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
  M5.Lcd.printf("X:%7.2f\n", gyroX);
  M5.Lcd.printf("Y:%7.2f\n", gyroY);
  M5.Lcd.printf("Z:%7.2f\n", gyroZ);
  delay(100);
}