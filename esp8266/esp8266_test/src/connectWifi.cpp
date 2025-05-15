# include <Arduino.h>
# include <ESP8266WiFi.h>
# include <WiFiClient.h>

//Server connect to WiFi Network
#define WIFI_SSID "turtle"
#define WIFI_PASSWORD "turtlebot3"
#define WIFI_PORT 8888

WiFiServer server(WIFI_PORT);

void setup(){
    Serial.begin(115200);
    Serial.println("\nESP8266 펌웨어 시작!");

    WiFi.mode(WIFI_STA);
    WiFi.disconnect(); // 기존 연결 끊기 (선택 사항)
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //Connect to wifi

    // Wait for connection
    Serial.println("Connecting to Wifi...");
    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED && retryCount < 10) {
        delay(500);
        Serial.print(".");
        retryCount++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(WIFI_SSID);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        server.begin();
        Serial.print("Open Telnet and connect to IP:");
        Serial.print(WiFi.localIP());
        Serial.print(" on port ");
        Serial.println(WIFI_PORT);
    } else {
        Serial.println("");
        Serial.println("WiFi connection failed!");
        Serial.print("Status code: ");
        Serial.println(WiFi.status()); // 연결 실패 상태 코드 출력
    }
}

void loop()
{
    WiFiClient client = server.accept();

    if (client) {
        if(client.connected())
        {
            Serial.println("Client Connected");
        }

        while(client.connected()){
            while(client.available()>0){
                // read data from the connected client
                Serial.write(client.read());
            }
            //Send Data to connected client
            while(Serial.available()>0){
                client.write(Serial.read());
            }
        }
        client.stop();
        Serial.println("Client disconnected");
    }
}