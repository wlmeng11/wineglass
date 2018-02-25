// wine glass smasher
#include <Adafruit_NeoPixel.h>

#define VOICE  14 // pin A0, microphone 1
#define MOTOR  9 // motor 1
#define SW     7 // limit switch 1

#define LEDBAR    0 // LED strip 1
#define NUMLED 	16
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(160, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ledbar = Adafruit_NeoPixel(NUMLED, LEDBAR, NEO_GRB + NEO_KHZ800);

#define DECAY 100
#define THRESHOLD 1000000

int16_t voice1;
int32_t sum1;
int32_t s;
uint8_t i;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(VOICE, INPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(SW, INPUT_PULLUP);
  ledbar.begin();
  ledbar.setBrightness(255); ledbar.show();
  delay(0.2);
  //ledbar.setBrightness(0); ledbar.show();

  voice1 = 0;
  sum1 = 0;
  digitalWrite(MOTOR, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  voice1 = analogRead(VOICE);
  Serial.print("voice1:\t"); Serial.print(voice1); Serial.print("\t\t");
  sum1 += voice1/4;
  if (sum1 > DECAY) {
	  sum1 -= DECAY;
  }
  else {
	  sum1 = 0;
  }
  Serial.print("sum1:\t"); Serial.println(sum1);

  /*
  s = sum1;
  //ledbar.setBrightness(0); // start with all pixels off
  for(i = 0; i < NUMLED; i++) { // turn on pixels 1 by 1
	  if (s >= THRESHOLD/NUMLED) {
		  //ledbar.setPixelColor(i, ledbar.Color(255,255,255));
		  Serial.println("led ON");
	  }
	  s -= THRESHOLD/NUMLED;
  }
  ledbar.show();
  */

  if (sum1 > THRESHOLD) {
	  Serial.println("YOU WIN");
	  digitalWrite(MOTOR, HIGH);
	  delay(1);
	  digitalWrite(MOTOR, LOW);
  }

  delay(0.2);
}
