#include <SparkFunLSM6DSO.h>
#include "Wire.h"

LSM6DSO myIMU; //Default constructor is I2C, addr 0x6B
int BTN_PIN = 7;
const int TAP_PIN = 4;

int currentBtn;
int lastBtn;
bool vibrate = false; 


int angleX = 0;
int angleY = 0;
int angleZ = 0;

int prevX = 0;
int prevZ = 0;


  // pinMode(buttonPin, INPUT);


void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  pinMode(TAP_PIN, OUTPUT); //taptic

  delay(10);
    if( myIMU.begin() )
      Serial.println("Ready.");
    else { 
      Serial.println("Could not connect to IMU.");
      Serial.println("Freezing");
    }

    if( myIMU.initialize(BASIC_SETTINGS) )
      Serial.println("Loaded Settings.");

  }

void loop() {

// int buttonState = digitalRead(BTN_PIN);
//   //   currentBtn = digitalRead(buttonPin);
//   //   // Serial.println(currentBtn);
//   //   if (lastBtn == LOW && currentBtn == HIGH) {
//   //     fix =! fix;         // LED 가 LOW 면 HIGH 로 바꿔준다.
//   //   }
//   //   lastBtn = currentBtn;

//   //   if(fix==true){
      
//   //   } else {


      angleX = myIMU.readFloatAccelX()*100;
      // angleY = myIMU.readFloatAccelY()*100;
      angleZ = myIMU.readFloatAccelZ()*100;

      Serial.print(angleX);
      Serial.print(',');
      Serial.println(angleZ);

      if(prevZ>-26 && angleZ<-34){
        vibrate = true;
      }

      if(prevZ<26 && angleZ>34){
        vibrate = true;
      }

      if(prevX<26 && angleX>34){
        vibrate = true;
      }

      if(prevX>-26 && angleX<-34){
        vibrate = true;
      }

      if (vibrate == true){
        tap(500);
        vibrate = false;
      }

      prevX = angleX;
      prevZ = angleZ;

      delay(100);
    // }
}

void tap(int time){
    digitalWrite(TAP_PIN, HIGH);
    delay(time);
    digitalWrite(TAP_PIN, LOW);
}