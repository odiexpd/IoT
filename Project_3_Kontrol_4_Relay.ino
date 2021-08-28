/*************************************
 * Program : Project 3 : Kontrol 4 Lampu
 * Input : -
 * Output : Relay 4 unit.
 * Iot Home Automation 4 Channel
 * SMKN 2 Probolinggo
 * ***********************************/
#include <ESP8266WiFi.h> 
const char* ssid = "ssidwifianda"; //ganti dengan ssid jaringan wifi anda
const char* password = "passwordwifianda"; //ganti dengan password jaringan wifi anda
#define Relay1 D5
#define Relay2 D6 
#define Relay3 D7 
#define Relay4 D8 
; // 
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  digitalWrite(Relay1, LOW);
  digitalWrite(Relay2, LOW);
  digitalWrite(Relay3, LOW);
  digitalWrite(Relay4, LOW); 
  
  Serial.println();
  Serial.println();
  Serial.print("Terhubung ke ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi tersambung");
 
  // Start the server
  server.begin();
  Serial.println("Server dimulai"); 
  Serial.print("Use this URL to connect: ");
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
  if (request.indexOf("/relay1on") > 0)  {
    digitalWrite(Relay1, HIGH);   
  }
  if (request.indexOf("/relay1off") >0)  {
    digitalWrite(Relay1, LOW);   
  }

   if (request.indexOf("/relay2on") > 0)  {
    digitalWrite(Relay2, HIGH);
   
  }
  if (request.indexOf("/relay2off") >0)  {
    digitalWrite(Relay2, LOW);
   
  }
    if (request.indexOf("/relay3on") >0)  {
    digitalWrite(Relay3, HIGH);
   
  }
  if (request.indexOf("/relay3off") > 0)  {
    digitalWrite(Relay3, LOW);
   
  }
   if (request.indexOf("/relay4on") > 0)  {
    digitalWrite(Relay4, HIGH);
   
  }
  if (request.indexOf("/relay4off") > 0)  {
    digitalWrite(Relay4, LOW);
   
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("</head>");
  client.println("<body bgcolor = \"#f7e6ec\">"); 
  client.println("<hr/><hr>");
  client.println("<h4><center> IoT Home Automation : Kontrol 4 Lampu  </center></h4>");
  client.println("<h4><center> SMKN 2 Probolinggo  </center></h4>");
  client.println("<hr/><hr>");  
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("Lampu 1");
  client.println("<a href=\"/relay1on\"\"><button>Nyalakan </button></a>");
  client.println("<a href=\"/relay1off\"\"><button>Matikan </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
  client.println("<center>");
  client.println("Lampu 2");
  client.println("<a href=\"/relay2on\"\"><button>Nyalakan </button></a>");
  client.println("<a href=\"/relay2off\"\"><button>Matikan </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("Lampu 3");
  client.println("<a href=\"/relay3on\"\"><button>Nyalakan </button></a>");
  client.println("<a href=\"/relay3off\"\"><button>Matikan </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("Lampu 4");
  client.println("<a href=\"/relay4on\"\"><button>Nyalakan </button></a>");
  client.println("<a href=\"/relay4off\"\"><button>Matikan </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");  
  client.println("<table border=\"5\">");
  client.println("<tr>");
  //=====================
  if (digitalRead(Relay1))
         { 
           client.print("<td>Lampu 1 = ON</td>");        
         }
  else
          {
            client.print("<td>Lampu 1 = OFF</td>");
          }     
  client.println("<br />");
  //======================           
  if (digitalRead(Relay2))
          { 
           client.print("<td>Lampu 2 = ON</td>");
          }
  else
          {
            client.print("<td>Lampu 2 = OFF</td>");
          }
  client.println("</tr>");
  //=======================
  client.println("<tr>");
  
  if (digitalRead(Relay3))
          { 
           client.print("<td>Lampu 3 = ON</td>");
          }
  else
          {
            client.print("<td>Lampu 3 = OFF</td>");
          }
  if (digitalRead(Relay4))
          { 
           client.print("<td>Lampu 4 = ON</td>");
          }
  else
          {
            client.print("<td>Lampu 4 = OFF</td>");
          }
  client.println("</tr>");  
  client.println("</table>");
  client.println("</center>");
  client.println("</html>"); 
  delay(1);
  Serial.println("Client terputus");
  Serial.println(""); 
}
