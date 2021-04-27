/**
 * @file MPU6050_Driver.c
 * @author Hayden Nanney
 * @date 24 April 2021
 * @brief C driver for the MPU6050 sensor
 */
#include "MPU6050_Driver.h"


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
        //data = 0x00;
        //HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 1, &data, 1, 50);
        //HAL_Delay(50);
        //data = 0x00;
        //HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_GYRO_CONFIG, 1, &data, 1, 50);
        //HAL_Delay(50);
        data = 0;
        HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_PWR_MGMT_1, 1, &data, 1, 1000);
        HAL_Delay(50);
    }
}

void MPU6050_GetGyroBuffer(uint8_t* buffer){
    HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_GYRO_XOUT_H, 1, buffer, 6, 100);
    HAL_Delay(50);
}

void MPU6050_GetAccelBuffer(uint8_t* buffer){
    HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, 1, buffer, 6, 100);
    HAL_Delay(50);
}
//page 30
void MPU6050_CalculateGyro(int16_t* x, int16_t* y, int16_t* z){
	uint8_t* buffer;
	HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_GYRO_CONFIG, 1, buffer, 1, 100);
	HAL_Delay(50);

	uint8_t hundredths = 100;
	uint8_t factor = hundredths;

	switch(MPU6050_GYRO_CONFIG & (0x18)){//register 27
		case 0://131 LSB/degree/second
			*x = (int16_t)(*x * factor / 131);
			*y = (int16_t)(*y * factor / 131);
			*z = (int16_t)(*z * factor / 131);
			break;
		case 8:
			*x = (int16_t)(*x * factor / 65.5);
			*y = (int16_t)(*y * factor / 65.5);
			*z = (int16_t)(*z * factor / 65.5);
			//65.5 LSB/degree/sec
			break;
		case 16:
			*x = (int16_t)(*x * factor / 32.8);
			*y = (int16_t)(*y * factor / 32.8);
			*z = (int16_t)(*z * factor / 32.8);
			break;
			//32.8 LSB/degree/sec
		case 24:
			*x = (int16_t)(*x * factor / 16.4);
			*y = (int16_t)(*y * factor / 16.4);
			*z = (int16_t)(*z * factor / 16.4);
			//16.4 LSB/degree/sec
			break;
		default:
			HAL_Delay(5);
			//error?
	}
}
void MPU6050_CalculateAccel(int16_t* x, int16_t* y, int16_t* z){
	uint8_t* buffer;
	HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 1, buffer, 1, 100);
	HAL_Delay(50);

	uint8_t hundredths = 100;
	uint8_t factor = hundredths;

	switch( (uint8_t)(MPU6050_ACCEL_CONFIG & (0x18)) ){//register 28
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

	uint8_t* buffer;

	HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_TEMP_OUT_H, 1, buffer, 2, 100);
	HAL_Delay(50);

	return (int16_t) ( ( ( (int16_t)(buffer[0] << 8 | buffer[1]) ) / 340 + 36.53) * 10);
}


void MPU6050_ParseRawIMUBuffer(uint8_t* buffer, int16_t* x, int16_t* y, int16_t* z){
	  *x = (int16_t) (buffer[0] << 8 | buffer[1]);
	  *y = (int16_t) (buffer[2] << 8 | buffer[3]);
	  *z = (int16_t) (buffer[4] << 8 | buffer[5]);
}
