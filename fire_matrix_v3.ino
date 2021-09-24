#include <FastLED.h>

#define NUM_STRIPS 7
#define NUM_LEDS_PER_STRIP 105
#define funk 1
bool gReverseDirection = false;
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
const byte LED_PIN[NUM_STRIPS];
#define MAX_BRIGHTNESS 255     
#define MIN_BRIGHTNESS 10       
#define MAX_high 100     
#define MIN_high 10       
#define MAX_color 200     
#define MIN_color 40       
const int brightnessInPin = A0;  // The Analog input pin that the brightness control potentiometer is attached to.
const int highInPin = A1;       // Analog input pin that the speed control potentiometer is attached to.
const int colourInPin = A2;      // The Analog input pin that the colour control potentiometer is attached to.
CRGBPalette16 gPal;

void setup() {

    
FastLED.addLeds<NEOPIXEL, 3>(leds[0], NUM_LEDS_PER_STRIP);
FastLED.addLeds<NEOPIXEL, 4>(leds[1], NUM_LEDS_PER_STRIP);
FastLED.addLeds<NEOPIXEL, 5>(leds[2], NUM_LEDS_PER_STRIP);
FastLED.addLeds<NEOPIXEL, 6>(leds[3], NUM_LEDS_PER_STRIP);
FastLED.addLeds<NEOPIXEL, 7>(leds[4], NUM_LEDS_PER_STRIP);
FastLED.addLeds<NEOPIXEL, 8>(leds[5], NUM_LEDS_PER_STRIP);
FastLED.addLeds<NEOPIXEL, 9>(leds[6], NUM_LEDS_PER_STRIP);   
FastLED.setBrightness( MAX_BRIGHTNESS );

  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
 //gPal = HeatColors_p;
  
  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
     gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
  
  // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
  //   gPal = CRGBPalette16( CRGB::Blue, CRGB::Green, CRGB::Fuchsia,  CRGB::White);
  
  // Third, here's a simpler, three-step gradient, from black to red to white
   // gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);

}

