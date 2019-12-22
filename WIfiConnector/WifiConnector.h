#include <ESP8266WiFi.h>

#ifndef WifiConnector_h
#define WifiConnector_h 
#define port 80
WiFiServer server(port);
//TODO create connection List htstName/pass/IPs
IPAddress staticIP(192, 168, 0, 140); //ESP static ip
IPAddress gateway(192, 168, 0, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask

class WifiConnector {
	private:
		float speedL, speedR;
		int httpCode, host;
		String req;
		String path;
		String responseDoc;
		unsigned long currentTime = millis();
		unsigned long previousTime = 0; 
		long timeoutTime = 2000;
		String getResponseStatus(int code);
		void configWiFi();
	public:
		WiFiClient client;
		void openAccessPoint();
		void connect(char* ssid, char* password);
		void setup();
		void activate();
		String getRequest();
		String getPath();
		void doResponce();
		void setSpeedLeft(float spped);
		void setSpeedRight(float spped);
		void doResponce(int status);
		WifiConnector(String response_arg, int httpCode_arg, long timeoutTime_arg) {
			responseDoc = response_arg;
			httpCode = httpCode_arg;
			timeoutTime = timeoutTime_arg;
		}
		WifiConnector(String response_arg) {
			responseDoc = response_arg;
			httpCode = 200;
		}
}; 

void WifiConnector::setup() {
}


void WifiConnector::activate() {
	client = server.available();
	if (!client) {
		return;
	}
	// Serial.println("new client");
	while(!client.available()) {
		delay(1);
	}
	// Read the first line of the request
	req = client.readStringUntil('\r');
	// Serial.println();
	// Serial.println(req);
	client.flush();

	if (req.indexOf("GET") != -1) {
		doResponce();					
	} else {
		doResponce(200);
	}
}

void  WifiConnector::doResponce() {
	if (client) {
		client.println(getResponseStatus(httpCode));  
		client.println(responseDoc); 
	}
}

void  WifiConnector::doResponce(int status) {
	if (client) {
		client.println(getResponseStatus(status)); 
		client.print("{"); 
		client.print("speedL:"); 
		client.print(speedL); 
		client.print(", speedR:"); 
		client.print(speedR); 
		client.print("}\n\n"); 
	}
}

String WifiConnector::getResponseStatus(int code) {
	return 	"HTTP/1.1 " + String(code) + " OK\n"+
			"Content-type:text/html\n"+
			"Connection: Keep-Alive\n\n";
}


void WifiConnector::openAccessPoint() {
	Serial.println("Setting soft-AP ... ");
	WiFi.hostname("robot-wifi");
  	WiFi.mode(WIFI_AP_STA);
	boolean result = 
		WiFi.softAPConfig(staticIP, gateway, subnet) && 
		WiFi.softAP("ESP_ROBOT");
	if(result == true) {
		Serial.println("Acces ponit Ready");
	} else {
		Serial.println("Acces ponit Failed!");
	}
	Serial.println(WiFi.localIP());
}

void WifiConnector::connect(char* ssid, char* password) {
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.mode(WIFI_STA); //WiFi mode station (connect to wifi router only
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(250);
		Serial.print(".");
	}
	// Print local IP address and start web server
	WiFi.config(staticIP, gateway, subnet);
	Serial.print("\nIP address: ");
	Serial.println(WiFi.localIP());
	server.begin();
	Serial.println("");
	Serial.println("WiFi connected.");
}

String WifiConnector::getRequest() {
	String requestData  = req;
	req = "";
	return requestData;
}

void WifiConnector::setSpeedLeft(float spped) {
	speedL = spped;
}
void WifiConnector::setSpeedRight(float spped) {
	speedR = spped;
}

String WifiConnector::getPath() {
	return path;}
#endif