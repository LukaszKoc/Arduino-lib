
#ifndef SerialLink_h
#define SerialLink_h 
 
#include <SoftwareSerial.h>
 
#define BAUD_RATE 9600

#define MSG_START_MARK "#"
#define MSG_OVER_MARK "$"

int MSG_LABELS_COUNT = 2;
String MSG_LABELS[] = {"SPEED", "DIRESTIONS"};

SoftwareSerial serialToRemote;    

class SerialLink {
  private:
    bool printData = false;
    void readMessageData(String msg, int &x, int &y);
    int find(String arr[], String value);
  public:
    String read();
    void read(int &x, int &y);
    void write(String message);
    void write(float speedL, float speedR);
    String midString(String str, String start, String finish);
    void setup(int baudRate);
    SerialLink(bool print_data = false){
      printData = print_data;
    }
}; 

void SerialLink::setup (int baudRate = BAUD_RATE) {
  Serial.print("SerialLink setup for ");
    Serial.println("NodeMcu");
  serialToRemote.begin(BAUD_RATE, SWSERIAL_8N1, RX_PIN, TX_PIN, false, 95, 11);
  Serial.println("\nSoftware serial test started");
}

void SerialLink::write(String message) {
  message = MSG_START_MARK + message + MSG_OVER_MARK + "\n";
  char copy[50];
  message.toCharArray(copy, 50);
    for (int i = 0; i < 50 && copy[i] != '\n'; i++) {
        serialToRemote.write(copy[i]);
    }
    serialToRemote.flush();
    delay(1);
    yield();
    return;
}

String SerialLink::read() {
  String temp = "";
  String msg = "-1";

  for(char in; serialToRemote.available() > 0;) {
    in = serialToRemote.read();
    temp += String(in);
    Serial.print(in);
  }
  if(temp != "") {
    msg = temp;
  }
  serialToRemote.flush();
  msg = midString(msg, MSG_START_MARK, MSG_OVER_MARK);
  delay(1);
  yield();
  return msg;
}


void SerialLink::read(int &x, int &y) {
  String msg = read();
  readMessageData(msg, x, y);
  // switch (find(MSG_LABELS, midString(msg, "[", ":"))) {
  // case 0: //SPEED
  //   readMessageData(msg, x, y);
  //   break;
  // case 1: //DIRECTIONS 
  //   readMessageData(msg, x, y);
  //   break;
  // default:
  //   write("Invalid message type: " + midString(msg, "[", ":"));
  //   break;
  // }  
  delay(200);

}

void SerialLink::readMessageData(String msg, int &x, int &y) {
  x = midString(msg, ":", ";").toInt();
  y = midString(msg, ":", ".").toInt();
}

void SerialLink::write(float speedL, float speedR) {
    String msg = String("{SPEED:") + speedL + ";" + speedR+ "}";
    write(msg);
}


String SerialLink::midString(String str, String start, String finish) {
  int locStart = str.indexOf(start);
  if (locStart == -1) return "null";
  locStart += start.length();
  int locFinish = str.indexOf(finish, locStart);
  if (locFinish == -1) return "null";
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