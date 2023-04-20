# ECE 4180 Security Cam
Security camera using Rapberry Pi Zero W and mbed peripherals

### Features:

+ Motion sensing camera using LiDAR
+ Pictures sent to email when objects get close to camera
+ Flashing light to alert when an object is close
+ Alarm sound when an object is close

### Required materials:

+ Raspberry Pi (we used Zero W)
+ Raspberry Pi Camera Module
+ Mbed NXP LPC1768 microcontroller (possible with other microcontrollers such as Arduino)
+ Breadboard for prototyping
+ Simple LED for breadboard
+ Speaker with Class D audio output
+ VL53L0X LiDAR
+ Jumper wires
+ micro SD card
+ External 5V power supply

## Process

### Setup Raspberry Pi

Perform a basic Raspberry Pi setup including Raspian OS using a micro SD card and an imager, as described [here](https://www.raspberrypi.com/software/).  
Setup wifi using the Raspberry Pi Imager.  
After OS is installed, update Raspberry Pi using `sudo apt update` and `sudo apt full-upgrade` in the terminal window.  
After upgrading, make sure Camera module is attached properly, and enabled via Preferences->Raspberry Pi Configuration->Interfaces.  
Also in Interfaces, enable VNC if desired to use a VNC on your computer for Pi operation.

### Setup Mbed

With the Mbed mounted to the breadboard, first attach VL53L0X using 3.3(Vout) for Vin, p28 for SDA, p27 for SCL, P26 for shdn, and Gnd to Gnd.
Attach LED in series with a 220 ohm resister from ground to P5.
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

