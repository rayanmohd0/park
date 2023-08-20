#define BLYNK_TEMPLATE_ID "TMPL3vPdSKeQZ"
#define BLYNK_TEMPLATE_NAME "park"
#define BLYNK_AUTH "CIpJGZWORl7gduR4Z3QxNo7iKGWQp3b1"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Servo.h>

char WLAN_SSID[]="Frisk";
char WLAN_PASS[]="qwertyuiop";

#define IR_SENSOR_PARKING1_PIN  13
#define IR_SENSOR_PARKING2_PIN  12
#define IR_SENSOR_PARKING3_PIN  33
#define IR_SENSOR_PARKING4_PIN  36

#define SERVO_ENTRANCE_PIN      27
#define SERVO_EXIT_PIN          26

Servo entranceGate;
Servo exitGate;

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR_PARKING1_PIN, INPUT);
  pinMode(IR_SENSOR_PARKING2_PIN, INPUT);
  pinMode(IR_SENSOR_PARKING3_PIN, INPUT);
  pinMode(IR_SENSOR_PARKING4_PIN, INPUT);

  entranceGate.attach(SERVO_ENTRANCE_PIN);
  exitGate.attach(SERVO_EXIT_PIN);

  Blynk.begin(BLYNK_AUTH, WLAN_SSID, WLAN_PASS);
}

void loop() {
  Blynk.run();

  int sensorValueParking1 = digitalRead(IR_SENSOR_PARKING1_PIN);
  int sensorValueParking2 = digitalRead(IR_SENSOR_PARKING2_PIN);
  int sensorValueParking3 = digitalRead(IR_SENSOR_PARKING3_PIN);
  int sensorValueParking4 = digitalRead(IR_SENSOR_PARKING4_PIN);

  // Publish occupancy status to Blynk virtual pins
  
  if (sensorValueParking1==0){
    Blynk.virtualWrite(V5,"occupied");
  }
  else
  {Blynk.virtualWrite(V5,"unoccupied");
    }
  
 if (sensorValueParking2==0){
    Blynk.virtualWrite(V6,"occupied");
  }
  else
  {Blynk.virtualWrite(V6,"unoccupied");
    }
  if (sensorValueParking3==0){
    Blynk.virtualWrite(V7,"occupied");
  }
  else
  {Blynk.virtualWrite(V7,"unoccupied");
    }
  Blynk.virtualWrite(V4, sensorValueParking4);
   if (sensorValueParking4==0){
    Blynk.virtualWrite(V8,"occupied");
  }
  else
  {Blynk.virtualWrite(V8,"unoccupied");
    }
Serial.println(sensorValueParking1); 
delay(2000);   
Serial.println(sensorValueParking2);
delay(2000);
Serial.println(sensorValueParking3);
delay(2000);    
Serial.println(sensorValueParking4);
delay(2000);


  // Control entrance and exit gates based on occupancy
  if (sensorValueParking1 == HIGH || sensorValueParking2 == HIGH || 
      sensorValueParking3 == HIGH || sensorValueParking4 == HIGH) {
    openGates();
  } else {
    closeGates();
  }
}

void openGates() {
  entranceGate.write(0); // Open the entrance gate
  exitGate.write(0);     // Open the exit gate
}

void closeGates() {
  entranceGate.write(90); // Close the entrance gate
  exitGate.write(90);     // Close the exit gate
}
