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

  pros::Optical optical_sensor(OPTICAL_PORT);

  pros::Rotation rotation_sensor(ROTATION_PORT);
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

  int sensorTest = 2;     // which sensor to test? 0 = no sensor, 1 = distance sensor, 2 = optical sensor;
                          // 3 = rotational sensor default = all sensors

  // Special setup for the optical sensor - soem functionailty coems via the C api only and
  // does must as such be declared in.

  pros::c::optical_rgb_s_t RGB_values;          // We need tp get this from the C api....
                                                // it is the structure for the RGB return

  optical_sensor.disable_gesture();             // Disable gesture mode
  optical_sensor.set_led_pwm(50);               // set the LED to 50% to help with relfective color detect
                                                // ine following detect

  // Rotation sensro setup - direction and Reset
  rotation_sensor.reverse();  //Rotation sensor recently reversed
  rotation_sensor.reset();    //Reset encoder - zero position

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
        std::cout << "Hue: " << optical_sensor.get_hue() << " ";
        std::cout << "Saturation: " << optical_sensor.get_saturation() << " ";
        std::cout << "Brithgness: " << optical_sensor.get_brightness() << " ";
        std::cout << "Proximity: " << optical_sensor.get_proximity() << " \n";
        RGB_values = optical_sensor.get_rgb();
        std::cout << "RGB: R=" << RGB_values.red << " G=" << RGB_values.green << " B=";
        std::cout << RGB_values.blue << " Brightness=" << RGB_values.brightness << "\n";
      break;

      case 3 :

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

      break;

    }
		pros::delay(20);
	}
}
