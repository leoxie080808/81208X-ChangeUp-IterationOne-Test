#include <stdio.h>
using namespace std;

vex::brain Brain;
vex::controller Controller = vex::controller();

vex::motor LeftOne = vex::motor(vex::PORT1, true);
vex::motor LeftTwo = vex::motor(vex::PORT4, true);
vex::motor RightOne = vex::motor(vex::PORT2, false);
vex::motor RightTwo = vex::motor(vex::PORT3, false);

vex::competition Competition = vex::competition();
vex::encoder RightEncoder = vex::encoder(Brain.ThreeWirePort.A);
vex::encoder LeftEncoder = vex::encoder(Brain.ThreeWirePort.C);

vex::rotationUnits raw = vex::rotationUnits::raw;
vex::percentUnits percent = vex::percentUnits::pct;
vex::directionType forwards = vex::directionType::fwd;
vex::directionType backwards = vex::directionType::rev;
vex::brakeType brake = vex::brakeType::brake;
vex::brakeType holdBrake = vex::brakeType::hold;
vex::brakeType coastBrake = vex::brakeType::coast;

vex::motor indexer = vex::motor(vex::PORT9, true);
vex::motor roller = vex::motor(vex::PORT10, false);
vex::motor intakeLeft = vex::motor(vex::PORT7,vex::gearSetting::ratio18_1,true);
vex::motor intakeRight = vex::motor(vex::PORT8, vex::gearSetting::ratio18_1, false);



	int leftDrive;
	int rightDrive;
    int leftTop;
int leftBottom;
int rightTop;
int rightBottom; 



#define PICKIP_POS   -700
#define LOW_POLE  -2450
#define HIGH_POLE -678
#define RESET_POSITION 0

#define DROP_LOW_POLE_CAP 




void drive() {
        leftTop = Controller.Axis3.value() + Controller.Axis1.value() + Controller.Axis4.value();
		leftBottom = Controller.Axis3.value() + Controller.Axis1.value() - Controller.Axis4.value();
		rightTop = Controller.Axis3.value() - Controller.Axis1.value() - Controller.Axis4.value();
        rightBottom = Controller.Axis3.value() - Controller.Axis1.value() + Controller.Axis4.value();

	LeftOne.spin(vex::directionType::fwd, leftTop, vex::velocityUnits::pct);
	LeftTwo.spin(vex::directionType::fwd, leftBottom, vex::velocityUnits::pct);
	RightOne.spin(vex::directionType::fwd, rightTop, vex::velocityUnits::pct);
	RightTwo.spin(vex::directionType::fwd, rightBottom, vex::velocityUnits::pct);
	vex::task::sleep(10);
  
}

void shoot() {
	if (Controller.ButtonR1.pressing()) {
		indexer.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        roller.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
	}
	else if (Controller.ButtonR2.pressing()) {
		indexer.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
        roller.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
	}
	else {
		indexer.stop(vex::brakeType::coast);
        roller.stop(vex::brakeType::coast);
	}
	//Controller.ButtonRight.pressed(DoingThePuncher);
	vex::task::sleep(10);
}


void intake() {
	if (Controller.ButtonL1.pressing()) {
		intakeLeft.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        intakeRight.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
	}
	else if (Controller.ButtonL2.pressing()) {
		intakeLeft.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
        intakeRight.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
	}
	else {
		intakeLeft.stop(vex::brakeType::coast);
        intakeRight.stop(vex::brakeType::coast);
	}
	//Controller.ButtonRight.pressed(DoingThePuncher);
	vex::task::sleep(10);
}






int main() {
	
	while (1) {
		drive();
        intake();
        shoot();
		/*if (Controller.ButtonL1.pressing()) {
			Intake.spin(vex::directionType::fwd, 90, vex::velocityUnits::pct);
		}
		else if (Controller.ButtonL2.pressing()) {
			Intake.spin(vex::directionType::rev, 60, vex::velocityUnits::pct);
		}
		else {
			Intake.stop(vex::brakeType::coast);
		}
		Controller.ButtonR2.pressed(DoingThePuncher);*/
	//vex::task::sleep(15);
		
		
        //for debug        Brain.Screen.clearLine(0,vex::color::black);
        Brain.Screen.clearLine(1,vex::color::black);
        Brain.Screen.clearLine(2,vex::color::black);
        Brain.Screen.setCursor(1,0);
        Brain.Screen.print("leftDrive = %d",leftDrive);
        Brain.Screen.setCursor(2,0);
        Brain.Screen.print("rightDrive = %d", rightDrive);
        //Brain.Screen.setCursor(3,0);
        //Brain.Screen.print("Right Encoder: %f", rightEncoder.rotation(vex::rotationUnits::raw) );
        
        Brain.Screen.render(); //push data to the LCD all at once to prevent image flickering
        vex::task::sleep(15);
         // test sensor and encoder first
        Brain.Screen.clearLine(0,vex::color::black);
        Brain.Screen.clearLine(1,vex::color::black);
        Brain.Screen.clearLine(2,vex::color::black);
      //  Brain.Screen.setCursor(1,0);
       // Brain.Screen.print("Robot Heading: %f degrees",Gyro.value(vex::rotationUnits::deg));
      //  Brain.Screen.setCursor(2,0);
        //Brain.Screen.print("Left Encoder: %f", leftEncoder.rotation(vex::rotationUnits::raw));
      //  Brain.Screen.setCursor(3,0);
       // Brain.Screen.print("Arm Position: %f",armMotor.rotation(vex::rotationUnits::deg)  );//rightEncoder.rotation(vex::rotationUnits::raw) );
        //Brain.Screen.print("Right Encoder: %f",rightEncoder.rotation(vex::rotationUnits::raw) );
        Brain.Screen.render(); //push data to the LCD all at once to prevent image flickering
        vex::task::sleep(10);
        
        }
    
 
	
}

