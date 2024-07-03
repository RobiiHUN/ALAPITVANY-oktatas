/*
  Ebben a file-ban egy rovid peldan keresztul megmutatjuk a taborban
  hasznalt LCD (16x2 meretu, I2C protokol szerint) hasznalatat.

  Itt az ESP32 Szinkron (vagyis orajelre torteno) Soros (egy adatvezeteken kuldjuk az adatokat, sorban)
  kommunikaciot folytat. Ennek egy tipusa az I2C protokol, amivel mukodik a kijelzonk. Ez szamunkra nem lesz
  fontos, hiszen a konzvtar elvegzi ezt nekunk.

  !!!FONTOS

  Az LCD kijelzon lathato 4 lab, rendre a GND (Fold), VCC (tap, nekunk ez 5V), SDA (adatkabel) es SCL (Orajel)
  Az ESP32-n nekunk az SDA labat a P21 labra, az SCL-t a P22 labra kell kotnunk, ezek az alapertelmezett I2C labak.
*/

// Ha hagyomanyos LCD kijelzovel van dolgunk akkor a LiquidCrystal.h-t szoktuk hasznalni, lenyegeben
// ennek egy I2C kommunikaciora modositott valtozata kell most nekunk

#include "LiquidCrystal_I2C.h"

int lcdColumns = 16; //  Megadjuk az oszlopok szamat
int lcdRows = 2; // Megadjuk a sorok szamat

// Alapvetoen ez a ket adat az LCD kijelzon meghataroz egy darab "cellat", amit mi kitoltunk egy
// altalunk valasztott karakterrel. (Ha egy karaktert keresunk akkor erre az LCD character table alkalmas)
// A megadott karaktert (ami 1 byte -> 8 bit) az ESP elkuldi az LCD-nek a cella adataival, o pedig ezt megjeleniti.


// Megadjuk az LCD I2C cimet (ezt a gyarto adta meg), majd ezt koveti az oszlopok es sorok szama 
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup(){
  // Ez a parancs az LCD-t uzemkesz allapotba rakja 
  lcd.begin();
  // Ez a parancs pedig a hattervilagitast kapcsolja be a kijelzon                      
  lcd.backlight();
}

void loop(){
  // Megadjuk az oszlop es sorszamot, ahonnan kezdve szeretnenk irni most (mindketto 0-tol van szamozva!) 
  lcd.setCursor(0, 0);
  // Es egy szoveget elkuldunk a kijelzonek (Ha ez nagyobb mint 16 karakter akkor lecsuszik!)
  lcd.print("Hello, World!");

  lcd.setCursor(4, 1); // Itt a masodik sorba es az otodik oszlopba lepunk

  lcd.print((char)0xF7); // Itt megadunk egy karakterkodot, ami kilesve a karaktertablabol a pi jele (ez binarisan = 1111 0111)
  
  lcd.setCursor(5, 1); // tovabblepunk egy karaktert

  lcd.print(" = 3.14");

  delay(2000); // Ez a parancs jelez az ESP32-nek hogy pihenjen 2000ms-ig (ami 2 masodperc)
  lcd.clear(); //  Ez a parancs letorol minden eddig megjelenitett karaktert

  // Es itt kiirunk egy ujabb szoveget, mar a tiszta kepernyore

  lcd.setCursor(0, 0);

  // Es egy szoveget elkuldunk a kijelzonek (Ha ez nagyobb mint 16 karakter akkor lecsuszik!)
  lcd.print("Eleqtroom tabor 2024!"); // Ez direkt egy olyan pelda, ami nagyobb mint 16 karakter
  // es lathatjuk, hogy lecsusznak a karakterek. 

  delay(2000); // Ez a parancs jelez az ESP32-nek hogy pihenjen 2000ms-ig (ami 2 masodperc)
  lcd.clear(); //  Ez a parancs letorol minden eddig megjelenitett karaktert

}