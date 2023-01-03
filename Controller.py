import hid, time, serial, time, sys, signal
import serial.tools.list_ports
def signal_handler(signal, frame):
	print("closing program")
	SerialPort.close()
	sys.exit(0)

COM=input("Enter the COM Port\n")
BAUD=input("Enter the Baudrate\n")
"""
for i in serial.tools.list_ports.comports():
    try:
            SerialPort = serial.Serial(i.device,9600,timeout=0.1)
    except:
            pass
"""
    
SerialPort = serial.Serial(COM,BAUD,timeout=1)

for device in hid.enumerate():
    if device['product_string'] == "Wireless Controller":
        gamepad = hid.device()
        gamepad.open(0x054c, 0x09cc)
        gamepad.set_nonblocking(True)

while True:
    report = gamepad.read(64)
    new_report = []
    if report:
        left = report[1] * 2
       
        up = report[4] * 2

        if left < 509:
            left = -left - 1
        else:
            left = left - 1

        if up < 509:
            up = -up - 1
        else:
            up = up - 1

        if left == -1:
            left = 0
        elif up == -1:
            up = 0

        left = left + 255
        up = up + 255

        if left > 762:
            left = -255
        if up > 762:
            up = -255

        if left < 15 and left > -15:
            left = 0
        if up < 15 and up > -15:
            up = 0

        if up > 200:
            up = 255
        if left > 200:
            left = 255
        if up < -200:
            up = -255
        if left < -200:
            left = -255

        motor_left = 0
        motor_right = 0
        
        if up != 0 and left == 0:
            motor_left = up
            motor_right = up
        if up == 0 and left != 0:
            if left > 0:
                motor_left = -left
                motor_right = left
            else:
                motor_right = left
                motor_left = abs(left)
        else:
            motor_left = up
            motor_right = up
            if left > 0 and up > 0:
                motor_left = motor_left - left
            elif left < 0 and up > 0:
                motor_right = motor_right + left
            else:
                if left > 0:
                    motor_left = motor_left + left
                else:
                    motor_right = motor_right - left
    else:
        left = 0
        up = 0
        motor_left = 0
        motor_right = 0
    
    directions = ""

    
    if motor_left > motor_right and motor_left > -1 and motor_right > -1:
            motor_right = 128
            yey = True
    elif motor_right > motor_left and motor_left > -1 and motor_right > -1:
            motor_left = 128
            yer = True
            
    
    if motor_left < 0:
        directions = directions + "R"
    elif motor_left == 0:
        directions = directions + "S"
    else:
        directions = directions + "F"

    if motor_right < 0:
        directions = directions + "R"
    elif motor_left == 0:
        directions = directions + "S"
    else:
        directions = directions + "F"

    if directions == "SS":
        directions = "S"
    elif directions == "FF":
        directions = "F"
    elif directions == "RF":
        directions = "J"
    elif directions == "FR":
        directions = "K"
    elif directions == "RR":
        directions = "R"

    try:
            if yer == True:
                    directions = "Z"
                    del yer
    except:
            pass
    try:        
            if yey == True:
                    directions = "X"
                    del yey
    except:
            pass
        
    #print(str(motor_left).replace('-', 'R')[0 + ":" + str(motor_right).replace('-', 'R'))
    SerialPort.write(bytes(directions + "\n",'utf-8'))
    

    #print(str(motor_left) + ":" + str(motor_right))
    print(directions)

    time.sleep(0.01)
