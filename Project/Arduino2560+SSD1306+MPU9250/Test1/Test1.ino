#include "DHT.h"
#include <Wire.h>
#include "MPU9250.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// SSD1306
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(4);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// MPU9250
MPU9250 IMU(Wire,0x68);
int status;

// Other Variable
//double tempature_c = 0.0;
double result[10];
double *getResult;


void setup() {
  // serial to display data
  Serial.begin(115200);
  while(!Serial) {}

  // Init MPU9250
  // start communication with IMU 
  status = IMU.begin();
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }

  // setting the accelerometer full scale range to +/-8G 
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  // setting the gyroscope full scale range to +/-500 deg/s
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  // setting DLPF bandwidth to 20 Hz
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  // setting SRD to 19 for a 50 Hz update rate
  IMU.setSrd(19);

  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
}

double * getIMUData(double result[]){
  // read the sensor
  IMU.readSensor();

  // display the data
  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelZ_mss(),6);
  Serial.print("\t");

  Serial.print(IMU.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroY_rads(),6);
  Serial.print("\t");
  Serial.print(IMU.getGyroZ_rads(),6);
  Serial.print("\t");

  Serial.print(IMU.getMagX_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagY_uT(),6);
  Serial.print("\t");
  Serial.print(IMU.getMagZ_uT(),6);
  Serial.print("\t");

  Serial.println(IMU.getTemperature_C(),6);
  
  result[0] = IMU.getAccelX_mss();
  result[1] = IMU.getAccelY_mss();
  result[2] = IMU.getAccelZ_mss();
  result[3] = IMU.getGyroX_rads();
  result[4] = IMU.getGyroY_rads();
  result[5] = IMU.getGyroZ_rads();

  return result;
}

void showData(double dataList[]){
//  Serial.println(dataList[0]);
//  Serial.println(dataList[1]);
//  Serial.println(dataList[2]);
  
  double acc_x = dataList[0];
  double acc_y = dataList[1];
  double acc_z = dataList[2];
  double gyr_x = dataList[3];
  double gyr_y = dataList[4];
  double gyr_z = dataList[5];
  
  // clear display
  display.clearDisplay();
  // display.display();
  // display a line of text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Acc
  display.setCursor(3, 1);
  display.print("acc_x: ");
  display.setCursor(3, 11);
  display.print(acc_x);

  display.setCursor(3, 22);
  display.print("acc_y: ");
  display.setCursor(3, 33);
  display.print(acc_y);

  display.setCursor(3, 44);
  display.print("acc_z: ");
  display.setCursor(3, 55);
  display.print(acc_z);

  // Gyr
  display.setCursor(64, 1);
  display.print("gyr_x: ");
  display.setCursor(64, 11);
  display.print(gyr_x);

  display.setCursor(64, 22);
  display.print("gyr_y: ");
  display.setCursor(64, 33);
  display.print(gyr_y);

  display.setCursor(64, 44);
  display.print("gyr_z: ");
  display.setCursor(64, 55);
  display.print(gyr_z);

  // Save to screen
  display.display();
}

void loop() {
  getResult = getIMUData(result);
  showData(getResult);
  delay(333);
}
