#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define SOUND_PIN D7 // Assuming the sound detection module is connected to pin D7
#define SERVO_PIN D8 // Assuming the servo motor is connected to pin D8

char auth[] = "gvi2iLYayduOm6GMCoHlG8rdUIx799st"; // Your Blynk auth token
char ssid[] = "realme 7"; // Your WiFi network SSID
char pass[] = "manasa19"; // Your WiFi network password

Servo servo;
bool servoOn = false;

BLYNK_WRITE(V2) // this command is listening when something is written to V2
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable

  if (pinValue == 1) {
    servoOn = true;
  } else {
    servoOn = false;
  }
  Serial.print("V2 switch value is: "); // printing value to serial monitor
  Serial.println(pinValue);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(SOUND_PIN, INPUT);
  servo.attach(SERVO_PIN); // Attaching servo to pin D8
}

void loop() {
  Blynk.run();
  int soundValue = analogRead(SOUND_PIN);

  if (soundValue > 490) { // Adjust this threshold as needed
    if (!servoOn) { // If servo is not already on, turn it on
      Blynk.notify("Sound detected! Swinging the servo.");
      servoOn = true;
    }
  } else {
    servoOn = false;
  }

  if (servoOn) {
    servo.write(180); // Rotate servo to 180 degrees
    delay(100); // Wait for a short time
    servo.write(0); // Rotate servo to 0 degrees
    delay(100); // Wait for a short time
  } else {
    servo.write(0); // Stop servo when switch is off
  }

  delay(100); // Adjust delay as needed for smoother operation
}
