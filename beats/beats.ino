int volt = 12;
int last = 0;
int state= 0;
float told;
float tint;
int beats = 0;
int oldBeat;
unsigned long t = 0;
int hr;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(volt, INPUT);
}

void loop() {

oldBeat = beats;
beatDetectDig();
beatInstantDig();




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

void beatInstantDig(){
   if (oldBeat - beats != 0) {
 t = millis();

 tint = t-told; // interval
 tint = tint/1000.000; // in seconds
 hr = (60/tint); //interval in minutes
 told = t;
Serial.println(hr);
   }
}

