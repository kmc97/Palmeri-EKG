/* EKG CODE 
 *BME 790
 *Katie Carroll & Deepti Gopinath 
 * Code takes in 3 lead- EKG signal and outputs both instantaneous and average HR for digital and analog signal
 * LED flashes in response to Bradycardia and TachyCardia.  LED input is based on Digital Signal.
  */

// Pin Numbers
int digitalPIN = 12;
int pausePIN =2;
int resetPIN = 3;
int LEDPIN = 8;
int analogPIN = A0;
int hrLightPin = 4;

// LED Parameters
int tach_f = 100; // 10 Hz
int brad_f = 500; // 2 Hz
int ledState = LOW; // set light LED
unsigned long previousMillis = 0; // last time value
int LEDstateHR = LOW;
// Interrupt Function Variables
boolean pauseFlag = LOW; // set pause flag to low, runs loop

// Digital Signal Parameters
int state; // current state
int oldBeat; // last beat count
int beatD = 0; // heart beat counter used to determine heart rate
int last = 0;  // to be compared to current state
float told; // last time step
float tint; // time step interval
unsigned long t = 0; // current time 
int hrD; // output, instantaneous heart rate from digital signal
int avgD; // output, average heart rate from digital signal

// Dummy variables
int i = 0;
int x = 0;
int p;

// Heart rate array parameters
int lengthArray = 60; // input length of indicies for heart rate average
int avgDig[60];

// Analog Signal Parameters
int sigA;
int beatA; // counts number of heart beats for analog signal
int sig2A;
int sig1A;
unsigned long t1= 0;
unsigned long t0;
int oldCount;
int hrA;
unsigned long tA;
float tintA;
float toldA;
int avgAna [60]; // average analog HR array
int avgA; // average analog HR output

/////////////////////////////////           SETUP         ///////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LEDPIN,OUTPUT);
pinMode(digitalPIN, INPUT);
pinMode(analogPIN, INPUT);
pinMode(hrLightPin,OUTPUT);
attachInterrupt(digitalPinToInterrupt(pausePIN),pauseF,RISING); // Pauses Function
attachInterrupt(digitalPinToInterrupt(resetPIN),reset,RISING); // Resets heart Rate information
}

/////////////////////////////////           LOOP         //////////////////////////////////////////////////
void loop() {
  if(pauseFlag == LOW){
    oldBeat = beatD; // used to trip bitDig flag 
    beatDetectDig(); // used to detect if digital HR event occurs
    HRlight(); // light blinks with digital heart Rate
    beatDig(); // outputs both average and instantaneous HR for digital signal
    tachy(); // LED if HR is Tachycardic
    brady(); // LED if HR is Bradycardic
    oldCount = beatA; // flag used to trip anaBeat
    anaDetect(); // used to detect if analog HR event occurs
    anaBeat(); // outputs both average and instantaneous HR for analog signal
      
      if (hrD> 40 && hrD<180){
      digitalWrite(LEDPIN, LOW); // Turns light off if the HR is in between HR standard
      }
    }
// if flag HIGH, nothing occurs in loop "pause"
}
 
////////////////////////////////     INTERRUPT FUNCTIONS    //////////////////////////////////////////////////////////
//set to 0 code runs, if interrupt fxn activate flag is 1 and code is paused
void pauseF (){
  pauseFlag = !pauseFlag;
  digitalWrite(LEDPIN,LOW);
}
// clears all heart rate values (Avg/Instant for Analog/Digital)
void reset () {
  for (int j =0; j< lengthArray; j++){
      avgDig[j] = 0; // reset values to zero in average digital array
       hrD = 0; // reset instantaneous digital HR to 0
      avgAna[j] = 0; //reset values to zero in average array
      hrA = 0; // reset instantaneous analog HR to 0
      
  }
}
//////////////////////////////       NORMAL FUNCTIONS     ///////////////////////////////////////////////////////////////
//Light Functions: Flash lights Tachy at 10 Hz, Brady at 2 Hz
void tachy (){
  unsigned long currentMillis = millis();
    if(hrD >= 180){
      if (currentMillis - previousMillis >= tach_f){
          previousMillis = currentMillis; // runs at 10 Hz
      if (ledState == LOW){
          ledState = HIGH; // if light is off, turn it on (blinking)
} else {
    ledState = LOW; // if light is on turn it off
}
digitalWrite(LEDPIN, ledState); // apply state changes
    }
  }
}

