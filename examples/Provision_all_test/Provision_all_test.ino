/*
    This sketch shows users how to use the provisioning library for WiFi
*/

#include <ArduinoJson.h>    // https://github.com/bblanchon/ArduinoJson
#include <xProvision.h>     // https://github.com/xinabox/arduino-Provision    

xProvision prv;
String ssid, password;
String yourName;
String broker, port;
String ubidotsToken, azureToken, blynkToken, cloudToken;

void setup() {
  // Set RGB Pins as outputs
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // put your setup code here, to run once:
  prv.begin();
  prv.addWiFi();
  prv.addMQTT();
  prv.addUbiDotsToken();
  prv.addAzureToken();
  prv.addBlynkToken();
  prv.addCloudToken();
  prv.addVariable("Name", "Your_Name");
  prv.optionBlinkLED();

  prv.transmit();
  //Writes this string, with the CRLF and SYNC prefixed and CRLF suffixed
  //$!${"WiFi_Network":"YourSSID","WiFi_Password":"YourPSK","MQTT_Server":"ServerHostname","MQTT_Port":"ServerPort","UbiDots_Token":"YourUbitdotsToken","Azure_Token":"YourAzureToken","Blynk_Token":"YourBlynkToken","Cloud_Token":"YourCloudToken","Name":"Your_Name","LED_to_blink":["Red","Green","Blue"]}


  prv.receive();
  //Reads this string, with CRLF suffixed
  //{"WiFi_Network":"YourSSID","WiFi_Password":"YourPSK","MQTT_Server":"ServerHostname","MQTT_Port":"ServerPort","UbiDots_Token":"YourUbitdotsToken","Azure_Token":"YourAzureToken","Blynk_Token":"YourBlynkToken","Cloud_Token":"YourCloudToken","Name":"Your_Name","LED_to_blink":["Red","Green","Blue"]}


  if (prv.success())
  {
    prv.getWiFi(ssid, password);
    prv.getMQTT(broker, port);
    prv.getUbiDotsToken(ubidotsToken);
    prv.getAzureToken(azureToken);
    prv.getBlynkToken(blynkToken);
    prv.getCloudToken(cloudToken);
    prv.getVariable("Name", yourName);
    prv.enableLED();

    WiFi.begin(ssid.c_str(), password.c_str());

    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_RED, HIGH);
      delay(250);
      digitalWrite(LED_RED, LOW);
      delay(250);
    }
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(LED_GREEN, HIGH);
  }
  else
  {
    prv.fail();
  }
}

void loop()
{
  Serial.println("Name: ");
  Serial.println(yourName);
  Serial.println("Ubidots token: ");
  Serial.println(ubidotsToken);
  Serial.println("Azure token: ");
  Serial.println(azureToken);
  Serial.println("Blynk token: ");
  Serial.println(blynkToken);
  Serial.println("Cloud token: ");
  Serial.println(cloudToken);

  prv.BlinkLED();
}
