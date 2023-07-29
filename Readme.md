https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json


Tutorial:https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/

sonar https://howtomechatronics.com/tutorials/arduino/ultrasonic-sensor-hc-sr04/


code
 int trigPin = 2;
 int echoPin = 4;
// defines variables
long duration;
int distance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(36000); // Starts the serial communication
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
}
