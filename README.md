# pros5-newSensor
PROSV5 New Sensor Test Code which can be used as a starting testbed to better understand the new Rotation Sensor, Optical Sensor, Distance Sensor and IMU.

The code use a selector to switch to a particular sensor to test and evaluate.  The variable sensorTest may have either be one of the following values:

0 - no sensor code is tested
1 - V5 Distance Sensor
2 - V5 Optical Sensor
3 - V5 Rotational Sensor
4 - V5 IMU sensor

Setting the value to anything higher then 5 will trigger the default case, and all sensors are read and data reported.

The default number of times a sensor is read and the values displayed is controlled by the boolean flag useLoopLimit, which when is set to true, will use the variable maxLoopCount to determine how many times the sensors are read and their values displayed.
