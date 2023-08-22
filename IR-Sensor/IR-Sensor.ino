
const int irSensorPin = 7;  // Analog pin for IR sensor


void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(irSensorPin, INPUT);
}

void loop() {
  int sensorValue = digitalRead(irSensorPin);  // Read the analog value from the sensor
  
  Serial.print("IR Sensor Value: ");
  Serial.println(sensorValue);  // Print the value to the Serial Monitor
  
  delay(500);  // Delay to prevent rapid readings
}
