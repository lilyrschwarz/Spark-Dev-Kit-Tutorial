# Spark-Dev-Tutorial
Tutorial for MachineQ Spark Dev Kit

Find the official tutorial here: https://support.machineq.com/s/article/Spark-Dev-Kit-Tutorial.
Below, find directions to get a more comprehensive sketch running.

1. Assemble the kit using the ribbon cables provided to plug in the sensors. The sensors included are Grove - Temperature Sensor, Grove - Ultrasonic Ranger, Grove - Sound Sensor, and Grove - 6-Axis Accelerometer & Gyroscope. In the code provided, Make sure the green LED blinks to ensure it is receiving power.

2. Open the Arduino IDE and specify the board type as Arduino Leonardo. Next, select the correct port for that board.

3. With the sketch provided, you will need to download additional libraries: CayenneLPP, ByteConvert, SparkFun LSM6DS3 and Grove Ultrasonic Ranger. To do this, go to Tools -> Manage Libraries, search for each library, and press the install button.

![alt text](https://github.com/lilyrschwarz/Spark-Dev-Tutorial/blob/master/images/cayenne.png "CayenneLPP")

![alt text](https://github.com/lilyrschwarz/Spark-Dev-Tutorial/blob/master/images/byteconvert.png "ByteConvert")

![alt text](https://github.com/lilyrschwarz/Spark-Dev-Tutorial/blob/master/images/sparkfun.png "SparkFun LSM6DS3")

![alt text](https://github.com/lilyrschwarz/Spark-Dev-Tutorial/blob/master/images/ultrasonic.png "Grove Ultrasonic Ranger")

4. Program the board with its DevEUI, AppEUI, and AppKey to send sensor data to the MachineQ platform.

5. Compile the and upload it to the board by pressing the green arrow in the upper left.
