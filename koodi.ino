#include <LiquidCrystal.h>
int Contrast = 60;
LiquidCrystal lcd(13, 10, 7, 6, 5, 2);
const int buttonPin = A5;
const int GamePin = A4;
long whiteTime;
long blackTime;
int buttonPushCounter = 0;
int buttonState = 0;
int GameState;
int lastButtonState = 0;
int startTime = millis();

const int buzzer = A3;
const int whiteButtonPin = 3;
const int blackButtonPin = 4;
const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

// Patterns for characters 0,1,2,3,4,5,6,7,8,9
int datArray[10] = {B00000011, B10011111, B00100101, B00001101,
                    B10011001, B01001001, B01000001, B00011111,
                    B00000001, B00001001};

void endSound() {
  tone(buzzer, 1000);
  delay(50);
  tone(buzzer, 2000);
  delay(50);
  tone(buzzer, 3000);
  delay(50);
  noTone(buzzer);
}

void countdown(long gameTime) {
  // declare times
  long whiteTime = gameTime;
  long blackTime = gameTime;
  long gameStartTime = millis();
  long turnStartTime = millis();
  long timeRemaining;
  long lastWhiteTime=gameTime;
  long lastBlackTime=gameTime;
  int isWhiteTurn = 1;
  
  while (true) {
    int whiteButtonState = digitalRead(whiteButtonPin);
    int blackButtonState = digitalRead(blackButtonPin);
    
    if (!whiteButtonState && isWhiteTurn) {
      // white button is pressed
      isWhiteTurn = 0;
      // add turn elapsed time to opponent's time
      blackTime += millis() - turnStartTime;
      // initialize next turn start time
      turnStartTime = millis();
    }
    
    if (!blackButtonState && !isWhiteTurn) {
      isWhiteTurn = 1;
      whiteTime += millis() - turnStartTime;
      turnStartTime = millis();
    }

    if (isWhiteTurn) {
      // add time that elapsed during gamesetup and
      // subtract time that is elapsed.
      timeRemaining = whiteTime + gameStartTime - millis();
      lastWhiteTime = timeRemaining;
    } else {
      timeRemaining = blackTime + gameStartTime - millis();
      lastBlackTime = timeRemaining;
    }
    
    if (timeRemaining <= 0) {
      // when time is up, print confirmation and break loop
      Serial.println("time is up");
      // play sound alert
      endSound();
      break;
    }
    
    //Serial.print(lastBlackTime);
    //Serial.print(" ");
    //Serial.println(lastWhiteTime);
    
    monitor(lastWhiteTime / 1000, lastBlackTime / 1000);
    long LEDtimer=((lastBlackTime+lastWhiteTime)/1000);
    lcd.setCursor(0,1);
    lcd.print("Total Time:");
    lcd.setCursor(12,1);
    lcd.print(LEDtimer);
  }
}

void getEachDigit(int time, int* ones, int* tens, int* hundreds) {
  if (time >= 10) {
    *tens = (time / 10);
  } else {
    *tens = 0;
  }
  if (time >= 10) {
    *hundreds = (time / 100);
  }
  *ones = time % 10;
  Serial.println(*tens);
}

void monitor(long whiteTime, long blackTime) {
  int ones, tens, hundred, b_ones, b_tens, b_hundred;
  getEachDigit(whiteTime, &ones, &tens, &hundred);
  getEachDigit(blackTime, &b_ones, &b_tens, &b_hundred);
  
  
  digitalWrite(latchPin, LOW);

  // right side
  shiftOut(dataPin, clockPin, MSBFIRST, datArray[b_hundred]);
  shiftOut(dataPin, clockPin, MSBFIRST, datArray[b_tens]);
  shiftOut(dataPin, clockPin, MSBFIRST, datArray[b_ones]);
  // left side
  shiftOut(dataPin, clockPin, MSBFIRST, datArray[ones]);
  shiftOut(dataPin, clockPin, MSBFIRST, datArray[tens]); 
  shiftOut(dataPin, clockPin, MSBFIRST, datArray[hundred]);
  digitalWrite(latchPin, HIGH);
}

void setup () {
  analogWrite(9, Contrast);
  lcd.begin(16,2);
  pinMode(buzzer, OUTPUT); 
  pinMode(buttonPin, INPUT);
  pinMode(GamePin, INPUT);
  Pelinalku();
  pinMode(whiteButtonPin, INPUT);
  pinMode(blackButtonPin, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
  
}

void loop(){
  buttonState = digitalRead(buttonPin);
  GameState = digitalRead(GamePin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
    }
    delay(50);
  }
  lastButtonState = buttonState;
  
  if (buttonPushCounter==2){
    lcd.setCursor(0,0);
    lcd.print("Gametime: 120");
    if (GameState==0) {
    countdown(120000);
    }
  }
  else if (buttonPushCounter==3){
    lcd.setCursor(0,0);
    lcd.print("Gametime: 240");
    if (GameState==0) {
    countdown(240000);
    }
  }
  else if (buttonPushCounter==4){
    lcd.setCursor(0,0);
    lcd.print("Gametime: 360");
    if (GameState==0) {
    countdown(360000);
    }
  }
  else if (buttonPushCounter==5){
    lcd.setCursor(0,0);
    lcd.print("Gametime: 480");
    if (GameState==0) {
    countdown(480000);
    }
  }
  else if (buttonPushCounter==6){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Failed to select");
    lcd.setCursor(0,1);
    lcd.print("Select again:");
    delay(5000);
    lcd.clear();
    buttonPushCounter=1;
  }  }




void Pelinalku() {
  lcd.setCursor(0,0);
  lcd.print("Select Game:");
  delay(2000);
  lcd.clear();
  lcd.print("Game 1: 120s");
  lcd.setCursor(0,1);
  lcd.print("Game 2: 240s");
  delay(4000);
  lcd.clear();
  lcd.print("Game 3: 360s");
  lcd.setCursor(0,1);
  lcd.print("Game 4: 480s");
  delay(4000);
  lcd.clear();
  lcd.print("Select by");
  lcd.setCursor(0,1);
  lcd.print("pressing button");
  delay(4000);
  lcd.clear();
}
