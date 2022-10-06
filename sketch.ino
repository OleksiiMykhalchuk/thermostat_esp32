#include <DHTesp.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <Wire.h>
//#include <FirebaseESP32.h>

#define PIN 13
#define RELAY 12
#define INCREASE 15
#define DECREASE 2
#define SHOW_INFO 4
uint8_t setPoint = 20;

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHTesp dht;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinModeSetup();
  dht.setup(PIN, DHTesp::DHT22);
  lcd.init();
  lcd.backlight();

  WiFi.begin("Wokwi-GUEST", "");
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  configTime(0,0,"pool.ntp.org");

}

void showInfo() {
  struct tm timeInfo;
  getLocalTime(&timeInfo);
  Serial.println(&timeInfo, "%H:%M:%S");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(&timeInfo, "%H:%M:%S");
  lcd.setCursor(0,1);
  lcd.print(WiFi.localIP());
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("WiFi Status");
  lcd.setCursor(0,1);
  if (isConnected()) {
    lcd.print("Connected");
  } else {
    lcd.print("Not Connected");
  }
  
  delay(1000);
}

int isConnected() {
  if (WiFi.status() == WL_CONNECTED) {
    return true;
  } else {
    return false;
  }
}

void loop() {
  
  TempAndHumidity data = dht.getTempAndHumidity();

  const char* status = getStatus(isTemperatureHigher(data.temperature));

  buttonPress();

  if (digitalRead(SHOW_INFO) == 0) {
    lcdPrint(data.temperature, data.humidity, status);
  } else {
    showInfo();
  }
  delay(1000); // this speeds up the simulation
}



