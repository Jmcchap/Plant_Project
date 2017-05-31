#include <ESP8266HTTPClient.h>

//#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>

/*THE MESSAGES*/
String messageLow[]=
  {"What's a plant gotta do to get some O's and H's around here?",
  "So...thirsty",
  "I guess I did want to be a cactus when I was a sprout",
  "Ooooh! I need some milk! I mean...water",
  "I'm thirsty, if you know what I mean"
  };

String messageHigh[]=
  {"Do I look like seaweed to you?",
  "I'm pretty sure I saw a fish swimming in my pot!",
  "Alright Poseidon, you can cool it now",
  "Blub...blub...blub",
  };

 int lowMessageIndex;
int highMessageIndex;
int qtyLowMessages =5;  // the number of "low" messages there are
int qtyHighMessages=4;  //the number of "high messgaes there are

/*THINGSPEAK SETTINGS*/
char thingSpeakAddress[] = "api.thingspeak.com";
String APIKey = "**********";          //the api key, duh
IPAddress server(184,106,153,149);

/*Variables*/
int waterLevel; //how much water the sensor is reading
int waterLow;   
int waterHigh;  

String tweet;   //the messgae that will be tweeted



bool messageNeeded;     //to know if there should be a tweet or not





//I don't really understand this block
WiFiClient espClient;
HTTPClient httpClient;
//PubSubClient client(espClient);




//connect to WiFi network
void setup_wifi(){

  Serial.println("Starting wireless.");
  WiFiManager wifiManager; //Load the Wi-Fi Manager library.
  wifiManager.setTimeout(300); //Give up with the AP if no users gives us configuration in this many secs.
  if(!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    ESP.restart();
  }
  
  Serial.println("");
  Serial.print("Successfully connected to ");
  Serial.println(WiFi.localIP());
}


//reconnect if wifi is lost
void reconnect(){
 Serial.println("Oh no! Lost connection!"); 
 
 while(!espClient.connected()) {
  Serial.print("One moment, please...");
  
  if(espClient.connect(server, 80)){
    Serial.println("There we go!");                                    //If there is a successful reconnection
        
    
  }else {
    Serial.print("Well, dra3t. The issue seems to be: ur dumb ");
    Serial.println("Trying again in a jiffy");
    //Wait a jiffy seconds and retry connecting
    delay(3340);
  }
 }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Begin!");
  pinMode(A0, INPUT); 
  pinMode(D5, OUTPUT);    //turning on/off the sensor
  digitalWrite(D5, LOW);  //the sensor is off
waterLevel =0;     
waterLow = 850;    //plantbro is thirsty below this threshold
waterHigh = 500;   //any more than this and it's too much water
  

setup_wifi();
if(messageNeeded == true){
   updateTwitterStatus(tweet);
   messageNeeded == false;
}
}


void getMessageLow(){
  lowMessageIndex = random(0,qtyLowMessages);
  tweet = messageLow[lowMessageIndex];
}

void getMessageHigh(){
  highMessageIndex = random(0, qtyHighMessages);
  tweet = messageHigh[highMessageIndex];
}

void updateTwitterStatus(String tsData){
  if (espClient.connect(thingSpeakAddress, 80)){ 
    // Create HTTP POST Data
    tsData = "api_key="+ APIKey+ "&status="+ tsData;
            
    espClient.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
    espClient.print("Host: api.thingspeak.com\n");
    espClient.print("Connection: close\n");
    espClient.print("Content-Type: application/x-www-form-urlencoded\n");
    espClient.print("Content-Length: ");
    espClient.print(tsData.length());
    espClient.print("\n\n");

    espClient.print(tsData);
  }
}

void loop(){

digitalWrite(D5, HIGH);           //turn the sensor on
delay(200);                       //wait to let the sensor read
waterLevel = analogRead(A0);      //read what the sensor says
Serial.println(waterLevel);      
digitalWrite(D5, LOW);          //turn the sensor back off

if(waterLow < waterLevel){      //if the water level is too low
  messageNeeded = true;
  getMessageLow();              //get a low message to tweet
}
else if(waterLevel < waterHigh){  //if the water level is too high
  messageNeeded = true;
  getMessageHigh();           //get a high message to tweet
}
else{
  messageNeeded = false;      //otherwise, don't tweet anything
}
  
  
if(messageNeeded == true){       //if a tweet is needed to be made
    if(!espClient.connected()){  //connect to the web if you're not
  reconnect();
 }
  updateTwitterStatus(tweet);   //tweet the tweet
  Serial.println(tweet);
   messageNeeded == false;      //'reset' the 'flag'
}

delay(86400000);      //delay 24hours
}

