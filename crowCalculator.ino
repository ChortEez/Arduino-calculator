#include <LiquidCrystal.h>
#include <Keypad.h>
#include <string.h>

const byte ROWS = 4; //4 rows
const byte COLS = 4; // 4 colums

char keys [COLS][ROWS] = { // keymap
  {'+','-','*','/'},
  {'7','8','9','B'},
  {'4','5','6','C'},
  {'1','2','3','.'}
  };
// char keys [COLS][ROWS] = { // second keymap
//   {'+','-','*','/'},
//   {'7','8','9','B'},
//   {'e','Y','o','u'},
//   {'I','l','o','v'}
//   };
byte colPins[COLS] = {A1,10,11,12};
byte rowPins[ROWS] = {A2,A3,A4,A5};
Keypad keypad = Keypad(makeKeymap(keys), rowPins,colPins, ROWS, COLS);

LiquidCrystal lcd(3, 5, 6,7,8,9);
int lcdCursorPosition = 1;
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
      lcdCursorPosition++;
      
      Serial.println("Cursor position");
      Serial.println(lcdCursorPosition);//debug
      number += key; 
      number.trim();
      Serial.println("Number:");
      Serial.println(number);

    } else if (key = 'C' && key !='B'){ // presed key = C
      lcd.clear();
      lcdCursorPosition = 1;
      number = ' ';

      Serial.println("Cursor position");
      Serial.println(lcdCursorPosition); // debug

    } else if (key ='B' && key != 'C' ){ // pressed key = B
      if (lcdCursorPosition > number.length()){
        // lcd.write(' '); // cursor position +1;
        lcdCursorPosition --;
        // lcdCursorPosition --;
        // lcdCursorPosition -= 2;
        lcd.setCursor(lcdCursorPosition, 0);
        // lcd.setCursor(lcdCursorPosition, 0);
        
        number.trim();

        Serial.println("Cursor position");
        Serial.println(lcdCursorPosition + 1);
        Serial.println("Number:");
        Serial.println(number);
      } else if (lcdCursorPosition == number.length()){
        Serial.println("перехід в блок 2");
        lcdCursorPosition = 1900;
        lcd.write(' ');
        lcd.setCursor(lcdCursorPosition, 0);
        lcd.write(' ');
        number.remove(lcdCursorPosition, 1); // delete last number, dont display, just for logic.

        Serial.println("Cursor position");
        Serial.println(lcdCursorPosition + 1);
        Serial.println("Number:");
        Serial.println(number);
      }
      
      
      
      
       
      
      Serial.println("Cursor position");
      Serial.println(lcdCursorPosition);
      Serial.println("Number:");
      Serial.println(number);

      
    }
    
  }
}
