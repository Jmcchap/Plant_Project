


int pin[]=  {D5, D6, D7, D8};

void setup() {
  // put your setup code here, to run once:

/*PinSetup*/
pinMode(D5, OUTPUT);
pinMode(D6, OUTPUT);
pinMode(D7, OUTPUT);
pinMode(D8, OUTPUT);
digitalWrite(D5, LOW);
digitalWrite(D6, LOW);
digitalWrite(D7, LOW);
digitalWrite(D8, LOW);

int sensorIndex=0;              //determines the 'active' sensor
int waterLevel[] = {0,0,0,0};   //the water level for each plant


/*Constants*/
int WaterLow = 3;     //the water level is too low and plantbro is thirsty
int WaterHigh =4;    // the water level is too high and the plantbro can't swim 
int Qty = 4;          //the number of sensors to this board

}


int readSensor(int sensorIndex){
  digitalWrite(pin[sensorIndex],HIGH);                        //turn on the sensor at sensorIndex
  int waterLevel[sensorIndex] = analogRead(sensorIndex);          //read and record the sensor value
  digitalWrite(pin[sensorIndes],LOW);                         //put the sensor back to sleep
  return();
}


void loop() {
for(int sensorIndex =0; sensorIndex < Qty; sensorIndex++){
  readSensor(sensorIndex);
}
}
