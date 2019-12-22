
#ifndef SerialLink_h
#define SerialLink_h 
#include <SoftwareSerial.h>

SoftwareSerial serialToRemote(RX_PIN, TX_PIN);
int MSG_LABELS_COUNT = 2;
String MSG_LABELS[] = {"SPEED", "DIRECTIONS"};

class SerialLink {
  private:
    void readMessageData(String msg, int &x, int &y);
    int find(String arr[], String value);
  public:
    String readMessage();
    void readMessage(int &x, int &y);
    void writeMessage(String message);
    void writeCurrentSpeed(float speedL, float speedR);
    String midString(String str, String start, String finish);
    void setup(int baudRate);
}; 


void SerialLink::setup (int baudRate) {
  serialToRemote.begin(baudRate);
  while (!Serial) {
    delay(10); // wait for serial port to connect. Needed for Native USB only
  }   
  serialToRemote.flush();
}

String SerialLink::readMessage() {
 return serialToRemote.readString();

}

void SerialLink::readMessage(int &x, int &y) {
  String msg = readMessage();
  switch (find(MSG_LABELS, midString(msg, "[", ":"))) {
  case 0: //SPEED
    readMessageData(msg, x, y);
    break;
  case 1: //DIRECTIONS 
    readMessageData(msg, x, y);
    break;
  default:
    Serial.println("Invalid message type: " + midString(msg, "[", ":"));
    break;
  }
}

void SerialLink::readMessageData(String msg, int &x, int &y) {
  x = midString(msg, ":", ";").toInt();
  y = midString(msg, ":", ".").toInt();
}

void SerialLink::writeCurrentSpeed(float speedL, float speedR) {
    String msg = String("{SPEED:") + speedL + ";" + speedR+ "}";
    writeMessage(msg);
}

void SerialLink::writeMessage(String message) {
    Serial.print(message);
}

String SerialLink::midString(String str, String start, String finish) {
  int locStart = str.indexOf(start);
  if (locStart == -1) return "";
  locStart += start.length();
  int locFinish = str.indexOf(finish, locStart);
  if (locFinish == -1) return "";
  return str.substring(locStart, locFinish);
}

int SerialLink::find(String arr[], String value) {
  for (int i=0; i < MSG_LABELS_COUNT; i++) {
     if (value = arr[i]) {
       return i;
     }
  }
  return -1;
}

#endif