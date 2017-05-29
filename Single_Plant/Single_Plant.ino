
int waterLevel; //how much water the sensor is reading
int waterLow;   
int waterHigh;  

String tweet;   //the messgae that will be tweeted

int lowMessageIndex;
int highMessageIndex;
int qtyLowMessages =3;  // the number of "low" messages there are
int qtyHighMessages=3;  //the number of "high messgaes there are

bool messageNeeded;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(A0, INPUT);  
waterLevel =0;
waterLow = 850;    //plantbro is thirsty below this threshold
waterHigh = 500;   //any more than this and it's too much water
}

String messageLow[]=
  {"What's a plant gotta do to get some O's and H's around here?",
  "So...thirsty",
  "I guess I did want to be a cactus when I was a sprout",
  };

String messageHigh[]=
  {"Do I look like seaweed to you?",
  "I'm pretty sure I saw a fish swimming in my pot!",
  "Alright Poseidon, you can cool it now"
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

if(waterLow > waterLevel){
  messageNeeded = true;
  getMessageLow();
}
else if(waterLevel > waterHigh){
  messageNeeded = true;
  getMessageHigh();
}
else{
  messageNeeded = false;
}
delay(5000);      //delay 10 seconds
}
