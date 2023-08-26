#include <WiFiNINA.h>
#include <ThingSpeak.h>

// Configuration for WiFi connection
const char* wifiSSID = "iPhone 13"; // Wifi name
const char* wifiPassword = "123456789"; // WiFi password

// ThingSpeak settings
channelID = 2252299;
const char* APIKey = "Q8S2VX9IVWLS0E9P";

WiFiClient client;

// Pin connected to the LDR sensor
int ldrPin = 12; // Connecting to digital pin

void setup() {
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(wifiSSID, wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Successfully connected to WiFi");

  // Initializing ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Reading digital value from LDR sensor
  int ldrValue = digitalRead(ldrPin);

  // Print the LDR value
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Setting the ThingSpeak field value
  ThingSpeak.setField(1, ldrValue);

  // Write data to ThingSpeak
  int responsecode = ThingSpeak.writeFields(channelID, APIKey);
  if (responsecode == 200) {
    Serial.println("Channel updated successful.");
  } else {
    Serial.println("Problem updating channel. HTTP error code " + String(response));
  }

  delay(200);
}
