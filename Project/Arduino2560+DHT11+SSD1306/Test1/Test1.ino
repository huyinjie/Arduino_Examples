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
float tempature_c = 0.0;


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

float getDhtData(){
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float tempature_c = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float tempature_f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(tempature_c) || isnan(tempature_f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float heatIndex_f = dht.computeHeatIndex(tempature_f, humidity);
  // Compute heat index in Celsius (isFahreheit = false)
  float heatIndex_c = dht.computeHeatIndex(tempature_c, humidity, false);

  // Serial.print(F("Humidity: "));
  // Serial.print(humidity);
  // Serial.print(F("%  Temperature: "));
  // Serial.print(tempature_c);
  // Serial.print(F("°C "));
  // Serial.print(tempature_f);
  // Serial.print(F("°F  Heat index: "));
  // Serial.print(heatIndex_c);
  // Serial.print(F("°C "));
  // Serial.print(heatIndex_f);
  // Serial.println(F("°F"));
  return tempature_c;
}

void showData(float data){
  // clear display
  display.clearDisplay();
  // display.display();
  // display a line of text
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(27, 30);
  display.print(data);

  // Save to screen
  display.display();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(333);
  tempature_c = getDhtData();
  showData(tempature_c);
}
