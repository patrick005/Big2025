// # include <Arduino.h>
// # include <ESP8266WiFi.h>
// # include <WiFiClient.h>

// //Server connect to WiFi Network
// #define WIFI_SSID "turtle"
// #define WIFI_PASSWORD "turtlebot3"
// #define WIFI_PORT 8888

// WiFiServer server(WIFI_PORT);

// void setup(){
//     Serial.begin(115200);
//     Serial.println("\nESP8266 펌웨어 시작!");

//     WiFi.mode(WIFI_STA);
//     WiFi.disconnect(); // 기존 연결 끊기 (선택 사항)
//     WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //Connect to wifi

//     // Wait for connection
//     Serial.println("Connecting to Wifi...");
//     int retryCount = 0;
//     while (WiFi.status() != WL_CONNECTED && retryCount < 10) {
//         delay(500);
//         Serial.print(".");
//         retryCount++;
//     }

//     if (WiFi.status() == WL_CONNECTED) {
//         Serial.println("");
//         Serial.print("Connected to ");
//         Serial.println(WIFI_SSID);
//         Serial.print("IP address: ");
//         Serial.println(WiFi.localIP());
//         server.begin();
//         Serial.print("Open Telnet and connect to IP:");
//         Serial.print(WiFi.localIP());
//         Serial.print(" on port ");
//         Serial.println(WIFI_PORT);
//     } else {
//         Serial.println("");
//         Serial.println("WiFi connection failed!");
//         Serial.print("Status code: ");
//         Serial.println(WiFi.status()); // 연결 실패 상태 코드 출력
//     }
// }

// void loop()
// {
//     WiFiClient client = server.accept();

//     if (client) {
//         if(client.connected())
//         {
//             Serial.println("Client Connected");
//         }

//         while(client.connected()){
//             while(client.available()>0){
//                 // read data from the connected client
//                 Serial.write(client.read());
//             }
//             //Send Data to connected client
//             while(Serial.available()>0){
//                 client.write(Serial.read());
//             }
//         }
//         client.stop();
//         Serial.println("Client disconnected");
//     }
// }

// // #include <Arduino.h>
// // #include <ESP8266WiFi.h>
// // #include <WiFiClient.h>
// // #include <zmq.hpp>
// // #include <ArduinoJson.h>

// // //Server connect to WiFi Network
// // const char* server_address = "tcp://192.168.0.43:4796"; // 라즈베리파이 ZeroMQ 수신 주소와 포트
// // const char* device_id = "ESP8266_1"; // 각 ESP8266마다 고유한 ID 설정 (필요에 따라 수정)

// // zmq::context_t context(1);
// // zmq::socket_t publisher(context, ZMQ_PUSH);

// // void connectWifi() {
// //   Serial.print("Connecting to WiFi...");
// //   WiFi.begin(ssid, password);
// //   while (WiFi.status() != WL_CONNECTED) {
// //     delay(500);
// //     Serial.print(".");
// //   }
// //   Serial.println("Connected!");
// //   Serial.print("IP address: ");
// //   Serial.println(WiFi.localIP());
// // }

// // void setup() {
// //   Serial.begin(115200);
// //   connectWifi();
// //   publisher.connect(server_address);
// //   Serial.println("Connected to ZeroMQ server.");
// // }

// // void loop() {
// //   if (Serial.available() > 0) {
// //     String serial_data = Serial.readStringUntil('\n');
// //     serial_data.trim();
// //     if (serial_data.length() > 0) {
// //       StaticJsonDocument<128> jsonDoc;
// //       jsonDoc["device_id"] = device_id;
// //       jsonDoc["data"] = serial_data;
// //       char jsonBuffer[128];
// //       serializeJson(jsonDoc, jsonBuffer);

// //       zmq::message_t message(strlen(jsonBuffer));
// //       memcpy(message.data(), jsonBuffer, strlen(jsonBuffer));
// //       publisher.send(message, zmq::send_flags::dontwait);
// //       Serial.print("Sent: ");
// //       Serial.println(jsonBuffer);
// //     }
// //   }
// //   delay(100);
// // }
// // #include <Arduino.h>
