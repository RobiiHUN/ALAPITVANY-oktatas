// DHT11-M0 teszteles ESP32-vel

/*
    !!FONTOS!!

    A DHT11-M0 adatlapjaban 3.5-5VDC szerepel viszont ebben az uzemmodban nem
    mukodik megfeleloen (az ESP32 flashelese hibat dob), viszont ha tapnak 3.3VDC-t
    adunk, akkor tokeletesen mukodik.
*/


// Ez a konyvtar mukodik az M0-as verzioval is hibatlanul.
#include <DHT11.h>

#define sensor_pin 2 // A DHT data pinje

DHT11 dht11(sensor_pin);

// Magyarra forditott hibakezelo a konyvtarhoz

String DHT11_hiba_kezelo(int error) {
  switch (error)
  {
  case DHT11::ERROR_TIMEOUT:
    return "Nem sikerult idoben valaszt kapni a homerseklet-szenzortol.";
  case DHT11::ERROR_CHECKSUM:
    return "A homerseklet-szenzor adata hibas.";
  default:
    return "Ismeretlen hiba a homerseklet-szenzorral.";
  }
}


void setup() {
    Serial.begin(9600);
    // Az alabbi kommentezett koddal lehet a meresek kozotti idotartamot allitani
    // Ha nem allitjuk be, akkor 500ms lesz alapertelmezetten.
    // dht11.setDelay(500);
}

void loop() {
    int homerseklet = 0;
    int paratartalom = 0;

    // Megprobalunk olvasni a DHT11 szenzorbol (mindket parameter referencia)
    int eredmeny = dht11.readTemperatureHumidity(homerseklet, paratartalom);

    // Ha nem volt hiba, akkor 0-at kapunk eredmenykent

    if (eredmeny == 0) {
        Serial.print("Temperature: ");
        Serial.print(homerseklet);
        Serial.print(" °C\t"); // \t a tabulatort jelzi
        Serial.print("Paratartalom: ");
        Serial.print(paratartalom);
        Serial.println(" %");
    } else {
        // Mas esetben megkaphatjuk eredmenykent, a hibat
        Serial.println(DHT11_hiba_kezelo(eredmeny));
    }
}