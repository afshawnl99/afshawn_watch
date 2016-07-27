import serial
import calendar
import datetime
import os



class SerialSSH:
    def __init__(self):
        self.epoch = str(calendar.timegm(datetime.datetime.now().timetuple()))


        try:
            self.serial_port = serial.Serial('/dev/cu.usbmodem411', 9600)
            
            self.ssh_client()
        except:
            pass



    
    
    def ssh_client(self):
        serial_input = self.serial_port.readline()
        if "launch-serial" in serial_input:
            self.serial_port.write("stop")
        elif "show-home" in serial_input:
            # print "T%s"%self.epoch
            self.serial_port.write("T%s"%self.epoch)

        


        elif "ssh-command" in serial_input:
            serial_input = serial_input.replace("ssh-command ", "").strip()
            print serial_input
            try:
                output = os.popen(serial_input).read()
                output_list = [y for y in (x.strip() for x in output.splitlines()) if y]
                output = ""
                for items in output_list:
                    output = output + items + ","

                print output_list
                print output
                self.serial_port.write(output)
            except:
                pass
        else:
            serial_read = self.serial_port.readline()
            print serial_read

        self.ssh_client()



    

serial_class = SerialSSH()

    
    








