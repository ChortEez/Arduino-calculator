#include <LiquidCrystal.h>
#include <Keypad.h>
#include <string.h>

const byte ROWS = 4; //4 Rows
const byte COLS = 4; // 4 Colums

char keys [COLS][ROWS] = { // keymap
  {'+','-','*','/'},
  {'7','8','9','B'},
  {'4','5','6','C'},
  {'1','2','3','.'}
  };
// char keys [COLS][ROWS] = { // keymap
//   {'+','-','*','/'},
//   {'7','8','9','B'},
//   {'e','Y','o','u'},
//   {'I','l','o','v'}
//   };
byte colPins[COLS] = {A1,10,11,12};
byte rowPins[ROWS] = {A2,A3,A4,A5};
Keypad keypad = Keypad(makeKeymap(keys), rowPins,colPins, ROWS, COLS);

LiquidCrystal lcd(3, 5, 6,7,8,9);
int lcdCursorPosition = 0;
String number;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // lcd initialization
  lcd.clear(); // lcd clear
  lcd.cursor();
}
void loop() {
  char key = keypad.getKey(); // getting a pressed key
  if (key) { // if key pressed print Serial
    Serial.println("Key pressed:");
    Serial.println(key);

    if (key != 'B' && key !='C'){ // checking the key
      lcd.write(key); // writing key
      lcdCursorPosition ++; 
      Serial.println(lcdCursorPosition);//debug
      number += key; 
      Serial.println(number);

    } else if (key = 'C' && key !='B'){ // presed key = C
      lcd.clear();
      lcdCursorPosition = 0;
      number = ' ';
      Serial.println(lcdCursorPosition); // debug

    } else if (key ='B' && key != 'C' ){ // pressed key = B
      lcdCursorPosition --;
      lcd.write(' ');
      lcd.setCursor(lcdCursorPosition, 0);
      number.remove(lcdCursorPosition, 1);
      Serial.println(lcdCursorPosition);
      Serial.println(number);

      
    }
    
  }
}
