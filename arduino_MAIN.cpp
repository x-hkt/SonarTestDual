#include<Servo.h>

#define S1_TRIG 6
#define S2_TRIG 5
#define S1_ECHO 12
#define S2_ECHO 3

/**//*--- servo parameters for `servoObject_surf`
#define MIN_SERVO_ANGLE_SERVO_SURF 30
//  ---*/

//  ...
/*--- servo parameters for `servoObject_mv`
#define SERVO_MV_STOPPED_MIDPOINT 88
#define SERVO_MV_X_DELTA 10
// ---*/

// /*--- for trigonometry
// used for HC-SR04 sensors

#define SURF_READ_TRIG_VALUE_A 5.5
#define SURF_READ_DELTA_SHIFT -2.4

// ---*/

//--- Servo servoObject_surf;
// TMP H DBG
/*---
Servo servoObject_mv;
// ---*/

void setup() {
  //_todo
  Serial.begin(9600);
  // servos
  /*---
  servoObject_surf.attach(11);
  servoObject_surf.write(MIN_SERVO_ANGLE_SERVO_SURF);
  ---*/
  //- servoObject_mv.attach(9);
  //..
  //-servoObject_mv.write(SERVO_MV_STOPPED_MIDPOINT);
  /*---
  ---*/
  //--
  // i am an idiot
  pinMode(S1_TRIG, OUTPUT); // Sets the trigPin as an Output
  pinMode(S1_ECHO, INPUT); // Sets the echoPin as an Input
  pinMode(S2_TRIG, OUTPUT); // Sets the trigPin as an Output
  pinMode(S2_ECHO, INPUT); // Sets the echoPin as an Input
}

//- void continuousservo_ServoObjectMV_GFWD() { servoObject_mv.write(SERVO_MV_STOPPED_MIDPOINT+SERVO_MV_X_DELTA); }
//- void continuousservo_ServoObjectMV_BKWD() { servoObject_mv.write(SERVO_MV_STOPPED_MIDPOINT-SERVO_MV_X_DELTA); }
//- void continuousservo_ServoObjectMV_STOP() { servoObject_mv.write(SERVO_MV_STOPPED_MIDPOINT); }

double surfRead_calcThetaValue(double s2dist) {
  return atan((s2dist+SURF_READ_DELTA_SHIFT)/SURF_READ_TRIG_VALUE_A);
}

void loop() {
  //_todo
  // true DBG
  // ((nvm))
  // true DBG
  /*-
  for (int i = MIN_SERVO_ANGLE_SERVO_SURF; i < 180; i += 10) {
    Serial.print("set: ");
    Serial.println(i);
    servoObject_surf.write(i);
    delay(1000);
  }
  for (int i = 180; i >= MIN_SERVO_ANGLE_SERVO_SURF; i -= 10) {
    Serial.print("set: ");
    Serial.println(i);
    servoObject_surf.write(i);
    delay(1000);
  }
  // true DBG -*/
  // DBG
  /*-
  double s1dist = getHCSR04distance(true);
  double s2dist = getHCSR04distance(false);
  Serial.print(double2string(s1dist, 4));
  Serial.print(" & ");
  Serial.print(double2string(s2dist, 4));
  Serial.println(" <END>");
  delay(500);
  // DBG -*/
  // .. .. .. .. .. sw_
  // MAIN BEGIN
  run_iterOutputSerialized();
  // MAIN END
}

void run_iterOutputSerialized() {
  //:read (/4) c
  double s1dist = getHCSR04distance(true);
  delay(50);
  double s2dist = getHCSR04distance(false);
  delay(50);
  //:proc (/2) c
  // WAS EQUIVALENT - double s2theta = atan((s2dist+SURF_READ_DELTA_SHIFT)/SURF_READ_TRIG_VALUE_A);
  double s2theta_inRadians = surfRead_calcThetaValue(s2dist);
  double s2theta_degs = (s2theta_inRadians/PI)*180;
  //-----
  // [...] @Angle [...] <Entry>
  //-----
  Serial.print("[");
  Serial.print(
    (s1dist <= 50) ? "b#False" : "b#True"
  );
  Serial.print("] \t@Angle [");
  Serial.print(double2string(90-s2theta_degs, 4));
  // DBG - Serial.print("|");
  // DBG - Serial.print(double2string(s2dist, 2));
  Serial.println("] <Entry>");
  delay(100);
}

double getHCSR04distance(boolean is_sensor_1) {
  //- DBG OLD Serial.println("::start");
  //:def ((nvm))
  // int OtrigPin = is_sensor_1 ? S1_TRIG : S2_TRIG;
  // int OechoPin = is_sensor_1 ? S1_ECHO : S2_ECHO;
  //.. -|
  //    |
  //    |-> end
  //:run
  // Clears the trigPin
  digitalWrite(is_sensor_1 ? S1_TRIG : S2_TRIG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(is_sensor_1 ? S1_TRIG : S2_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(is_sensor_1 ? S1_TRIG : S2_TRIG, LOW);
  //- DBG OLDL Serial.println("::read");
  // Reads the echoPin, returns the sound wave travel time in microseconds
  double duration = pulseIn(is_sensor_1 ? S1_ECHO : S2_ECHO, HIGH);
  //- DBG OLD Serial.print("end with ");
  //- DBG OLD Serial.println(duration);
  // Calculating the distance
  double distance = duration*0.034/2;
  //+cooldown /*-
  delay(50);
  //-cooldown -*/
  return distance;
}

// cp~
String double2string(double n, int ndec) {
    String r = "";
    int v = (int) n;
    r += v;     // whole number part
    r += '.';   // decimal point
    int i;
    for (i=0;i<ndec;i++) {
        // iterate through each decimal digit for 0..ndec 
        n -= v;
        n *= 10; 
        v = n;
        r += abs(v);
    }

    return r;
}
