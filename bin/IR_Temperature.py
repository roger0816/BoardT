import sys
import smbus
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(17, GPIO.IN)   #IR 1
GPIO.setup(27, GPIO.OUT)  #Green LED 1
GPIO.setup(22, GPIO.OUT)  #Red LED 1
GPIO.setup(10, GPIO.IN)   #IR 2
GPIO.setup(9, GPIO.OUT)   #Green LED 2
GPIO.setup(11, GPIO.OUT)  #Red LED 2
GPIO.setup(5, GPIO.IN)    #IR 3
GPIO.setup(6, GPIO.OUT)   #Green LED 3
GPIO.setup(12, GPIO.OUT)  #Red LED 3
GPIO.setup(13, GPIO.IN)   #IR 4
GPIO.setup(19, GPIO.OUT)  #Green LED 4
GPIO.setup(26, GPIO.OUT)  #Red LED 4
GPIO.setup(16, GPIO.IN)   #IR 5
GPIO.setup(20, GPIO.OUT)  #Green LED 5
GPIO.setup(21, GPIO.OUT)  #Red LED 5

IR_GPIO = [17, 10, 5, 13, 16]
G_LED_GPIO = [27, 9, 6, 19, 20]
R_LED_GPIO = [22, 11, 12, 26, 21]

arg_len = len(sys.argv)

if (arg_len > 1) or (arg_len < 7):
    del sys.argv[0]
    addr_list = []
    for addr_item in sys.argv:
        addr_value = int(str(addr_item),16)
        if (addr_value >= 0x03) and (addr_value <= 0x77):
            addr_list.append(addr_value)
            print "address = " , addr_value
        else:
            print "Please set correct device address (0x01 ~ 0xFE)"
            break
    addr_list_len = len(addr_list)
    if (addr_list_len == arg_len - 1):
        i2c = smbus.SMBus(1)  # use /dev/i2c-1
        chk_hum_flag = 0
        while (1):
            out_str = ""                
            temp_list = []
            idx = 0
            if (chk_hum_flag == 0):              
                chk_hum = GPIO.input(IR_GPIO[idx])
                if (chk_hum > 0):
                    chk_hum_flag = 5
                else:
                    temp_value = 0
                    GPIO.output(G_LED_GPIO[idx],0)
                    GPIO.output(R_LED_GPIO[idx],0)
            elif (chk_hum_flag > 0):
                chk_hum_flag -= 1
                for addr_value in addr_list:
                    reg = 0x0c            # access BO high byte reg
                    read_value = i2c.read_byte_data(addr_value,reg)   # read data
                    temp_value = 256.0*read_value
                    reg = 0x0d            # access BO low byte reg
                    read_value = i2c.read_byte_data(addr_value,reg)   # read data
                    temp_value = (temp_value + read_value)/100
                    print "sensor temp_value:", temp_value
                    if (temp_value > 37):
                        GPIO.output(R_LED_GPIO[idx],1)
                        GPIO.output(G_LED_GPIO[idx],0)
                    elif (temp_value >= 33):
                        GPIO.output(R_LED_GPIO[idx],0)
                        GPIO.output(G_LED_GPIO[idx],1)
                    else:
                        temp_value = 0
                        GPIO.output(G_LED_GPIO[idx],0)
                        GPIO.output(R_LED_GPIO[idx],0)   
                        
                    temp_list.append(temp_value)
                    idx += 1
                
            for temp_item in temp_list:
                out_str += str(temp_item) + " ";
            print out_str                     
            file = open("input.txt","w")                    
            file.writelines(out_str)
            file.close()
            time.sleep(1)                    
            
elif (arg_len < 2):
    print "Please set device address"
else:
    print "Please set less than 5 devices"


