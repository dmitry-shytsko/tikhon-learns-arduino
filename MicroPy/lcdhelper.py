from machine import I2C, Pin
from I2C_LCD import I2cLcd


def init_lcd(scl_pin: int, sda_pin: int):
    i2c = I2C(scl=Pin(25), sda=Pin(26), freq=400000)
    i2c_devices = i2c.scan()

    if len(i2c_devices) == 0:
        print("No I2C device found :(")
    else:
        for device in i2c_devices:
            # So far we are assuming that there is a single LCD device
            print("I2C address: " + hex(device))
            return I2cLcd(i2c, device, 2, 16)

    return None
