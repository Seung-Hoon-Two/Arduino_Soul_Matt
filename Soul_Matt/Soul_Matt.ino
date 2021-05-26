#include "BluetoothSerial.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define left_hand1 34
#define left_hand2 35
#define right_hand1 32
#define right_hand2 33

#define LED_PIN 13 //네오픽셀 핀
#define NUM_LEDS 10
#define brightness 150

const int numReadings = 10;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRBW + NEO_KHZ800);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup()
{
  Serial.begin(115200);
  SerialBT.begin("ESP32_CLASSIC_BT"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  strip.setBrightness(brightness);
  strip.begin();
  strip.show();
  Serial.println("left_hand");
  Serial.println("right_hand");
}

void loop()
{
  if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available())
  {
    Serial.write(SerialBT.read());
  }


  double left_hand = sensor(left_hand1,left_hand2);
  double right_hand = sensor(right_hand1,right_hand2);

  Serial.print(left_hand);
  Serial.print(",");
  Serial.println(right_hand);
  delay(100);

}

double sensor(int sensor_num1, int sensor_num2){
  int value = analogRead(sensor_num1) + analogRead(sensor_num2);
  return filtered_value(value,0.1);
}

double filtered_value(double value, double sensitivity){
  return value * (1 - sensitivity ) + value * sensitivity;
}

int peak_counter(){}
