//#include <Arduino.h>
/***************************************************************************
  This sketch is based on Adafruit BME280 and SSD1306 sample sketches.
  I have merged the sketches and modified them to display temperature(Hiti)
  pressure, altitude(Haed) and humidity(Raki). This sketch has been setup
  for Seeduino Xiao board, but should work on most SAMD boards by modifying
  pin definitions.
  /***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface. The device's I2C address is either 0x76 or 0x77.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
  See the LICENSE file for details.
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_VEML7700.h>

//#define BME_SCK 13
//#define BME_MISO 12
//#define BME_MOSI 11
//#define BME_CS 10


#define SEALEVELPRESSURE_HPA (1013.25)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_DC     2
#define OLED_CS     6
#define OLED_RESET  1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         &SPI, OLED_DC, OLED_RESET, OLED_CS);

//Adafruit_VEML7700 veml = Adafruit_VEML7700();
//  veml.setGain(VEML7700_GAIN_1);
//  veml.setIntegrationTime(VEML7700_IT_800MS);
//

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  //while (!Serial);   // time to get serial running
  Serial.println(F("BME280 test"));
//  Serial.println("Adafruit VEML7700 Test");


  unsigned status;

//  Serial.print(F("Gain: "));
//  switch (veml.getGain()) {
//    case VEML7700_GAIN_1: Serial.println("1"); break;
//    case VEML7700_GAIN_2: Serial.println("2"); break;
//    case VEML7700_GAIN_1_4: Serial.println("1/4"); break;
//    case VEML7700_GAIN_1_8: Serial.println("1/8"); break;
//  }
//
//  Serial.print(F("Integration Time (ms): "));
//  switch (veml.getIntegrationTime()) {
//    case VEML7700_IT_25MS: Serial.println("25"); break;
//    case VEML7700_IT_50MS: Serial.println("50"); break;
//    case VEML7700_IT_100MS: Serial.println("100"); break;
//    case VEML7700_IT_200MS: Serial.println("200"); break;
//    case VEML7700_IT_400MS: Serial.println("400"); break;
//    case VEML7700_IT_800MS: Serial.println("800"); break;
//  }

  //veml.powerSaveEnable(true);
  //veml.setPowerSaveMode(VEML7700_POWERSAVE_MODE4);

//  veml.setLowThreshold(10000);
//  veml.setHighThreshold(20000);
//  veml.interruptEnable(true);
//

  status = bme.begin(0x76);

//  if (!veml.begin()) {
//    Serial.println("Sensor not found");
//    while (1);
//  }
//
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}

void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  display.setTextColor(SSD1306_WHITE);
  //display.clearDisplay();
  display.setCursor(0, 9);
  //display.clearDisplay();
  display.println("Hiti");
  display.setCursor(60, 9);
  display.println(bme.readTemperature());
  display.setCursor(93, 9);
  display.println("C");
  display.display();

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");


  display.setCursor(0, 25);
  display.println(F("Pressure"));
  display.setCursor(56, 25);
  display.println(bme.readPressure() / 100.0F);
  display.setCursor(100, 25);
  display.println(F("hPa"));
  display.display();

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  display.setCursor(0, 35);
  display.println(F("Haed"));
  display.setCursor(56, 35);
  display.println(bme.readAltitude(SEALEVELPRESSURE_HPA));
  display.setCursor(94, 35);
  display.println(F("m"));
  display.display();

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  display.setCursor(0, 45);
  display.println(F("Raki"));
  display.setCursor(56, 45);
  display.println(bme.readHumidity());
  display.setCursor(88, 45);
  display.println(F("%"));
  display.display();

//  Serial.print("Lux: "); Serial.println(veml.readLux());
//  Serial.print("White: "); Serial.println(veml.readWhite());
//  Serial.print("Raw ALS: "); Serial.println(veml.readALS());
//  display.setCursor(0, 55);
//  display.println(F("Lux"));
//  display.setCursor(56, 55);
//  display.println(veml.readLux());
//  display.display();
//

  Serial.println();
}

void loop() {
  printValues();
  delay(delayTime);
//  uint16_t irq = veml.interruptStatus();
//  if (irq & VEML7700_INTERRUPT_LOW) {
//    Serial.println("** Low threshold");
//  }
//  if (irq & VEML7700_INTERRUPT_HIGH) {
//    Serial.println("** High threshold");
//  }}
}
