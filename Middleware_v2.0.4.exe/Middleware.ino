#include <LiquidCrystal.h>
#include <Ethernet.h>
#include <SPI.h>

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String temperature="30000";
String clouds="";
EthernetClient client;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 26 };
byte server[] = { 192, 168, 0, 16 };
String response;

void setup() {
  
  Ethernet.begin(mac, ip);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  callService();
  Serial.println(temperature);
  Serial.println(clouds);
  
  lcd.print("Temp: " + String(convertKelvin(temperature)) +"C");
  lcd.setCursor(0, 1);
  lcd.print(clouds);
  delay(600000);
}

void callService(){
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /SERVIS/WebService1.asmx/returnWether? HTTP/1.1");
    client.println("Host: localhost");
    client.println();
  }
delay(1000);
   if (client.available()) {
    for(int i=0;i<467;i++){
      char c = client.read();
      response.concat(c);
      Serial.print(c);
      }
      temperature=response.substring(425,432);
      clouds = response.substring(454,467);
      response="";
      client.stop();
   }
      
    if (!client.connected()) {
    Serial.println();    
    Serial.println("disconnecting.");
    client.stop();
    }
}

 float convertKelvin(String nesto){
  double rez;
  if(nesto.toDouble()>10000){
    rez = ((nesto.toFloat()+272.15f)/100)-272.15f;
    }else{
    rez = nesto.toDouble(); 
    }
    return rez;
  }

