#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 10, A5, A4, A3);

// Keypad konfiguracija
const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

uint8_t colPins[COLS] = {5, 4, 3, 2};
uint8_t rowPins[ROWS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
Servo servo;

String correctPin = "1234";
String enteredPin = "";
volatile bool hasEntered = false;

String resetPasswordPattern = "*201*";
volatile bool isResetPasswordMode = false;
String inputPassword = "";

const int ntcPin = A0;
const int servoPin = 13;

void setup()
{
  servo.attach(servoPin);
  servo.write(-90);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("Dobrodosli!");
  lcd.setCursor(0, 1);
  lcd.print("Unesite PIN:");
}

void loop()
{
  char key = keypad.getKey();

  if (key != NO_KEY && !hasEntered)
  {
    if (key == '#')
    {
      checkPin();
    }
    else if (key == 'C')
    {
      enteredPin = "";
      lcd.setCursor(0, 2);
      lcd.print("                ");
    }
    else
    {
      enteredPin += key;
    }

    // Prikaz maskiranog unosa (zadnja znamenka ostaje vidljiva)
    lcd.setCursor(0, 2);
    lcd.print("Unos: ");
    for (int i = 0; i < enteredPin.length(); i++)
    {
      if (i == enteredPin.length() - 1)
      {
        lcd.print(enteredPin[i]);
      }
      else
      {
        lcd.print("*");
      }
    }
    lcd.print("        ");
  }
}

void checkPin()
{
  lcd.clear();

  if (enteredPin == correctPin)
  {
  float temp = readTemperature();
  Serial.println(temp);
  if (temp > 38.0 || temp < 0.0)
  {
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temp, 1);
    lcd.setCursor(0, 1);
    lcd.print("Ne moze se otvoriti");
    lcd.setCursor(0, 2);
    lcd.print("Temp izvan granica");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unesite PIN:");
    enteredPin = "";
    return;
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Tocan PIN!");
    lcd.setCursor(0, 1);
    lcd.print("Sef otvoren!");
    hasEntered = true;
    unlock();
    delay(5000); // sef ostaje otvoren 5 sekundi

    // Zakljucavanje
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sef zakljucan.");
    lock();
    delay(2000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unesite PIN:");
    hasEntered = false;
    enteredPin = "";
  }
  }
  else if (enteredPin == resetPasswordPattern)
  {
    isResetPasswordMode = true;
    newPin();
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Pogresan PIN!");
    lcd.setCursor(0, 1);
    lcd.print("Pokusajte opet");
    enteredPin = "";
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Unesite PIN:");
  }
}

void newPin()
{
  inputPassword = "";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Postavi novi PIN");

  while (isResetPasswordMode)
  {
    char key = keypad.getKey();

    if (key)
    {
      if (key == 'C')
      {
        inputPassword = "";
        lcd.setCursor(0, 2);
        lcd.print("                ");
      }
      else if (key == '#')
      {
        if (inputPassword == resetPasswordPattern)
        {
          lcd.setCursor(0, 3);
          lcd.print("Neispravan PIN!");
          inputPassword = "";
          delay(2000);
          lcd.setCursor(0, 3);
          lcd.print("                ");
        }
        else
        {
          correctPin = inputPassword;
          enteredPin = "";
          isResetPasswordMode = false;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("PIN postavljen!");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Unesite PIN:");
        }
      }
      else
      {
        inputPassword += key;
      }

      // Prikaz maskiranog unosa novog PIN-a (zadnja znamenka vidljiva)
      lcd.setCursor(0, 2);
      lcd.print("Unos: ");
      for (int i = 0; i < inputPassword.length(); i++)
      {
        if (i == inputPassword.length() - 1)
        {
          lcd.print(inputPassword[i]);
        }
        else
        {
          lcd.print("*");
        }
      }
      lcd.print("        ");
    }
  }
}

float readTemperature()
{
  const float BETA = 3950;
  int analogValue = analogRead(ntcPin);
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  return celsius;
}

void unlock() {
  servo.write(180);
}

void lock() {
  servo.write(-90);
}