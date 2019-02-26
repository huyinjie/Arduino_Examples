#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// DHT11
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// SSD1306
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(4);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Other Variable
//float tempature_c = 0.0;
float result[2] = {50.0,50.0};
float *getResult;

void setup() {
  // Init Serial
  Serial.begin(9600);

  // Init DHT sensor 
  dht.begin();
  delay(1000);

  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
}


float * getDhtData(float result[]){
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float tempature_c = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(tempature_c) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // delay(3000);

  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(tempature_c);
  Serial.println(F("°C "));

  result[0] = humidity;
  result[1] = tempature_c;

  return result;
}

void showData(float dataList[]){
  float tempature_c = dataList[1];
  float humidity = dataList[0];
  
  // clear display
  display.clearDisplay();
  // display.display();
  // display a line of text
  display.setTextSize(1.1);
  display.setTextColor(WHITE);
  
  display.setCursor(1, 20);
  display.print("Temperature: ");
  display.setCursor(80, 20);
  display.print(tempature_c);

  display.setCursor(1, 40);
  display.print("Humidity: ");
  display.setCursor(80, 40);
  display.print(humidity);

  // Save to screen
  display.display();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(333);
  getResult = getDhtData(result);
  showData(getResult);
}
