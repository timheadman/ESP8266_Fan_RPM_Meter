#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
volatile int val;
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void rpm()
{
  val++;
}

void setup()
{
  Serial.begin(115200);
  Serial.println(F("\nInitializing... "));
  attachInterrupt(0, rpm, CHANGE);
  lcd.init();
  lcd.backlight();
  analogWrite(9, 1);
}

void loop()
{
  static uint8_t i = 0;
  val = 0;    // сбрасываем счетчик и ждем.
  delay(500); // так как прерывание CHANGE, срабатывает два раза, считываем каждые пол секунды
  if (i > 55) i = 0;
  analogWrite(9, i++);
  lcd.home();
  lcd.print((val * 60) / 2); // количество импульсов на 60 секунд и делим на количество импульсов на оборот
  lcd.print("rpm; ");
  lcd.print(val);
  lcd.print("val             ");
  lcd.setCursor(0, 1);
  lcd.print(i);
  lcd.print("                ");


}