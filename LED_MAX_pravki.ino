
#include "FastLED.h"          // библиотека для работы с лентой

#define LED_COUNT 407        // число светодиодов в кольце/ленте
#define LED_DT 9           // пин, куда подключен DIN ленты

int max_bright = 255;         // максимальная яркость (0 - 255)
unsigned long timing;

int BOTTOM_INDEX = 0;        // светодиод начала отсчёта
int TOP_INDEX = int(LED_COUNT / 2);
int EVENODD = LED_COUNT % 2;
struct CRGB leds[LED_COUNT];
int ledsX[LED_COUNT][3];     //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)
int time1 = 100;
int thissat = 255;           //-FX LOOPS DELAY VAR


void one_color_all(int cred, int cgrn, int cblu) {       //-SET ALL LEDS TO ONE COLOR
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i].setRGB( cred, cgrn, cblu);
  }
}

void one_color_allHSV(int ahue) {    //-SET ALL LEDS TO ONE COLOR (HSV)
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i] = CHSV(ahue, thissat, 255);
  }
}

void second_speed(int x, int x1) {

  int n = x - 80;

  for (n; n < (x1 + 80) ; n++ ) {
  //Serial.print(n);
    int light = 94;

    for (int k = n; k < (n + 80); k++) {

      light = light + 2;

      if (k > 0 && k < 407) {
        leds[k] = CHSV(0, thissat, light);
      }
    }
    if (n > -78 && n < 325) {
      leds[n + 79].setRGB(255, 255, 255);
      leds[n + 80].setRGB(200, 200, 200);
    }
    LEDS.show();


    if (n > -60 && n < 17) {
      if (n < (-60 + 5)) {
        time1 = time1 - 1;
      } else if (n > (17 - 5)) {
        time1 = time1 + 1;
      } else {
        time1 = 2;
      }
    } else if (n > 125 && n < 365) {
      if (n < (125 + 5)) {
        time1 = time1 - 1;
      } else if (n > (365 - 5)) {
        time1 = time1 + 1;
      } else {
        time1 = 2;
      }
    } else {
      time1 = 13;
    }

    //delay(time1);
    timing = millis();
    while (millis() - timing < time1) {
    }
  }
  int time1 = 17;
}


void setup()
{
  //Serial.begin(9600);
  LEDS.setBrightness(max_bright);  // ограничить максимальную яркость

  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  one_color_all(40, 0, 0);          // подсетка всех светодиодов
  LEDS.show();                     // отослать команду
}

void loop() {
  second_speed(0, 407);
  delay(1000);


}
