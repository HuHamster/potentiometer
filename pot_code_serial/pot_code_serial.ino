/*
If you use this information anywhere, please cite the source. 
YouTube: https://www.youtube.com/@HuHamster
GitHub: https://www.github.com/HuHamster
*/

// Define the pin to which the potentiometer is connected
const int POT_PIN = A0; // Use analog pin A0

// Variable to store the read value
int pot; // The value will range from 0 to 1023

void setup() {
  // Initialize serial communication
  Serial.begin(9600); // Set the baud rate to 9600
}

void loop() {
  pot = analogRead(POT_PIN); // Read the voltage level on A0
  Serial.println(sensorValue); // Print the actual reading (followed by a newline)
  delay(100); // Wait for 100 milliseconds
}