import smtplib
import time
import serial

from picamera import PiCamera
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage

#Camera Settings
camera = PiCamera()
camera.resolution = (2592, 1944)
camera.framerate = 15

#Email Variables
SMTP_SERVER = 'smtp.gmail.com' #Email Server (don't change!)
SMTP_PORT = 587 #Server Port (don't change!)
GMAIL_USERNAME = '' #change this to match your gmail account
GMAIL_PASSWORD = ''  #change this to match your gmail password

class Emailer:
    def sendmail(self, recipient, subject, content, image):

        #Create Headers
        emailData = MIMEMultipart()
        emailData['Subject'] = subject
        emailData['To'] = recipient
        emailData['From'] = GMAIL_USERNAME

        #Attach our text data
        emailData.attach(MIMEText(content))

        #Create our Image Data from the defined image
        imageData = MIMEImage(open(image, 'rb').read(), 'jpg')
        imageData.add_header('Content-Disposition', 'attachment; filename="image.jpg"')
        emailData.attach(imageData)

        #Connect to Gmail Server
        session = smtplib.SMTP(SMTP_SERVER, SMTP_PORT)
        session.ehlo()
        session.starttls()
        session.ehlo()

        #Login to Gmail
        session.login(GMAIL_USERNAME, GMAIL_PASSWORD)

        #Send Email & Exit
        session.sendmail(GMAIL_USERNAME, recipient, emailData.as_string())
        session.quit

sender = Emailer()

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
	if '1' in line:
            detected = True
	if(detected == True):
            	detected = False
		image = '/home/pi/Desktop/image.jpg'
		camera.capture(image)
		sendTo = '' #change this to your recipient, or yourself
		emailSubject = "Motion Detected"
		emailContent = "Image attached"
		sender.sendmail(sendTo, emailSubject, emailContent, image)
		print("Email Sent")
    time.sleep(10)
