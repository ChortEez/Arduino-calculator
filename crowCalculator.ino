#include <LiquidCrystal.h>
#include <Keypad.h>
#include <string.h>

const byte ROWS = 4;  //4 Rows
const byte COLS = 4;  // 4 Colums


char keys[COLS][ROWS] = {  // keymap
  { '+', '-', '*', '/' },
  { '7', '8', '9', 'B' },
  { '4', '5', '6', 'C' },
  { '1', '2', '3', '=' }
};
// char keys [COLS][ROWS] = { // second keymap
//   {'+','-','*','/'},
//   {'7','8','9','B'},
//   {'e','Y','o','u'},
//   {'I','l','o','v'}
//   };
byte colPins[COLS] = { A1, 10, 11, 12 };
byte rowPins[ROWS] = { A2, A3, A4, A5 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(3, 5, 6, 7, 8, 9);
int lcdCursorPosition = 1;
int lcdLinePosition = 0;
String number;
long num;
long num2;
char symbol;

void debug(String num, int pos, char key, int line, String numLength, long iNum) {
  Serial.print("POS:");
  Serial.println(pos);

  Serial.print("NUM:");
  Serial.println(num);

  Serial.print("KEY:");
  Serial.println(key);

  Serial.print("LINE:");
  Serial.println(line);

  Serial.print("LENGTH:");
  Serial.println(numLength.length());

  Serial.print("SAVED NUM");
  Serial.println(iNum);

  Serial.println(' ');
}
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);  // lcd initialization
  lcd.clear();       // lcd clear
  lcd.cursor();
}
void loop() {
  char key = keypad.getKey();  // getting a pressed key
  if (key) {
    Serial.println(F("test"));
    switch (key) {
      case 'C':
        lcd.clear();
        lcdCursorPosition = 1;
        lcdLinePosition = 0;
        number = ' ';
        debug(number, lcdCursorPosition, key, lcdLinePosition, number, num);
        break;

      case 'B':
        if (lcdCursorPosition > number.length()) {  //number and position sync check
          lcdCursorPosition--;
          lcd.setCursor(lcdCursorPosition - 1, lcdLinePosition);
          number.trim();
          debug(number, lcdCursorPosition, key, lcdLinePosition,number,num);
        } else if (lcdCursorPosition == number.length()) {  //erase
          lcd.write(' ');
          lcdCursorPosition--;
          lcd.setCursor(lcdCursorPosition - 1, lcdLinePosition = 0);
          number.remove(lcdCursorPosition, 1);  // delete last number, dont displayed, just for logic.
          debug(number, lcdCursorPosition, key, lcdLinePosition,number,num);
        }
        break;

        case '+': 
        case '-':
        case '*':
        case '/':
          lcdCursorPosition = 1;
          num = number.toInt();
          number = ' ';
          lcd.clear();
          lcd.write(key);
          delay(1000);
          if(key){
            lcd.clear();
          }
          symbol = key;
          debug(number, lcdCursorPosition, key, lcdLinePosition, number, num);
          break;
        case '=':
          num2 = number.toInt();
          number = ' ';
          lcd.clear();
          Serial.println(key);
          switch(symbol){
            case '+': lcd.println(num+num2); break;
            case '-': lcd.println(num-num2); break;
            case '*': lcd.println(num*num2); break;
            case '/': lcd.println(num/num2); break;
          }
          break;
          

      default:
        if (lcdCursorPosition > 0 && lcdCursorPosition < 17) {
          lcd.write(key);  // writing key
          lcdCursorPosition++;
          number += key;
          number.trim();
          debug(number, lcdCursorPosition, key, lcdLinePosition, number, num);
        }
        break;
    }
    if (lcdCursorPosition <= 0) {  // check if cursor position smaller than 0
      lcd.setCursor(0, 0);
      lcdCursorPosition = 1;
      Serial.println("achtung");
    }
  }
}
