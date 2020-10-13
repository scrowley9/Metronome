#include <Arduino.h>

class Tempo{
  
  float pulse_width;

public:
  Tempo(unsigned long bpm){
    pulse_width = (float)((float) 60.0/(float)bpm)*(float)1000.0;
  }

  /* Wait HIGH */
  void pulse_high(void){
    // Serial.println(pulse_width/2);
    // Serial.println((unsigned long)pulse_width/2);
    delay(pulse_width/2);
  }

  void pulse_low(){
    delay(pulse_width/2);
  }

};

class Metronome{


public:
  
  Tempo* beats_per_minute; // Tempo = # of beats per minute. -- 60 Tempo == 1 beat a second
  
  Metronome(unsigned long bpm){
    beats_per_minute = new Tempo(bpm);
  }

  ~Metronome(){
    delete beats_per_minute;
  }

  // Time division
  // Intensity

};



#define BPM 40

uint8_t digital_pin = 7;
Metronome met(BPM);

void setup() {
  pinMode(digital_pin, OUTPUT);
  // Serial.begin(9600);
}

void loop() {

  digitalWrite(digital_pin, 1); // Write anything but 0x0 (if 0 write low, else write high)
  met.beats_per_minute->pulse_high();
  // delay(250);
  digitalWrite(digital_pin, 0);
  // delay(250);
  met.beats_per_minute->pulse_low();

}