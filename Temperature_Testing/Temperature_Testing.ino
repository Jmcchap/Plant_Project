#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN D2   //Temperature Sensor Signal Pin
#define DHTTYPE DHT11  //becasue the sensor used is the DHT11; for DHT22, put that

float temperature = 3;  

//Initilize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void gather_data(){
  //wait the minimum 2 seconds to get a reading
  delay(2000);

  //read the temperature
  temperature = dht.readTemperature(true); //in true = Fahrenheit, because I don't feel like converting

  //make sure we're at least getting numbers
  if(isnan(temperature)){
    Serial.println("ABC error!");
    return;
  }
} 


void setup() {
  Serial.begin(9600);
  Serial.print("The temperature is... ");

  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  gather_data();
  Serial.println(temperature);
  delay(3000);
}
