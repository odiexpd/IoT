/*************************************
 * Program : Project 1 Kontrol LED
 * Input : -
 * Output : LED1 
 * Iot Kontrol LED 1 Channel Relay
 * SMKN 2 Probolinggo
 * ***********************************/

#include <ESP8266WiFi.h> 
const char* ssid = "ssidwifianda"; //ganti dengan ssid jaringan wifi anda
const char* password = "passwordwifianda"; //ganti dengan password jaringan wifi anda
 
int ledPin = D5;
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10); 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi tersambung");  
  server.begin();
  Serial.println("Server dimulai"); 
  Serial.print("Gunakan URL ini untuk tersambung: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}
 
void loop() {  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  Serial.println("client baru");
  while(!client.available()){
    delay(1);
  }
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  } 
 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led sekarang: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Nyalakan </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Matikan </button></a><br />");  
  client.println("</html>"); 
  delay(1);
  Serial.println("Client Terputus");
  Serial.println(""); 
}
 
