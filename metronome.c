// Metronome, Leading Accent, Visual&Audible Tact - 2019 Peter Csurgay
#include 
#include 
#include 
#include 
#include "TimerOne.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define pin_neopixel 7
#define NUMPIXELS 8
#define BRIGHTNESS 32
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, pin_neopixel, NEO_GRB + NEO_KHZ800);
#define IDLE_11 0
#define SCLK_01 1
#define SCLK_00 2
#define SCLK_10 3
#define SDT_10 4
#define SDT_00 5
#define SDT_01 6
int state = IDLE_11;
#define CLK 2
#define DT 3
#define pin_switch 4
#define pin_buzzer 5
int bpm = 60;
int bpmFirst = 0; // LED On at First, Off at the rest...
int tack = 4;
bool leadingTack = false;
int pos = 0;
int curVal = 0;
int prevVal = 0;

void setup() {
  pixels.begin();
  pinMode(pin_buzzer, OUTPUT);
  Timer1.initialize(1000000*60/bpm/2);
  Timer1.attachInterrupt(buzztick);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(pin_switch, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLK), rotaryCLK, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT), rotaryDT, CHANGE);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  if (digitalRead(pin_switch)==LOW) {
    delay(100);
    while(digitalRead(pin_switch)==LOW) ;
    delay(100);
    Timer1.detachInterrupt();
    showGreenTacks();
    while(digitalRead(pin_switch)==HIGH) {
      if (curVal>prevVal) {
        tack+=1; if (tack>8) { if (leadingTack) tack = 8; else { leadingTack = true; tack = 1; } }
      } else if (curValprevVal) {
    bpm+=2; if (bpm>240) bpm = 240;
  } else if (curVal=100) display.print("       "); else display.print("        "); 
  display.print(bpm);
  display.display();
}