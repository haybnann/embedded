/*
 * Files: bmp180driver.h
 * These files are a driver for the BMP180 Temperature & Pressure sensor
 *
 */


#include "stm32f1xx_hal.h"
#include "math.h"

extern I2C_HandleTypeDef hi2c2;//define which i2c port the sensor is attached to
#define BMP180_I2C &hi2c2		// point to the i2c port with generalized name

//pg 20 shows the BMP180 address
#define BMP180_ADDRESS 				(0xEE)
#define BMP180_CTRL_MEAS_REG        (0xF4)
#define BMP180_ADC_OUT_MSB_REG      (0xF6)



// Defines according to the datsheet
//TAble 5 data sheet
//variables to store calibration data in EEPROM
short AC1 = 0;
short AC2 = 0;
short AC3 = 0;
unsigned short AC4 = 0;
unsigned short AC5 = 0;
unsigned short AC6 = 0;
short B1 = 0;
short B2 = 0;
short MB = 0;
short MC = 0;
short MD = 0;

/********************/
//pg 15 intermediate values to do calculations with
long UT = 0;
short oss = 0;//controls oversampling ratio - register F4h
long UP = 0;
long X1 = 0;
long X2 = 0;
long X3 = 0;
long B3 = 0;
long B5 = 0;
unsigned long B4 = 0;
long B6 = 0;
unsigned long B7 = 0;

/*******************/
//globals to store current temp & pressure
long Press = 0;
long Temp = 0;


//sea level pressure in pascals
#define atmPress 101325 //Pa


/*
 * This function
 */
void read_calliberation_data (void)
{
	uint8_t Callib_Data[22] = {0};//empty buffer to store data in
	uint16_t Callib_Start = 0xAA; //first EEPROM register
	//send & receive i2c data
	//READ more on i2cmemread
	HAL_I2C_Mem_Read(BMP180_I2C, BMP180_ADDRESS, Callib_Start, 1, Callib_Data,22, HAL_MAX_DELAY);
	//save values into respective uint16 variables
	//shifting and ORing as necessary(convert 2 8-bits into a single 16 bit value)
	AC1 = ((Callib_Data[0] << 8) | Callib_Data[1]);
	AC2 = ((Callib_Data[2] << 8) | Callib_Data[3]);
	AC3 = ((Callib_Data[4] << 8) | Callib_Data[5]);
	AC4 = ((Callib_Data[6] << 8) | Callib_Data[7]);
	AC5 = ((Callib_Data[8] << 8) | Callib_Data[9]);
	AC6 = ((Callib_Data[10] << 8) | Callib_Data[11]);
	B1 = ((Callib_Data[12] << 8) | Callib_Data[13]);
	B2 = ((Callib_Data[14] << 8) | Callib_Data[15]);
	MB = ((Callib_Data[16] << 8) | Callib_Data[17]);
	MC = ((Callib_Data[18] << 8) | Callib_Data[19]);
	MD = ((Callib_Data[20] << 8) | Callib_Data[21]);

}


// Get uncompensated Temp
uint16_t Get_UTemp (void)
{
	uint8_t datatowrite = 0x2E;//Temperature register address: page 21
	uint8_t Temp_RAW[2] = {0}; //empty buffer to write to

	//write data from temp register to 0xF4(control registrer)
	HAL_I2C_Mem_Write(BMP180_I2C, BMP180_ADDRESS, BMP180_CTRL_MEAS_REG, 1, &datatowrite, 1, 1000);
	HAL_Delay (5);  // wait 4.5 ms

	//read data from 0xF6 and write it to temp_raw
	HAL_I2C_Mem_Read(BMP180_I2C, BMP180_ADDRESS, BMP180_ADC_OUT_MSB_REG , 1, Temp_RAW, 2, 1000);

	//return the 16 bit representation of non-calibrated temperature data
	return ((Temp_RAW[0]<<8) + Temp_RAW[1]);
}

float BMP180_GetTemp (void)
{
	UT = Get_UTemp();//get non-calibrated temp
	//calibrate the temperature
	//formula is found on page 15 in datasheet
	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
	X2 = ((MC*(pow(2,11))) / (X1+MD));
	B5 = X1+X2;
	Temp = (B5+8)/(pow(2,4));
	//reture calibrated floating point representation of the temperature
	return Temp/10.0;
}

// Get uncompensated Pressure
uint32_t Get_UPress (int oss)   // oversampling setting 0,1,2,3
{
	uint8_t datatowrite = 0x34+(oss<<6);//read from whichever register 0 to 3 (depends on oss)
	uint8_t Press_RAW[3] = {0}; //registers to write raw data to
	//write data from 0x34 to control register 0xf4 ??
	HAL_I2C_Mem_Write(BMP180_I2C, BMP180_ADDRESS, BMP180_CTRL_MEAS_REG, 1, &datatowrite, 1, 1000);
	//delay time is dependent on oversampling setting
	switch (oss)
	{
		case (0):
			HAL_Delay (5);
			break;
		case (1):
			HAL_Delay (8);
			break;
		case (2):
			HAL_Delay (14);
			break;
		case (3):
			HAL_Delay (26);
			break;
	}
	//read data from pressure register to empty pressure buffer
	HAL_I2C_Mem_Read(BMP180_I2C, BMP180_ADDRESS, BMP180_ADC_OUT_MSB_REG , 1, Press_RAW, 3, 1000);
	//return the non-calibrated value as 32 bit value
	return (((Press_RAW[0]<<16)+(Press_RAW[1]<<8)+Press_RAW[2]) >> (8-oss));
}


float BMP180_GetPress (int oss)
{
	UP = Get_UPress(oss);//get non-calibrated pressure
	//calibrate the prssure
	//change all the powers to bit shifts and get rid of math lib

	X1 = ((UT-AC6) * (AC5/(pow(2,15))));
	X2 = ((MC*(pow(2,11))) / (X1+MD));
	B5 = X1+X2;
	B6 = B5-4000;
	X1 = (B2 * (B6*B6/(pow(2,12))))/(pow(2,11));
	X2 = AC2*B6/(pow(2,11));
	X3 = X1+X2;
	B3 = (((AC1*4+X3)<<oss)+2)/4;
	X1 = AC3*B6/pow(2,13);
	X2 = (B1 * (B6*B6/(pow(2,12))))/(pow(2,16));
	X3 = ((X1+X2)+2)/pow(2,2);
	B4 = AC4*(unsigned long)(X3+32768)/(pow(2,15));
	B7 = ((unsigned long)UP-B3)*(50000>>oss);
	if (B7<0x80000000) Press = (B7*2)/B4;
	else Press = (B7/B4)*2;
	X1 = (Press/(pow(2,8)))*(Press/(pow(2,8)));
	X1 = (X1*3038)/(pow(2,16));
	X2 = (-7357*Press)/(pow(2,16));
	Press = Press + (X1+X2+3791)/(pow(2,4));


	//return floating point value of calibrated pressure
	return Press;
}


float BMP180_GetAlt (int oss)
{
	BMP180_GetPress (oss);//get pressure
	//compare it to sea level pressures
	//formula on  pg 16
	return 44330*(1-(pow((Press/(float)atmPress), 0.19029495718)));
}

void BMP180_Start (void)
{
	//read calibration data from registers
	read_calliberation_data();
}
