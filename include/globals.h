#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "main.h"

// ------------ Define the remote control controllers ---------------------
extern pros::Controller master;
extern pros::Controller partner;

// ------------ Define the IMU sensor -------------------------------------
extern pros::Imu imu_sensor;

// ------------ Define the port Extender  -------------------------------------
extern pros::Distance distance_sensor;
extern pros::Optical optical_sensor;
extern pros::Rotation rotation_sensor;

// ------------ Global accessible functions -------------------------------
extern void robotDataLogger();

// ----------- Global variable to control drive base mode -----------------
#define ARCADE_MODE false     // run in tankmode - if true arcade mode

// ----------- Global variables to assist in code development ------------
#define DEBUG true            // turn on DEBUG statements, should be off in final build

#define MANUAL_AUTON false    // allow for autonomous testing use Remote intead of
                              // competition switch -- set to false for production
                              // and competition!!!


#endif
