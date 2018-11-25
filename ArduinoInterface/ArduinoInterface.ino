int channel1 = 12;
int channel2 = 11;
int channel3 = 10;
int channel4 = 9;
int channel5 = 8;
int channel6 = 7;

int pwm_value;

void setup()
{
  pinMode(channel1, INPUT);
  pinMode(channel2, INPUT);
  pinMode(channel3, INPUT);
  pinMode(channel4, INPUT);
  pinMode(channel5, INPUT);
  pinMode(channel6, INPUT);
  Serial.begin(230400);
}

void loop()
{
  pwm_value = pulseIn(channel3, HIGH);      // Channel 3 is throttle
  Serial.print(pwm_value);
  Serial.print(" ");
  pwm_value = pulseIn(channel4, HIGH);      // Channel 4 is Yaw
  Serial.print(pwm_value);
  Serial.print(" ");
  pwm_value = pulseIn(channel2, HIGH);      // Channel 2 is Pitch
  Serial.print(pwm_value);
  Serial.print(" ");
  pwm_value = pulseIn(channel1, HIGH);      // Channel 1 is Roll
  Serial.print(pwm_value);
  Serial.print(" ");
  pwm_value = pulseIn(channel5, HIGH);
  Serial.print(pwm_value);
  Serial.print(" ");
  pwm_value = pulseIn(channel6, HIGH);
  Serial.print(pwm_value);
  Serial.print("\n");
}