
// Provide digital output given the analogue voltage input
// from Citroen steering wheel stereo controls.
// ADS, 6/10/16

// set pins
const int wheelButtonsIn1 = 0; // use analog pins 0 and 1 to read voltage
const int wheelButtonsIn2 = 1; // output from wheel buttons.
const int volUp = 9;         // use digital pins for output.
const int volDown = 10;
const int fwdSkip = 8;
const int bwdSkip = 7;
const int memo = 5;
const int mute = 6;
const int custom1 = 3;
const int custom2 = 4;
const int buttonArray1[] = {volUp,volDown,memo,custom1};  // group buttons in arrays
const int buttonArray2[] = {fwdSkip,bwdSkip,mute,custom2};// for neater pin resets.

// voltage levels required for pin activation- if driving the wheel from 5v, values are:
// const int vLev0 = 1
// const int vLev1 = 1.5
// const int vLev2 = 2
// const int vLev3 = 3.9
// If driving from 3.6v:
const int vLev0 = 0.5;
const int vLev1 = 1.8;
const int vLev2 = 2.2;
const int vLev3 = 2.6;

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
  float voltageA1 = buttonArray1Value * (3.6 / 1023.0); // lower multiplier will change depending on 
  float voltageA2 = buttonArray2Value * (3.6 / 1023.0); // voltage used to drive the circuit. 3.6v here.
  
  // Read array 1 (volume controls and memo button).
  if(voltageA1 < vLev0)  {
    digitalWrite(volDown, HIGH);
    serialDebug(voltageA1,"volDown");
    delay(25);
  }

  else if(voltageA1 > vLev1 && voltageA1 < vLev2)  {
    digitalWrite(volUp, HIGH);
    serialDebug(voltageA1,"volUp");
    delay(25);  
  }
  else if(voltageA1 > vLev2 && voltageA1 < vLev3)  {
    digitalWrite(memo, HIGH);
    serialDebug(voltageA1,"memo");
    delay(25);
  }
  else if(voltageA1 > vLev3)  {
    for (int i=0; i < 3; i++){
      digitalWrite(buttonArray1[i],LOW);
      delay(25);
    }
    serialDebug(voltageA1,"none(a1)");
  }
  
  // Read array two (skip and mute buttons)
  
  if(voltageA2 < vLev0)  {
      digitalWrite(mute, HIGH);   
      serialDebug(voltageA2,"mute");
      delay(25);
  }

  else if(voltageA2 < vLev1 && voltageA2 < vLev2)  {
    digitalWrite(bwdSkip, HIGH);
    serialDebug(voltageA2,"bwdSkip");
    delay(25); 
  }
  else if(voltageA2 < vLev2 && voltageA2 < vLev3)  {
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

 delay(25);
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
