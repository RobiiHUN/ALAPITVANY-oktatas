// ez lesz nekunk a bekotott led-ek szama
#define ledNum 8 
// ez pedig a hangerzekelo labanak a sorszama (P15)
#define sound_sensor 15 

// Tombok (listak)
// az elso tomb fog nekunk a labak tarolasara szolgalni
// a masodik tomb egy igaz/hamis (bool) erteket tarol, ami azt mondja meg nekunk, hogy az adott led be van e kapcsolva

const int ledarray[] = { 2, 0, 4, 16, 17, 5, 18, 19 }; // ezek a labak amikre a ledeket kotottuk (Mindenkepp tegyetek ele ellenallast, 100 Ohm eleg 3.3V-on) 
bool led_states[] = { false }; // Itt azt taroljuk, hogy a LED be van-e kapcsolva

void initLed() {
  // Ez a fuggveny inicializalja a LED-eket (elokesziti)
  for (int i = 0; i < ledNum; ++i) { // egy ciklusban vegigszaladunk a listankban levo ledeken
    pinMode(ledarray[i], OUTPUT); // Egyesevel kimenetre allitjuk oket
  }

  // az alabbi kodreszlet arra szolgal hogy adjunk valami visszajelzest arrol, hogy sikerult elokesziteni a ledeket, nem tortent hiba.
  
  turnOnAll(); // felkapcsoljuk mindegyiket
  delay(1000); // varunk egy masodpercet
  turnOffAll(); // lekapcsoljuk az osszeset
}

void ledON(int n) {
  // ezzel egy kivalasztott sorszamu LED-et tudunk felkapcsolni
  led_states[n - 1] = true; // elmentjuk azt, hogy felkapcsoltuk
  digitalWrite(ledarray[n - 1], HIGH); // es utana fel is kapcsoljuk
}

void ledOFF(int n) {
  // ez a fuggveny egy adott sorszamu LED-et lekapcsol szamunkra
  led_states[n - 1] = false; // ugyanugy elmentjuk, hogy lekapcsoltuk
  digitalWrite(ledarray[n - 1], LOW); // es le is kapcsoljuk utana
}

void turnOnAll() {
  // Ez a fuggveny az osszes ledet felkapcsolja nekunk
  for (int i = 0; i < ledNum; ++i) {  // egy ciklusban vegigszalad az osszes LED-en
    ledON(i + 1); // majd minden sorszamra (0-7) bekapcsolja a LED-et.
  }
}

void turnOffAll() {
  // ez a fuggveny lekapcsolja az osszes LED-et
  for (int i = 0; i < ledNum; ++i) { // itt is egy cikluson keresztul vegigszaladunk a LED-eken
    ledOFF(i + 1); // es a sorszamuk alapjan felkapcsoljuk egyesevel
  }
}

// Setup kodreszlet, ez fut le majd a loop elott, itt modnjuk meg az ESP-nek, hogy
// miket kell a programhoz elore megcsinalni, csak ugy mint egy receptben az elokeszuletek resz :D

void setup() {
  initLed(); // LED-ek elokeszitese
  pinMode(sound_sensor, INPUT); // beallitjuk, hogy bemenet legyen a hangerzekelo

  // Itt kotjuk hozza az interrupt fuggvenyunket, a P15-os labhoz. A CHANGE kulcsszo lenyegeben azt jelenti, hogy minden valtozasra
  // inditsa el nekunk a P15_ISR nevezetu kodreszletet (fuggvenyt). Ezt kesobb egyetemen ISR-nek fogjatok hivni ami Interrupt Sub Routine-t jelent
  // Ezek a fajta fuggvenyek nagyon hasznosak, es a jovoben ha a villamosmernoki palyan gondolkodtok, akkor talalkozni is fogtok vele, Digitalis Elektronikai kurzusokon.

  //Na de miert bonyolitjuk megjobban ezzel?
  // Lenyegeben ha mindig csak tesztelgetnenk if elagazassal, akkor az egesz loop ebbol allna, es a mikrokontrollerunk nem tudna addig mast csinalni.
  // hiaba nem jott meg jel nekunk. Ehelyett hagyjuk, hogy csinalja a dolgat es csak a kulso hatas (P15-os lab magas feszultsege) eseten szolunk neki. 
  
  attachInterrupt(digitalPinToInterrupt(sound_sensor), P15_ISR, CHANGE); //
}

int futo = 1; // egy valtozo ami a jelenlegi LED sorszamat tartalmazza
bool elert = false; // elertuk-e mar az utolso ledet, vagy meg valahol mashol vagyunk-e
volatile bool clapped = false; // tapsoltak-e mar


// Ez az a fuggveny amit meghiv nekunk a P15-os lab megvaltozasa

void P15_ISR() {
  if (digitalRead(sound_sensor) == HIGH) { // megnezzuk, hogy biztosan magas-e, nem csak valami zaj jatszott kozbe
    turnOffAll(); // kikapcsoljuk a LED-eket
    clapped = !clapped; // megforditjuk a tapsolas eddigi erteket
  }
}


void loop() {
  if (clapped) { // ennek az if-nek a hasaba akkor kerulunk, ha mar tudjuk, hogy tapsolt korabban az illeto
    ledON(futo); // a futo LED-et lekapcsoljuk
    delay(200); // varunk 0.2 masodpercet
    ledOFF(futo); // felkapcsoljuk a futo LED-et
    delay(200); // varunk ujra 0.2 mp-t

    if (futo == 8) { // ha a futo 8, akkor elertunk a LED sor vegere, innentol visszafele kell menni
      elert = true;
    }

    if (elert && futo == 1) { // ha elertuk mar korabban a veget, es a futonk is visszajutott az elejere akkor kezdjuk elorol az egeszet
      elert = false; // ilyenkor csak annyit kell tennunk, hogy szolunk a gepnek, hogy meg nem erte el a veget
    }

    if (elert) { // ha elertuk mar a veget akkor visszafele megyunk az elso led fele
      futo--;
    } else { // ha meg nem ertuk el, akkor megyunk elore, ilyenkor noveljuk a futo erteket
      futo++;
    }
  }
  else{ // ez akkor fut le, ha nem tapsolt meg az illetto, ekkor villogtatjuk az osszes LED-et egyszerre
    turnOnAll(); 
    delay(500);
    turnOffAll();
    delay(500);
  }
}
