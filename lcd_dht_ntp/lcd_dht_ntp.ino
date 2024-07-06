#include "LiquidCrystal_I2C.h" // LCD I2C konyvtar
#include "DHT11.h" // Homerseklet-szenzor konyvtar
#include <WiFi.h> // ESP/Arduino wifi konyvtara (Arduino-bol csak egyes darabok tamogatnak wifit, mint az MK1000)
#include "time.h" // Beepitett C/C++ konyvtar az ido feldolgozasara (Kb. minden nagyobb program tartalmazza ezt)
#define sensor_pin 32 // A DHT data pinje

int lcdColumns = 16; // LCD oszlopok szama
int lcdRows = 2; // LCD sorok szama

DHT11 dht11(sensor_pin); // Homerseklet Szenzor objektuma, ez fogja nekunk intezni a kommunikaciot

// Magyarra forditott hibakezelo a  DHT11 konyvtarhoz.
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

// TODO GMT Offset beallitasa !!!!!!!!!!!!!!

void connectToWifi(const char* ssid, const char* password) {
  /*Ez a fuggveny fogja biztositani a WIFI csatlakozast szamunkra.
    Itt tortenik az ntp szerverre kapcsolodas is, ahonnan lekerdezzuk az idot.
    Ennek eleg csak egyszer meghivodnia, onnantol folytonos kapcsolatot biztosit.
  */
  const char* ntpServer = "hu.pool.ntp.org"; // magyar szervert valasztjuk
  const long gmtOffset_sec = 0;

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  
  // Init and get the time
  configTime(0, 0, ntpServer);
}

// Megadjuk az LCD I2C cimet (ezt a gyarto adta meg), majd ezt koveti az oszlopok es sorok szama 
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup(){
  // Debugolashoz hasznalni fogjuk a Serial Monitort
  Serial.begin(9600);

  // Ez a parancs az LCD-t uzemkesz allapotba rakja 
  lcd.begin();
  // Ez a parancs pedig a hattervilagitast kapcsolja be a kijelzon                      
  lcd.backlight();

  // Ide kell beirnunk a wifi nevet, es kodjat.
  connectToWifi("LuteranWifi", "DonerKing1724");
}

void clearLine(int n) {
  // Nagyon primitiv sortorlo fuggveny, ezzel szebb eredmenyt erunk el, mintha az egesz kepernyot torolnenk.
  lcd.setCursor(0, n);
  lcd.print("                 "); // Lenyegeben ha kiirunk 16-nal tobb space-t, akkor toroljuk a sort :D
  return;
}

void loop(){
  struct tm timeinfo; // A tm egy olyan adatstruktura, ami tud tartalmazni minden idovel kapcsolatos adatot, mint az ora, ev vagy a het napjai
  
  if(!getLocalTime(&timeinfo)){ // Megprobaljuk lekerdezni az idot.
    Serial.println("Failed to obtain time"); // Log-olas
    return;
  }
   
  clearLine(0); // Letoroljuk a korabbi idot, es feltoltjuk a cellakat az uj adatokkal.

  lcd.setCursor(4, 0); // azert kezdjuk az 5. karaktertol, hogy kozepen legyen az ido nekunk

  lcd.print(&timeinfo, "%H:"); // ez az ora
  lcd.print(&timeinfo, "%M:"); // ez a perc 
  lcd.print(&timeinfo, "%S"); // ez a masodperc

  int homerseklet = 0; // ebben taroljuk majd a homersekletet
  int paratartalom = 0; // itt a paratartalom lesz tarolva

  // Megprobalunk olvasni a DHT11 szenzorbol (mindket parameter referencia)
  int eredmeny = dht11.readTemperatureHumidity(homerseklet, paratartalom);
  // Ha nem volt hiba, akkor 0-at kapunk eredmenykent

   /*
    Miert most toroljuk a masodik sort, ha ezt megtehettuk volna hamarabb is?

    Sajnos a kommunikacio a homerseklet-szenzor, es a mikrokontroller kozott picit lassu, megesik, hogy varnunk kell a valaszra,
    hiszen o nem kuld folyton ugy adatot. A DHT11-nek kell kuldenunk egy jelet, hogy adatot szeretnenk kerni es erre kapjuk valaszkent
    a homersekletet es a paratartalmat.

    Ezert szebb eredmenyt kapunk ha csak akkor torlunk amikor mar megerkezett az uj adat, addit mutatjuk a regit. 
   */
  clearLine(1);

  lcd.setCursor(1, 1); // Ezt is kozepre illesztjuk.

  if (eredmeny == 0) { // Ha kaptunk adatot
      lcd.print(homerseklet);
      lcd.print((char)0xDF); // Sajnos a fokot jelzo karaktert be kell utnunk, ez a 1101 1111 ha binarisan abrazoljuk.
      lcd.print("C "); 
      lcd.print("Para: ");
      lcd.print(paratartalom);
      lcd.println("%  ");
  } else {
      // Mas esetben megkaphatjuk eredmenykent, a hibat
      Serial.println(DHT11_hiba_kezelo(eredmeny));
  }

  // Ha sokszor frissitenenk a kepet, akkor halvany lenne a szoveg, nem lenne eleg ideje kirajzolni, a sor vegen levo karakterek mar nem is
  // latszodnanak ezert eleg ha 2 masodperc alatt 5x frissitunk

  delay(400);
}