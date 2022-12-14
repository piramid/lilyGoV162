#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);

int inputPin = 19;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
String motion;
void setup() {
  pinMode(inputPin, INPUT);     // declare sensor as input
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
  display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
  display.setTextSize(1); // กำหนดขนาดตัวอักษร
  display.setTextColor(WHITE);
  display.setCursor(0,0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
  display.println("** TC Motion Alarm **");
//  display.setCursor(0,10);
//  display.setTextSize(2);
//  display.setTextColor(BLACK, WHITE); //กำหนดข้อความสีขาว ฉากหลังสีดำ
//  display.println(" Myarduino");
//  display.setCursor(0,32);
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.println("128 x 64 Pixels 0.96");
//  display.setCursor(0,48);
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.println(" www.myarduino.net "); // แสดงผลข้อความ www.Myarduino.net
  display.display();
}

void show(String message) {
// text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
  display.println("** TC Motion Alarm **");
  display.setCursor(0,10);
  display.print("Motion : ");
  display.print(message);
  display.display();
  display.clearDisplay();
}

void loop() {
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    //digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      motion = "detected";
      show(motion);
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    //digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH) {
      // we have just turned of
      Serial.println("Motion ended!");
      motion = "ended";
      show(motion);
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
