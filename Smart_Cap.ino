// ---------- PIN DEFINITIONS ----------
#define TRIG_PIN    17
#define ECHO_PIN    16
#define BUZZER_PIN  26

long duration;
float distance;

// ---------- ULTRASONIC FUNCTION ----------
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout

  if (duration == 0) return -1;

  return (duration * 0.034) / 2;
}

// ---------- BUZZER FUNCTION ----------
void beep(int times, int onTime, int offTime) {
  for (int i = 0; i < times; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(onTime);
    digitalWrite(BUZZER_PIN, LOW);
    delay(offTime);
  }
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);
}

// ---------- LOOP ----------
void loop() {

  distance = getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 0) {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // 🔴 0 – 50 cm → Continuous beep
  else if (distance <= 50) {
    Serial.println("Very Close - Continuous Beep");
    digitalWrite(BUZZER_PIN, HIGH);
  }
   // 🔴 50 – 100 cm → 3 Beeps
  else if (distance > 50 && distance <= 100) {
    Serial.println("Medium Distance - 3 Beeps");
    beep(3, 200, 250);
  }

  // 🟠 100 – 150 cm → 2 Beeps
  else if (distance > 100 && distance <= 150) {
    Serial.println("Medium Distance - 3 Beeps");
    beep(2, 200, 250);
  }

  // 🟡 150 – 300 cm → 1 Beeps
  else if (distance > 150 && distance <= 300) {
    Serial.println("Far Distance - 2 Beeps");
    beep(1, 200, 250);
  }

  else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(400);
}
