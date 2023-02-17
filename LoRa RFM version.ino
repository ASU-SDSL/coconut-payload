#include <SPI.h>
#include <Adafruit_RFM95.h>

//Define the pin connections for the RFM95 module
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

Adafruit_RFM95 rfm95;

void setup() {
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, LOW);

  // Wait for the module to be ready
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  // Initialize the RFM95 module
  if (!rfm95.begin(RFM95_CS, RFM95_INT)) {
    Serial.println("RFM95 module not detected!");
    while (1);
  }
  rfm95.setFrequency(868E6);
  rfm95.setTxPower(20, false);
}

void loop() {
  // Send a packet
  char packet[] = "Hello, World!";
  rfm95.beginPacket();
  rfm95.write(packet, sizeof(packet));
  rfm95.endPacket();

  Serial.println("Packet sent: ");
  Serial.println(packet);

  // Wait for a packet to be received
  int packetSize = rfm95.parsePacket();
  if (packetSize) {
    char receivedPacket[packetSize + 1];
    rfm95.read(receivedPacket, packetSize);
    receivedPacket[packetSize] = 0;

    Serial.println("Packet received:");
    Serial.println(receivedPacket);
  }
}
/*
This code uses the Adafruit_RFM95 library to communicate with the RFM95 LoRa module. In the setup function, it initializes the RFM95 module and sets the frequency to 868 MHz.
In the loop function, it sends a packet with the string "Hello, World!" and print the sent packet to the serial monitor. It then waits for a packet to be received, 
and when it is, it reads the packet and print the received packet to the serial monitor.
*/