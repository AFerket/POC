//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************

  This program will test the LCD panel and the buttons

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int positie;
int lijn;
int led;
// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);      // read the value from the sensor
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  // For V1.1 us this threshold
  /* if (adc_key_in < 50)   return btnRIGHT;
    if (adc_key_in < 250)  return btnUP;
    if (adc_key_in < 450)  return btnDOWN;
    if (adc_key_in < 650)  return btnLEFT;
    if (adc_key_in < 850)  return btnSELECT;
  */
  // For V1.0 comment the other threshold and use the one below:

  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;



  return btnNONE;  // when all others fail, return this...
}

void setup()
{

  lcd.begin(16, 2);              // start the library
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Test met LED");

  lcd.setCursor(15, 1);
  lcd.print("3");
  lcd.setCursor(14, 1);
  lcd.print("2");
  lcd.setCursor(13, 1);
  lcd.print("1");

  lcd.setCursor(4, 1);
  lcd.print("Aan");
  lcd.setCursor(0, 1);
  lcd.print("Uit");

  lcd.blink();
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  positie = 0;
  lijn = 0;
  Serial.begin(9600);
}


void loop()
{
  lcd.setCursor(13, 0);
  lcd.print(led);
  lcd.setCursor(positie, lijn);
  Serial.print("LED: ");
  Serial.print(led);
  Serial.print(", Positie: ");
  Serial.print(positie);
  Serial.print(", Lijn: ");
  Serial.println(lijn);

  lcd_key = read_LCD_buttons();  // read the buttons
  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
    case btnRIGHT:
      {
        positie++;
        if (positie >= 0 && positie <= 15)
        {
          lcd.setCursor(positie, lijn);
        }
        else if (positie > 15)
        {
          positie = 15;
        }
        break;
      }
    case btnLEFT:
      {
        positie = positie - 1;
        if (positie >= 0 && positie <= 15)
        {
          lcd.setCursor(positie, lijn);
        }
        else if (positie < 0)
        {
          positie = 0;
        }
        break;
      }
    case btnUP:
      {
        lijn = 0;
        lcd.setCursor(positie, lijn);
        break;
      }
    case btnDOWN:
      {
        lijn = 1;
        lcd.setCursor(positie, lijn);
        break;
      }
    case btnSELECT:
      {
        if (positie == 4 && lijn == 1)
        {
          if (led == 1)
          {
            digitalWrite(11, HIGH);
          }
          else if (led == 2)
          {
            digitalWrite(12, HIGH);
          }
          if (led == 3)
          {
            digitalWrite(13, HIGH);
          }

        }
        else if (positie == 0 && lijn == 1)
        {
          if (led == 1)
          {
            digitalWrite(11, LOW);
          }
          else if (led == 2)
          {
            digitalWrite(12, LOW);
          }
          if (led == 3)
          {
            digitalWrite(13, LOW);
          }
        }

        else if (positie == 15 && lijn == 1)
        {
          led = 3;
        }
        else if (positie == 14 && lijn == 1)
        {
          led = 2;
        }

        else if (positie == 13 && lijn == 1)
        {
          led = 1;
        }

        break;
      }

    case btnNONE:
      {
        break;
      }
  }
  delay(200);
}
