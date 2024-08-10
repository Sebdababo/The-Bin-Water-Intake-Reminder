#include <Wire.h>
#include <LiquidCrystal.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <RTClib.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#define LCD_RS 25
#define LCD_EN 26
#define LCD_D4 12
#define LCD_D5 13
#define LCD_D6 14
#define LCD_D7 27
#define POT_PIN 34
#define DHT_PIN 4
#define DS18B20_PIN 5
#define BUZZER_PIN 18
#define IR_PIN 19

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR 0x3C

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);
DHT dht(DHT_PIN, DHT22);
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);
IRrecv irrecv(IR_PIN);
decode_results results;
RTC_DS3231 rtc;

float temperature = 0.0;
float humidity = 0.0;
float liquidTemperature = 0.0;
int waterIntake = 0;
int dailyGoal = 2000;
unsigned long lastReminderTime = 0;
const unsigned long reminderInterval = 3600000;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  dht.begin();
  sensors.begin();
  irrecv.enableIRIn();
  rtc.begin();
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void readSensors() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  sensors.requestTemperatures();
  liquidTemperature = sensors.getTempCByIndex(0);
}

int calculateRecommendedIntake() {
  return 2000 + (temperature - 20) * 100 + (humidity - 50) * 20;
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Intake: ");
  lcd.print(waterIntake);
  lcd.print("ml");
  lcd.setCursor(0, 1);
  lcd.print("Goal: ");
  lcd.print(dailyGoal);
  lcd.print("ml");
}

void updateOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.print("C Hum: ");
  display.print(humidity);
  display.print("%");
  display.setCursor(0, 10);
  display.print("Liquid Temp: ");
  display.print(liquidTemperature);
  display.print("C");
  display.setCursor(0, 20);
  display.print("Recommended: ");
  display.print(calculateRecommendedIntake());
  display.print("ml");
  display.setCursor(0, 30);
  DateTime now = rtc.now();
  display.print(now.timestamp(DateTime::TIMESTAMP_TIME));
  display.display();
}

void handleIRRemote() {
  if (irrecv.decode(&results)) {
    switch(results.value) {
      case 0xFF6897: // Example: Button 1 (replace with your remote's actual codes)
        waterIntake += 100;
        break;
      case 0xFF9867: // Example: Button 2
        waterIntake += 250;
        break;
      case 0xFFB04F: // Example: Button 3
        waterIntake += 500;
        break;
    }
    irrecv.resume();
  }
}

void checkReminder() {
  unsigned long currentTime = millis();
  if (currentTime - lastReminderTime >= reminderInterval) {
    if (waterIntake < dailyGoal) {
      tone(BUZZER_PIN, 1000, 1000);
    }
    lastReminderTime = currentTime;
  }
}

void adjustDailyGoal() {
  int potValue = analogRead(POT_PIN);
  dailyGoal = map(potValue, 0, 4095, 1000, 5000);
}

void loop() {
  readSensors();
  handleIRRemote();
  adjustDailyGoal();
  checkReminder();
  updateLCD();
  updateOLED();
  delay(1000);
}