/*Variables*/
int waterLevel; //how much water the sensor is reading
int waterLow;   
int waterHigh;  

String tweet;   //the messgae that will be tweeted

int lowMessageIndex;
int highMessageIndex;
int qtyLowMessages =8;  // the number of "low" messages there are
int qtyHighMessages=8;  //the number of "high messgaes there are

bool messageNeeded;     //to know if there should be a tweet or not



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0, INPUT);   
pinMode(D5, OUTPUT);  //to turn on the sensor
digitalWrite(D5, LOW);   //"off"
waterLevel =0;     
waterLow = 850;    //plantbro is thirsty below this threshold
waterHigh = 500;   //any more than this and it's too much water
}

/*THE MESSAGES*/
String messageLow[]=
  {"What's a plant gotta do to get some O's and H's around here?",
  "So...thirsty",
  "I guess I did want to be a cactus when I was a sprout",
  "Ooooh! I need some milk! I mean...water",
  "My future perch is parched!",
  "I'm drying over here!",
  "1-800-GET-WATER",
  "Someone please shame @Jmcchap into watering me!"
  };

String messageHigh[]=
  {"Do I look like seaweed to you?",
  "I'm pretty sure I saw a fish swimming in my pot!",
  "Alright Poseidon, you can cool it now",
  "Blub...blub...blub",
  "WATER you doing?",
  "H20h no more water for me, kthx",
  "Where's the fire? 'Cause you need to put this extra water there",
  "Leaf me alone!"
  };


void getMessageLow(){
  lowMessageIndex = random(0,qtyLowMessages);
  tweet = messageLow[lowMessageIndex];
}

void getMessageHigh(){
  highMessageIndex = random(0, qtyHighMessages);
  tweet = messageHigh[highMessageIndex];
}

void loop() {
  
digitalWrite(D5, HIGH);           //turn on the sensor
delay(200);                       //wait to let the sensor get values
waterLevel = analogRead(A0);      //read what the sensor says
digitalWrite(D5, LOW);            //turn off the sensor
Serial.println(waterLevel);      

if(waterLow > waterLevel){      //if the water level is too low
  messageNeeded = true;
  getMessageLow();              //get a low message to tweet
}
else if(waterLevel > waterHigh){  //if the water level is too high
  messageNeeded = true;
  getMessageHigh();           //get a high message to tweet
}
else{
  messageNeeded = false;      //otherwise, don't tweet anything
}
delay(5000);      //delay 5 seconds
}
