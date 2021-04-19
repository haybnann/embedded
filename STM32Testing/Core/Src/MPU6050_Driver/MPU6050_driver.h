/*
 * MPU6050_driver.h
 *
 *  Created on: Jan 22, 2021
 *      Author: Hayden Nanney
 *      GPS connection made jan 22 2021
 *
 *      Description:
 *
 */

#ifndef MPU6050_DRIVER_H
#define MPU6050_DRIVER_H

#include "stm32f1xx_hal.h"

extern I2C_HandleTypeDef hi2c2; //define which i2c port the sensor is attached to
#define I2C_PORT &hi2c2


#define MPU6050_ADDRESS_AD0_LOW     0x68
#define MPU6050_ADDRESS_AD0_HIGH    0x69
#define MPU6050_ADDR     			0x68//0xD0//MPU6050_ADDRESS_AD0_LOW


//REGISTER MAP on Page 6
#define MPU6050_SELF_TEST_X	    (0x0D)
#define MPU6050_SELF_TEST_Y		  (0x0E)
#define MPU6050_SELF_TEST_Z		  (0x0F)
#define MPU6050_SELF_TEST_A		  (0x10)
#define MPU6050_SMPLRT_DIV		  (0x19)
#define MPU6050_CONFIG			    (0x1A)
#define MPU6050_GYRO_CONFIG		  (0x1B)
#define MPU6050_ACCEL_CONFIG	  (0x1C)
#define MPU6050_MOT_THR			    (0x1F)
#define MPU6050_FIFO_EN			    (0x23)
#define MPU6050_I2C_MST_CTRL	  (0x24)
#define MPU6050_I2C_SLV0_ADDR	  (0x25)
#define MPU6050_I2C_SLV0_REG	  (0x26)
#define MPU6050_I2C_SLV0_CTRL	  (0x27)
#define MPU6050_I2C_SLV1_ADDR	  (0x28)
#define MPU6050_I2C_SLV1_REG	  (0x29)
#define MPU6050_I2C_SLV1_CTRL	  (0x2A)
#define MPU6050_I2C_SLV2_ADDR	  (0x2B)
#define MPU6050_I2C_SLV2_REG	  (0x2C)
#define MPU6050_I2C_SLV2_CTRL	  (0x2D)
#define MPU6050_I2C_SLV3_ADDR	  (0x2E)
#define MPU6050_I2C_SLV3_REG	  (0x2F)
#define MPU6050_I2C_SLV3_CTRL	  (0x30)
#define MPU6050_I2C_SLV4_ADDR	  (0x31)
#define MPU6050_I2C_SLV4_REG	  (0x32)
#define MPU6050_I2C_SLV4_DO		  (0x33)
#define MPU6050_I2C_SLV4_CTRL	  (0x34)
#define MPU6050_I2C_SLV4_DI		  (0x35)
#define MPU6050_I2C_MST_STATUS	(0x36)
#define MPU6050_INT_PIN_CFG		  (0x37)
#define MPU6050_INT_ENABLE		  (0x38)

