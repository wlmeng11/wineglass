// wine glass smasher
#include <Adafruit_NeoPixel.h>

#define VOICE1  14 // pin A0, microphone 1
#define VOICE2  15 // pin A1, microphone 2
#define MOTOR1  9 // motor 1
#define MOTOR2  10 // motor 2
#define SW1     7 // limit switch 1
#define SW2     8 // limit switch 2

#define BAR1    0 // LED strip 1
#define BAR2    1 // LED strip 2
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(160, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bar1 = Adafruit_NeoPixel(30, BAR1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel bar2 = Adafruit_NeoPixel(30, BAR2, NEO_GRB + NEO_KHZ800);

#define DECAY 100
#define THRESHOLD 5000000

uint16_t voice1;
uint32_t sum1;
unsigned int sum2; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(VOICE1, INPUT);
  pinMode(VOICE2, INPUT);
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  bar1.begin(); bar2.begin();
  bar1.setBrightness(255); bar2.setBrightness(255);

  voice1 = 0;
  sum1 = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  voice1 = analogRead(VOICE1);
  Serial.print("voice1:\t"); Serial.print(voice1); Serial.print("\t\t");
  sum1 += voice1/4;
  if (sum1 > DECAY) {
	  sum1 -= DECAY;
	  //sum1 -= sum1 >> 12;
  }
  else {
	  sum1 = 0;
  }
  Serial.print("sum1:\t"); Serial.println(sum1);

  if (sum1 > THRESHOLD)
	  Serial.println("YOU WIN");

  delay(0.2);
}
