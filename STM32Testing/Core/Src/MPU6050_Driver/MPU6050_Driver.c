/**
 * @file MPU6050_Driver.c
 * @author Hayden Nanney
 * @date 24 April 2021
 * @brief C driver for the MPU6050 sensor
 */
#include "MPU6050_Driver.h"
#include "stdio.h"
#include "math.h"



#define PI (22/7)


void MPU6050_Init(){
    uint8_t check;
	uint8_t data;
	//check for response
    HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_WHO_AM_I, 1, &check, 1, 1000);
    if(check == 104)
    {
        data = 0x07;
        HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_SMPLRT_DIV, 1, &data, 1, 50);
        HAL_Delay(50);
        data = 0x00;
        HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 1, &data, 1, 50);
        HAL_Delay(50);
        data = 0x00;
        HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_GYRO_CONFIG, 1, &data, 1, 50);
        HAL_Delay(50);
        data = 0;
        HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_PWR_MGMT_1, 1, &data, 1, 1000);
        HAL_Delay(50);
    }
}
void MPU6050_GetIMUBuffer(uint8_t* buffer){
    HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, 1, buffer, 14, 100);
    HAL_Delay(100);
}

void MPU6050_GetGyroBuffer(uint8_t* buffer){
    HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_GYRO_XOUT_H, 1, buffer, 6, 100);
    HAL_Delay(100);
}

void MPU6050_GetAccelBuffer(uint8_t* buffer){
    HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, 1, buffer, 6, 100);
    HAL_Delay(100);
}
//rename to ScaleGyroscope
void MPU6050_ScaleGyroscope(int16_t* x, int16_t* y, int16_t* z){
	//remove the buffer read and replace with a global state of the register???
	uint8_t buf;
	HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_GYRO_CONFIG, 1, &buf, 1, 100);

	//change the factor to a parameter of the function???
	uint8_t hundredths = 100;
	uint8_t factor = hundredths;

	switch(buf & (0x18)){//register 27
		case 0://131 LSB/degree/second
			*x = (int16_t)(*x * factor / 131);
			*y = (int16_t)(*y * factor / 131);
			*z = (int16_t)(*z * factor / 131);
			break;
		case 8://65.5 LSB/degree/sec
			*x = (int16_t)(*x * factor / 65.5);
			*y = (int16_t)(*y * factor / 65.5);
			*z = (int16_t)(*z * factor / 65.5);
			break;
		case 16://32.8 LSB/degree/sec
			*x = (int16_t)(*x * factor / 32.8);
			*y = (int16_t)(*y * factor / 32.8);
			*z = (int16_t)(*z * factor / 32.8);
			break;
		case 24://16.4 LSB/degree/sec
			*x = (int16_t)(*x * factor / 16.4);
			*y = (int16_t)(*y * factor / 16.4);
			*z = (int16_t)(*z * factor / 16.4);
			break;
		default:
			HAL_Delay(0);
			//error?
	}
}


void MPU6050_ScaleAcceleration(int16_t* x, int16_t* y, int16_t* z){
	//remove the buffer read and replace with a global state of the register???
	uint8_t buf;
	HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 1, &buf, 1, 100);

	uint8_t hundredths = 100;
	uint8_t factor = hundredths;

	switch(buf & (0x18) ){//register 28
		case 0:
			*x = (int16_t)(*x * factor / 16384);
			*y = (int16_t)(*y * factor / 16384);
			*z = (int16_t)(*z * factor / 16384);
			break;
		case 8:
			*x = (int16_t)(*x * factor / 8192);
			*y = (int16_t)(*y * factor / 8192);
			*z = (int16_t)(*z * factor / 8192);
			break;
		case 16:
			*x = (int16_t)(*x * factor / 4096);
			*y = (int16_t)(*y * factor / 4096);
			*z = (int16_t)(*z * factor / 4096);
			break;
		case 24:
			*x = (int16_t)(*x * factor / 2048);
			*y = (int16_t)(*y * factor / 2048);
			*z = (int16_t)(*z * factor / 2048);
			break;
		default:
			HAL_Delay(0);
			//REPORT ERROR
	}
}

int16_t MPU6050_GetTempC(){

	uint8_t buffer[2];

	HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_TEMP_OUT_H, 1, &buffer, 2, 100);//ERROR
	HAL_Delay(200);

	return (int16_t) ( ( ( (int16_t)(buffer[0] << 8 | buffer[1]) ) / 340 + 36.53) * 10);
}

//rename to something else
void MPU6050_ParseRawIMUBuffer(uint8_t* buffer, int16_t* x, int16_t* y, int16_t* z){
	*x = (int16_t) (buffer[0] << 8 | buffer[1]);
	*y = (int16_t) (buffer[2] << 8 | buffer[3]);
	*z = (int16_t) (buffer[4] << 8 | buffer[5]);
}

//change name to get scaled IMU data
void MPU6050_ParseIMUBuffer(uint8_t* buffer, int16_t* ax, int16_t* ay, int16_t* az, int16_t* t, int16_t* gx, int16_t* gy, int16_t* gz){
	MPU6050_ParseRawIMUBuffer(buffer[0], &ax, &ay, &az);
	//Add temperature parsing
	MPU6050_ParseRawIMUBuffer(buffer[8], &gx, &gy, &gz);
}

void testProgram(){

	uint8_t first = 1;
	double 	time = 0,
			prevTime  = 0,
			dt = 0;

	uint16_t 	ax = 0,
				ay = 0,
				az = 0,
				t  = 0,
				gx = 0,
				gy = 0,
				gz = 0;

	int16_t		arx = 0,
				ary = 0,
				arz = 0,
				grx = 0,
				gry = 0,
				grz = 0;


	uint8_t buffer[14] = {0};

	while(1){

		prevTime = time;
		time = HAL_GetTick();//milliseconds
		dt = (time - prevTime)/1000; //time is seconds


		MPU6050_GetIMUBuffer(&buffer);
		MPU6050_ParseIMUBuffer(buffer, &ax,&ay, &az, &t, &gx, &gy, &gz); //returns scaled data

		//acceleration angles
		arx = (180 / PI) * atan( ax / sqrt( pow(ay,2) + pow(az,2) ) );
		ary = (180 / PI) * atan( ay / sqrt( pow(ax,2) + pow(az,2) ) );
		arz = (180 / PI) * atan( sqrt( pow(ay,2) + pow(ax,2) ) / az );
		/*
		 * void getAccelerationAngles( int16_t* ax, int16_t* ay, int16_t* az, int16_t* arx, int16_t* ary, int16_t* arz){
		 * 		*arx = (180 / PI) * atan( ax / sqrt( pow(ay,2) + pow(az,2) ) );
				*ary = (180 / PI) * atan( ay / sqrt( pow(ax,2) + pow(az,2) ) );
				*arz = (180 / PI) * atan( sqrt( pow(ay,2) + pow(ax,2) ) / az );
			}
		 */

		//gyro

		//initially set equal to accel
		if(first){
			grx = arx;
			gry = ary;
			grz = arz;
			first = 0;

		}else{
			//otherwise:
			grx = grx + dt * gx;
			gry = gry + dt * gy;
			grz = grz + dt * gz;
		}

		//filter portion
		arx = (0.96 * arx) + (0.04 * gx);
		ary = (0.96 * ary) + (0.04 * gy);
		arz = (0.96 * arz) + (0.04 * gz);
		//...same for rest

	}


}
