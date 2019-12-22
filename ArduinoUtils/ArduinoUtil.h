#ifndef ArduinoUtil_h
#define ArduinoUtil_h 

class ArduinoUtil {
	public:
		static void endLoop(int duration);
		static int mathAbs(int value);
	
}; 

void ArduinoUtil::endLoop(int duration = 500) {
	delay(duration);
	// Serial.print("\n\t\t\t\t\t\t\t\t Loop =====> \n");
}

int ArduinoUtil::mathAbs(int input) {
	if(input < 0){ return -input;}
	return input;
}
#endif