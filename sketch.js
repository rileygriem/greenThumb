const serviceUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";
let ble;
let soilMoistureCharacteristic;
let soilMoisturePercentage = 0;

function setup() {
  createCanvas(400, 200);
  
  ble = new p5ble();

  // Set up a button to start the connection
  const connectButton = createButton('Connect to Arduino');
  connectButton.mousePressed(connectToArduino);

  // Create a placeholder for the soil moisture percentage
  text("Soil Moisture Percentage: ", 20, height / 2);
}

function draw() {
  background(220);

  // Display the soil moisture percentage
  textSize(20);
  text("Soil Moisture Percentage: " + soilMoisturePercentage + "%", 20, height / 2);
}

function connectToArduino() {
  // Search for the Arduino Nano 33 BLE
  ble.connect(serviceUuid, gotCharacteristics);
}

function gotCharacteristics(error, characteristics) {
  if (error) {
    console.log('Error:', error);
    return;
  }

  for (let characteristic of characteristics) {
    // Check for the matching characteristic UUID
    if (characteristic.uuid === '19b10002-e8f2-537e-4f6c-d104768a1214') {
      soilMoistureCharacteristic = characteristics[0];
      soilMoistureCharacteristic.startNotifications(gotSoilMoisture);
      console.log('Soil moisture characteristic found!');
      console.log(characteristics)
    }
  }
}

function gotSoilMoisture(data) {
  // Parse the received data as a float (percentage)
  soilMoisturePercentage = data.getFloatValue();
  console.log(data);
}
