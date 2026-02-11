#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define TRIG_PIN 17
#define ECHO_PIN 16
#define BUZZER_PIN 26

// BLE UUIDs
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcdefab-1234-5678-1234-abcdefabcdef"

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

long duration;
float distance;

// -------- BLE CALLBACK --------
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

// -------- DISTANCE FUNCTION --------
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout 30ms
  if (duration == 0) return -1;

  return (duration * 0.034) / 2; // cm
}

// -------- BUZZER CONTROL --------
unsigned long lastToggle = 0;
bool buzzerState = false;

void buzzerPattern(int interval) {
  if (interval == 0) {              // continuous ON
    digitalWrite(BUZZER_PIN, HIGH);
    return;
  }

  if (millis() - lastToggle >= interval) {
    buzzerState = !buzzerState;
    digitalWrite(BUZZER_PIN, buzzerState);
    lastToggle = millis();
  }
}

// -------- SETUP --------
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  BLEDevice::init("Smart_Cap");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  BLEDevice::getAdvertising()->start();
  Serial.println("Smart Cap BLE Ready");
}

// -------- LOOP --------
String lastMessage = "";

void loop() {
  distance = getDistance();

  String message = "";

  if (distance < 0) {
    digitalWrite(BUZZER_PIN, LOW);
    message = "No obstacle detected";
  }
  else if (distance <= 50) {
    message = "Danger: Obstacle very close";
    buzzerPattern(0);        // continuous
  }
  else if (distance <= 100) {
    message = "Warning: Obstacle closer";
    buzzerPattern(200);      // fast beep
  }
  else if (distance <= 150) {
    message = "Obstacle detected nearby";
    buzzerPattern(600);      // slow beep
  }
  else {
    digitalWrite(BUZZER_PIN, LOW);
    message = "Path clear";
  }

  // Send BLE notification ONLY if connected and message changed
  if (deviceConnected && message != lastMessage) {
    pCharacteristic->setValue(message.c_str());
    pCharacteristic->notify();
    Serial.println(message);
    lastMessage = message;
  }

  delay(100); // small stability delay
}