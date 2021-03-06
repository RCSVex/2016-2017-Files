#pragma config(Sensor, dgtl1,  shaftEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port1,           topLeftOut,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           clawLeft,      tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port3,           clawRight,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port4,           driveBackLeft, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           driveBackRight, tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port6,           driveFrontLeft, tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port7,           driveFrontRight, tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           topLeftIn,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port9,           topRightIn,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port10,          topRightOut,   tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
This code is the competition code for the team 25565B Robot for the 2016-2017 Starstruck competition
For non-competition testing, use the file 2016-2017 Controller.c file, which has no competition control structures
The robot was built by (last name alphabetical order, no favoritism):
- Nolan Flynn
- Ryan Garcia
- Ben Kaufman
- Justin Kretchman
- Dashiell Slamowitz
Code built by Nolan Flynn
This file based on code from:
-	The 2016-2017 Controller.c program
- The Vex_Competition_Template.c template sample program, included in the ROBOTC app
*/

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	SensorValue[shaftEncoder] = 0; //Calibrate the shaft encoder- must be in fully down position. Remove from other program parts!
	bStopTasksBetweenModes = true; //DO NOT CHANGE

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	// ..........................................................................
	// Insert user code here.
	// ..........................................................................
	clearTimer(1);//Reset timer
	//Loop Forever
	while(1 == 1)
	{
		//All variables are named with A at the end just in case it interferes with the user control variables
		int section1A = 2300; //Drive back for this ms
		int section2A = 2000; //Strafe sideways for this ms
		int section3A = 200; //Drive forward for this ms
		int section4A = 2000; //Close claw for this ms
		int section5A = 500; //Drive back with claw closing for this ms
		int section6A = 2000; //Throw for this ms

		bool leftSide = true; //Left or right side

		int driveMotorPowerA = 100; //Drive motors at 100 power
		int frontDriveMotorPowerA = 80;
		//int frontMotorReductionFactorA = 0.8; //Front motors operate at 0.8 of the full drive power to offset weight imbalance

		int clawMotorPowerA = 70; //Claw motors operate at 70 power
		int clawMotorBoostPowerA = 85; //Claw motors operate at 85 power when fast opening while throwing

		int armMotorPowerA = 110; //Arm motors operate at 110 power

		int clawOpenAngleA = 70; //Claw motors start opening at clawMotorBoostPowerA

		int armMaxAngleA = 130; //Maximum angle of the arm before the arm and claw motors stop



		if(time1[1] < section1A){ //Drive backward section
			motor[driveFrontRight] = -frontDriveMotorPowerA;
			motor[driveBackRight] =  -driveMotorPowerA;
			motor[driveFrontLeft] = -frontDriveMotorPowerA;
			motor[driveBackLeft] =  -driveMotorPowerA;
		}
		else if(time1[1] < section1A+section2A){ //Strafe sideways section
			if(leftSide == true){
				motor[driveFrontRight] = frontDriveMotorPowerA;
				motor[driveBackRight] =  driveMotorPowerA;
				motor[driveFrontLeft] = -frontDriveMotorPowerA;
				motor[driveBackLeft] =  -driveMotorPowerA;
			}
			else{
				motor[driveFrontRight] = -frontDriveMotorPowerA;
				motor[driveBackRight] =  -driveMotorPowerA;
				motor[driveFrontLeft] = frontDriveMotorPowerA;
				motor[driveBackLeft] =  driveMotorPowerA;
			}
		}
		else if(time1[1] < section1A+section2A+section3A){ //Drive forward to cube section
			motor[driveFrontRight] = frontDriveMotorPowerA;
			motor[driveBackRight] =  driveMotorPowerA;
			motor[driveFrontLeft] = frontDriveMotorPowerA;
			motor[driveBackLeft] =  driveMotorPowerA;
		}
		else if(time1[1] < section1A+section2A+section3A+section4A){ //Claw close section
			motor[clawLeft] = clawMotorPowerA;
			motor[clawRight] = clawMotorPowerA;
		}
		else if(time1[1] < section1A+section2A+section3A+section4A+section5A){ //Drive back with claw closing section
			motor[driveFrontRight] = -frontDriveMotorPowerA;
			motor[driveBackRight] =  -driveMotorPowerA;
			motor[driveFrontLeft] = -frontDriveMotorPowerA;
			motor[driveBackLeft] =  -driveMotorPowerA;

			motor[clawLeft] = clawMotorPowerA;
			motor[clawRight] = clawMotorPowerA;
		}
		else if(time1[1] < section1A+section2A+section3A+section4A+section5A+section6A){ //Throw section
			if(SensorValue[shaftEncoder] < armMaxAngleA){
				motor[topLeftOut] = armMotorPowerA; //all arm motors up at arm motor power
				motor[topLeftIn] = armMotorPowerA;
				motor[topRightIn] = armMotorPowerA;
				motor[topRightOut] = armMotorPowerA;

				if(SensorValue[shaftEncoder] < clawOpenAngleA){
					motor[clawLeft] = clawMotorPowerA;
					motor[clawRight] = clawMotorPowerA;
				}
				else if(SensorValue[shaftEncoder] > clawOpenAngleA){
					motor[clawLeft] = -clawMotorBoostPowerA;
					motor[clawRight] = -clawMotorBoostPowerA;
				}
			}
		}
		else{
			motor[driveBackLeft] = 0;
			motor[driveBackRight] = 0;
			motor[driveFrontLeft] = 0;
			motor[driveFrontRight] = 0;

			motor[topLeftOut] = 0;
			motor[topLeftIn] = 0;
			motor[topRightIn] = 0;
			motor[topRightOut] = 0;

			motor[clawLeft] = 0;
			motor[clawRight] = 0;
		}

	}
}

