//Adafruit RFM95W LoRa module

#include <SPI.h> // Include the SPI library for communication with the LoRa module
#include <LoRa.h> // Include the LoRa library for sending and receiving data

int led = 13; // Define a variable for the onboard LED

void setup() {
  pinMode(led, OUTPUT); // Set the LED pin as an output
  digitalWrite(led, LOW); // Turn off the LED

  Serial.begin(115200); // Initialize the serial communication at 115200 baud rate

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (!LoRa.begin(868E6)) { // Start the LoRa module with a frequency of 868 MHz
    Serial.println("Starting LoRa failed!");
    while (1); // If the LoRa module failed to start, keep looping
  }
}

void loop() {
  digitalWrite(led, HIGH); // Turn on the LED
  delay(1000); // Wait for 1 second
  digitalWrite(led, LOW); // Turn off the LED
  delay(1000); // Wait for 1 second

  if (Serial.available()) { // If there is data available on the serial port
    String data = Serial.readString(); // Read the data as a string

    LoRa.beginPacket(); // Start a new packet to send
    LoRa.print(data); // Send the data
    LoRa.endPacket(); // End the packet
  }

  int packetSize = LoRa.parsePacket(); // Check if a packet has been received
  if (packetSize) { // If a packet has been received
    String data = ""; // Create an empty string to hold the received data
    while (LoRa.available()) { // While there is data available to read
      data += (char)LoRa.read(); // Add the data to the string
    }

    Serial.print("Received packet '"); // Print a message indicating a packet was received
    Serial.print(data); // Print the received data
    Serial.println("' with RSSI ");
    Serial.println(LoRa.packetRssi()); // Print the received signal strength indicator (RSSI) of the packet
  }
}
