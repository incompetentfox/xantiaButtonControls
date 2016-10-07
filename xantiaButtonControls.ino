
// Provide digital output given the analogue voltage input
// from Citroen steering wheel stereo controls.
// ADS, 6/10/16

// set pins
const int wheelButtonsIn1 = 0; // use analog pins 0 and 1 to read voltage
const int wheelButtonsIn2 = 1; // output from wheel buttons.
const int volUp = 7;           // use digital pins for output.
const int volDown = 8;
const int fwdSkip = 9;
const int bwdSkip = 10;
const int memo = 11;
const int mute = 12;
const int custom1 = 5;
const int custom2 = 6;
const int buttonArray1[] = {volUp,volDown,memo,custom1};  // group buttons in arrays
const int buttonArray2[] = {fwdSkip,bwdSkip,custom2};// for neater pin resets.
// int ampIsOn = 0; // This flag is to toggle the amplifier standby. Presently not reliable enough. 

int debugFlag = 1; 
char* buttonName = "";
float voltage = 0.0;

void setup(){
  // set up the pins as inputs and outputs
  pinMode(wheelButtonsIn1, INPUT);
  pinMode(wheelButtonsIn2, INPUT);
  pinMode(volUp, OUTPUT);
  pinMode(volDown, OUTPUT);
  pinMode(fwdSkip, OUTPUT);
  pinMode(bwdSkip, OUTPUT);
  pinMode(memo, OUTPUT);
  pinMode(mute, OUTPUT);

  Serial.begin(9600); // debug over serial
}

void loop() {

  int buttonArray1Value = analogRead(wheelButtonsIn1);
  int buttonArray2Value = analogRead(wheelButtonsIn2);
  float voltageA1 = buttonArray1Value * (5.0 / 1023.0);
  float voltageA2 = buttonArray2Value * (5.0 / 1023.0);
  
  // Read array 1 (volume controls and memo button).
  if(voltageA1 < 1.00)  {
    digitalWrite(volDown, HIGH);
    serialDebug(voltageA1,"volDown");
    delay(25);
  }
  if(voltageA1 > 1.00 && voltageA1 < 1.50)  {
    digitalWrite(custom1, HIGH);
    serialDebug(voltageA1,"Memo&VolUp");
    delay(25);
  }
  else if(voltageA1 > 1.50 && voltageA1 < 2.00)  {
    digitalWrite(volUp, HIGH);
    serialDebug(voltageA1,"volUp");
    delay(25);  
  }
  else if(voltageA1 > 2.00 && voltageA1 < 3.90)  {
    digitalWrite(memo, HIGH);
    serialDebug(voltageA1,"memo");
    delay(25);
  }
  else if(voltageA1 > 3.90)  {
    for (int i=0; i < 3; i++){
      digitalWrite(buttonArray1[i],LOW);
      delay(25);
    }
    serialDebug(voltageA1,"none(a1)");
  }
  
  // Read array two (skip and mute buttons)
  if(voltageA2 < 1.00)  {
      digitalWrite(mute, LOW);      // Amp standby needs to be pulled LOW.
      serialDebug(voltageA2,"mute");
      delay(25);
  }

    // the following is code to toggle the amp standby state when the mute button is pressed.
    // it seems to get stuck in the while loop for some reason- will try to debug.
    /*switch(ampIsOn) {
      case 0:
        {
            digitalWrite(mute,LOW);
            delay(250);
            ampIsOn = 1;
            Serial.println("Amp switched ON");
            while(voltageA2 < 1.00)  {
             
              voltageA2 = (analogRead(wheelButtonsIn2)* (5.0 / 1023.0));
            }
            break;
        }
      case 1:
        {
          digitalWrite(mute,HIGH);
          delay(250);
          ampIsOn = 0;
          Serial.println("Amp switched OFF");
          while(voltageA2 < 1.00)  {
              
              voltageA2 = (analogRead(wheelButtonsIn2)* (5.0 / 1023.0));
          }
          break;
        }
    }*/

  }
  else if(voltageA2 < 1.00 && voltageA2 < 1.50)  {
    digitalWrite(custom2, HIGH);
    serialDebug(voltageA2,"fwdSkip+bwdSkip");
    delay(25);
  }
  else if(voltageA2 < 1.50 && voltageA2 < 2.00)  {
    digitalWrite(bwdSkip, HIGH);
    serialDebug(voltageA2,"bwdSkip");
    delay(25); 
  }
  else if(voltageA2 < 2.00 && voltageA2 <3.90)  {
    digitalWrite(fwdSkip, HIGH);
    serialDebug(voltageA2,"fwdSkip");
    delay(25);  
  }
  else if(voltageA2 > 4.00)  {
    for (int i=0; i < 3; i++){
      digitalWrite(buttonArray2[i],LOW);
      delay(25);      
    }
    digitalWrite(mute,HIGH); 
    serialDebug(voltageA2,"none(a2)");
  }

 delay(250);
}

// debug (optional)
void serialDebug(float voltage, char* buttonName)  {
  if(debugFlag == 1)  {
    Serial.print("Button pressed: ");
    Serial.print(buttonName);
    Serial.print(" Voltage: ");
    Serial.print(voltage);
    Serial.println();
    char* buttonName = "";
  }
    
    else  {
      return;
    }
}    
