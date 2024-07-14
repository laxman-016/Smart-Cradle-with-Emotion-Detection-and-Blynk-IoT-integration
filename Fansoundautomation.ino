 //DHT11 And NodeMCU With Blynk
//My GitHub https://github.com/manoranjan2050
//My Hackster.io https://www.hackster.io/Manoranjan2050
//This Video Link https://youtu.be/0dbws1i2GoE
#define BLYNK_PRINT Serial

// #include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define MOTOR_IN1 D5
#define MOTOR_IN2 D6
// #define SOUND_PIN D7 
const int sensor_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */
#include <DHT.h>
// #include <Servo.h>
// Servo servo;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "gvi2iLYayduOm6GMCoHlG8rdUIx799st"; // Your Blynk auth token
char ssid[] = "realme 7"; // Your WiFi network SSID
char pass[] = "manasa19"; // Your WiFi network password
 
#define DHTPIN D4          // D3
 
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
//   servo.write(150);
//  // delay(1000);
//   servo.write(0);
//   Serial.println("SERVO ROTATE");

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    // return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  // int soundValue = digitalRead(SOUND_PIN);

  // if (soundValue == HIGH) {
  //   // Send notification to Blynk app
  //   //Blynk.notify("Sound detected!");
   
  //   Serial.println("Sound detected!");
  // }
  // soundValue=LOW;
  delay(2000);
float moisture_percentage;

  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );
  float M=analogRead(sensor_pin);
  Serial.print("Soil Moisture(in Percentage) = ");
  Blynk.virtualWrite(V3, moisture_percentage);
  Serial.println(moisture_percentage);
  Serial.print(M);
  Serial.println("%");

  delay(1000);

  // if (t > 37 ){
  // // Turn on motor in forward direction
  // digitalWrite(MOTOR_IN1, HIGH);
  // digitalWrite(MOTOR_IN2, LOW);
  // }
  // else{
  //   digitalWrite(MOTOR_IN1, LOW);   // Turn fan off
  //   digitalWrite(MOTOR_IN2, LOW);
  // }
}
  BLYNK_WRITE(V1) // this command is listening when something is written to V1
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
  if (pinValue == 1){
   // do something when button is pressed;
  digitalWrite(MOTOR_IN1, HIGH);
  digitalWrite(MOTOR_IN2, LOW);
  } else if (pinValue == 0) {
   // do something when button is released;
   digitalWrite(MOTOR_IN1, LOW);   // Turn fan off
  digitalWrite(MOTOR_IN2, LOW);
  }
  
  Serial.print("V1 button value is: "); // printing value to serial monitor
  Serial.println(pinValue);
}


 
void setup()
{
  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
 
  dht.begin();
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  // pinMode(SOUND_PIN, INPUT);
  
  // servo.attach(D8); //D4
  // servo.write(0);
  // delay(1000);



  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{

  Blynk.run();
  timer.run();
}








