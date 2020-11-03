#include <Wire.h>
#include <SparkFun_MS5803_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); //블루투스의 Tx, Rx핀을 2번 3번핀으로 설정
MS5803 sensor(ADDRESS_HIGH);
int ledPin = 10; // LED connected to digital pin 10

//Create variables to store results
float temperature_c, temperature_f;
double pressure_abs, pressure_relative, altitude_delta, pressure_baseline;

// Create Variable to store altitude in (m) for calculations;
double base_altitude = 1655.0; // Altitude of SparkFun's HQ in Boulder, CO. in (m)

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600); // baud rate 9600으로 설정


    sensor.reset();
    sensor.begin();
    
    pressure_baseline = sensor.getPressure(ADC_4096);

    pinMode(ledPin, OUTPUT);      // sets the digital pin 10 as output
    digitalWrite(ledPin, LOW);    // set the LED off
    
}

void loop() {

//수압 센서
  // Read pressure from the sensor in mbar.
  pressure_abs = sensor.getPressure(ADC_4096);
  pressure_relative = sealevel(pressure_abs, base_altitude);
  altitude_delta = altitude(pressure_abs , pressure_baseline);
  
  // Report values via UART
  mySerial.print("Pressure abs (mbar)= ");
  mySerial.println(pressure_abs);
   
//  mySerial.print("Pressure relative (mbar)= ");
//  mySerial.println(pressure_relative); 
  
//  mySerial.print("Altitude change (m) = ");
//  mySerial.println(altitude_delta); 

//수위 센서
  int level = analogRead(A1);  // 수분센서의 신호를 측정합니다.
  mySerial.println(level);   //시리얼 모니터에 값을 출력합니다.

//전도성 고무줄 센서
  int rubberVal = analogRead(A0);
  Serial.println(rubberVal);

  delay(1000);

//LED
  if(pressure_abs>0 & level>400){
      digitalWrite(ledPin, HIGH);    // set the LED on
  }
  else{
      digitalWrite(ledPin, LOW);    // set the LED off
  }

  }

 double sealevel(double P, double A)
// Given a pressure P (mbar) taken at a specific altitude (meters),
// return the equivalent pressure (mbar) at sea level.
// This produces pressure readings that can be used for weather measurements.
{
	return(P/pow(1-(A/44330.0),5.255));
}


double altitude(double P, double P0)
// Given a pressure measurement P (mbar) and the pressure at a baseline P0 (mbar),
// return altitude (meters) above baseline.
{
	return(44330.0*(1-pow(P/P0,1/5.255)));
}
  
