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
	//buffer[6] ='\0';
    HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_GYRO_XOUT_H, 1, buffer, 6, 100);
    HAL_Delay(50);
}

void MPU6050_GetAccelBuffer(uint8_t* buffer){
	//buffer[6] ='\0';
    HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, 1, buffer, 6, 100);
    HAL_Delay(50);
}

void MPU6050_ParseRawIMUBuffer(uint8_t* buffer, int16_t* x, int16_t* y, int16_t* z){
	  *x = (int16_t) (buffer[0] << 8 | buffer[1]);
	  *y = (int16_t) (buffer[2] << 8 | buffer[3]);
	  *z = (int16_t) (buffer[4] << 8 | buffer[5]);
}
