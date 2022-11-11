#Smart Mining Gear

//#include <SoftwareSerial.h>    
//SoftwareSerial esp(P3_4, P3_5);   //Pin 6 and 7 act as RX and TX. Connect them to TX and RX of ESP8266   
   
#define DEBUG true
int LpgA2 = A2;               // P6_2
int sensorThres_2 = 900;      //Set the threshold value
int number;
String mySSID = "";  // Wi-Fi SSID
String myPWD = ""; // Wi-Fi Password
String myAPI = "";   // WRITE API Key
String myHOST = "";   //Wi-Fi Host
String myPORT = "";   //Declare the port
String myFIELD = "";  //Field label for Dashboard

 #include <LiquidCrystal.h>
LiquidCrystal lcd(P2_0, P8_1, P2_2, P2_3, P2_4, P2_5);    //

void setup()
{
  lcd.begin(16, 2);
  pinMode(LpgA2, INPUT);
  Serial.begin(115200);
  Serial1.begin(115200);
  Send_AT_Cmd("AT+RST", 1000, DEBUG);                      
  Send_AT_Cmd("AT+CWMODE=1", 1000, DEBUG);                 
  Send_AT_Cmd("AT+CWJAP=\""+ mySSID +"\",\""+ myPWD +"\"", 1000, DEBUG);   
  delay(1000); 
}
