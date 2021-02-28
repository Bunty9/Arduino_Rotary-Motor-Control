#include "Button2.h"; //  https://github.com/LennartHennigs/Button2
#include "ESPRotary.h";    //https://github.com/LennartHennigs/ESPRotary

#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //SDA = A4, SCL = A5
LiquidCrystal_I2C lcd(0x27, 16, 2);

/////////////////////////////////////////////////////////////////

#define ROTARY_PIN1 14           //Clock Pin
#define ROTARY_PIN2 12           //DT pin
#define BUTTON_PIN 13            //Button pin
#define MOTOR_B_PWM 15            //motor pin for pwm

#define CLICKS_PER_STEP 4   // this number depends on your rotary encoder 
/////////////////////////////////////////////////////////////////

ESPRotary r = ESPRotary(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);
Button2 b = Button2(BUTTON_PIN);

/////////////////////////////////////////////////////////////////
byte arrow[] = {  B00000,  B00100,  B00110,  B11111,  B00110,  B00100,  B00000,  B00000}; //binary for arrow character
byte fan1[] = {  B00000,  B10001,  B01010,  B00100,  B01010,  B10001,  B00000,  B00000};
byte fan2[] = {  B00000,  B00100,  B00100,  B11111,  B00100,  B00100,  B00000,  B00000};

//////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  delay(50);
  Serial.println("\n\nSimple Counter");
  pinMode(MOTOR_B_PWM, OUTPUT);
  r.setChangedHandler(rotate);
  r.setLeftRotationHandler(showDirection);
  r.setRightRotationHandler(showDirection);
  
  b.setTapHandler(click);
  b.setLongClickHandler(resetPosition);
  lcd.init();                       // initialize the lcd   
  lcd.backlight();
  lcd.createChar(0, arrow);
  lcd.createChar(1, fan1);
  lcd.createChar(2, fan2);
 
  for (int i=0 ; i<16 ; i++){           //lcd animation
  lcd.setCursor(i,0);
  lcd.write(1);
  delay(100);
  lcd.clear();
  lcd.setCursor(i+1,0);
  lcd.write(2);
  delay(100);
  lcd.clear();
  i++;
  }

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Encoder Control");
}

void loop() {
  r.loop();                     //rotary encoder loop start
  b.loop();                      //button encoder loop start
}

void character(){

}
void rotate(ESPRotary& r) {
//   Serial.println(r.getPosition());
   int RotaryPosition = r.getPosition();
   String dir = r.directionToString(r.getDirection());

   if (dir == "RIGHT") {
     if (RotaryPosition >= 10) {                  //maximum count is set to 10
       RotaryPosition = 10;
       r.resetPosition(10);                       //reset when max is reached
       Serial.println (RotaryPosition); 
     }
     else {
         RotaryPosition=RotaryPosition;
         Serial.println (RotaryPosition); 
     }
   }
   if (dir == "LEFT") {
     if (RotaryPosition <= 0) {                 //minimum count is set to 10
       RotaryPosition = 0;                        
       r.resetPosition();                       //reset when min is reached
       Serial.println (RotaryPosition); 
     }        
     else {
      RotaryPosition=RotaryPosition;          
       Serial.println (RotaryPosition); 
      }
    }
    
    if (RotaryPosition == 0 ) { 
      analogWrite( MOTOR_B_PWM, LOW );
    } 
    if (RotaryPosition == 1 ) {
      analogWrite( MOTOR_B_PWM, 100 );
    }
    if (RotaryPosition == 2 ) {
      analogWrite( MOTOR_B_PWM, 200 );
    }
    if (RotaryPosition == 3 ) {
      analogWrite( MOTOR_B_PWM, 300 );
    }
    if (RotaryPosition == 4 ) {
      analogWrite( MOTOR_B_PWM, 400 );
    } 
    if (RotaryPosition == 5 ) {
      analogWrite( MOTOR_B_PWM, 500 );
    } 
    if (RotaryPosition == 6 ) {
      analogWrite( MOTOR_B_PWM, 600 );
    }
    if (RotaryPosition == 7 ) { 
      analogWrite( MOTOR_B_PWM, 700 );
    }
    if (RotaryPosition == 8 ) { 
      analogWrite( MOTOR_B_PWM, 800 );
    }
    if (RotaryPosition == 9) { 
     analogWrite( MOTOR_B_PWM, 900 );
    }
    if (RotaryPosition == 10) { 
     analogWrite( MOTOR_B_PWM, 1024 );
    }
    
  int currentValue = RotaryPosition;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Encoder Control");
  lcd.setCursor(0,1);
  lcd.print("Speed ");
  lcd.print(currentValue*10);
  lcd.print("%");
 
}


////////////////////////////////////////////////////////////////////
// on left or right rotation
void showDirection(ESPRotary& r) {
  Serial.println(r.directionToString(r.getDirection()));
}
 
// single click
void click(Button2& btn) {                  //stop motor on click
  Serial.println("Click!");
  r.resetPosition();
  analogWrite( MOTOR_B_PWM, LOW );
}

// long click
void resetPosition(Button2& btn) {
  Serial.println("long click!");
}

////////////////////////////////////////////////////////////////////////
