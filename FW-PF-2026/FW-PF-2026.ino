#include <Adafruit_NeoPixel.h>

#define LED_PIN    3 
#define LED_COUNT 39 

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// --- NASTAVENÍ JASU A BAREV ---
// Pozadí: velmi tlumená žlutá (působí spíše jako teplý svit)
uint32_t barvaPozadi = strip.Color(6, 3, 0); 
// Jiskra: snížený jas (původně byl 80, teď zkusíme 30–40)
uint32_t barvaJiskry = strip.Color(20, 15, 5); 

void setup() {
  strip.begin();
  probarviPozadi();
  strip.show();
  randomSeed(analogRead(0));
}

void loop() {
  // 1. Určíme náhodný počet jisker, které se v tomto kroku objeví (1 až 3)
  int pocetJisker = random(1, 4); // random(min, max) -> max je exkluzivní, takže 1, 2 nebo 3
  
  // Pole pro uložení pozic, abychom je pak mohli snadno zhasnout
  int pozice[3];

  // 2. Vybereme náhodné pozice a rozsvítíme je
  for (int i = 0; i < pocetJisker; i++) {
    pozice[i] = random(0, LED_COUNT);
    strip.setPixelColor(pozice[i], barvaJiskry);
  }
  strip.show();
  
  // 3. Jiskry necháme svítit jen krátce
  delay(random(30, 70)); 

  // 4. Vrátíme vybrané LED zpět do barvy pozadí
  for (int i = 0; i < pocetJisker; i++) {
    strip.setPixelColor(pozice[i], barvaPozadi);
  }
  strip.show();

  // 5. Náhodná pauza do dalšího "výbuchu"
  delay(random(50, 200));
}

void probarviPozadi() {
  for(int n = 0; n < LED_COUNT; n++) {
    strip.setPixelColor(n, barvaPozadi);
  }
}