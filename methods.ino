int isTemperatureHigher(int temp) {
  if (temp < setPoint) {
    return true;
  } else {
   return false;
  }
}

void pinModeSetup() {
  pinMode(PIN, INPUT);
  pinMode(RELAY, OUTPUT);
  pinMode(INCREASE, INPUT);
  pinMode(DECREASE, INPUT);
  pinMode(SHOW_INFO, INPUT);
}

void buttonPress() {
  int button = digitalRead(INCREASE);
  int decrease = digitalRead(DECREASE);
 if (button == 1) {
    setPoint++;
  }
  if (decrease == 1) {
    setPoint--;
  }
}

void lcdPrint(float temp, float humid, const char* status) {
  
  lcd.setCursor(0,0);
  lcd.print("T/H:");
  lcd.setCursor(4,0);
  lcd.print(temp);
  lcd.setCursor(9,0);
  lcd.print("/");
  lcd.setCursor(10,0);
  lcd.print(humid);
  lcd.setCursor(13,1);
  lcd.print(status);
  lcd.setCursor(0,1);
  lcd.print("setPoint: ");
  lcd.setCursor(10,1);
  lcd.print(setPoint);
  lcd.setCursor(12,1);
  lcd.print(" ");
}

const char* getStatus(int isHigher) {
 if (isHigher) {
    digitalWrite(RELAY, HIGH);
    return "ON ";
  } else {
    digitalWrite(RELAY, LOW);
    return "OFF";
  }
}