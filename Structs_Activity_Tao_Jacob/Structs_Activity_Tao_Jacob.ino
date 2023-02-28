/* Activity - Struts (Banker(
   Description
   Created by: Jacob Wen  & Tao Zheng
   Date Started:
   date finished:
*/
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
String LCD[20];
const byte rows = 4;
const byte cols = 4;
char customKey;
char keymap[rows][cols] =
{
  {'1', '2', '3', '4'},
  {'5', '6', '7', '8'},
  {'9', 'A', 'B', 'C'},
  {'D', '*', '0', '#'}
};
byte rowPin[rows] = {4, 5, 6, 7};
byte colPin[cols] = {8, 9, 10, 11};

Keypad customKeypad =
  Keypad(makeKeymap(keymap), rowPin, colPin, rows, cols);


struct account
{
  String acount1 = " ";
  String pass1 = " ";
  String email = " ";
  int phone = " ";
  String licensenum = " ";
  String state = " ";
  String city = " ";
  String enteredacount = " ";
  String enteredpass = " ";
};
struct account info ;

struct payment
{
  String information;
  String amount;
};
struct payment card;

struct parkinginfo
{
  int parkingtime;
  int cost;
  String date;
  int timenow;
  int Zone;
  int daydone;
};
struct parkinginfo park;

void setup()
{
  Serial.flush();
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.backlight();
}

void loop()
{
  parking();

}
void parking()
{
  Serial.println("press 1 to log in");
  Serial.println("press 2 to open a new account");
  Serial.println("press 3 to close a account");

  customKey = customKeypad.waitForKey();

  if (customKey == '2')
  {
    Serial.print("Please enter your username ");
    while (Serial.available() == 0) {}
    info.acount1 = Serial.readString();
    Serial.println(info.acount1);

    Serial.print("Please enter your password ");
    while (Serial.available() == 0) {}
    info.pass1 = Serial.readString();
    Serial.println(info.pass1);

    Serial.print("Please enter you email ");
    while (Serial.available() == 0) {}
    info.email = Serial.readString();
    Serial.println(info.email);

    Serial.print("Please enter you phone number ");
    while (Serial.available() == 0) {}
    info.phone = Serial.parseInt();
    Serial.println(info.phone);

    Serial.print("Please enter you license number ");
    while (Serial.available() == 0) {}
    info.licensenum = Serial.readString();
    Serial.println(info.licensenum);
    Serial.print("Please enter you license State ");
    while (Serial.available() == 0) {}
    info.state = Serial.readString();
    Serial.println(info.state);
    Serial.print("Please enter you license city ");
    while (Serial.available() == 0) {}
    info.city = Serial.readString();
    Serial.println(info.city);
    

  }

  if (customKey == '1')
  {
    Serial.println("Please enter your username");
    while (Serial.available() == 0) {}
    info.enteredacount = Serial.readString();
    if (info.enteredacount == info.acount1)
    {
      Serial.println("What is your password");
      while (Serial.available() == 0) {}
      info.enteredpass = Serial.readString();
      if (info.enteredpass == info.pass1)
      {
        Serial.println("What is your payment method?");
        Serial.println("please select 5, 6, or 7");
        Serial.println("5 = cash");
        Serial.println("6 = debit");
        Serial.println("7 = credit");
        customKey = customKeypad.waitForKey();
        Serial.println(customKey);
        Payment();

      }
      else
      {
        Serial.println("that was not the right password");
        Serial.println("please select a new function");
      }
    }
    else
    {
      Serial.println("that was not the right username");
      Serial.println("please select a new function");

    }

  }
  if (customKey == '3')
  {
    info.acount1 = " ";
    info.pass1 = " ";
    info.email = " ";
    info.phone = " ";
    info.licensenum = " ";
    info.state = " ";
    info.city = " ";

  }

}
void Payment()
{
  switch (customKey)
  {
    case '5':
      {
        card.information = "cash";
        Serial.println(card.information);
        Parking();
        break;
      }
    case '6':
      {
        card.information = "debit";
        Serial.println(card.information);
        Parking();
        break;
      }
    case '7':
      {
        card.information = "credit";
        Serial.println(card.information);
        Parking();
        break;
      }
    default:
      {
        Serial.print("error");
        break;
      }
  }
}

void Parking()
{
  Serial.println("How long would you like to stay in hours");
  while (Serial.available() == 0) {}
  park.parkingtime = Serial.parseInt();

  park.cost = park.parkingtime * 2;

  Serial.print("It will cost you ");
  Serial.println(park.cost);
  Serial.println("Confirm. 1 Yes, 2 No");

  customKey = customKeypad.waitForKey();

  if (customKey == '1')
  {
    Serial.println("Would you like extended time? 1 Yes, 2 No");

    customKey = customKeypad.waitForKey();
    if (customKey = '1')
    {
    Serial.println("How many more days would you like?");
    while (Serial.available() == 0) {}
    park.daydone = Serial.parseInt();

    park.cost = park.cost + (park.daydone *48);

    Serial.print("It will cost you ");
    Serial.println(park.cost);
    }
    
    else {}
    
    Serial.println("what is todays date ");
    while (Serial.available() == 0) {}
    park.date = Serial.readString();

    Serial.println("what is the time ");
    while (Serial.available() == 0) {}
    park.timenow = Serial.parseInt();

    park.Zone = random(100);

    Serial.print("your parking zone is ");
    Serial.println(park.Zone);
    Serial.print("Today is ");
    Serial.println(park.date);
    Serial.print("You end in ");
    Serial.print(park.daydone);
    Serial.print(" days and ");
    Serial.print(park.parkingtime);
    Serial.println(" hours");
    Storing();
  }
}
void Storing()
{
  LCD[0] =info.acount1;
  LCD[1] =info.pass1;
  LCD[2] =info.email;
  LCD[3] =info.phone;
  LCD[4] =info.licensenum;
  LCD[5] =info.state;
  LCD[6] =info.city;
  LCD[7] =card.information;
  LCD[8] =card.amount;
  LCD[9] =park.parkingtime;
  LCD[10] =park.cost;
  LCD[11] =park.date;
  LCD[12] =park.timenow;
  LCD[13] =park.Zone;
  LCD[14] =park.daydone;
  LCDisplay();
}
void LCDisplay()
{
  int j = 1, i = 0; 
  for(int i = 0;i<=14;i++)
  {
    lcd.clear();
    lcd.setCursor(j,1);
    lcd.print(LCD[i]);
    delay(1000); 
  }
}

