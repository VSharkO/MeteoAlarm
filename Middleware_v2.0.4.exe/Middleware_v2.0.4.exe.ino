#include <Ethernet.h>
#include <SPI.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 26 };
byte server[] = { 192, 168, 0, 25 };
String responce;
int i=0;
int flag=0;
EthernetClient client;

void setup()
{
  flag==true;
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
    responce.concat(c);
    Serial.print(c);
    
    }
    }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
}

