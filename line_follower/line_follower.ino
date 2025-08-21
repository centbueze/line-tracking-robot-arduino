// Line Follower – 2 digital sensors, L298N, Arduino Uno
// Left sensor on D2, Right sensor on D3
// L298N: IN1=D8 IN2=D9 IN3=D10 IN4=D11 ENA=D5 ENB=D6

// Tune these:
const int baseSpeed = 140;     // 0..255
const int turnBoost = 80;      // extra speed difference on turns
const bool SENSOR_LOW_ON_LINE = true; // set false if your modules are opposite

// Pins
const int L_SENS = 2;
const int R_SENS = 3;

const int ENA = 5;    // left motor PWM
const int IN1 = 8;
const int IN2 = 9;

const int ENB = 6;    // right motor PWM
const int IN3 = 10;
const int IN4 = 11;

void setup() {
  pinMode(L_SENS, INPUT);
  pinMode(R_SENS, INPUT);

  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  // Both motors forward by default
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);

  analogWrite(ENA, baseSpeed);
  analogWrite(ENB, baseSpeed);
}

bool onLine(int raw) {
  // Convert sensor reading to "on line?" considering polarity
  return SENSOR_LOW_ON_LINE ? (raw == LOW) : (raw == HIGH);
}

void loop() {
  int L_raw = digitalRead(L_SENS);
  int R_raw = digitalRead(R_SENS);

  bool L_on = onLine(L_raw);
  bool R_on = onLine(R_raw);

  // Cases:
  // 1) Both on line -> go straight
  // 2) Left on line, Right off -> turn left
  // 3) Right on line, Left off -> turn right
  // 4) Both off -> keep last direction or slow straight (simple fallback)

  if (L_on && R_on) {
    analogWrite(ENA, baseSpeed);
    analogWrite(ENB, baseSpeed);
  } else if (L_on && !R_on) {
    // drift right -> steer left (slow left, speed right)
    analogWrite(ENA, max(0, baseSpeed - turnBoost));
    analogWrite(ENB, min(255, baseSpeed + turnBoost));
  } else if (!L_on && R_on) {
    // drift left -> steer right
    analogWrite(ENA, min(255, baseSpeed + turnBoost));
    analogWrite(ENB, max(0, baseSpeed - turnBoost));
  } else {
    // both off line – gentle search: slow straight
    analogWrite(ENA, baseSpeed / 2);
    analogWrite(ENB, baseSpeed / 2);
  }
}
