// Include M5Unified library
#include <M5Unified.h>

// Port.C UART pins on CoreS3
#define PORT_C_RX 18  // Port.C RX (GPIO18)
#define PORT_C_TX 17  // Port.C TX (GPIO17)

// Buffer to store received data
String receivedData = "";
int lineCount = 0;
const int MAX_LINES = 8;  // Maximum lines to display on screen

void setup() {
  // Initialize M5Unified for CoreS3
  auto cfg = M5.config();
  M5.begin(cfg);

  // Initialize USB Serial for debugging
  Serial.begin(115200);

  // Initialize Port.C UART (Serial2)
  // Baud rate: 115200, Config: 8N1 (8 data bits, No parity, 1 stop bit)
  Serial2.begin(115200, SERIAL_8N1, PORT_C_RX, PORT_C_TX);

  // Set display brightness
  M5.Display.setBrightness(128);

  // Clear screen with black background
  M5.Display.fillScreen(TFT_BLACK);

  // Set text properties
  M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
  M5.Display.setTextSize(2);

  // Display title
  M5.Display.setCursor(10, 10);
  M5.Display.println("Port.C UART Monitor");
  M5.Display.drawLine(10, 35, 310, 35, TFT_CYAN);

  // Display connection info
  M5.Display.setTextSize(1);
  M5.Display.setTextColor(TFT_YELLOW, TFT_BLACK);
  M5.Display.setCursor(10, 45);
  M5.Display.printf("Baud: 115200 | RX:G18 TX:G17");

  // Set text area for received data
  M5.Display.setTextSize(2);
  M5.Display.setTextColor(TFT_GREEN, TFT_BLACK);

  Serial.println("Port.C UART Monitor Started");
  Serial.println("Waiting for data on Port.C (GPIO18/RX, GPIO17/TX)...");
}

void loop() {
  // Update M5 state
  M5.update();

  // Check if data is available from Port.C UART
  if (Serial2.available()) {
    // Read incoming byte
    char incomingByte = Serial2.read();

    // Add to buffer
    if (incomingByte == '\n' || incomingByte == '\r') {
      // New line received, display the data
      if (receivedData.length() > 0) {
        displayData(receivedData);

        // Echo to USB Serial for debugging
        Serial.println("Received: " + receivedData);

        // Clear buffer
        receivedData = "";
      }
    } else {
      // Append character to buffer
      receivedData += incomingByte;

      // Prevent buffer overflow
      if (receivedData.length() > 100) {
        receivedData = receivedData.substring(1);
      }
    }
  }

  // Small delay for stability
  delay(10);
}

void displayData(String data) {
  // Calculate Y position for new line
  int yPos = 70 + (lineCount * 20);

  // If we've reached max lines, clear the display area and reset
  if (lineCount >= MAX_LINES) {
    M5.Display.fillRect(0, 70, 320, 240 - 70, TFT_BLACK);
    lineCount = 0;
    yPos = 70;
  }

  // Display the received data
  M5.Display.setCursor(10, yPos);
  M5.Display.setTextColor(TFT_GREEN, TFT_BLACK);
  M5.Display.setTextSize(2);

  // Truncate if too long to fit on screen
  if (data.length() > 25) {
    data = data.substring(0, 25) + "...";
  }

  M5.Display.println(data);

  lineCount++;
}
