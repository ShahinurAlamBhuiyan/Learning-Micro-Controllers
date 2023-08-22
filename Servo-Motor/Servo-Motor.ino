
#include <Servo.h> // servo motor code

Servo myservo;  // Create a Servo object

void setup() {
  myservo.attach(9);  // Attach the servo to pin 9
}

void loop() {
  // Rotate servo to 0 degrees
  myservo.write(0);
  delay(1000);  // Wait for 1 second
  
  // Rotate servo to 90 degrees
  myservo.write(180);
  delay(1000);  // Wait for 1 second
  
  // Rotate servo to 180 degrees
  myservo.write(180);
  delay(100);  // Wait for 1 second
}
