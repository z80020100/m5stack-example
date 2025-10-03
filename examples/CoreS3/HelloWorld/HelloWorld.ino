// Include M5Unified library
#include <M5Unified.h>

void setup() {
  // Initialize M5Unified for CoreS3
  auto cfg = M5.config();
  M5.begin(cfg);

  // Set display brightness (CoreS3 has 320x240 display)
  M5.Display.setBrightness(128);

  // Clear screen with black background
  M5.Display.fillScreen(TFT_BLACK);

  // Set text properties
  M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Display.setTextDatum(middle_center);
  M5.Display.setTextSize(3);

  // Display "Hello World" in the center of CoreS3 screen (320x240)
  M5.Display.drawString("Hello World!", M5.Display.width() / 2, M5.Display.height() / 2);

  // Print to serial monitor
  Serial.println("Hello World from CoreS3!");
}

void loop() {
  // Update M5 state
  M5.update();

  // Simple delay
  delay(100);
}
