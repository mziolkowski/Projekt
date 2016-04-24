#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
Serial.begin(9600);
sensors.begin();
}

void loop() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("YOLO I etap");
  delay(2000);
  lcd.clear();



}