void loop() {
    random16_add_entropy( random());
   int mappedValue0 = map(analogRead(brightnessInPin), 0, 1023, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
     FastLED.setBrightness(mappedValue0);
    int mappedValue1 = map(analogRead(highInPin), 0, 1023, MIN_high, MAX_high);
    int mappedValue2 = map(analogRead(colourInPin), 0, 1023, MIN_color, MAX_color); 
  switch (funk){
case 1:
  Fire(0,mappedValue2,mappedValue1); //stripe nr , cooling, sparking
  Fire(1,mappedValue2-10,mappedValue1+10);
  Fire(2,mappedValue2-20,mappedValue1+20);
  Fire(3,mappedValue2-30,mappedValue1+30); 
  Fire(4,mappedValue2-20,mappedValue1+20);
  Fire(5,mappedValue2-10,mappedValue1+10);
  Fire(6,mappedValue2,mappedValue1);
  FastLED.show();
break;
  case 2:
         for( int x = 0; x < NUM_STRIPS; x++) {
        fill_solid( leds[x], NUM_LEDS_PER_STRIP, CRGB(mappedValue1+155,mappedValue2+55,100));
        }
          FastLED.show();
break;
  case 3:
  for( int x = 0; x < NUM_STRIPS; x++) {
            pacifica_loop(x);
  }
    FastLED.show();
break;
  }
}




void Fire(int x,int COOLING,int SPARKING)
{
// Array of temperature readings at each simulation cell
 static byte heat[NUM_STRIPS][NUM_LEDS_PER_STRIP];


  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      heat[x][i] = qsub8( heat[x][i],  random8(0, ((COOLING * 10) / NUM_LEDS_PER_STRIP) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS_PER_STRIP - 1; k >= 2; k--) {
      heat[x][k] = (heat[x][k - 1] + heat[x][k - 2] + heat[x][k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < SPARKING ) {
      int y = random8(10); //originalwert 7 hier kann man den abstand der punkte und farben regeln
      heat[x][y] = qadd8( heat[x][y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
       byte colorindex = scale8( heat[x][j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
     // CRGB color = HeatColor( heat[x][j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS_PER_STRIP-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[x][pixelnumber] = color;
    }
}
// case 3
//-----------------------------------------------------------------------------------------------
CRGBPalette16 pacifica_palette_1 = 
    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50 };
CRGBPalette16 pacifica_palette_2 = 
    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F };
CRGBPalette16 pacifica_palette_3 = 
    { 0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33, 
      0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF };


void pacifica_loop(int x)
{
  // Increment the four "color index start" counters, one for each wave layer.
  // Each is incremented at a different speed, and the speeds vary over time.
  static uint16_t sCIStart1, sCIStart2, sCIStart3, sCIStart4;
  static uint32_t sLastms = 0;
  uint32_t ms = GET_MILLIS();
  uint32_t deltams = ms - sLastms;
  sLastms = ms;
  uint16_t speedfactor1 = beatsin16(3, 179, 269);
  uint16_t speedfactor2 = beatsin16(4, 179, 269);
  uint32_t deltams1 = (deltams * speedfactor1) / 256;
  uint32_t deltams2 = (deltams * speedfactor2) / 256;
  uint32_t deltams21 = (deltams1 + deltams2) / 2;
  sCIStart1 += (deltams1 * beatsin88(1011,10,13));
  sCIStart2 -= (deltams21 * beatsin88(777,8,11));
  sCIStart3 -= (deltams1 * beatsin88(501,5,7));
  sCIStart4 -= (deltams2 * beatsin88(257,4,6));

  // Clear out the LED array to a dim background blue-green
  fill_solid( leds[x], NUM_LEDS_PER_STRIP, CRGB( 2, 6, 10));

  // Render each of four layers, with different scales and speeds, that vary over time
  pacifica_one_layer(x, pacifica_palette_1, sCIStart1, beatsin16( 3, 11+x * 256, 14 * 256), beatsin8( 10, 70, 130), 0-beat16( 301) );
  pacifica_one_layer(x, pacifica_palette_2, sCIStart2, beatsin16( 4,  6+x * 256,  9 * 256), beatsin8( 17, 40,  80), beat16( 401) );
  pacifica_one_layer(x, pacifica_palette_3, sCIStart3, 6+x * 256, beatsin8( 9, 10,38), 0-beat16(503));
  pacifica_one_layer(x, pacifica_palette_3, sCIStart4, 5+x * 256, beatsin8( 8, 10,28), beat16(601));

  // Add brighter 'whitecaps' where the waves lines up more
  pacifica_add_whitecaps(x);

  // Deepen the blues and greens a bit
  pacifica_deepen_colors(x);
}

// Add one layer of waves into the led array
void pacifica_one_layer(int x, CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff)
{
  uint16_t ci = cistart;
  uint16_t waveangle = ioff;
  uint16_t wavescale_half = (wavescale / 2) + 20;
  for( uint16_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    waveangle += 250;
    uint16_t s16 = sin16( waveangle ) + 32768;
    uint16_t cs = scale16( s16 , wavescale_half ) + wavescale_half;
    ci += cs;
    uint16_t sindex16 = sin16( ci) + 32768;
    uint8_t sindex8 = scale16( sindex16, 240);
    CRGB c = ColorFromPalette( p, sindex8, bri, LINEARBLEND);
    leds[x][i] += c;
  }
}

// Add extra 'white' to areas where the four layers of light have lined up brightly
void pacifica_add_whitecaps(int x)
{
  uint8_t basethreshold = beatsin8( 9, 55, 65);
  uint8_t wave = beat8( 7 );
  
  for( uint16_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    uint8_t threshold = scale8( sin8( wave), 20) + basethreshold;
    wave += 7;
    uint8_t l = leds[x][i].getAverageLight();
    if( l > threshold) {
      uint8_t overage = l - threshold;
      uint8_t overage2 = qadd8( overage, overage);
      leds[x][i] += CRGB( overage, overage2, qadd8( overage2, overage2));
    }
  }
}

// Deepen the blues and greens
void pacifica_deepen_colors(int x)
{
  for( uint16_t i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    leds[x][i].blue = scale8( leds[x][i].blue,  145); 
    leds[x][i].green= scale8( leds[x][i].green, 200); 
    leds[x][i] |= CRGB( 2, 5, 7);
  }
}
