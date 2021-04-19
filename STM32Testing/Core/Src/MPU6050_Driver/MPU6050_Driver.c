/*
 * MPU6050_Driver.c
 *
 *  Created on: Apr 18, 2021
 *      Author: A
 */
#include "MPU6050_Driver.h"

void MPU6050_Init(){
    uint8_t check;
	uint8_t data;
    HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_WHO_AM_I, 1, &check, 1, 100);
    if(check == 104)
    {
        //data = 0x07;
        //HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_SMPLRT_DIV, 1, &data, 1, 50);
        //HAL_Delay(50);
        //data = 0x00;
        //HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_ACCEL_CONFIG, 1, &data, 1, 50);
        //HAL_Delay(50);
        //data = 0x00;
        //HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_GYRO_CONFIG, 1, &data, 1, 50);
        //HAL_Delay(50);
        data = 0;
        HAL_I2C_Mem_Write(I2C_PORT, MPU6050_ADDR, MPU6050_PWR_MGMT_1, 1, &data, 1, 50);
        HAL_Delay(50);
    }
}

int16_t MPU6050_Read_Accel(void)
{
    uint8_t recData[6];
    //for(int i=0;i<6;i++) recData[i] = 0;
    memset(recData, 0, sizeof(recData));

    HAL_I2C_Mem_Read(I2C_PORT, MPU6050_ADDR, MPU6050_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT,recData,6,100);
    HAL_Delay(50);

    int16_t Accel_X_RAW = (int16_t)(recData[0] << 8 | recData[1]);
    //Accel_Y_RAW = (int16_t)(recData[2] << 8 | recData[3]);
    //Accel_Z_RAW = (int16_t)(recData[4] << 8 | recData[5]);

    int16_t Ax = (int16_t)(Accel_X_RAW / 16384);
    //Ay = (int16_t)(Accel_Y_RAW / 16384);
    //Az = (int16_t)(Accel_Z_RAW / 16384);
    return Accel_X_RAW;
}
