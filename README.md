# mpu6050
mpu6050 - very simple driver for the popular six-axis (accelerometer + gyroscope) sensor

No fluff, just read raw values off device and convert into useful units.

I wanted to write it in pure C, but am using the Arduino `Wire` library for I2C r/w.

Tested, see `example.c`.