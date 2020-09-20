#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup() 
{
  Serial.begin(9600);        
  SPI.begin();            
  mfrc522.PCD_Init();
  lcd.begin();   
  lcd.backlight(); 
  lcd.setCursor(0,0);
  lcd.print(".Security System.");
  lcd.setCursor(0,1);
  lcd.print("......Ready......");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("..System Locked..");
  lcd.setCursor(0,1);
  lcd.print("..Scan Card/Tag..");
}
void loop()
{
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) 
  {
    key.keyByte[i] = 0xFF;
  }
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  } 
  byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI 
      && piccType != MFRC522::PICC_TYPE_MIFARE_1K
      && piccType != MFRC522::PICC_TYPE_MIFARE_4K) 
      {
         return;
      }
   if( (mfrc522.uid.uidByte[0] == 208) && (mfrc522.uid.uidByte[1] == 148) && (mfrc522.uid.uidByte[2] == 112) && (mfrc522.uid.uidByte[3] == 37) ) 
   {
    lcd.setCursor(0,0);
    lcd.print(".System Unlocked.");
    lcd.setCursor(0,1);
    lcd.print(".....Welcome.....");
    delay(3000);
    lcd.setCursor(0,0);
    lcd.print("..System Locked..");
    lcd.setCursor(0,1);
    lcd.print("..Scan Card/Tag..");
    Serial.print("ready");
   }
   else if( (mfrc522.uid.uidByte[0] == 99) && (mfrc522.uid.uidByte[1] == 01) && (mfrc522.uid.uidByte[2] == 83) && (mfrc522.uid.uidByte[3] == 211) ) 
   {
    lcd.setCursor(0,0);
    lcd.print(".System Unlocked.");
    lcd.setCursor(0,1);
    lcd.print(".....Welcome.....");
    delay(3000);
    lcd.setCursor(0,0);
    lcd.print("..System Locked..");
    lcd.setCursor(0,1);
    lcd.print("..Scan Card/Tag..");
   }
   else
   {
    lcd.setCursor(0,0);
    lcd.print("..System Locked..");
    lcd.setCursor(0,1);
    lcd.print("...Invalid Tag...");
    delay(3000);
    lcd.setCursor(0,0);
    lcd.print("..System Locked..");
    lcd.setCursor(0,1);
    lcd.print("..Scan Card/Tag..");
   }
}
        
