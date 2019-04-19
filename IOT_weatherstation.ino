#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"
#define DHTPIN 2     
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

#define OLED_RESET LED_BUILTIN //4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };
  
#define SSD1306_LCDHEIGHT 64
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
void setup() {
  pinMode(14,INPUT);
 Serial.begin(115200); 
  Serial.println("DHT11 Monitor System");
 dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
   display.display();
  delay(2000);
  display.clearDisplay();
display.drawPixel(10, 10, WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(25,11);
  display.print("Hello");
  display.setTextSize(1);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setCursor(0,3);
  display.print("ROBOKITS INDIA");
  display.display();
  delay(4000);
  display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
 showTemp();
 display.clearDisplay();
// Pir();
 // display.clearDisplay();
}
void Pir(void)
{
  int pir=digitalRead(14);
  if(pir==HIGH)
  {
  display.setTextSize(1);
  display.setCursor(25,11);
  display.print("MOTION DETECTED");
 display.display();
  }
  else if(pir==LOW)
  {
    display.setTextSize(1);
  display.setCursor(25,11);
  display.print("NO MOTION ");
 display.display();
  }
}

void showTemp(void) {   // function to read and display temperature
   delay(2000);// Wait a few seconds for sensor to measure
  
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
   Serial.println("Failed to read from DHT sensor!");
    return;
  }

  notehum(h);
    display.clearDisplay();
  delay(3000);
  notetemp(t,'C');   

 delay(3000);  
 display.clearDisplay();
 notetemp(f,'F');   
 delay(3000); 
}
void notehum(float hum)
{ display.drawRect(1, 1, display.width()-1, display.height()-1, WHITE);  
   display.setTextSize(2);
    display.setCursor(15,10);
  display.print(hum);
  display.setCursor(80,10);
  display.print("%"); 
    display.setCursor(112,10);    
  display.print("H"); 
 display.display();
  
}
void notetemp(float temp, char C_F)   
 {
 display.drawRect(1, 1, display.width()-1, display.height()-1, WHITE);  
  display.setTextColor(WHITE);   
  display.setTextSize(1);       
  display.setCursor(104,3);
  display.print("o");            
  display.setTextSize(2);
  display.setCursor(112,10);    
  display.print(C_F);            

 if(temp >=100 || temp < 0){    
    display.setTextSize(2);
    display.setCursor(15,10);
 }
 else if(temp < 10 && temp >= 0){  
  display.setTextSize(3);
  display.setCursor(25,6);
 }

 else
 {
    display.setTextSize(3);   
    display.setCursor(10,6);
 }

  display.print(temp);  
  display.display();
  
 }
