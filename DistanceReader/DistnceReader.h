#ifndef DistnceReader_h
#define DistnceReader_h 

class DistnceReader {
	private:
		int trigPin, echoPin;
	public:
		void setup();
		int readDistance();
		int off();
		DistnceReader(int trigPin_arg, int echoPin_arg) {
			trigPin = trigPin_arg; 
			echoPin = echoPin_arg;
		}
}; 

void DistnceReader::setup() {
	pinMode(trigPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
	pinMode(echoPin, INPUT); //a echo, jako wejście
}

int DistnceReader::readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long time = pulseIn(echoPin, HIGH);
  return time / 58;
}


int DistnceReader::off() {
  digitalWrite(trigPin, LOW);
}

#endif