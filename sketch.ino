#include <Keypad.h>

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 5, 4, 3, 2 };
uint8_t rowPins[ROWS] = { 9, 8, 7, 6 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String correctPin = "1234";
String enteredPin = "";
volatile bool hasEntered = false;

String resetPasswordPattern = "*201*";
volatile bool isResetPasswordMode = false;
String inputPassword = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Dobrodošli u simulaciju sefa!");
}

void loop() {
    char key = keypad.getKey();
    if (key != NO_KEY && !hasEntered) {
      if (key == '#') {
        checkPin();
      } else if (key == 'C') {
        enteredPin = "";
      } else {
        enteredPin += key;
      }
    }
}

void checkPin() {
  if (enteredPin == correctPin) {
    Serial.println("Točan pin!");
    Serial.println("Sef otvoren!");
    hasEntered = true;
    delay(2000);
  } else if(enteredPin == resetPasswordPattern) {
    isResetPasswordMode = true;
    newPin();
  } else {
    Serial.println("Pogresan PIN!");
    Serial.println("Unesite PIN:");
    enteredPin = "";
  }
}

void newPin() {
  if (isResetPasswordMode) {
    inputPassword = "";
    while (isResetPasswordMode) {
      Serial.print("Novi pin - postavljanje: ");
      Serial.println(inputPassword);
      char key = keypad.getKey();
      if (key) {
        if (key == 'C') {
          inputPassword = "";
        } else if (key == '#') {
          if (inputPassword == resetPasswordPattern) {
            Serial.println("PIN se ne može postaviti, pokušajte sa drugim pinom!");
            inputPassword = "";
          } else {
            correctPin = inputPassword;
            enteredPin = "";
            isResetPasswordMode = false;
          }
        } else {
          inputPassword += key;
        }
      }
    }
  }
}
