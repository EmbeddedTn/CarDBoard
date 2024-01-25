#ifndef HAL_TMP006_H_
#define HAL_TMP006_H_

/* CONSTANTS */
#define TMP006_SLAVE_ADDRESS    0x40

/* TEMPERATURE SENSOR REGISTER DEFINITIONS */
#define TMP006_P_VOBJ           0x00
#define TMP006_P_TABT           0x01
#define TMP006_WRITE_REG        0x02
#define TMP006_P_MAN_ID         0xFE
#define TMP006_P_DEVICE_ID      0xFF

/* CONFIGURATION REGISTER SETTINGS */
#define TMP006_RST              0x8000
#define TMP006_POWER_DOWN       0x0000
#define TMP006_POWER_UP         0x7000
#define TMP006_CR_4             0x0000
#define TMP006_CR_2             0x0200
#define TMP006_CR_1             0x0400
#define TMP006_CR_0_5           0x0600
#define TMP006_CR_0_25          0x0800
#define TMP006_EN               0x0100
#define TMP006_DRDY             0x0080

#define I2C_SCL    BIT7;
#define I2C_SDA    BIT6;

void TMP006_init(void);
long double TMP006_getTemp(void);
int TMP006_readDeviceId(void);
int TMP006_readObjectVoltage(void);
int TMP006_readAmbientTemperature(void);
int TMP006_read(unsigned char);
void TMP006_write(unsigned char pointer, unsigned int writeByte);


#endif /* HAL_TMP006_H_ */
