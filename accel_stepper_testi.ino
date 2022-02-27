
  
  
  /* Example sketch to control a 28BYJ-48 stepper motor with ULN2003 driver board and Arduino UNO. More info: https://www.makerguides.com */
// Include the Arduino Stepper.h library:
#include <Stepper.h>
const int buttonPin = 7;     // the number of the pushbutton pin
// Define number of steps per rotation:
const int stepsPerRevolution = 2048;
const int RevolutionsPerMove = 228;
int counter = 0;  
bool directionUP = true;  
    
bool morning = true;
bool stopped = true;
int buttonState = LOW;         // variable for reading the pushbutton status
unsigned long previousDayMillis = 0;
const unsigned long dayTIme =43200000;//1000*60*60*12;
int motorSpeed = 15;

// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 9,11,10,12);

void setup() {
  
  // Begin Serial communication at a baud rate of 9600:
  pinMode(buttonPin, INPUT);
  myStepper.setSpeed(motorSpeed);
  Serial.begin(9600);
}
void loop() {
buttonState = digitalRead(buttonPin);
unsigned long currentMillis = millis();

  if (stopped) 
  {
    if (buttonState == HIGH)
    {
      startMotor();
      runMotor();
    }
    if (currentMillis - previousDayMillis >= dayTIme)
    {
      if (morning)
        {
          directionUP = true;
          morning = false;
        }
        else 
        {
          directionUP = false;
          morning = true;
        }
    startMotor();
    previousDayMillis = currentMillis;
    }
  }
  else 
  {
    if (buttonState == HIGH) 
    {
      stopMotor();
      delay(2000);
      return;
    }

    runMotor();
  }

}
void startMotor()
{
    myStepper.setSpeed(motorSpeed);
  stopped = false;
}
void runMotor()
{
    
    if (directionUP)
    {
      if (counter == RevolutionsPerMove) 
        {
          stopMotor();
          return; 
        }
      /*else if ( counter >= 190)
         myStepper.setSpeed(5);
      else if ( counter >= 180)
         myStepper.setSpeed(8);
      else if (counter >= 150)
         myStepper.setSpeed(10);
      else if (counter >= 120)
         myStepper.setSpeed(12);*/
      counter++;
      myStepper.step(-stepsPerRevolution);
    }
    else
    {
      if (counter == 0) 
        {
          stopMotor();
          return;
        }
      counter--;
      myStepper.step(stepsPerRevolution);
    }
    
  
  
}

void stopMotor()
{
    directionUP = !directionUP;
    stopped = true;
  
  // Motor powers off
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
}



