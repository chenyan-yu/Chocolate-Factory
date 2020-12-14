#include "Nokia_5110.h"
#include <Servo.h> 

#define RST 2
#define CE 3
#define DC 4
#define DIN 5
#define CLK 6

Servo strawberry;
Servo peach;
Servo nut;

Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);


void setup() {
    /**
     * Note: if instead of text being shown on the display, all the segments are on, you may need to decrease contrast value.
     */
    lcd.setContrast(30); // 60 is the default value set by the driver
    
//    lcd.print("Take a rest. ");
//    delay(1000);
//    lcd.clear();

    lcd.println("Take a rest. ");

    strawberry.attach(8);
    peach.attach(9);
    nut.attach(10);
    strawberry.write(45);
    peach.write(45);
    nut.write(45);
}

void loop() {
  //How long will the topping switch be turned on after the screen is on for the first time, which can be modified
  delay(500);
//  delay(250000);
  nut.write(80);
  delay(300);
  nut.write(45);
  delay(1000);

  peach.write(80);
  delay(300);
  peach.write(45);
  delay(1000);

  strawberry.write(80);
  delay(300);
  strawberry.write(45);
  delay(1000);

  delay(350000);
  lcd.clear();
  lcd.println("The chocolate is ready =)");
  
 }
