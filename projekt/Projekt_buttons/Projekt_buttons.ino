#include <Adafruit_BMP085.h>
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 3
#define DHTTYPE DHT11

Adafruit_BMP085 bmp;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
  
void setup() {
  
  Serial.begin(9600);

  //przyciski
  pinMode(7, INPUT_PULLUP); //TEMP
  pinMode(5, INPUT_PULLUP); //CISNIENIE
  pinMode(13, INPUT_PULLUP); // OPADY
  pinMode(4, INPUT_PULLUP); //SWIATLO
    
  //wyswietlacz
  lcd.clear();
  lcd.init();
  lcd.backlight();
  lcd.setBacklight(HIGH);
  
  //czujnik DHT11
  dht.begin();

  //czujnik BMP180
  bmp.begin();

 
  Serial.println("Dane odczytane z czujnikow!!!");

}

void loop() {
  String wilg, wys, cis, temp, opa, swi;
  wilg = String ("Wilg: ");
  temp = String ("Temp: ");
  cis = String ("Cis: ");
  wys = String ("Wys: ");
  opa = String ("Opady: ");
  swi = String ("Swiatlo: ");
  
  //czujnik cisnienia
  float c = bmp.readPressure();
  float w = bmp.readAltitude(101325);
  
  //czujnik opadow
  int sensorA=analogRead(A0);
  int sensorD=digitalRead(8);
  int o = map (sensorA, 1023, 0, 0, 100);
  
  //czujnik DHT11
  float h=dht.readHumidity();
  float t=dht.readTemperature();  
  
   // czujnik swiatla
  int fotosensor = analogRead(A1);
  float s = fotosensor * (100.00 / 1023.0);

  String temp1 = (temp + t + "C");
  String wilg1 = (wilg + h + "%");
  String cis1 = (cis + (c/100) + "hPa");
  String opady1 = (opa + o + "%"); 
  String wys1 = (wys + w + "m");
  String swi1 = (swi + s + "%");

  //wyswietlenie informacji w knsoli i na lcd
  if(isnan(t) || isnan(h) || isnan(o) || !bmp.begin())
  {
    Serial.println("Blad odczytu danych z czujnika. Sprawdz wszystkie czujniki!!!");
    tone(12, 3000, 1000);
  }
  else
  { 
    Serial.println(temp1);
    Serial.println(wilg1);
    Serial.println(cis1);
    Serial.println(opady1);
    Serial.println(wys1);
    Serial.println(swi1);
    Serial.println();
    delay(2000);
  }
  
  if(digitalRead(7) == LOW)
  {
    delay(20);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(temp);
    lcd.print(t);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print(wilg);
    lcd.print(h);
    lcd.print("%");
  }

  else if(digitalRead(5) == LOW)
  {
    delay(20);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cis);
    lcd.print(c/100);
    lcd.print("hPa");
    lcd.setCursor(0,1);
    lcd.print(wys);
    lcd.print(w);
    lcd.print("m npm"); 
  }
  
  else if (digitalRead(13) == LOW)  
  {
    delay(20);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(opa);
    lcd.print(o);
    lcd.print("%");
    lcd.setCursor(0,1);  
    if (o <= 40)
    {
      lcd.print("Pogodnie");
    }
      //lcd.print("Pogodnie");
    else if (o > 40 && o < 60)
      lcd.print("Zachmurzenie");
    else if (o >= 60)
      {
        tone(12, 2000, 1000);
        lcd.print("Pada deszcz"); 
      }   
  }

   else if (digitalRead(4) == LOW)  
  { 
    delay(20);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(swi);
    lcd.print(s);
    lcd.print("%");
  }
  
  
  else
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(temp);
    lcd.print(t);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print(wilg);
    lcd.print(h);
    lcd.print("%");
    delay(2500);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cis);
    lcd.print(c/100);
    lcd.print("hPa");
    lcd.setCursor(0,1);
    lcd.print(wys);
    lcd.print(w);
    lcd.print("m npm");
    delay(2500);
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(opa);
    lcd.print(o);
    lcd.print("%");
    lcd.setCursor(0,1);  
    if (o <= 40)
     lcd.print("Pogodnie");
    else if (o > 40 && o < 60)
      lcd.print("Zachmurzenie");
    else if (o >= 60)
      {
        tone(12, 2000, 1000);
        lcd.print("Pada deszcz"); 
      }  
    delay(2500);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(swi);
    lcd.print(s);
    lcd.print("%");
    delay(3500);
  }
}

