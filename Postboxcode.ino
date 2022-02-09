#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "gabriiel_can"; //Change this with your WIFI name
const char* password = "123456789"; // This is WIFI password
const char* host = "api.callmebot.com";
const int httpsPort = 443;
const int analogInPin = A0;
int  val, condition=0;

WiFiClientSecure client;

void setup() {
  
  Serial.begin(115200); // Starts the serial communication
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

 void loop  ( ) {
  val  =  analogRead (analogInPin);  //  The current signal at the sensor is read out
  if   (val  > 500 && val<1023 && condition == 0){
      client.setInsecure(); 
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    loop();
    return;
  }
         String url = "/signal/send.php?phone=+321231321&apikey=5464654&text=You+have+a+mail+in+your+postbox+✉"; // Change here the important stuff
         Serial.print("requesting URL: ");
         Serial.println(url);

         client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

        Serial.println("request sent");
        while (client.connected()) {
              String line = client.readStringUntil('y');
              if (line == "\r") {
                Serial.println("headers received");
                 break;
              }
        }
        String line = client.readStringUntil('\n');
        if (line.startsWith("Apikey")) {
        } else {
       
        }
        Serial.println("reply was:");
        Serial.println("==========");
        Serial.println(line);
        Serial.println("==========");
        Serial.println("closing connection");
        delay(1000);
        condition=1;
    }
    if(val == 1024 && condition == 1)ESP.restart();

  }