//Bit Placements for page 6 of document
#define MPU6050_XA_TEST_4_2_BIT			  (7)
#define MPU6050_XG_TEST_4_0_BIT			  (4)
#define MPU6050_YA_TEST_4_2_BIT			  (7)
#define MPU6050_YG_TEST_4_0_BIT			  (4)
#define MPU6050_ZA_TEST_4_2_BIT			  (7)
#define MPU6050_ZG_TEST_4_0_BIT			  (4)
#define MPU6050_XA_TEST_1_0_BIT 		  (5)
#define MPU6050_YA_TEST_1_0_BIT			  (3)
#define MPU6050_ZA_TEST_1_0_BIT 		  (1)
#define MPU6050_EXT_SYNC_SET_BIT		  (5)
#define MPU6050_DLPF_CFG_BIT			    (2)
#define MPU6050_FS_SEL_BIT				    (4)
#define MPU6050_XA_ST_BIT				      (7)
#define MPU6050_YA_ST_BIT				      (6)
#define MPU6050_ZA_ST_BIT				      (5)
#define MPU6050_AFS_SEL_BIT				    (4)
#define MPU6050_TEMP_FIFO_EN_BIT		  (7)
#define MPU6050_XG_FIFO_EN_BIT			  (6)
#define MPU6050_YG_FIFO_EN_BIT			  (5)
#define MPU6050_ZG_FIFO_EN_BIT			  (4)
#define MPU6050_ACCEL_FIFO_EN_BIT		  (3)
#define MPU6050_SLV2_FIFO_EN_BIT		  (2)
#define MPU6050_SLV1_FIFO_EN_BIT		  (1)
#define MPU6050_SLV0_FIFO_EN_BIT		  (0)
#define MPU6050_MULT_MST_EN_BIT			  (7)
#define MPU6050_WAIT_FOR_ES_BIT			  (6)
#define MPU6050_SLV_3_FIFO_EN_BIT		  (5)
#define MPU6050_I2C_MST_P_NSR_BIT		  (4)
#define MPU6050_I2C_MST_CLK_BIT			  (3)
#define MPU6050_I2C_SLV0_RW_BIT			  (7)
#define MPU6050_I2C_SLV0_ADDR_BIT		  (6)
#define MPU6050_I2C_SLV0_EN_BIT			  (7)
#define MPU6050_I2C_SLV0_BYTE_SW_BIT	(6)
#define MPU6050_I2C_SLV0_REG_DIS_BIT	(5)
#define MPU6050_I2C_SLV0_GRP_BIT		  (4)
#define MPU6050_I2C_SLV0_LEN_BIT		  (3)
#define MPU6050_I2C_SLV1_RW_BIT			  (7)
#define MPU6050_I2C_SLV1_ADDR_BIT		  (6)
#define MPU6050_I2C_SLV1_EN_BIT			  (7)
#define MPU6050_I2C_SLV1_BYTE_SW_BIT	(6)
#define MPU6050_I2C_SLV1_REG_DIS_BIT	(5)
#define MPU6050_I2C_SLV1_GRP_BIT		  (4)
#define MPU6050_I2C_SLV1_LEN_BIT		  (3)
#define MPU6050_I2C_SLV2_RW_BIT			  (7)
#define MPU6050_I2C_SLV2_ADDR_BIT		  (6)
#define MPU6050_I2C_SLV2_EN_BIT			  (7)
#define MPU6050_I2C_SLV2_BYTE_SW_BIT	(6)
#define MPU6050_I2C_SLV2_REG_DIS_BIT	(5)
#define MPU6050_I2C_SLV2_GRP_BIT		  (4)
#define MPU6050_I2C_SLV2_LEN_BIT		  (3)
#define MPU6050_I2C_SLV3_RW_BIT			  (7)
#define MPU6050_I2C_SLV3_ADDR_BIT		  (6)
#define MPU6050_I2C_SLV3_EN_BIT			  (7)
#define MPU6050_I2C_SLV3_BYTE_SW_BIT	(6)
#define MPU6050_I2C_SLV3_REG_DIS_BIT	(5)
#define MPU6050_I2C_SLV3_GRP_BIT		  (4)
#define MPU6050_I2C_SLV3_LEN_BIT		  (3)
#define MPU6050_I2C_SLV4_RW_BIT			  (7)
#define MPU6050_I2C_SLV4_ADDR_BIT		  (6)
#define MPU6050_I2C_SLV4_EN_BIT			  (7)
#define MPU6050_I2C_SLV4_INT_EN_BIT		(6)
#define MPU6050_I2C_SLV4_REG_DIS_BIT	(5)
#define MPU6050_I2C_SLV4_DLY_BIT		  (4)
#define MPU6050_PASS_THROUGH_BIT		  (7)
#define MPU6050_I2C_SLV4_DONE_BIT		  (6)
#define MPU6050_I2C_LOST_ARB			    (5)
#define MPU6050_I2C_SLV4_NACK			    (4)
#define MPU6050_I2C_SLV3_NACK			    (3)
#define MPU6050_I2C_SLV2_NACK			    (2)
#define MPU6050_I2C_SLV1_NACK			    (1)
#define MPU6050_I2C_SLV0_NACK			    (0)
#define MPU6050_INT_LEVEL				      (7)
#define MPU6050_INT_OPEN				      (6)
#define MPU6050_LATCH_INT_EN			    (5)
#define MPU6050_INT_RD_CLEAR			    (4)
#define MPU6050_FSYNC_INT_LEVEL			  (3)
#define MPU6050_FSYNC_INT_EN			    (2)
#define MPU6050_I2C_BYPASS_EN			    (1)
#define MPU6050_MOT_EN					      (6)
#define MPU6050_FIFO_OFLOW_EN			    (4)
#define MPU6050_I2C_MST_INT_EN			  (3)
#define MPU6050_DATA_RDY_EN				    (0)

