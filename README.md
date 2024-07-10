# EleQtRooM Tábor 2024

Az itt található Github Repository-ban találhatjátok meg a forráskódokat a projektekhez. Minden amit megcsináltunk keddes és szerdán
azokat, kommentezve megtalálhatjátok itt. Egy-két helyen részletesebben leírjuk a használt függvényeket, methódusokat, ha a jövőben szeretnétek
mélyebb ismeretet szerezni a témában.

## Első nap

Az első napi nagyprojekt egy bővebb verzióját fogjátok megtalálni [itt](ledfuzer), ezt nem tudtuk befejezni, de kipróbáltuk a digitális hang-érzékelőt
a közlekedési lámpánál, de ennek az alkalmazása nem különbözik itt.

> [!IMPORTANT]
> Sajnos a közlekedési lámpa kódját újra kell írnunk, valószínüleg nem mentettük le, ezért ezt még a héten újraírjuk, de ha ez nemm történne meg jelezzetek mindenképpen!

### Interrupt függvény a hangérzékelő jelzéséhez

Ez tartalmaz egy olyan különleges függvényt amit nem részleteztünk a tábor során, ez pedig az interrupt függvény. Ez egy olyan kódrészlet, ami
valamilyen külső/belső megváltozásra meghívódik. Mi itt az egyik lábhoz írtuk, méghozzá a hangérzékelő lábához. Ha jött nekünk jelzés, hogy érzékelt a szenzor, akkor meghívódik
ez a függvény, ezzel elérve hogy csak a tapsra tudjon ki/be kapcsolni. Ezt a táborban egy egyszerű feltételes elágazással oldottuk meg, de ez egy biztosabb működéssel biró megoldás.

A közlekedési lámpát tartalmazo .ino-t még keressük azt hamarosan feltöltjük ide, egy kozlekedesi_lampa nevű mappába.

## Második nap

A második napon elkészített projekt egy picit nagyobb témakört fed le ezért több szegmensre bontottuk, hogy egyesével is ki tudjátok próbálni.

Ha a második nap teljes projektjét szeretnétek felhasználni, akkor [itt](lcd_dht_ntp) keressétek.

## Összefoglalás

Ha a jövőben is szeretnétek ESP32/Arduino-val foglalkozni, akkor ezeket a projekteket használjátok fel bátran, direkt úgy állítottuk össze, hogy ezekkel lefedjük a legfontosabb témaköröket,
amikre a jövőben saját projektjeitekben szükségetek lesz.  

> [!NOTE]
> Ha bármilyen elektronikai/informatikai témával kapcsolatban kérdésetek lenne, keressetek meg minket nyugodtan, szívesen segítünk nektek. Sok sikert a továbbiakban! :)

