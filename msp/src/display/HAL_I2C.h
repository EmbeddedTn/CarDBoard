#ifndef __HAL_I2C_H_
#define __HAL_I2C_H_

void Init_I2C_GPIO(void);
void I2C_init(void);
int I2C_read16(unsigned char);
void I2C_write16(unsigned char pointer, unsigned int writeByte);
void I2C_setslave(unsigned int slaveAdr);


#endif /* __HAL_I2C_H_ */
