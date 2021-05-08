/*
 * Description: This file performs Unit Tests for the MPU6050 IMU
 * Date:  30 April 2021
 * Author: Hayden Nanney
 */

#ifndef MPU6050_UNITTEST_H
#define MPU6050_UNITTEST_H


#include "MPU6050_Driver.h"
#include <assert.h>
#include <stdbool.h>


/*** NOTES ***
 *	Why does Calculate Gyro Test fail,but Calculate Accel test doesn't?
 *	 - Signedness of 16 bit numbers
 *	 - 2's Complement
 */






//make a deep copy of these variables before each test
int16_t short_AAAA = 0xAAAA;
int16_t short_5555 = 0x5555;

uint8_t array_AAAA[] = {0xAA, 0xAA};
uint8_t array_5555[] = {0x55, 0x44};

uint8_t buffer_AA[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
uint8_t buffer_55[] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55};


//init new array to assign values
void deepCopy(uint8_t* source, uint8_t* dest, int length){
	for(int i = 0; i < length; i++){
		dest[i] = source[i];
	}
}

bool ParseIMUBufferTest(){

	uint8_t imuBuffer[6];
	int16_t x = 0, y = 0, z = 0;


	deepCopy(buffer_AA, imuBuffer, 6);
	MPU6050_ParseRawIMUBuffer(imuBuffer[0], &x, &y, &z);

	assert(x == short_AAAA);
	assert(y == short_AAAA);
	assert(z == short_AAAA);


	deepCopy(buffer_55, imuBuffer, 6);
	MPU6050_ParseRawIMUBuffer(imuBuffer, &x, &y, &z);


	assert(x == short_5555);
	assert(y == short_5555);
	assert(z == short_5555);

	return true;
}

bool ScaleGyroscopeTest(){



	int16_t x = 0x2AAA;
	int16_t y = 0x2AAA;
	int16_t z = 0x2AAA;

	MPU6050_ScaleGyroscope(&x, &y, &z);

	int16_t answer = 0x2091; //0x2AAA * 100 /131 = 8337 = 0x2091

	assert(x == answer);
	assert(y == answer);
	assert(z == answer);



	x = 0x5555;
	y = 0x5555;
	z = 0x5555;

	answer = 0x4123;

	MPU6050_ScaleGyroscope(&x, &y, &z);

	assert(x == answer);
	assert(y == answer);
	assert(z == answer);

	return true;

}
/*
 * Current test only work when ACCEL_CONFIG = 0x18
 */
bool ScaleAccelerationTest(){



	int16_t x = 0xAAAA;
	int16_t y = 0xAAAA;
	int16_t z = 0xAAAA;

	MPU6050_ScaleAcceleration(&x, &y, &z);

	int16_t answer = 0xFF7B;

	assert(x == answer);
	assert(y == answer);
	assert(z == answer);


	x = 0x5555;
	y = 0x5555;
	z = 0x5555;

	answer = 0x0085;

	MPU6050_ScaleAcceleration(&x, &y, &z);

	assert(x == answer);
	assert(y == answer);
	assert(z == answer);

	return true;
}



void RunMPU6050UnitTests(){
	if (ParseIMUBufferTest()){	/*print ParseIMUBufferTest Passed*/}
	if (ScaleAccelerationTest()){	/*print passed*/ }
	if (ScaleGyroscopeTest()){	/*print passed*/ }


}






#endif /* MPU6050_UNITTEST_H */
