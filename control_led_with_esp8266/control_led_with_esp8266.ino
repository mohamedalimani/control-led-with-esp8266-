#include <ESP8266WiFi.h>

const char* ssid = "type your ssid here";   
const char* password = "type your password here";
int LED = 16; 
WiFiServer server(80);

void setup()
{
Serial.begin(115200); //Default Baudrate
pinMode(LED, OUTPUT);
digitalWrite(LED, LOW);

Serial.print("Connecting to the Newtork");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

Serial.println("WiFi connected"); 
server.begin();  // Starts the Server
Serial.println("Server started");
Serial.print("IP Address of network: ");
Serial.println(WiFi.localIP());
Serial.print("Copy and paste the following URL: https://");
Serial.print(WiFi.localIP());
Serial.println("/");
}

void loop(){
  WiFiClient client = server.available() ;
  if (!client){
    return ;
    }
    Serial.println("waiting for a client to connect to the interface") ; 

    while(!client.available()){
      delay(1) ;
    }
    String request = client.readStringUntil('\r') ;
    Serial.println(request) ; 
    client.flush() ;
    int value = LOW ;
    if (request.indexOf("/LED=ON") != -1){
      digitalWrite(LED,HIGH);
      value = HIGH ;
      }
    if (request.indexOf("/LED=OFF") != -1){
      digitalWrite(LED,LOW) ;
      value = LOW ;
      }

// HTML CODE "this is the response from our esp8266 to the client who'se gonna go to
// the url of the esp8266"

client.println("HTTP/1.1 200 OK"); //
client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.print(" CONTROL LED: ");

if(value == HIGH)
{
  client.print("ON");
}
else
{
  client.print("OFF");
}
client.println("<br><br>");
client.println("<a href=\"/LED=ON\"\"><button>ON</button></a>");
client.println("<a href=\"/LED=OFF\"\"><button>OFF</button></a><br />");
client.println("</html>");

delay(1);
Serial.println("Client disonnected");
Serial.println("");
}
