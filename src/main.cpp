#include "main.h"

volatile uint16_t val;
volatile uint8_t button;
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void rpm_interrupt()
{
  val++;
}

void button_interrupt()
{
  button += 5;
}

void setup()
{
  Serial.begin(115200);
  Serial.println(F("\nInitializing... "));
  attachInterrupt(1, rpm_interrupt, CHANGE);
  attachInterrupt(0, button_interrupt, FALLING);
  lcd.init();
  lcd.backlight();
  analogWrite(9, 1);
}

void loop()
{
  val = 0;    // сбрасываем счетчик и ждем.
  delay(500); // так как прерывание CHANGE, срабатывает два раза, считываем каждые пол секунды
  button += 5;
  analogWrite(9, button);
  lcd.home();
  lcd.print("RPM:");
  lcd.print((val * 60) / 2); // количество импульсов на 60 секунд и делим на количество импульсов на оборот
  lcd.print(" (");
  lcd.print(val);
  lcd.print(") - " + String(String((val * 60) / 2).length()));
  lcd.print(val);
  lcd.setCursor(0, 1);
  lcd.print(button);
  lcd.print("                ");
}