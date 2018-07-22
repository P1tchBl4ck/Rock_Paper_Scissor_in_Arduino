#include <LiquidCrystal.h>
/**
 * Created by Alberto De Angelis for the
 * exhibition "Robot al mercato", which took place
 * in Cuneo in 2016, where our school partecipated
 * bringing some robots programmed by us.
 * This snippet contains a code to control an Arduino
 * with three buttons and a LiquidCrystal display
 * to play Rock, paper, scissor with an AI.
 */

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int button1=7;
const int button2=8;
const int button3=9;
int matches;
int matches_won;
int matches_lost;
int move;
int random_number;
void setup() {
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);
  matches = 0;
  matches_won = 0;
  matches_lost = 0;
  randomSeed(analogRead(0));
}
void loop() {
     if(digitalRead(button2) == HIGH){
       Serial.println("1");
     }else{
       Serial.println("0");
     }
     lcd.setCursor(0,0);
     delay (500);
     if(digitalRead(button1)== HIGH ||
      digitalRead(button2)==HIGH ||
      digitalRead(button3)==HIGH && matches!=0){
        matches=1;
     }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Premi SaSso");
        lcd.setCursor(0,1);
        lcd.print("per iniziare..."); 
     }
     if(matches){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Scegli la move");
        delay(500);
        if(digitalRead(button1)== HIGH || digitalRead(button2)==HIGH || digitalRead(button3)==HIGH){
            boolean b1=digitalRead(button1);
            boolean b2=digitalRead(button2);
            boolean b3=digitalRead(button3);
            if(b1){
              move=0;
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Tu: SaSso");
            }else{
              if(b2){
                move=1;
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Tu: carta");
              }else{
                if(b3){
                  move=2;
                  lcd.clear();
                  lcd.setCursor(0,0);
                  lcd.print("Tu: forbici");
                }
              }
            }
            randomSeed(analogRead(0));
            random_number = random(3);
            if(random_number == 0){
              lcd.setCursor(0,1);
              lcd.print("PC: SaSso");
              delay(1000);
            }
            if(random_number == 1){
              lcd.setCursor(0,1);
              lcd.print("PC: carta");
              delay(1000);
            }
            if(random_number == 2){
              lcd.setCursor(0,1);
              lcd.print("PC: SaSso");
              delay(1000);
            }
            if(move == random_number){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Pareggio.");
              delay(500);
            }else{
              if(move == 0 && random_number == 2 ||
                 move == 1 && random_number == 0 ||
                 move == 2 && random_number == 1)  {
              //Vince il giocatore
                matches_won++;
                matches++;
              }else{
                matches_lost++;
                matches++;
              }
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Tu: ");
              lcd.print(matches_won);
              lcd.setCursor(0,1);
              lcd.print("PC: ");
              lcd.print(matches_lost);
              delay(500);
              if(matches_won == 3){
                lcd.clear();
                lcd.setCursor(0,1);
                lcd.print("Hai vinto!");
                delay(500);
                matches = 0;
                matches_won = 0;
                matches_lost = 0;
              }
              if(matches_lost == 3){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Hai perso...");
                delay(500);
                matches = 0;
                matches_won = 0;
                matches_lost = 0;
              }
            }
        }else{
          delay(30);
        }
    }
}