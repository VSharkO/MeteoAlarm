#include <Ethernet.h>
#include <SPI.h>
#include <LiquidCrystal.h>

//LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//service
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 26 };
byte server[] = { 192, 168, 0, 16 };
//variables
String response;
String temperature;
String clouds;
String windSpeed;
String pressure;

EthernetClient client;

void setup()
{
  //setup lcd num of columns and rows
  lcd.begin(16, 2);
  
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  
  delay(1000);

  Serial.println("connecting...");

  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /SERVIS/WebService1.asmx/returnWether? HTTP/1.1");
    client.println("Host: localhost");
    client.println();
    
  } else {
    Serial.println("connection failed");
  }
}

void loop()
{
  if (client.available()) {
    
    char c = client.read();
    response.concat(c);
    Serial.print(c);
    
    }
    
    
      if (!client.connected()) {
        Serial.println();
        printResponseOnLCD();

        
        Serial.println("disconnecting.");
        client.stop();
        response = "";
        delay(60000);
        
        if (client.connect(server, 80)) {
        Serial.println("connected");
        client.println("GET /SERVIS/WebService1.asmx/returnWether? HTTP/1.1");
        client.println("Host: localhost");
        client.println();
        
      } else {
        Serial.println("connection failed");
    }
  }
 }

void printResponseOnLCD(){
  
    temperature =response.substring(425,432);
    clouds = "Clouds: " + response.substring(454,463);
    windSpeed = "Wind: " + response.substring(484,488)+"mps";
    pressure = "Pressure: " + response.substring(509,516)+"hPa";
    float temperatureFloat = temperature.toFloat();
    if (temperatureFloat>10000){
        temperatureFloat=((temperatureFloat+272.15f)/100)-272.15f;
    }

    temperature = "Temp: " + String(temperatureFloat)+ "°C";
    Serial.println(temperature);
    Serial.println(clouds);
    Serial.println(windSpeed);
    Serial.println(pressure);
    lcd.print(temperature+"\n"+pressure);
  }

