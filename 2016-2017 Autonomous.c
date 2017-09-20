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
//This code is written reeeeeeally hastily. Look at one of the other files for info.

task main()
{
	SensorValue[shaftEncoder] = 0; //Calibrate the shaft encoder- must be in fully down position
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
