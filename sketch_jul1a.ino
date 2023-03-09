#include <Servo.h>  //includes the servo library
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;

#define ir_enter 2
#define ir_back 4

#define ir_car1 7
#define ir_car2 12
#define ir_car3 5



int S1 = 0, S2 = 0, S3 = 0;
int flag1 = 0, flag2 = 0, flag3 = 0;
int slots = 3;

void setup() {

  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);

  myservo.attach(3);
  myservo.write(100);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("      HELLO  ");
  lcd.setCursor(0, 1);
  lcd.print(" Parking System   ");
  delay(3000);
  lcd.clear();

  Read_Sensor();

  int total = S1 + S2 + S3;
  slots = slots - total;
}

void loop() {

  Read_Sensor();

  lcd.setCursor(0, 0);
  lcd.print("  Have Slots:");
  lcd.print(slots);
  lcd.print("  ");

  lcd.setCursor(0, 1);

  lcd.setCursor(0, 1);
  if (S1 == 1) {
    lcd.print("S1:F ");
  } else {
    lcd.print("S1:E ");
  }

  lcd.setCursor(5, 1);
  if (S2 == 1) {
    lcd.print(" S2:F ");
  } else {
    lcd.print(" S2:E ");
  }
  lcd.setCursor(10, 1);
  if (S3== 1) {
    lcd.print("  S3:F ");
  } else {
    lcd.print("  S3:E ");
  }

  if (digitalRead(ir_enter) == 0 && flag1 == 0) {
    if (slots > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(180);
        slots = slots - 1;
      }
    } else {
      delay(100);
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print(" SORRY ");
      lcd.setCursor(0, 1);
      lcd.print(" Parking is full ");
      delay(2500);
      lcd.clear();
    }
  }

  if (digitalRead(ir_back) == 0 && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(180);
      slots = slots + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1) {
    delay(1000);
    myservo.write(90);
    flag1 = 0, flag2 = 0;
  }

  delay(100);
}

void Read_Sensor() {
  S1 = 0, S2 = 0, S3 = 0;

  if (digitalRead(ir_car1) == 0) { S1 = 1; }
  if (digitalRead(ir_car2) == 0) { S2 = 1; }
  if (digitalRead(ir_car3) == 0) { S3 = 1; }
}