

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

  void loop()
  {
    int analogSensor_2 = analogRead(LpgA2); // read lpg input
    Serial.println("LPG: ");
    Serial.println(analogSensor_2);

    if ( analogSensor_2 < sensorThres_2 ){
    //digitalWrite(LED, HIGH);  
    //digitalWrite(Buzzer, HIGH);  
    Serial.println("[<900]");
    lcd.setCursor(0, 1);
    lcd.print("FTR : OFF");
    lcd.setCursor(10, 1);
    lcd.println("[<900]");
    }
    else{       
    //digitalWrite(LED, LOW);
    //digitalWrite(Buzzer, LOW); 
    Serial.println("[>900]");     
    lcd.setCursor(0, 1);
    lcd.print("FTR : ON");
    lcd.setCursor(9, 1);
    lcd.println("[>900]");      
    }

  
    lcd.setCursor(0, 0);
    lcd.print("LPG: ");
    lcd.setCursor(9, 0);
    lcd.print(analogSensor_2);
    lcd.setCursor(13, 0);
    lcd.print("ppm");
    String sendData = "GET /update?api_key="+ myAPI +"&"+ myFIELD +"="+String(analogSensor_2);
    Send_AT_Cmd("AT+CIPMUX=1", 1000, DEBUG);       //Allow multiple connections
    Send_AT_Cmd("AT+CIPSTART=0,\"TCP\",\""+ myHOST +"\","+ myPORT, 1000, DEBUG);
    Send_AT_Cmd("AT+CIPSEND=0," +String(sendData.length()+4),1000,DEBUG);  
    Serial1.find(">"); 
    Serial1.println(sendData);
    Serial.print("LPG Detected: ");
    Serial.print(analogSensor_2);
    Send_AT_Cmd("AT+CIPCLOSE=0",1000,DEBUG);
    Serial.println("Done!");
    Serial.println("");
    delay(10000);
  }

  String Send_AT_Cmd(String command, const int timeout, boolean debug)
{
  Serial.print(command);
  Serial.println("     ");
  
  String response = "";
  Serial1.println(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (Serial1.available())
    {
      char c = Serial1.read();
      response += c;
    }
  }
  if (debug)
  {
    //Serial.print(response);
  }
  return response;
}
