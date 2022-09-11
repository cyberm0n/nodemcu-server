#include <ESP8266WiFi.h>  
 const char* ssid = "wifi-name";
 const char* password = "password";  
 int ledPin = 13; // D7 
 WiFiServer server(80);
 void setup() {  
  Serial.begin(9600);  
  delay(10);  
  pinMode(ledPin, OUTPUT);  
  digitalWrite(ledPin, LOW);  
  // Connect to WiFi network  
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
  Serial.println("WiFi connected");  
  // Start the server  
  server.begin();  
  Serial.println("Server started");  
  // Print the IP address  
  Serial.print("Use this URL to connect: ");  
  Serial.print("http://");  
  Serial.print(WiFi.localIP()); 
  Serial.println("/");  
 }  
 void loop() {  
  // Check if a client has connected  
  WiFiClient client = server.available();  
  if (!client) {  
   return;  
  }  
  // Wait until the client sends some data  
  Serial.println("new client");  
  while(!client.available()){  
   delay(1);  
  }  
  // Read the first line of the request  
  String request = client.readStringUntil('\r');  
  Serial.println(request);  
  client.flush();  
  // Match the request  
  int value = LOW;  
  if (request.indexOf("/ON") != -1) {  
   digitalWrite(ledPin, HIGH);  
   value = HIGH;  
  }  
  if (request.indexOf("/OFF") != -1) {  
   digitalWrite(ledPin, LOW);  
   value = LOW;  
  }  
 // Set ledPin according to the request  
 //digitalWrite(ledPin, value);  
  // Return the response  
  client.println("HTTP/1.1 200 OK");  
  client.println("Content-Type: text/html");  
  client.println(""); // do not forget this one  
  client.println("<!DOCTYPE HTML>");  
  client.println("<html>");  
  client.print("Status: ");  
  if(value == HIGH) {  
   client.print("On");  
  } else {  
   client.print("Off");  
  }  
  client.println("<br><br>");  
  client.println("<a href=\"/ON\"\"><button>Turn On </button></a>");  
  client.println("<a href=\"/OFF\"\"><button>Turn Off </button></a><br />");   
  client.println("</html>");  
  delay(1);  
  Serial.println("Client disonnected");  
  Serial.println("");  
 }  
