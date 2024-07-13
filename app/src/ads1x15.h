#ifndef ADS1X15_H
#define ADS1X15_H

#include "ads1015_defs.h"
#include <zephyr/kernel.h>
#include <limits.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/drivers/i2c.h>

/**
 * @brief Set the thresholds for ADS1015 through i2c
 *
 * @param ads_i2c the ads i2c device
 * @param lowerThreshold must be between INT12_MIN and INT12_MAX
 * @param upperThreshold must be between INT12_MIN and INT12_MAX
 * @return if there is any errors while sending i2c
 */
static int ADS1x15_set_thresholds(const struct i2c_dt_spec *ads_i2c, int16_t lowerThreshold, int16_t upperThreshold)
{
    int err;
    uint8_t sendConfigBuff[3];
    int16_t *pConfigData = (int16_t *)&sendConfigBuff[1];

    // set lower threshold for ALRT signal trigger with sendConfigBuff
    sendConfigBuff[0] = ADS1015_REG_POINTER_LOWTHRESH;
    *pConfigData = sys_cpu_to_be16(lowerThreshold);
    err = i2c_write_dt(ads_i2c, sendConfigBuff, 3);
    if (err != 0)
    {
        printk("write i2c error while writing lower threshold\n");
        return -1;
    }

    // set upper threshold for ALRT signal trigger with sendConfigBuff
    sendConfigBuff[0] = ADS1015_REG_POINTER_HITHRESH;
    *pConfigData = sys_cpu_to_be16(upperThreshold);
    err = i2c_write_dt(ads_i2c, sendConfigBuff, 3);
    if (err != 0)
    {
        printk("write i2c error while writing upper threshold\n");
        return -1;
    }
    return 0;
}

static int ADS1x15_set_config(const struct i2c_dt_spec *ads_i2c, uint16_t config_bitmask)
{
    int err;
    uint8_t sendConfigBuff[3];

    sendConfigBuff[0] = ADS1015_REG_POINTER_CONFIG;
    *((int16_t *)&sendConfigBuff[1]) = sys_cpu_to_be16(config_bitmask);

    err = i2c_write_dt(ads_i2c, sendConfigBuff, 3);
    if (err != 0)
    {
        printk("write i2c error\n");
        return -1;
    }
    return 0;
}

/**
 * @brief Reads what's avaliable from ADS1015 currently. Does not check
 * for if data is ready, nor have i2c error handling
 *
 * @param ads_i2c the ads i2c device
 * @return the value that is read from ads1015, between INT12_MIN and INT12_MAX
 */
static int16_t ADS1x15_read(const struct i2c_dt_spec *ads_i2c)
{
    int err;
    static const uint8_t sendDataReqBuff = ADS1015_REG_POINTER_CONVERT;
    err = i2c_write_dt(ads_i2c, &sendDataReqBuff, 1);

    uint8_t rx_bytes[2];
    err = i2c_read_dt(ads_i2c, rx_bytes, 2);
    int16_t value = ((rx_bytes[0] << 8) | rx_bytes[1]);
    return value;
}

#endif