#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>

#include "ads1x15.h"
#include "ads1115_defs.h"

// i2c adc devices
struct i2c_dt_spec ads_i2c = I2C_DT_SPEC_GET(DT_ALIAS(ads1015device));

int main_thread(void)
{
    int ret;

    if (!device_is_ready(ads_i2c.bus))
    {
        printk("the i2c bus for the ads1015 is not ready\n");
        return -1;
    }

    while (true)
    {
        // send configuration to ads1015
        ret = ADS1x15_set_config(
            &ads_i2c,
            (ADS1115_REG_CONFIG_MUX_DIFF_0_1 |
             ADS1115_REG_CONFIG_OS_SINGLE |
             ADS1115_REG_CONFIG_PGA_6_144V |
             ADS1115_REG_CONFIG_DR_860SPS |
             ADS1115_REG_CONFIG_MODE_CONTIN |
             ADS1115_REG_CONFIG_CMODE_TRAD |
             ADS1115_REG_CONFIG_CPOL_ACTVLOW |
             ADS1115_REG_CONFIG_CLAT_NONLAT |
             ADS1115_REG_CONFIG_CQUE_1CONV));
        if (ret != 0)
            return 1;

        // wait for data
        k_sleep(K_MSEC(100));

        int16_t value = ADS1x15_read(&ads_i2c);
        double voltage = value * (6.144 / (32768));
        printk("channel 1: %lf", voltage);
    }

    return 0;
}

K_THREAD_DEFINE(thread_main, 40960, main_thread, NULL, NULL, NULL, 1, 0, 0);
