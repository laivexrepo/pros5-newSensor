// ------- globals.cpp ---------------------------------------------------------
//
// Use globals.cpp together with globals.h to define all motor and other objects
// which should be available/accessible in autonomous and opcontrol code.
//
// forexample setup a motor definition and then add a extern pros::motor to
// globals.h to ensure all other modules have access -- of course by including
// #include "globals.h" in the relevant source (.cpp) files

#include "main.h"
#include "portdef.h"

// ------------------ IMU ------------------------------------------------------
pros::Imu imu_sensor(IMU_PORT);

// ----------------- DISTANCE SENSOR -------------------------------------------
pros::Distance distance_sensor(DISTANCE_PORT);

// --------------------- Global Function definitions ---------------------------

void robotDataLogger() {
  // This function can be called and will write an entry to the dataLogger file
  // which is stored on the SD card and can record actions as the program runs
  // for later evaluation of performance

}
