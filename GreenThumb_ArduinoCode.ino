#include <ArduinoBLE.h>

const int soilMoisturePin = A0;

BLEService soilMoistureService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Custom service UUID
BLEFloatCharacteristic soilMoistureCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

void setup() {
  Serial.begin(9600);
  //FROM EXAMPLE CODE
  while (!Serial);

  pinMode(soilMoisturePin, INPUT);

  // FROM OLD CODE
  //BLE.begin();

  //FROM EXAMPLE CODE
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  BLE.setLocalName("SoilMoistureSensor");

  BLE.setAdvertisedService(soilMoistureService);

  soilMoistureService.addCharacteristic(soilMoistureCharacteristic);

  BLE.addService(soilMoistureService);

  //was soilMoistureCharacteristic.setValue(0.0);
  soilMoistureCharacteristic.writeValue(0); // Initialize to 0%

  BLE.advertise();

  Serial.println("Bluetooth® device active, waiting for connections...");

}

void loop() {

// FOR TESTING WITHOUT BLUETOOTH
  // int rawValue = analogRead(soilMoisturePin);

  //   float moisturePercentage = map(rawValue, 0, 1023, 100, 0);

  //   Serial.print("Moisture Value: ");
  //   Serial.print(rawValue);
  //   Serial.print(" Moisture Percentage: ");
  //   Serial.println(moisturePercentage);

  //   delay(1000);
// END TESTING

  //EXAMPLE CODE HAD THIS IDK WHAT IT DOES
  //BLE.poll();


  BLEDevice central = BLE.central();

  if (central) {
    while (central.connected()) {
      // Read soil moisture level from sensor and convert it to a percentage
      int rawValue = analogRead(soilMoisturePin);

      float moisturePercentage = map(rawValue, 0, 1023, 0, 100);

      Serial.print("Moisture Value: ");
      Serial.print(rawValue);
      Serial.print(" Moisture Percentage: ");
      Serial.println(moisturePercentage);

      // Update the BLE characteristic with the moisture percentage
      soilMoistureCharacteristic.writeValue(moisturePercentage);

      delay(1000);
    }
  }
}