void brady (){
unsigned long currentMillis = millis();
if(hrD <= 40){
  if (currentMillis - previousMillis >= brad_f){
      previousMillis = currentMillis; // runs at 2 hz
  if (ledState == LOW){
      ledState = HIGH; // if light is off, turn it on (blinking)
  } else {
      ledState = LOW; // if light is on turn it off
      }
digitalWrite(LEDPIN, ledState); // apply state changes
    }
  }
}

void HRlight() {
  if (oldBeat-beatD != 0){
    LEDstateHR = HIGH;
    digitalWrite(hrLightPin, LEDstateHR);
    delay(20);
    LEDstateHR = LOW;
    digitalWrite(hrLightPin,LEDstateHR);
  }
}

// Digital Functions
void beatDetectDig(){
   state = digitalRead(digitalPIN);  // read state of digital pin
if (state != last){
  if(state == HIGH){
    beatD++;            // if state changes and the state is high, count heart beat, (rising)
  } else {
  }
  delay(15);            // debouncing techinque to avoid double heart beat counts
}
last = state;           // reset last state flag to compare for next loop
}

void beatDig(){
   if (oldBeat - beatD != 0) {  // detect event (it changed aka not 0)
      Serial.print(hrD);   // print instantaneous digital HR
      t = millis();       // current time stamp
      tint = t-told;       // interval calculation
      tint = tint/1000.000;   // in seconds
      hrD = (60/tint);    //heart beat in minutes
      told = t;             // reset flag
      Serial.print(" ");    // print space

  if (hrD> 250){ 
    hrD = 0;        // get rid of any HR that is greater than a phsyiological bound
  }
      avgDig[i] = hrD; // assign heart rate values to avg array
      i++; // increment index
   if (i % lengthArray == 0){ // reset index, once 60 beats is obtained, to form running average
      i = 0; // reset index
        }
      avgD = 0; // clears average
   for (int j =0; j< lengthArray; j++){
      avgD += avgDig[j]; // sum up elements of array
  }
      avgD = avgD/lengthArray; // find average
      Serial.print(avgD);
      Serial.print("   ");
      }
   }



void anaBeat(){
 if (oldCount - beatA != 0) {  // detect analog event
     Serial.print(hrA); // serial print instantaneous analog HR
      tA = millis(); // current time stamp
      tintA = tA-toldA; // analog time interval
      tintA = tintA/1000.000; // in seconds
      hrA = (60/tintA); //interval in minutes
      toldA = tA; // reset flag
      
       if (hrA> 250){ 
          hrA = 0;  // get rid of large HR outside of phsyiological bounds
  }
     Serial.print(" ");
      avgAna[p] = hrA; // assign heart rate values to avg array
      p++; // increment index
      
   if (p % lengthArray == 0){ // reset index, once 60 beats is obtained, to form running average
    p = 0; // reset index
      }
      avgA = 0; // clears average
   for (int j =0; j< lengthArray; j++){
      avgA += avgAna[j]; // sum up elements of array
  }
      avgA = avgA/lengthArray; // find average
  Serial.println(avgA);

 }
}
void anaDetect(){
   sigA = analogRead(analogPIN); // read signal from analog pin
  if (sigA> 100){       //make sure its the Big peak, delay to ensure we are only detecting ONE heart beat
    t0 = millis();    // current time stamp
  if (t0 - t1 >= 50){   // delay used to only detect one Heart beat, time value delay guess and checked
    t1 = t0;      // reset flag
    beatA++;      // incremental beats
      }
  }
}

