#include <ESP8266HTTPClient.h>

//#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>


IPAddress server(184,106,153,149);

//I don't really understand this block
WiFiClient espClient;
HTTPClient httpClient;
//PubSubClient client(espClient);

// ThingSpeak Settings
char thingSpeakAddress[] = "api.thingspeak.com";
String APIKey = "XXX";          //the api key, duh


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
  

setup_wifi();
   updateTwitterStatus("Hello, Sunshine \u1F331 #PlantsInc");
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
   if(!espClient.connected()){
  reconnect();
 }
 
}

