#include "mbed.h"
#include "rtos.h"
#include "SDFileSystem.h"
#include "wave_player.h"
#include "uLCD_4DGL.h"
#include "XNucleo53L0A1.h"
#include <stdio.h>

RawSerial pi(USBTX, USBRX);
DigitalOut shdn(p26);
// This VL53L0X board test application performs a range measurement in polling mode
// Use 3.3(Vout) for Vin, p28 for SDA, p27 for SCL, P26 for shdn on mbed LPC1768

//I2C sensor pins
#define VL53L0_I2C_SDA   p28
#define VL53L0_I2C_SCL   p27

static XNucleo53L0A1 *board=NULL;

PwmOut speaker(p24);

class RGBLed
{
public:
    RGBLed(PinName redpin, PinName greenpin, PinName bluepin);
    void write(float red,float green, float blue);
private:
    PwmOut _redpin;
    PwmOut _greenpin;
    PwmOut _bluepin;
};

RGBLed::RGBLed (PinName redpin, PinName greenpin, PinName bluepin)
    : _redpin(redpin), _greenpin(greenpin), _bluepin(bluepin)
{
    //50Hz PWM clock default a bit too low, go to 2000Hz (less flicker)
    _redpin.period(0.0005);
}

void RGBLed::write(float red,float green, float blue)
{
    _redpin = red;
    _greenpin = green;
    _bluepin = blue;
}

//Setup RGB led using PWM pins and class
RGBLed myRGBled(p23,p22,p21); //RGB PWM pins
PwmOut red(p23);
PwmOut green(p22);
PwmOut blue(p21);

void siren(void const *args) {
    int i;
    for (i=0; i<26; i=i+2) {
            speaker.period(1.0/969.0);
            speaker = float(i)/50.0;
            wait(.5);
            speaker.period(1.0/800.0);
            wait(.5);
        }
// decrease volume
        for (i=25; i>=0; i=i-2) {
            speaker.period(1.0/969.0);
            speaker = float(i)/50.0;
            wait(.5);
            speaker.period(1.0/800.0);
            wait(.5);
        }
        speaker = 0.0;
        wait(2);
}

void police(void const *args)
{
    while(1) {
        //flash three times on LED1
        for (float x=1.0; x>=0.0001; x=x*0.9) {
            myRGBled.write(x, 0.0, 0.0);
            Thread::wait(2);
        }
        for (float x=1.0; x>=0.0001; x=x*0.9) {
            myRGBled.write(0.0, 0.0, x);
            Thread::wait(2);
        }
    }
}

int main()
{
   // FILE *wave_file;
    Thread thread1(police);
    Thread thread2(siren);
    // Thread thread3(text);
    pi.baud(9600);
    int status;
    uint32_t distance;
    DevI2C *device_i2c = new DevI2C(VL53L0_I2C_SDA, VL53L0_I2C_SCL);
    /* creates the 53L0A1 expansion board singleton obj */
    board = XNucleo53L0A1::instance(device_i2c, A2, D8, D2);
    shdn = 0; //must reset sensor for an mbed reset to work
    wait(0.1);
    shdn = 1;
    wait(0.1);
    /* init the 53L0A1 board with default values */
    status = board->init_board();
    //loop taking and printing distance
    while (1) {
        status = board->sensor_centre->get_distance(&distance);
        if (status == VL53L0X_ERROR_NONE) {
            if (distance < 500) {
                pi.putc(1);
                Thread thread1(police);
                Thread thread2(siren);
            } else {
                pi.putc(0);
                thread1.terminate();
                thread2.terminate();
            }
        }
        wait(2);
    }
}
