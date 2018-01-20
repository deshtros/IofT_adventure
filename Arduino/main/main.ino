#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

// Change SSID and PASSWORD
const char* ssid = "iPhone de 2Pat";
const char* password = "11111111";

int doorPin = 2; // GPIO2

WiFiServer server(80);

void initVariant() {
  uint8_t mac[] = {0xDE, 0xAD, 0xBE, 0x03, 0x04, 0x05};

  wifi_set_macaddr(STATION_IF, &mac[0]);
}

void setup() {
  // Setup serial-output
  Serial.begin(115200);
  delay(10);

  WiFi.mode(WIFI_STA);

  // Pin 2 has an integrated LED - configure it, and turn it off
  pinMode(doorPin, OUTPUT);
  digitalWrite(doorPin, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Set the hostname
  WiFi.hostname("web-blink");
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


  while(client.connected() && !client.available())
  {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request
  int value = LOW;
  if (request.indexOf("/door/open") != -1) {
    digitalWrite(doorPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/door/close") != -1) {
    digitalWrite(doorPin, LOW);
    value = LOW;
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Access-Control-Allow-Headers: content-type, cache-control");
  client.println("cache-control: no-cache");
  client.println(""); // do not forget this one
  client.println("HTTP/1.1 200 OK");
  client.println("Access-Control-Allow-Origin: *");
  client.println("cache-control: no-cache");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println(""); // do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  if(value == HIGH) {
    client.println("Open");
  } else {
    client.println("Close");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/door/open\">here</a> to OPEN the door<br>");
  client.println("Click <a href=\"/door/close\">here</a> to CLOSE the door<br>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
