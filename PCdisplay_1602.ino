
#define DRIVER_VERSION 1    // 0 - маркировка драйвера кончается на 4АТ, 1 - на 4Т

// -------------------- БИБЛИОТЕКИ ---------------------
#include <Wire.h>               // библиотека для соединения
#include <LiquidCrystal_I2C.h>  // библтотека дислея
#include <TimeLib.h>
// -------------------- БИБЛИОТЕКИ ---------------------

// -------- АВТОВЫБОР ОПРЕДЕЛЕНИЯ ДИСПЛЕЯ-------------
// Если кончается на 4Т - это 0х27. Если на 4АТ - 0х3f
#if (DRIVER_VERSION)
LiquidCrystal_I2C lcd(0x27, 16, 2);
#else
LiquidCrystal_I2C lcd(0x3f, 16, 2);
#endif
// -------- АВТОВЫБОР ОПРЕДЕЛЕНИЯ ДИСПЛЕЯ-------------

#define printByte(args)  write(args);
#define TEMPERATURE_PRECISION 9


char inData[108];       // массив входных значений (СИМВОЛЫ)
int PCdata[26];        // массив численных значений показаний с компьютера

byte index = 0;
int display_mode = 0, percent = 0;
String string_convert,perc;
unsigned long timeout;
boolean reDraw_flag = 1, updateDisplay_flag, updateTemp_flag, timeOut_flag = 1;
byte lines[] = {4, 5, 7, 6};
unsigned long sec;
unsigned int mins, hrs;

tmElements_t tm;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  show_logo();
  delay(2500);
  lcd.clear();
  setTime(1);  // устанавливаем начальное время
}
// ------------------------------ ОСНОВНОЙ ЦИКЛ -------------------------------
void loop() {
  parsing();                          // парсим строки с компьютера
  updateDisplay();                    // обновить показания на дисплее
  timeoutTick();                      // проверка таймаута
}
// ------------------------------ ОСНОВНОЙ ЦИКЛ -------------------------------

void parsing() {
  while (Serial.available() > 0) {
    char aChar = Serial.read();
    if (aChar != 'E') {
      inData[index] = aChar;
      index++;
      inData[index] = '\0';
    } else
    {
      char *p = inData;
      char *str;
      index = 0;
      String value = "";
      while ((str = strtok_r(p, ";", &p)) != NULL) {
        string_convert = str;
        PCdata[index] = string_convert.toInt();
        index++;
      }
      index = 0;
      updateDisplay_flag = 1;
      updateTemp_flag = 1;
      tm.Second = PCdata[21];
      tm.Hour = PCdata[19];
      tm.Minute = PCdata[20];
      tm.Day = PCdata[22];
      tm.Month = PCdata[23];
      tm.Year = PCdata[24] - 1970;
      setTime(makeTime(tm));
    }
    timeout = millis();
    timeOut_flag = 1;
  }
}

void updateDisplay() {
  if (updateDisplay_flag) {
    if (reDraw_flag) {
      lcd.clear();
      switch (display_mode) {
        case 0: draw_labels_11();
          break;

      }
      reDraw_flag = 0;
    }
    switch (display_mode) {
      case 0: draw_stats_11();
        break;
    }
    updateDisplay_flag = 0;
  }
}

void draw_stats_11() {
  lcd.backlight();

  lcd.setCursor(4, 0); lcd.print(PCdata[4]);
  if (PCdata[4] < 100) perc = "% ";
  else perc = "";  lcd.print(perc);

  lcd.setCursor(4, 1); lcd.print(PCdata[5]);
  if (PCdata[5] < 100) perc = "% ";
  else perc = "";  lcd.print(perc);

  lcd.setCursor(13, 1); lcd.print(PCdata[7]);
  if (PCdata[7] < 100) perc = "% ";
  else perc = "";  lcd.print(perc);

  lcd.setCursor(13, 0); lcd.print(PCdata[6]);
  if (PCdata[6] < 100) perc = "% ";
  else perc = "";  lcd.print(perc);
}
void draw_labels_11() {
  lcd.setCursor(0, 0);
  lcd.print("CPU:");
  lcd.setCursor(0, 1);
  lcd.print("GPU:");
  lcd.setCursor(9, 0);
  lcd.print("RAM:");
  lcd.setCursor(9, 1);
  lcd.print("GPm:");
}
void timeoutTick() {
  if (millis() - timeout > 3000) {
    if (timeOut_flag == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Connect...");
      lcd.setCursor(12, 0);
      lcd.print("Fail");
      timeOut_flag = 0;
      reDraw_flag = 1;
      lcd.noBacklight();
    }
    char lcd_time_i[10];
    snprintf(lcd_time_i, sizeof(lcd_time_i), "%02d:%02d", hour(), minute());
    char lcd_date_i[12];
    snprintf(lcd_date_i, sizeof(lcd_date_i), "%02d/%02d/%04d", day(), month(), year());
    lcd.setCursor(0, 1);
    lcd.print(lcd_time_i);
    lcd.setCursor(6, 1);
    lcd.print(lcd_date_i);
  }
}
void show_logo() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("VL_PLAY Games");
  lcd.setCursor(2, 1);
  lcd.print("by Alex Gyver");
}
