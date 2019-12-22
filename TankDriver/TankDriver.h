#ifndef TankDriver_h
#define TankDriver_h 


class TankDriver {
	private:
		MotorControl motorLeft, motorRight;
		int speedL, speedR;
		boolean singleJoystickMode;
		const String LEFT = "LEFT";
		const String RIGHT = "RIGHT";
		String calculateDirection(int arq);
	public:
		void drive(int x, int y);
		void stop();
		void setup();
		TankDriver(MotorControl _motorLeft, MotorControl _motorRight, boolean _singleJoystickMode = true) {
			motorLeft = _motorLeft;
			motorRight = _motorRight;
			singleJoystickMode = _singleJoystickMode;
		}
};

void TankDriver::setup() {
}


void TankDriver::drive(int y, int x) {
	stop();
	delay(5);	
	
	int speedRight, speedLeft;
	speedLeft = y;
	speedRight = y;
	
		if(x > 30) {
			speedLeft = -25;
			speedRight = 25;
		} else if(x < -30) {
			speedLeft = 25;
			speedRight = -25;
		}
		if(x > 50) {
			speedLeft = -40;
			speedRight = 40;
		} else if(x < -50) {
			speedLeft = 40;
			speedRight = -40;
		}
		if(x > 70) {
			speedLeft = -50;
			speedRight = 50;
		} else if(x < -70) {
			speedLeft = 50;
			speedRight = -100;
		}

	
	speedLeft = map(speedLeft, 0, 100, 0, 1024);
	speedRight = map(speedRight, 0, 100, 0, 1024);

	// print(speedLeft, speedRight);
	motorLeft.setSpeed(speedLeft);
	motorRight.setSpeed(speedRight);
}

void TankDriver::stop() {
	motorLeft.stop();
	motorRight.stop();
}

String TankDriver::calculateDirection(int turn) {
	if(turn >= 0){ return RIGHT;}
	return LEFT;
}
#endif