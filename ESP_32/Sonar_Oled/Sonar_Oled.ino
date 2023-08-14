#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


Adafruit_SSD1306 display(128, 64, &Wire, -1);

void displaySetup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();  //showing the Adafruit logo
  //do not forget display.display(); otherwise the picture will not be visible
  delay(100); //waiting 10ms
  display.clearDisplay();
  //loading screen
  display.setTextColor(WHITE); 
}




void setup() {
  Serial.begin(115200);
  displaySetup();
}

void loop() {
  Serial.print("Front: ");
  int front = Sonar(15,2);
  
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Front: ");
  display.println(front);
  Serial.println(front);
  display.display();
  display.clearDisplay();
  
  delay(200);
}



int Sonar(int trigPin, int echoPin){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  long duration;
  int distance;

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
  Serial.println(distance);

  return distance;
}

