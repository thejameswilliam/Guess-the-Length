#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Stepper motor (DRV8825)
#define STEP_PIN 26
#define DIR_PIN 25

// Button
#define BUTTON_PIN 33

void setup() {
  Serial.begin(115200);

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Active LOW

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Size Does");
  display.setCursor(0, 24);
  display.println("Matter!");
  display.display();
  delay(2000);
  display.clearDisplay();
}

void moveStepper(int steps, bool direction, int delayMicro = 800) {
  digitalWrite(DIR_PIN, direction);
  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delayMicro);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delayMicro);
  }
}

void displayDistance(int steps) {
  float mm = steps * 0.1f; // Adjust this scale to match real-world distance
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Distance:");
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print(mm, 1);
  display.print(" mm");
  display.display();
}

void countdown() {
  const char* messages[] = { "3...", "2...", "1...", "ZOOM!" };
  for (int i = 0; i < 4; i++) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.setTextSize(i == 3 ? 3 : 4);
    display.setTextColor(SSD1306_WHITE);
    display.println(messages[i]);
    display.display();
    delay(i == 3 ? 500 : 700);
  }
}

void loop() {
  // Wait for button press
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("Press the button");
  display.setCursor(0, 35);
  display.println("to launch the car!");
  display.display();

  // Wait for LOW (button press)
  while (digitalRead(BUTTON_PIN) == HIGH) {
    delay(10);
  }

  // Debounce and wait for release
  delay(50);
  while (digitalRead(BUTTON_PIN) == LOW) {
    delay(10);
  }

  // Countdown sequence
  countdown();

  // Launch car
  int randomSteps = random(500, 3000);
  bool direction = true; // Always forward for now

  Serial.print("Driving ");
  Serial.print(randomSteps);
  Serial.println(" steps");

  moveStepper(randomSteps, direction);
  displayDistance(randomSteps);

  delay(4000); // Hold result before resetting
}