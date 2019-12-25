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
		void neutral();
		int mapSpeed(int speed);
		TankDriver(MotorControl _motorLeft, MotorControl _motorRight, boolean _singleJoystickMode = true) {
			motorLeft = _motorLeft;
			motorRight = _motorRight;
			singleJoystickMode = _singleJoystickMode;
		}
};

void TankDriver::drive(int y, int x) {
	neutral();	
	if(y < 5 && y > -5 && x < 5 && x > -5) {
		return;
	}
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


	motorLeft.setSpeed(mapSpeed(speedLeft));
	motorRight.setSpeed(mapSpeed(speedRight));
}

int TankDriver::mapSpeed(int speed) {
	if(speed < 0) {
		return - map(-speed, 0, 100, DC_RANGE/3, DC_RANGE);
	} else {
		return  map(speed, 0, 100, DC_RANGE/3, DC_RANGE);	
	}	
}


void TankDriver::stop() {
	motorLeft.stop();
	motorRight.stop();
}
void TankDriver::neutral() {
	motorLeft.neutral();
	motorRight.neutral();
}

String TankDriver::calculateDirection(int turn) {
	if(turn >= 0){ return RIGHT;}
	return LEFT;
}
#endif