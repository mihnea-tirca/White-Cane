#define ECHO_PIN 5
#define TRIGGER_PIN 6
#define VIBRATOR_PIN 3
#define MAX_DISTANCE 100.0 // maximum distance of sensor in cm
#define MAX_PWM 255.0 // Maximum value of PWM (at distance 0)
#define MIN_PWM 50.0 // Minimum value of PWM (at distance MAX_DISTANCE)
#define COUNT_NUMBER 10 // Number of times I count the distance before I process it

long duration_us; // variable for the duration of sound wave travel
int distance_now; // variable for the distance measurement
int vibratingMotorPWM; // PWM value of vibrating motor
int distance_sum = 0;
int count = 0;
int distance_average = MAX_DISTANCE;
double distance = 0;

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(VIBRATOR_PIN, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  distance = 0;
  for(count = 0; count < COUNT_NUMBER; count++){
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    duration_us = pulseIn(ECHO_PIN, HIGH);
    distance_now = duration_us * 0.034 / 2;
    if(distance_now > MAX_DISTANCE)
      distance_now = MAX_DISTANCE;

    distance = max(distance, distance_now);
    count++;
  }
  vibratingMotorPWM = exponential(distance);  
  analogWrite(VIBRATOR_PIN, vibratingMotorPWM);
  Serial.print((int)distance);
  Serial.print(" ");
  Serial.println(vibratingMotorPWM);
}

int linear(int distance){
  return MAX_PWM * (1- (float(distance)/MAX_DISTANCE));
}

//https://courses.lumenlearning.com/waymakercollegealgebra/chapter/find-the-equation-of-an-exponential-function/
int exponential(int distance){
  vibratingMotorPWM = (double)MAX_PWM * pow(MIN_PWM/MAX_PWM, distance/MAX_DISTANCE);
}