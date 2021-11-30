#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

int buzzer = 8;
int readsuccess;
byte readcard[4];
char str[32] = "";
char str2[32] = "";
String StrUID;

void setup() {
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card

  Serial.println("CLEARDATA");
  Serial.println("LABEL,Date,Time,RFID UID");
  delay(1000);
  
  Serial.println("Scan PICC to see UID...");
  Serial.println("");
}
// --------------------------------------------------------------------
void loop() {
  readsuccess = getid();
 
  if(readsuccess){
    //Serial.println(StrUID[0]);
    //Serial.println(StrUID[0]);
    if(StrUID[0] == '1' && StrUID[1] == '7' && StrUID[2] == '0' &&StrUID[3] == '7' &&StrUID[4] == '0'){
          Serial.println( (String) "DATA,DATE,TIME," + StrUID );
          tone(buzzer, 2000);
          delay(200);
          noTone(buzzer);
      }
    else{

      /*buzzer/LED code goes here*/
      tone(buzzer, 1000); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
      delay(300);
      noTone(buzzer);
      delay(200);
      tone(buzzer, 1000); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
      delay(300);
      noTone(buzzer);
      delay(200);
       tone(buzzer, 1000); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
      delay(300);
      noTone(buzzer);
      
      }  
    
  }
}
// --------------------------------------------------------------------
int getid(){  
  if(!mfrc522.PICC_IsNewCardPresent()){
    return 0;
  }
  if(!mfrc522.PICC_ReadCardSerial()){
    return 0;
  }
 
  
  Serial.println("THE UID OF THE SCANNED CARD IS:");
  
  for(int i=0;i<4;i++){
    readcard[i]=mfrc522.uid.uidByte[i]; //storing the UID of the tag in readcard
    array_to_string(readcard, 4, str);
    if(strcmp(str, "4551312A") == 0){
      strcpy(str2, "1707043");
      }
    else if(strcmp(str, "90D9BA32") == 0){
      strcpy(str2, "1707033");
      }  
    else if(strcmp(str, "12C97D34") == 0){
      strcpy(str2, "1707022");
      }   
    else if(strcmp(str, "93AE7F40") == 0){
      strcpy(str2, "1707019");
      }
    else{
      strcpy(str2, str);
      }    
    StrUID = str2;
  }
  mfrc522.PICC_HaltA();
  return 1;
}
// --------------------------------------------------------------------
void array_to_string(byte array[], unsigned int len, char buffer[])
{
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}
