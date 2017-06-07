# mynewt-de-schilken-microbit
Experimental apache mynewt bsp and drivers for bbc microbit: button, ssd1306, si1145, led-matrix 


#usage
### Make the repo available locally in your proeject.yml
```

project.repositories:
    - apache-mynewt-core
    - mynewt-de-schilken-microbit

repository.mynewt-de-schilken-microbit:
    type: github
    vers: 0-latest
    user: schilken
    repo: mynewt-de-schilken-microbit
```



### Create a target

```
newt target create mydrivertest_repo
newt target set mydrivertest_repo \
	app=@mynewt-de-schilken-microbit/apps/mydrivertest \
	bsp=@mynewt-de-schilken-microbit/hw/bsp/bbc_microbit \
	build_profile=debug
newt target show mydrivertest_repo
```

### build and deploy it to a connected bbc_microbit 
newt run mydrivertest_repo 0.7.7


### Connect a terminal to the usb-uart ( I use CoolTerm on m mac :-)

Try out the commands:
* write string to microbit 5x5 LED matrix
* write character to microbit 5x5 LED matrix
* react on button press with writing to LEDs
* scan i2c-bus
* set gpios
* write text to a connected oled ( ssd1306 )
* read uv index of connected SI1145 ( I use the one of adafruit )


```
33659: > ?

Commands:
33842:     stat    config       log      imgr      echo         ? 
33843:   prompt     ticks     tasks  mempools      date      gpio 
33845:      i2c      oled        uv    matrix 

33846: > gpio
usage: gpio <pin> <onOff>, <pin>: P0..P20 oder p0..p30, onOff: 0 oder 1

35569: > i2c
i2c probe|scan

36258: > oled
oled clr|p <string>

36737: > uv
uv check|r

37232: > matrix

matrix c <char> | p <string>
```


Modify the pin configuration in hw/bsp/bbc_microbit/src/hal_bsp.c, if you don't want to use the standard i2c bus:

```
#if MYNEWT_VAL(I2C_0)
static const struct nrf51_hal_i2c_cfg hal_i2c_cfg = {
    .scl_pin = 0,   // EDGE PIN 20
    .sda_pin = 30,  // EDGE PIN 19
    .i2c_frequency = 100    /* 100 kHz */
};
#endif
```
