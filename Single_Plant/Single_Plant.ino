/*Variables*/
int waterLevel; //how much water the sensor is reading
int waterLow;   
int waterHigh;  

String tweet;   //the messgae that will be tweeted

int lowMessageIndex;
int highMessageIndex;
int qtyLowMessages =4;  // the number of "low" messages there are
int qtyHighMessages=4;  //the number of "high messgaes there are

bool messageNeeded;     //to know if there should be a tweet or not



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0, INPUT);  
waterLevel =0;     
waterLow = 850;    //plantbro is thirsty below this threshold
waterHigh = 500;   //any more than this and it's too much water
}

/*THE MESSAGES*/
String messageLow[]=
  {"What's a plant gotta do to get some O's and H's around here?",
  "So...thirsty",
  "I guess I did want to be a cactus when I was a sprout",
  "Ooooh! I need some milk! I mean...water"
  };

String messageHigh[]=
  {"Do I look like seaweed to you?",
  "I'm pretty sure I saw a fish swimming in my pot!",
  "Alright Poseidon, you can cool it now",
  "Blub...blub...blub"
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
  // put your main code here, to run repeatedly:
waterLevel = analogRead(A0);      //read what the sensor says
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
