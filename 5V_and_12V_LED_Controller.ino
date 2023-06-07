/*///////////////////////////////////////////////////////////////////////////////
FILENAME   : 5V_and_12V_LED_Controller.ino
AUTHOR     : Brian Denton <denton_brian_david@lilly.com>
DATE       : 2023-05-30
PROJECT    : 
DESCRIPTION: 
///////////////////////////////////////////////////////////////////////////////*/

#include <FastLED.h>
#include "FastLED_RGBW.h"

#define NUM_LEDS    300
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER RGB

// Arduino UNO pin numbers
// #define BRAKE_PIN 9
// #define LEFT_TURN_PIN 7
// #define RIGHT_TURN_PIN 8
// #define OUT1_PIN 4

//Arduino Nano pin numbers
#define BRAKE_PIN 2
#define LEFT_TURN_PIN 3
#define RIGHT_TURN_PIN 4
#define OUT1_PIN 8

//#define TURN_COLOR CRGB(255,255,51) 
//#define TURN_COLOR CRGB(255,100,0)
//#define TURN_COLOR CRGB(255,172,28) 
//#define TURN_COLOR CRGB(255,0,0) 
//#define TURN_COLOR CRGB::Yellow

//#define BRAKE_COLOR CRGB(255,0,0)


#define ALL CRGBW(255,255,255,255)
#define FORESTGREEN CRGBW(34,139,34,0)
#define PURPLE CRGBW(128,0,128,0)
#define RED CRGBW(255,0,0,0)
#define WHITE CRGBW(0,0,0,255)
#define YELLOW CRGBW(255,255,51,255)

#define TURN_COLOR YELLOW
#define BRAKE_COLOR RED


// TODO: Define multiple led strips
CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];

#define UPDATES_PER_SECOND 100

void setup() {
  Serial.begin(9600);
  Serial.println("Starting setup");

  FastLED.addLeds<LED_TYPE, OUT1_PIN, COLOR_ORDER>(ledsRGB, getRGBWsize(NUM_LEDS));
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  
  pinMode(BRAKE_PIN, INPUT);
  pinMode(LEFT_TURN_PIN, INPUT);
  pinMode(RIGHT_TURN_PIN, INPUT);
}

void set_color(CRGBW *leds, CRGBW color){
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = color;
  }
}

void loop(){  
  
  FastLED.clear();
  
  int left_turn_value = 0;
  left_turn_value = digitalRead(LEFT_TURN_PIN);
  
  int right_turn_value = 0;
  right_turn_value = digitalRead(RIGHT_TURN_PIN);
  
  int brake_value = 0;
  brake_value = digitalRead(BRAKE_PIN);
  
  if(left_turn_value == 1){
    Serial.println("left turn");
    set_color(leds, TURN_COLOR);
    
  }else if(right_turn_value == 1){
    Serial.println("right turn");
    set_color(leds, TURN_COLOR);
    
  }else if(brake_value == 1){
    Serial.println("brake");
    set_color(leds, BRAKE_COLOR);
  }
  
  FastLED.show();
  FastLED.delay(1000/UPDATES_PER_SECOND);
}

// END OF FILE
