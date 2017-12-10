int volt = 12;
int last = 0;
int state= 0;
float told;
float tint;
int beats = 0;
int oldBeat;
unsigned long t = 0;
int hr;
int lengthArray = 60;
int avgDig[60];
boolean avgFlag = HIGH;
int i = 0;
int avg;
int LED = 8;
int pausePIN =2;
int resetPIN = 3;
int tach_f = 100;
int brad_f = 500;
int heartrate = 230;
int x = 0;
int ledState = LOW; // set light LED
boolean pauseFlag = LOW;
unsigned long previousMillis = 0; // last time value

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(LED,OUTPUT);
pinMode(volt, INPUT);
attachInterrupt(digitalPinToInterrupt(pausePIN),pauseF,RISING); // Pauses Function
attachInterrupt(digitalPinToInterrupt(resetPIN),reset,RISING); // Resets heart Rate information

}

void loop() {
  if(pauseFlag == LOW){
oldBeat = beats;
beatDetectDig();
beatDig();
tachy();
brady();
if (hr> 40 && hr<180){
digitalWrite(LED, LOW);
}}

    }
 
// INTERRUPT FUNCTIONS
//set to 0 code runs, if interrupt fxn activate flag is 1 and code is paused
void pauseF (){
  pauseFlag = !pauseFlag;
  digitalWrite(LED,LOW);
}

void reset () {
  for (int j =0; j< lengthArray; j++){
      avgDig[j] = 0; // sum up elements of array
        hr = 0;
  }
}


 
void beatDetectDig(){
   state = digitalRead(volt);
  // put your main code here, to run repeatedly:
if (state != last){
  if(state == HIGH){
    beats++;
    //Serial.println(beats);
  } else {
  }
  delay(15);
}
last = state;
}

void beatDig(){
   if (oldBeat - beats != 0) {
     Serial.print(hr);
      t = millis();
      tint = t-told; // interval
      tint = tint/1000.000; // in seconds
      hr = (60/tint); //interval in minutes
      told = t;
  Serial.print(" ");
      avgDig[i] = hr; // assign heart rate values to avg array
      i++; // increment index
   if (i % lengthArray == 0){ // reset index, once 60 beats is obtained, to form running average
    i = 0;
      }
      avg = 0; // clears average
   for (int j =0; j< lengthArray; j++){
      avg += avgDig[j]; // sum up elements of array
  }
      avg = avg/lengthArray; // find average
  Serial.println(avg);
   }
   }

// NORMAL FUNCTIONS: Flash lights Tachy at 10 Hz, Brady at 2 Hz
void tachy (){
unsigned long currentMillis = millis();
if(hr >= 180){
if (currentMillis - previousMillis >= tach_f){
    previousMillis = currentMillis;
if (ledState == LOW){
    ledState = HIGH;
} else {
    ledState = LOW;
}
digitalWrite(LED, ledState);
    }
  }
}

void brady (){
unsigned long currentMillis = millis();
if(hr <= 40){
  if (currentMillis - previousMillis >= brad_f){
      previousMillis = currentMillis;
  if (ledState == LOW){
      ledState = HIGH;
  } else {
      ledState = LOW;
      }
digitalWrite(LED, ledState);
    }
  }
}