//BIT LENGTHS FOR PAGE 6
#define MPU6050_XA_TEST_4_2_LEN			(3)
#define MPU6050_XG_TEST_4_0_LEN			(5)
#define MPU6050_YA_TEST_4_2_LEN			(3)
#define MPU6050_YG_TEST_4_0_LEN			(5)
#define MPU6050_ZA_TEST_4_2_LEN			(3)
#define MPU6050_ZG_TEST_4_0_LEN			(5)
#define MPU6050_XA_TEST_1_0_LEN			(2)
#define MPU6050_YA_TEST_1_0_LEN			(2)
#define MPU6050_ZA_TEST_1_0_LEN			(2)
#define MPU6050_EXT_SYNC_SET_LEN		(3)
#define MPU6050_DLPF_CFG_LEN			  (3)
#define MPU6050_FS_SEL_LEN				  (2)
#define MPU6050_I2C_MST_CLK_LEN			(4)
#define MPU6050_I2C_SLV0_ADDR_LEN		(7)
#define MPU6050_I2C_SLV0_LEN_LEN		(4)
#define MPU6050_I2C_SLV1_ADDR_LEN		(7)
#define MPU6050_I2C_SLV1_LEN_LEN		(4)
#define MPU6050_I2C_SLV2_ADDR_LEN		(7)
#define MPU6050_I2C_SLV2_LEN_LEN		(4)
#define MPU6050_I2C_SLV3_ADDR_LEN		(7)
#define MPU6050_I2C_SLV3_LEN_LEN		(4)
#define MPU6050_I2C_SLV4_ADDR_LEN		(7)
#define MPU6050_I2C_MST_DLY_LEN			(5)
//END PAGE 6 DEFS

//PAGE 7 REGISTERS
#define MPU6050_INT_STATUS			(0x3A)
#define MPU6050_ACCEL_XOUT_H		(0x3B)
#define MPU6050_ACCEL_XOUT_L		(0x3C)
#define MPU6050_ACCEL_YOUT_H		(0x3D)
#define MPU6050_ACCEL_YOUT_L		(0x3E)
#define MPU6050_ACCEL_ZOUT_H		(0x3F)
#define MPU6050_ACCEL_ZOUT_L		(0x40)
#define MPU6050_TEMP_OUT_H			(0x41)
#define MPU6050_TEMP_OUT_L			(0x42)
#define MPU6050_GYRO_XOUT_H			(0x43)
#define MPU6050_GYRO_XOUT_L			(0x44)
#define MPU6050_GYRO_YOUT_H			(0x45)
#define MPU6050_GYRO_YOUT_L			  (0x46)
#define MPU6050_GYRO_ZOUT_H			  (0x47)
#define MPU6050_GYRO_ZOUT_L			  (0x48)
#define MPU6050_EXT_SENSE_DATA_00	(0x49)
#define MPU6050_EXT_SENSE_DATA_01	(0x4A)
#define MPU6050_EXT_SENSE_DATA_02	(0x4B)
#define MPU6050_EXT_SENSE_DATA_03	(0x4C)
#define MPU6050_EXT_SENSE_DATA_04	(0x4D)
#define MPU6050_EXT_SENSE_DATA_05	(0x4E)
#define MPU6050_EXT_SENSE_DATA_06	(0x4F)
#define MPU6050_EXT_SENSE_DATA_07	(0x50)
#define MPU6050_EXT_SENSE_DATA_08	(0x51)
#define MPU6050_EXT_SENSE_DATA_09	(0x52)
#define MPU6050_EXT_SENSE_DATA_10	(0x53)
#define MPU6050_EXT_SENSE_DATA_11	(0x54)
#define MPU6050_EXT_SENSE_DATA_12	(0x55)
#define MPU6050_EXT_SENSE_DATA_13	(0x56)
#define MPU6050_EXT_SENSE_DATA_14	(0x57)
#define MPU6050_EXT_SENSE_DATA_15	(0x58)
#define MPU6050_EXT_SENSE_DATA_16	(0x59)
#define MPU6050_EXT_SENSE_DATA_17	(0x5A)
#define MPU6050_EXT_SENSE_DATA_18	(0x5B)
#define MPU6050_EXT_SENSE_DATA_19	(0x5C)
#define MPU6050_EXT_SENSE_DATA_20	(0x5D)
#define MPU6050_EXT_SENSE_DATA_21	(0x5E)
#define MPU6050_EXT_SENSE_DATA_22	(0x5F)
#define MPU6050_EXT_SENSE_DATA_23	(0x60)
#define MPU6050_I2C_SLV0_DO			  (0X63)
#define MPU6050_I2C_SLV1_DO			  (0X64)

