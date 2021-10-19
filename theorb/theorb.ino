#include <Adafruit_CircuitPlayground.h>
#include "Keyboard.h"

int lastButtonState;
int currentButtonState;

int lastButtonState2;
int currentButtonState2;

int light = LOW;
long time = 0;
int state = HIGH;
boolean yes;
boolean previous = false;
int debounce = 200;

int light2 = LOW;
long time2 = 0;
int state2 = HIGH;
boolean yes2;
boolean previous2 = false;
int debounce2 = 200;

int light3 = LOW;
long time3 = 0;
int state3 = HIGH;
boolean yes3;
boolean previous3 = false;
int debounce3 = 200;



bool message;
bool message2;
bool message3;


#define LED 12  // The pin the LED is connected to
#define LED2 6  // The pin the LED is connected to
#define LED3 9


void setup() {
  message = true; // for user testing, message is already received from another user
  message2 = true;
  message3 = true;
  
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  Keyboard.begin();
  CircuitPlayground.begin();

  pinMode(LED, OUTPUT); // Declare the LED as an output
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  //shorter wire on LED bulb connected to the GND, 
  // longer wire connecteed to pin 

  //button states set up
  currentButtonState = CircuitPlayground.leftButton();
  currentButtonState2 = CircuitPlayground.rightButton();

  digitalWrite(LED2, HIGH); 
  digitalWrite(LED3, HIGH); 
}

void loop() {


  lastButtonState    = currentButtonState;
  currentButtonState = CircuitPlayground.leftButton();

  lastButtonState2    = currentButtonState2;
  currentButtonState2 = CircuitPlayground.rightButton();

  



  if( CircuitPlayground.readCap(0) > 100 ) {

      yes = true ;
  } else {
    yes = false;
  }
  if( CircuitPlayground.readCap(1) > 100 ) {

      yes2 = true ;
  } else {
    yes2 = false;
  }

  if( CircuitPlayground.readCap(2) > 100 ) {

      yes3 = true ;
  } else {
    yes3 = false;
  }


  if(lastButtonState == HIGH && currentButtonState == LOW) {
    Serial.println("The left button is pressed");
    
//    state = HIGH;
    light = !light;
    digitalWrite(LED, light); 
  } 
  // make the button toggle the light not the touch sensor.
  
  if(lastButtonState2 == HIGH && currentButtonState2 == LOW) {
    Serial.println("The right button is pressed");
    light3 = !light3;
    digitalWrite(LED3, light3); 
  } 

  //button pressed turn on / off 
  //touch sensor send keyboard message

  //https://forum.arduino.cc/t/cap-sensing-single-event-while-button-pressed/282380
  // to toggle the state of state
  if(yes == true && previous  == false && millis() - time> debounce){
    
     if(state == LOW){
       state = HIGH;
       
       Keyboard.press('=');
       Keyboard.releaseAll();
       //time = millis(); 
     }
     else {
       state = LOW;
       time = millis();   
       
       Keyboard.press('=');
       Keyboard.releaseAll(); 
     }
  }
   message = state;
   previous = yes;
   delay(10);

   if(yes2 == true && previous2  == false && millis() - time2> debounce2){
    
     if(state2 == LOW){
       state2 = HIGH;
       
       Keyboard.press('_');
       Keyboard.releaseAll();
       //time = millis(); 
     }
     else {
       state2 = LOW;
       time2 = millis();    

       Keyboard.press('_');
       Keyboard.releaseAll();
     }
  }
   message2 = state2;
   previous2 = yes2;
   delay(10);


  if(yes3 == true && previous3  == false && millis() - time3> debounce3){
    
     if(state3 == LOW){
       state3 = HIGH;
       
       Keyboard.press('|');
       Keyboard.releaseAll();
       //time = millis(); 
     }
     else {
       state3 = LOW;
       time3 = millis();    

       Keyboard.press('|');
       Keyboard.releaseAll();
     }
  }
   message3 = state3;
   previous3 = yes3;
   delay(10);

   //터치센서 눌렀을때 토글 되게하는게 아니라 그냥 꺼지게 하고 
   // 버튼 눌렀을때 켜지게 해야함
  

  if(light == HIGH) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
  if(message == HIGH) {
//    digitalWrite(LED, HIGH); 
    
   
  } else {
    // turn longer to turn off blink cuz the board detects cap sensor late by delay with blinking
//    digitalWrite(LED, LOW); 
//    digitalWrite(LED2, LOW);
//    digitalWrite(LED3, LOW);
    
  }

  if(message2 == HIGH) {
    
    digitalWrite(LED2, HIGH); 
//    digitalWrite(LED3, HIGH); 
   
  } else {
    // turn longer to turn off blink cuz the board detects cap sensor late by delay with blinking
//    digitalWrite(LED, LOW); 
    digitalWrite(LED2, LOW);
//    digitalWrite(LED3, LOW);
    
  }

  if(message3 == HIGH) {
    

//    digitalWrite(LED3, HIGH); 
   
  } else {
    // turn longer to turn off blink cuz the board detects cap sensor late by delay with blinking

//    digitalWrite(LED3, LOW);
    
  }

  

  Keyboard.end(); 

  Serial.println("time");
  Serial.println(millis() - time);
  
  Serial.print("message:");Serial.println(message);
  Serial.print("message2:");Serial.println(message2);
  Serial.print("message3:");Serial.println(message3);
  
  Serial.print("Capsense #0: "); Serial.println(CircuitPlayground.readCap(0));
  Serial.print("Capsense #1: "); Serial.println(CircuitPlayground.readCap(1));
  Serial.print("Capsense #2: "); Serial.println(CircuitPlayground.readCap(2));
  delay(300);
}

// button triggers the clarity change. both users should trigger at the same time. central server will observe it. 
