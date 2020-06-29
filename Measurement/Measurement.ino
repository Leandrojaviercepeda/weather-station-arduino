#include <DHT.h> //Library for humidity and temperature sensor
#include <RTClib.h> //Library for clock component
#include <SFE_BMP180.h> //Library for pressure sensor


/*
================================================================================
Meteorological data Measurement devices
================================================================================
*/
#define DHTPIN 3 //DHT 11 humidity and temperature sensor pin
#define DHTTYPE DHT11 //DHT 11 object
#define fc_37 A0 //fc-37 rain_intensity sensor pin
#define SDA_BMP180 20 //SDA pressure sensor pin
#define SCL_BMP180 21 //SCL pressure sensor pin


/*
================================================================================
Objects initializations
================================================================================
*/
DHT dht(DHTPIN, DHTTYPE); //Initializing humidity and temperature sensor
SFE_BMP180 bmp180; //Initializing pressure sensor
RTC_DS3231 rtc; //Initializing clock sensor

void setup() {
  
  Serial.begin(9600);

}

void loop() {
  
  //readTemperature();
  //readHumidity();
  //readPressure();
  //readUvRadiation();
  //readWindVelocity();
  //readWindDirection();
  //readRainMilimeters();
  //readRainIntensity();

}


double readTemperature(){
  /*
   * This function read the temperature using a "DHT11" sensor.
   * Returns: float temperature
   */
  
  // Read temperature as Celsius (the default)
  double temperature = dht.readTemperature();
  
  if (isnan(temperature))
    Serial.print("\nFailed to read Temperature from DHT sensor!");

  else 
    Serial.print("\nTermperature: "); Serial.print(temperature); Serial.print(" C°");

  return temperature;

}


double readHumidity(){
  /*
   * This function read the humudity using a "DHT11" sensor.
   * Returns: float humudity
   */
  
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  double humidity = dht.readHumidity();

  if (isnan(humidity))
    Serial.print("\nFailed to read Humidity from DHT sensor!");

  else 
    Serial.print("\nHumidity: "); Serial.print(humidity); Serial.print("%");

  return humidity;

}


double readPressure(){
  /*
   * This function read the pressure using a "BMP180" sensor.
   * Returns: float pressure
   * Format: Hectopascals
   */

  if (!bmp180.begin())
    Serial.print(F("\nCouldn't read pressure."));

  else {
    Serial.print(F("\nPressure sensor initialized correctly."));

    char status;
    double T,P;
    double pressure = P;

    status = bmp180.startTemperature();//Init to read temperature
    if (status != 0) {

      delay(status); //Stop to finalize read
      status = bmp180.getTemperature(T); //Get Temperature

      if (status != 0) {

        status = bmp180.startPressure(3); //Init to read pressure

        if (status != 0) {

          delay(status);//Stop to finalize read
          status = bmp180.getPressure(P,T); //Get pressure
          pressure = P;

        }
      }
    }

    Serial.print("\nPressure: "); Serial.print(pressure);
    return pressure;  

  }
  
}


double readUvRadiation(){
  /*
   * 
   */

  double uv_radiation;
  Serial.print("\nUltraviolet radiation: "); Serial.print(uv_radiation);
  return uv_radiation;

};


double readWindVelocity(){
  /*
   * 
   */

  double wind_vel;
  Serial.print("\nWind velocity: "); Serial.print(wind_vel);
  return wind_vel;

};


double readWindDirection(){
  /*
   * 
   */

  double wind_dir;
  Serial.print("\nWind direction: "); Serial.print(wind_dir);
  return wind_dir;

};


double readRainMilimeters(){
  /*
   * 
   */

  double rain_mm;
  Serial.print("\nRain milimeters: "); Serial.print(rain_mm);
  return rain_mm;

}


int readRainIntensity(){
  /*
   * This function read the rain intensity using a "fc_37" sensor.
   * Returns: int rain_intesity 
   * Consider: 
   *  That while value >= 1024, the intensity is lower.
   *  Otherwise, while the value <= 400, the intensity is higher.
   */

  int rain_intensity = analogRead(fc_37);
  Serial.print("\nRain intensity: "); Serial.print(rain_intensity);
  return rain_intensity;
  
}