//PAGE 7 BIT PLACEMENT
#define MPU6050_MOT_INT_BIT			    (6)
#define MPU6050_FIFO_OFLOW_INT_BIT	(4)
#define MPU6050_I2C_MST_INT_BIT		  (3)
#define MPU6050_DATA_RDY_INT_BIT	  (0)
//END PAGE 7

//START PAGE 8
//REGISTERS
#define MPU6050_I2C_SLV2_DO			    (0x65)
#define MPU6050_I2C_SLV3_DO			    (0x66)
#define MPU6050_I2C_MST_DELAY_CT_RL	(0x67)
#define MPU6050_SIGNAL_PATH_RESET	  (0x68)
#define MPU6050_MOT_DETECT_CTRL		  (0x69)
#define MPU6050_USER_CTRL			      (0x6A)
#define MPU6050_PWR_MGMT_1			    (0x6B)
#define MPU6050_PWR_MGMT_2			    (0x6C)
#define MPU6050_FIFO_COUNTH			    (0x72)
#define MPU6050_FIFO_COUNTL			    (0x73)
#define MPU6050_FIFO_R_W			      (0x74)
#define MPU6050_WHO_AM_I			      (0x75)

//BIT PLACEMENTS
#define MPU6050_DELAY_ES_SHADOW_BIT	(7)
#define MPU6050_I2C_SLV4_DLY_EN_BIT	(4)
#define MPU6050_I2C_SLV3_DLY_EN_BIT	(3)
#define MPU6050_I2C_SLV2_DLY_EN_BIT (2)
#define MPU6050_I2C_SLV1_DLY_EN_BIT (1)
#define MPU6050_I2C_SLV0_DLY_EN_BIT (0)
#define MPU6050_GYRO_RESET_BIT		  (2)
#define MPU6050_ACCEL_RESET_BIT		  (1)
#define MPU6050_TEMP_RESET			    (0)
#define MPU6050_ACCEL_ON_DELAY_BIT	(5)
#define MPU6050_FIFO_EN_BIT			    (6)
#define MPU6050_I2C_MST_EN_BIT		  (5)
#define MPU6050_I2C_ID_DIS_BIT		  (4)
#define MPU6050_FIFO_RESET_BIT		  (2)
#define MPU6050_I2C_MST_RESET_BIT	  (1)
#define MPU6050_SIG_COND_RESET_BIT	(0)
#define MPU6050_DEVICE_RESET_BIT	  (7)
#define MPU6050_SLEEP_BIT			      (6)
#define MPU6050_CYCLE_BIT			      (5)
#define MPU6050_TEMP_DIS_BIT		    (3)
#define MPU6050_CLKSEL_BIT			    (2)
#define MPU6050_LP_WAKE_CTRL_BIT	  (7)
#define MPU6050_STBY_XA_BIT			    (5)
#define MPU6050_STBY_YA_BIT			    (4)
#define MPU6050_STBY_ZA_BIT			    (3)
#define MPU6050_STBY_XG_BIT			    (2)
#define MPU6050_STBY_YG_BIT			    (1)
#define MPU6050_STBY_ZG_BIT			    (0)
#define MPU6050_WHO_AM_I_BIT		    (6)

//BIT FIELD LENGTHS

#define MPU6050_ACCEL_ON_DELAY_LEN	(2)
#define MPU6050_CLKSEL_LEN			(3)
#define MPU6050_LP_WAKE_CTRL_LEN	(4)
#define MPU6050_WHO_AM_I_LEN		(6)

//END PAGE 8


#define MPU6050_RESET_REGISTER_VAL	(0x00)

//END PAGE 8

//page 9
//Gyroscope self test code found in MotionApps software by InvenSense
//self test response (STR) = gyroscope output w selftest enabled - "" disabled

//change from factory trim = (STR -FT)/FT where FT is factory trim value from motionapps

//uint8_t MPU6050_getAccel_X_SelfTestFactoryTrim(){
	//HAL_I2C_Mem_Read(I2C_PORT, MPU6050_DEFAULT_ADDRESS, MPU6050_SELF_TEST_X, 1, &buf[0]);

//}



//Init
void MPU6050_Init();
int16_t MPU6050_Read_Accel(void);

#endif /* MPU6050_DRIVER_H */
