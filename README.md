# ECE 4180 Security Cam
Security camera using Rapberry Pi Zero W and mbed peripherals

### Features:

+ Motion sensing camera using LiDAR
+ Pictures sent to email when objects get close to camera
+ Flashing light to alert when an object is close
+ Alarm sound when an object is close

### Required materials:

+ Raspberry Pi (we used Zero W)
![Zero W](https://images.prismic.io/rpf-products/9371b539-77d4-47f1-b89b-aa65b23c9833_RPI%20ZERO%20W%20ANGLE%202%20REFRESH_.jpg?ixlib=gatsbyFP&auto=compress%2Cformat&fit=max&w=799&h=533)
+ Raspberry Pi Camera Module
![Camera](https://images.prismic.io/rpf-products/ffa68a46-fd44-4995-9ad4-ac846a5563f1_Camera%20V2%20Hero.jpg?ixlib=gatsbyFP&auto=compress%2Cformat&fit=max&w=799&h=533)
+ Mbed NXP LPC1768 microcontroller (possible with other microcontrollers such as Arduino)  
![Mbed](https://os.mbed.com/media/platforms/lpc1768_pinout.png)
+ Breadboard for prototyping
+ RGB LED for breadboard
+ Speaker with Class D audio output
+ VL53L0X LiDAR  
![VL53L0X](https://www.geeky-gadgets.com/wp-content/uploads/2016/11/Time-of-Flight-Distance-Sensor.jpg)
+ Jumper wires
+ micro SD card
+ External 5V power supply
+ 2 100 ohm resistors
+ 1 180 ohm resistor

## Process

### Setup Raspberry Pi

Perform a basic Raspberry Pi setup including Raspian OS using a micro SD card and an imager, as described [here](https://www.raspberrypi.com/software/).  
Setup wifi using the Raspberry Pi Imager.  
After OS is installed, update Raspberry Pi using `sudo apt update` and `sudo apt full-upgrade` in the terminal window.  
After upgrading, make sure Camera module is attached properly, and enabled via Preferences->Raspberry Pi Configuration->Interfaces.  
Also in Interfaces, enable VNC if desired to use a VNC on your computer for Pi operation.

### Setup Mbed

With the Mbed mounted to the breadboard, first attach VL53L0X using 3.3(Vout) for Vin, p28 for SDA, p27 for SCL, P26 for shdn, and Gnd to Gnd.  
![image](https://user-images.githubusercontent.com/109312052/234923030-9e7328f0-6e25-4d12-9294-a8aed80df002.png)  
Attach RGB LED in series with 3 resistors. The 180 ohm resistor is used for the red LED, and 100 ohm resistors lead from the green and blue LEDs. The red LED connects with p23, the green with p22, and blue with p21 PWM outputs on the Mbed. Don't forget to connect the ground lead on the LED as well.
![LED](https://os.mbed.com/media/uploads/4180_1/rgbledschematic.png)
Attach speaker with Class D audio output as described [here](https://os.mbed.com/users/4180_1/notebook/using-a-speaker-for-audio-output/).  
Attach Mbed to Raspberry Pi using micro USB cable with USBTX and USBRX.

### Program Mbed and Raspberry Pi

Using Keil Studio Cloud, upload the included .tar file project and build the project with your Mbed attached.  
On the Raspberry Pi, download the attached main.py file.  
Using a python editor, alter main.py by changing:
```
GMAIL_USERNAME = '' #change this to match your gmail account
GMAIL_PASSWORD = ''  #change this to match your gmail password
```
along with:
```
sendTo = ''
emailSubject = "Motion Detected"
emailContent = "Image attached"
```
with your desired inputs.  
Attach the Mbed to the Raspberry Pi using the micro USB and restart.  
Run the Pi program using `python3 ~/ECE-4180-Security-Cam/code/Pi/main.py`.

Now, every time an object comes within 0.5 meters of the LiDAR, a picture will be taken and sent to your email address.  
This will only happen once every 10 seconds to prevent an email flood from occurring.

### Optional

Build a case or housing for the security camera using a 3D printer or other preferred method.

