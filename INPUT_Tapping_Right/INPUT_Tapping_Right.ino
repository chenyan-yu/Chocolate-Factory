#include "Stepper.h"
#include <Servo.h> 
Servo blackChoco; 
Servo whiteChoco;

int FSR = 0;
int lastFSR = 0;
int tapCount = 0;
int tapTime = 0;
int lastTapTime = 0;
int timeSum = 0;
int tapFrequency = -1;
int highest = 0;
int posStart = 60;
int posMiddle = 105;
int posEnd = 150;

//The number of rotating steps, which controls the crawler, can be adjusted according to the position of the funnel
const int stepsPerRevolution = 2150;  
                                     
Stepper myStepper(stepsPerRevolution, 8,9,10,11);   

// make chocolate according to different mood 
void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(10);
  // initialize the serial port:
  Serial.begin(9600);
  blackChoco.attach(7);
  whiteChoco.attach(6);
  blackChoco.write(135);
  whiteChoco.write(45);
}
 
void anxious() {
  // drop 1 black choco 1 milk choco
  delay(300);
  blackChoco.write(75);
  
  delay(300);
  blackChoco.write(30);
  delay(300);
  blackChoco.write(75);
  delay(300);
  blackChoco.write(120);
  delay(1000);

  whiteChoco.write(posMiddle);
  delay(300);
  whiteChoco.write(posEnd);
  delay(300);
  whiteChoco.write(posMiddle);
  delay(300);
  whiteChoco.write(posStart); 
  delay(5000); 
  
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  ////Move to the heating plate, after the delay "heating time", move back to the cooling plate, the heating time can be modified
  delay(10000);

  myStepper.step(-stepsPerRevolution);
  
    tapCount = 0;
  timeSum = 0;
  tapTime = 0;
  lastTapTime = 0;
  highest = 0;
  tapFrequency = -1;
}

void angry() {
  // drop 2 black choco
    delay(300);
  blackChoco.write(75);
  
  delay(300);
  blackChoco.write(30);
  delay(300);
  blackChoco.write(75);
  delay(300);
  blackChoco.write(120);
  delay(1000);

    delay(300);
  blackChoco.write(75);
  
  delay(300);
  blackChoco.write(30);
  delay(300);
  blackChoco.write(75);
  delay(300);
  blackChoco.write(120);
  delay(1000);
  
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(10000);

  myStepper.step(-stepsPerRevolution);
  
    tapCount = 0;
  timeSum = 0;
  tapTime = 0;
  lastTapTime = 0;
  highest = 0;
  tapFrequency = -1;
}

void sad() {
  // drop 2 milk choco
  whiteChoco.write(posMiddle);
  delay(300);
  whiteChoco.write(posEnd);
  delay(300);
  whiteChoco.write(posMiddle);
  delay(300);
  whiteChoco.write(posStart); 
  delay(5000); 

  whiteChoco.write(posMiddle);
  delay(300);
  whiteChoco.write(posEnd);
  delay(300);
  whiteChoco.write(posMiddle);
  delay(300);
  whiteChoco.write(posStart); 
  delay(5000); 
  
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(10000);

  myStepper.step(-stepsPerRevolution);
  
    tapCount = 0;
  timeSum = 0;
  tapTime = 0;
  lastTapTime = 0;
  highest = 0;
  tapFrequency = -1;
}


void loop() {
  FSR = analogRead(A0);

  // record the highest reading
  if (FSR > highest){
    highest = FSR;
  }
  
  // if two successive readings have a significant difference, that means one tapping
  if (FSR - lastFSR > 200){
    tapCount = tapCount + 1;
    // record the tap time
    tapTime = millis() / 100;
    // if no tapping for more than 10s, restart the program
//    if (tapTime - lastTapTime > 100){
//      tapCount = 0;
//      timeSum = 0;
//    }
    // calculate the total tapping time only when successive tapping is detected
    // the total tapping time equals to the sum of intervals between tappings
    if (lastTapTime != 0){
      timeSum = timeSum + tapTime - lastTapTime;
    }
    lastTapTime = tapTime;
  }
  
  // calculate the frequency, *10 is just used to present the number as integers
  if (millis() / 100 - lastTapTime > 100) {
    tapFrequency = tapCount * 10 / timeSum;
  }
  
  Serial.print(timeSum);
  Serial.print('\t');
  Serial.print(tapCount);
  Serial.print('\t');
  Serial.print(highest);
  Serial.print('\t');
  Serial.println(tapFrequency);
  lastFSR = FSR;

  // classify the mood
  if (tapFrequency > 5){
    anxious();
  }
  
  if (tapFrequency >= 0 && tapFrequency <= 5){
    if (highest > 600){
      angry();
    }
    if (highest > 20 && highest <= 600){
      sad();
    }
  }

//  delay(40);
  
}
