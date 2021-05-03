/*
  SparkFun Inventor’s Kit
  Circuit 4A-HelloWorld

  The LCD will display the words "Hello World" and show how many seconds have passed since
  the RedBoard was last reset.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);   // tell the RedBoard what pins are connected to the display

void setup() {
  pinMode(2, INPUT_PULLUP);
  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();                      //clear the display
}

int mins = 0;

void loop() {

  lcd.setCursor(0, 0);              //set the cursor to the 0,0 position (top left corner)
  lcd.print("Get Rekt");       //print hello, world! starting at that position

  lcd.setCursor(0, 1);             //move the cursor to the first space of the bottom row
  int secs = millis() / 1000;
  lcd.print(secs);       //print the number of seconds that have passed since the last reset

  lcd.setCursor(10,0);
  if(secs % 60 == 0){
    mins = mins + 1;
  }
  lcd.print(mins);

  if(digitalRead(2) == LOW){
    lcd.setCursor(10,1);
    lcd.print("Oh Yeah"); 
  }
}