// Remove this function call once you have "real" code.
//AutonomousCodePlaceholderForTesting();


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	//SensorValue[shaftEncoder] = 0; //Calibrate the shaft encoder- must be in fully down position. REMOVE FROM HERE IN COMPETITION FILE!!!
	//Loop Forever
	while(1 == 1)
	{
		//Declaring variables- All variables can be changed from here, only modify other stuff if you need to add actual logic
		int armMotorPower = 110; //Arm moves up at this power below armPowerAngle
		int armMotorBoostPower = 110; //Arm moves up at this power above armPowerAngle
		int armMotorPowerDown = 60; //Arm moves down at this power below armPowerDownAngle
		int armMotorBoostPowerDown = 80; //Arm moves down at this power above armPowerDownAngle

		int driveMotorPower = 90; //Drive power is this at maximum

		int armPowerAngle = 60; //Arm boost power activated, and claw closing when the arm is higher than this degrees from start
		int armPowerDownAngle = 60; //Boost power activated when arm going down

		int clawClampAngle = 11; //Claw starts clamping while throwing at this degrees
		int clawOpenAngle = 70; //Claw starts opening while throwing when the arm is higher than this degrees

		int clawPower = 70; //Power at which the claw operates
		int clawBoostPower = 85; //Power at which the claw operates when clamping and releasing while throwing

		int holdPower = 30;//Power at which the arm moves when holding up or down

		float frontMotorReductionFactor = 0.8; //Front drive motors are reduced by 20%,
		//to help equalize the weight difference between the front and back of the bot.

		int encoderMax = 130; //Encoder stops arm from moving up at 130 degrees
		int encoderMin = 10; //Encoder stops arm from moving down at 10 degrees


		//Remote Control Commands- DON'T CHANGE! EVER!
		int DFR = vexRT[Ch3] - vexRT[Ch4] + vexRT[Ch1]; //Drive Front Right power movement controls DONT CHANGE!
		int DBR =  vexRT[Ch3] - vexRT[Ch4] - vexRT[Ch1]; //Drive Back Right
		int DFL = vexRT[Ch3] + vexRT[Ch4] - vexRT[Ch1]; //Drive Front Left
		int DBL =  vexRT[Ch3] + vexRT[Ch4] + vexRT[Ch1]; //Drive Front Right

		if(SensorValue[shaftEncoder] > armPowerAngle){ //If the encoder is at higher than the angle it should be boosted at
			armMotorPower = armMotorBoostPower; //Arm motors will move at boost motor power
		}
		if(vexRT[Btn6U]==1 && SensorValue[shaftEncoder] < encoderMax){ //If 6Up is pressed and the encoder isn't past its maximum
			motor[topLeftOut] = armMotorPower; //all arm motors up at arm motor power
			motor[topLeftIn] = armMotorPower;
			motor[topRightIn] = armMotorPower;
			motor[topRightOut] = armMotorPower;
			if(SensorValue[shaftEncoder] > clawClampAngle && SensorValue[shaftEncoder] < clawOpenAngle){
				motor[clawLeft] = clawBoostPower;
				motor[clawRight] = clawBoostPower;
			}
			else if(SensorValue[shaftEncoder] > clawOpenAngle){
				motor[clawLeft] = -clawBoostPower;
				motor[clawRight] = -clawBoostPower;
			}
		}
		else if(vexRT[Btn6D]==1 && SensorValue[shaftEncoder] > encoderMin){ //If 6Down is pressed and the encoder isn't past its minimum
			if(SensorValue[shaftEncoder] > armPowerDownAngle){
				motor[topLeftOut] = -armMotorBoostPowerDown; //all arm motors down at arm boost motor power down
				motor[topLeftIn] = -armMotorBoostPowerDown;
				motor[topRightIn] = -armMotorBoostPowerDown;
				motor[topRightOut] = -armMotorBoostPowerDown;
			}
			else{
				motor[topLeftOut] = -armMotorPowerDown; //all arm motors down at arm motor power down
				motor[topLeftIn] = -armMotorPowerDown;
				motor[topRightIn] = -armMotorPowerDown;
				motor[topRightOut] = -armMotorPowerDown;
			}
		}
		else if(vexRT[Btn7D]==1 && SensorValue[shaftEncoder] > encoderMin){ //If 7Down is pressed and the encoder isn't past its minimum
			motor[topLeftOut] = -armMotorBoostPower; //all arm motors down at boost power
			motor[topLeftIn] = -armMotorBoostPower;
			motor[topRightIn] = -armMotorBoostPower;
			motor[topRightOut] = -armMotorBoostPower;
		}
		/*else if(vexRT[Btn5U]==1 && SensorValue[shaftEncoder] < encoderMax && SensorValue[shaftEncoder] > encoderMin){ //If 5Up is pressed
			motor[topLeftOut] = holdPower; //Give arm motors a bit of power to keep it from moving down
			motor[topLeftIn] = holdPower;
			motor[topRightIn] = holdPower;
			motor[topRightOut] = holdPower;
		}
		else if(vexRT[Btn5D]==1 && SensorValue[shaftEncoder] < encoderMax && SensorValue[shaftEncoder] > encoderMin){ //If 5Up is pressed
			motor[topLeftOut] = -holdPower; //Give arm motors a bit of power to keep it from moving down
			motor[topLeftIn] = -holdPower;
			motor[topRightIn] = -holdPower;
			motor[topRightOut] = -holdPower;
		}*/
		else if(vexRT[Btn5D]==1){
			motor[clawLeft] = clawPower;
			motor[clawRight] = clawPower;
		}
		else if(vexRT[Btn5U]==1){
			motor[clawLeft] = -clawPower;
	    motor[clawRight] = -clawPower;
		}
		else if(vexRT[Btn8L]==1){
			motor[clawLeft] = clawPower;
			motor[clawRight] = clawPower;
		}
		else if(vexRT[Btn8R]==1){
			motor[clawLeft] = -clawPower;
	    motor[clawRight] = -clawPower;
		}
		else{
			motor[topLeftOut] = 0; //If nothing pressed, don't move arm motors
			motor[topLeftIn] = 0;
			motor[topRightIn] = 0;
			motor[topRightOut] = 0;

			motor[clawLeft] = 0;
			motor[clawRight] = 0;
		}


		if(DFR>driveMotorPower){ //If each motor value is above or below the maximum drive motor power, set the motor to the max. or min. drive motor power
			DFR = driveMotorPower; //Just caps each drive motor's power
		}
		else if(DFR<-driveMotorPower){
			DFR = -driveMotorPower;
		}

		if(DBR>driveMotorPower){
			DBR = driveMotorPower;
		}
		else if(DBR<-driveMotorPower){
			DBR = -driveMotorPower;
		}

		if(DFL>driveMotorPower){
			DFL = driveMotorPower;
		}
		else if(DFL<-driveMotorPower){
			DFL = -driveMotorPower;
		}

		if(DBL>driveMotorPower){
			DBL = driveMotorPower;
		}
		else if(DBL<-driveMotorPower){
			DBL = -driveMotorPower;
		}
		DFR = DFR*frontMotorReductionFactor; //Reduces the front motor power by the reduction factor, to help equalize from weight being more over the back wheels
		DFL = DFL*frontMotorReductionFactor;
		motor[driveFrontRight] = DFR; //Set the drive motors to their final values
		motor[driveBackRight] =  DBR;
		motor[driveFrontLeft] = DFL;
		motor[driveBackLeft] =  DBL;

	}
}
