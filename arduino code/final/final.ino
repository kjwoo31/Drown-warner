#include <Wire.h>
#include <SparkFun_MS5803_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4); //블루투스의 Tx, Rx핀을 1번 0번핀으로 설정
MS5803 sensor(ADDRESS_HIGH);

int Electromagnet = 10;

int warn = 0;
int t1 = 0;
int t2 = 0;
int prev_pressure_abs;

float temperature_c, temperature_f;
double pressure_abs, pressure_relative, altitude_delta, pressure_baseline;
double base_altitude = 1655.0; // Altitude of SparkFun's HQ in Boulder, CO. in (m)

void setup() {
    Serial.begin(9600);
    mySerial.begin(9600); // baud rate 9600으로 설정

    sensor.reset();
    sensor.begin();

    pressure_baseline = sensor.getPressure(ADC_4096);

    pinMode(Electromagnet, OUTPUT); 
}

void loop() {
//수압 센서 - pressure_abs
  pressure_abs = sensor.getPressure(ADC_4096);
  pressure_abs = - floor(pressure_abs - 13633);
  if(pressure_abs<0) pressure_abs=0;

//수위 센서 - level
  int level = analogRead(A1);  // 수분센서의 신호를 측정합니다.

// 1) 같은 깊이 너무 오랫동안 - 1 이상 차이 X
  if(abs(pressure_abs - prev_pressure_abs)<1) t1 = t1 + 1.5;
  if(t1>5) warn=1;
  prev_pressure_abs = pressure_abs;

// 2) 너무 깊은 깊이
  if(pressure_abs>4) t2 = t2+1.5;
  if(t2>3) warn=1;
  
// 수위 센서 닦았을 때/물 속 아닐 때 reset
  if(level < 50) {
    warn = 0;
    t1 = 0;
    t2 = 0;
  }

  if(mySerial.available())   mySerial.println(warn); 
  Serial.println(warn); 
  
  delay(1500);
  }
  
