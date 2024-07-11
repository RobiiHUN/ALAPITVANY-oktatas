#define led1 2 // piros
#define led2 3 // sarga 
#define led3 4 // zold
#define szenzor 32 // hangszenzor

void setup() {
  // ledek inicializalasa
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(szenzor, INPUT);
}

void loop() {

  if (digitalRead(szenzor) == HIGH) { // ha tapsoltak

  digitalWrite(led1, HIGH); // piros van
  delay(500);
  
  digitalWrite(led2, HIGH); // piros es sarga van
  delay(500);
  
  digitalWrite(led1, LOW); // zold van
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);

  delay(500); 

  digitalWrite(led3, LOW);  // ujra sarga van
  digitalWrite(led2, HIGH);
  
  delay(500);

  digitalWrite(led2, LOW); // vege, lekapcsoljuk a sargat, es pirosra valtunk
  
  delay(500);
  
  digitalWrite(led1, HIGH); // visszamegy pirosba 
  delay(500);
  
  digitalWrite(led1, LOW); // majd lekapcsoljuk ezt is
  }



}