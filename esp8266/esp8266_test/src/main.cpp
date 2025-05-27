#include <Arduino.h> // Arduino 코드를 사용하므로 필수 포함
#include <ESP8266WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
// #include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <WiFiClient.h> // WiFiClient 클래스를 사용하므로 명시적으로 포함

#define PIN D7
#define NUM_LEDS 1

const char* ssid = "turtle";
const char* password = "turtlebot3";
const char* serverIP = "192.168.0.43";
const int serverPort = 7755;

Adafruit_MPU6050 mpu;
Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_RGB + NEO_KHZ800);
WiFiClient client;

float attackThresholdX = 15.0;
float movementThresholdY = 15.0;
float acceptThresholdZ = 25.0;

unsigned long lastActionTime = 0;
unsigned long actionInterval = 200;

// 함수 프로토타입 선언 (setup() 또는 loop()에서 호출되기 전에 선언되어야 합니다.)
void setColor(uint8_t r, uint8_t g, uint8_t b);

void setup() {
  strip.begin();
  strip.show();

  // Serial.begin(115200);
  WiFi.begin(ssid, password);
  setColor(0, 0, 255); // 파란불: WiFi 연결 중

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Serial.println("WiFi connected");
  setColor(0, 255, 0); // 초록불: WiFi 연결 완료

  // Wire 라이브러리 초기화는 MPU6050.begin() 내부에서 처리되는 경우가 많지만,
  // 명시적으로 Wire.begin()을 호출할 필요가 있다면 여기에 추가할 수 있습니다.
  // Wire.begin();

  if (!mpu.begin()) {
    // Serial.println("MPU6050 not found");
    while (1) { // MPU6050을 찾을 때까지 무한 대기
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  delay(500); // 센서 안정화 대기
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setColor(0, 0, 255); // 파란불: WiFi 끊김
    WiFi.begin(ssid, password);
    delay(1000);
    return;
  }

  if (!client.connected()) {
    if (!client.connect(serverIP, serverPort)) {
      setColor(255, 0, 0); // 빨간불: 서버 연결 실패
      delay(1000);
      return;
    }
    // Serial.println("서버에 재연결 성공");
    setColor(0, 255, 0); // 초록불: 서버 재연결 성공
  }

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float ax = abs(a.acceleration.x);
  float ay = abs(a.acceleration.y);
  float az = abs(a.acceleration.z);
  float maxAccel = max(max(ax, ay), az);

  String dataToSend = "";
  unsigned long now = millis();

  if (now - lastActionTime < actionInterval) {
    delay(10);
    return;
  }

  if (maxAccel == ax && ax > attackThresholdX) {
    dataToSend = "ATTACK";
  } else if (maxAccel == ay && ay > movementThresholdY) {
    dataToSend = "MOVEMENT";
  } else if (maxAccel == az && az > acceptThresholdZ) {
    dataToSend = "ACCEPT";
  }

  if (dataToSend.length() > 0) {
    client.println(dataToSend);    // 개행 포함 전송
    lastActionTime = now;
    // 전송 성공 시의 LED 색상은 전송 로직이 완료된 후 업데이트
    // 예를 들어, 전송 완료 후 잠시 특정 색을 보여주는 로직 추가 가능
    // 현재는 WiFi 연결 성공 및 서버 재연결 성공 시 초록불이 켜지도록 되어 있습니다.
    // 여기서는 별도로 LED 색상을 변경하지 않습니다.
  }

  delay(120);
}

void setColor(uint8_t r, uint8_t g, uint8_t b) {
  strip.setPixelColor(0, strip.Color(r, g, b));
  strip.show();
}