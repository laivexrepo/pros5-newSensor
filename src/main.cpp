#include "main.h"
#include "portdef.h"
#include "globals.h"

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

	imu_sensor.reset();				// Reset the IMU and start calibration process, robot
														// should not be moved during this stage of calibration.

	int time = pros::millis();
	int iter = 0;
	while (imu_sensor.is_calibrating()) {
		std::cout << "IMU calibrating... " << iter << "\n";
		iter += 10;
		pros::delay(10);
	}
	// should print about 2000 ms
	std::cout << "IMU is done calibrating (took: " << iter - time << "ms \n";

  pros::Distance distance_sensor(DISTANCE_PORT);
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

  int sensorTest = 1;     // which sensor to test? 0 = no sensor, 1 = distance sensor, 2 = optical sensor;
                          // 3 = rotational sensor default = all sensors
	while (true) {
    // Lets contineously read the selected sensor data and write
    // to console.
    switch(sensorTest) {
      case 0 :
        std::cout << "No sensor selected \n";
      break;

      case 1 :          // distance sensor
        std::cout << "Distance: " << distance_sensor.get() <<  " mm";
        std::cout << " Velocity: " << distance_sensor.get_object_velocity() << " m/s ";
        std::cout << " Size: " << distance_sensor.get_object_size() << " \n";
      break;

      case 2 :

      break;
      
      default :
        // Distance Sensor
        std::cout << "Distance: " << distance_sensor.get() <<  " mm";
        std::cout << " Velocity: " << distance_sensor.get_object_velocity() << " m/s ";
        std::cout << " Size: " << distance_sensor.get_object_size() << " \n";
      break;

    }
		pros::delay(20);
	}
}
