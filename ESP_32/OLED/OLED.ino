#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();  //showing the Adafruit logo
  //do not forget display.display(); otherwise the picture will not be visible
  delay(100); //waiting 10ms
  display.clearDisplay();
  //loading screen
  display.setTextColor(WHITE); 
}

void loop() {

  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("JHSTC");
  ;

  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print("Computer Science & Engineering");
  
  display.display();
  delay(2000);
  
}

