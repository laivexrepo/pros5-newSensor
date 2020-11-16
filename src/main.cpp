#include "main.h"
#include "portdef.h"
#include "globals.h"
#include <iomanip>      // so we can manipulate precision of float
                        // Header providing parametric manipulators

/**
 * Put callback functions here.
 *
 */

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

	// initialize inertial sensor and calibrate
  pros::Imu imu_sensor(IMU_PORT);
  pros::delay(100);	        // give sensor time to settle in

	imu_sensor.reset();				// Reset the IMU and start calibration process, robot
														// should not be moved during this stage of calibration.

	int time = pros::millis();
	int iter = 0;
	while (imu_sensor.is_calibrating()) {
    // Un comment if you want to see the calibration loop working/running
		//std::cout << "IMU calibrating... " << iter << "\n";
		iter += 10;
		pros::delay(10);
	}
  int endTime = pros::millis();
	std::cout << "IMU is done calibrating (took: iter=" << iter << "ms  Start Time=" << time << "ms End Time=" << endTime << "ms ) \n";

  pros::Distance distance_sensor(DISTANCE_PORT);
  pros::delay(100);	        // give sensor time to settle in

  pros::Optical optical_sensor(OPTICAL_PORT);
  pros::delay(100);	        // give sensor time to settle in

  pros::Rotation rotation_sensor(ROTATION_PORT);
  pros::delay(100);	        // give sensor time to settle in
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // ---------------------------- WHICH SENSOR TO TEST -----------------------------------------------------------
  int sensorTest = 4;     // which sensor to test? 0 = no sensor, 1 = distance sensor, 2 = optical sensor;
                          // 3 = rotational sensor 4 = IMU test
                          //
                          // default = all sensors  (set the value to say 10) to trigger default

  // ---------------------------- OPTICAL SENSOR -----------------------------------------------------------------
  // Special setup for the optical sensor - some functionailty comes via the C api only and
  // does must as such be declared in.

  pros::c::optical_rgb_s_t RGB_values;          // We need tp get this from the C api....
                                                // it is the structure for the RGB return

  optical_sensor.disable_gesture();             // Disable gesture mode
  // Turn on the ligting LED to help measure color, hue etc PWM runs from 0 (off) to 100 (Full)
  optical_sensor.set_led_pwm(0);               // set the LED to 50% to help with relfective color detect
                                                // ine following detect

  // ---------------------------- ROTATION SENSOR -----------------------------------------------------------------
  // Rotation sensor setup - direction and Reset
  // Contol the dircetion the sensor counts in reverse - counter clockwise,
  //rotation_sensor.reverse();    //Rotation sensor recently reversed
                                //Reverses the rotational sensor’s positive
                                //counterclockwise/clockwise direction
  // Setting reverse -- both .revers and .set_reverse do the same thing use 1 or the other
  //rotation_sensor.set_reversed(true);

  // set the rotation sensor position to 0 - should be normal operation when initializinf robot
  // However for an arm you may want to set to a desired angle in centi degrees and count up/down from it
  rotation_sensor.reset_position();
  pros::delay(100);	          // give sensor time to settle in

  // set the rotation sensor to a specified position
  //rotation_sensor.set_position(18000);      // degrees in centi degrees - 180 degrees is 18000 cneti degrees
  pros::delay(100);	          // give sensor time to settle in

  float rpm = 0.0;            // variable for rpm calculation
  float wheelRadius = 0.1;    // wheel radius is .1m (10cm)
  float linearVelocity = 0.0; // liniar velocity in m/s

  int startPosition = abs(rotation_sensor.get_position());
  int totalPosition = 0;
  int endPosition = 0;
  float distanceTraveled = 0.0;

  // --------------------------- IMU -----------------------------------------------------------------------------
  pros::c::quaternion_s_t qt;       // store Quarternion data strature on IMU call

  // --------------------------- HELP RUNNING LOOP FOR TESTING ---------------------------------------------------
  bool controlLoop = true;
  bool useLoopLimit = true;        // Do we want to loop for a number of times?
                                    // If set to true - use maxLoopCount to set
                                    // the number of times we run the testign loop
  int loopCount = 0;
  int maxLoopCount = 10;

	while (controlLoop) {
    // Lets contineously read the selected sensor data and write
    // to console.
    switch(sensorTest) {
      case 0 :
        std::cout << "No sensor selected \n";
        controlLoop = false;            // break out of loop
      break;

      case 1 :          // distance sensor
        std::cout << "Distance: " << distance_sensor.get() <<  " mm";
        std::cout << " Velocity: " << distance_sensor.get_object_velocity() << " m/s ";
        std::cout << " Size: " << distance_sensor.get_object_size() << " \n";
      break;

      case 2 :
        std::cout << "Hue: " << optical_sensor.get_hue() << " ";
        std::cout << "Saturation: " << optical_sensor.get_saturation() << " ";
        std::cout << "Brithgness: " << optical_sensor.get_brightness() << " ";
        std::cout << "Proximity: " << optical_sensor.get_proximity() << " \n";
        RGB_values = optical_sensor.get_rgb();
        std::cout << "RGB: R=" << RGB_values.red << " G=" << RGB_values.green << " B=";
        std::cout << RGB_values.blue << " Clear=" << RGB_values.brightness << " Brightness=" << RGB_values.brightness << "\n";
      break;

      case 3 :
        std::cout << "Position: " << rotation_sensor.get_position() <<  " ";
        std::cout << "Reversed: " << rotation_sensor.get_reversed() <<  " \n";
        std::cout << "Velocity: " << rotation_sensor.get_velocity() <<  " cdeg/s";
        rpm = (rotation_sensor.get_velocity() / 36000.00) * 60.0;
        std::cout << " = " << std::fixed << std::setprecision(4) << rpm <<  " rpm ";
        linearVelocity = ((2 * 3.14) / 60) * wheelRadius * rpm;
        std::cout << " Linear Velocity " << std::fixed << std::setprecision(4) << linearVelocity <<  " m/s \n";
        endPosition =  rotation_sensor.get_position();
      break;

      case 4 :
        std::cout << "Current Heading: " << imu_sensor.get_heading() << " ";
        qt = imu_sensor.get_quaternion();
        std::cout << "Quaternion: x:" << qt.x << " y:" << qt.y << " z:" << qt.z << " w:" << qt.w << " \n";
      break;

      default :
        // Distance Sensor
        std::cout << "Distance: " << distance_sensor.get() <<  " mm";
        std::cout << " Velocity: " << distance_sensor.get_object_velocity() << " m/s ";
        std::cout << " Size: " << distance_sensor.get_object_size() << " \n";
        // Optical Sensor
        std::cout << "Hue: " << optical_sensor.get_hue() << " ";
        std::cout << "Saturation: " << optical_sensor.get_saturation() << " ";
        std::cout << "Brithgness: " << optical_sensor.get_brightness() << " ";
        std::cout << "Proximity: " << optical_sensor.get_proximity() << " \n";
        RGB_values = optical_sensor.get_rgb();
        std::cout << "RGB: R=" << RGB_values.red << " G=" << RGB_values.green << " B=";
        std::cout << RGB_values.blue << " Brightness=" << RGB_values.brightness << "\n";
        // IMU
        std::cout << "Current Heading: " << imu_sensor.get_heading() << " ";
        qt = imu_sensor.get_quaternion();
        std::cout << "Quaternion: x:" << qt.x << " y:" << qt.y << " z:" << qt.z << " w:" << qt.w << " \n";
        // Rotation sensor
        std::cout << "Position: " << rotation_sensor.get_position() <<  " ";
        std::cout << "Reversed: " << rotation_sensor.get_reversed() <<  " \n";
        std::cout << "Velocity: " << rotation_sensor.get_velocity() <<  " cdeg/s";
        rpm = (rotation_sensor.get_velocity() / 36000.00) * 60.0;
        std::cout << " = " << std::fixed << std::setprecision(4) << rpm <<  " rpm ";
        linearVelocity = ((2 * 3.14) / 60) * wheelRadius * rpm;
        std::cout << " Linear Velocity for wheelradius of .1m: " << std::fixed << std::setprecision(4) << linearVelocity <<  " m/s \n";
        endPosition =  rotation_sensor.get_position();
      break;
    }
		pros::delay(200);
    // provide mechanism to run only a certain number of times through while loop
    if(useLoopLimit){
      loopCount++;
      if(loopCount < 0 || loopCount > maxLoopCount) { controlLoop = false; }
    }
	} // End while (
  // print distance travelled if testing rotation sensor
  if(sensorTest == 3) {
    totalPosition = endPosition - startPosition;
    distanceTraveled = (totalPosition / 36000.00) * (2 * 3.14 * wheelRadius);
    std::cout << "Total Position: (ABS) " << abs(totalPosition) << "cdeg  " << totalPosition << "cdeg ";
    std::cout << " Displacement " << std::fixed << std::setprecision(4) << distanceTraveled <<  " m \n";
  }
}
