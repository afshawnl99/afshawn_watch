import serial
import calendar
import datetime
import os


class SerialSSH:
    def __init__(self):
        self.epoch = str(calendar.timegm(datetime.datetime.now().timetuple()))


        try:
            self.serial_port = serial.Serial('/dev/cu.HC-06-DevB', 9600)
            
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
                output_read = os.popen(serial_input).read()
                output_list = [y for y in (x.strip() for x in output_read.splitlines()) if y]
                output = ""
                for items in output_list:
                    output = output + items + ","

                print output_list
                print output
                self.serial_port.write(output)
            except:
                pass

        else:
            print serial_input
        self.ssh_client()




    

serial_class = SerialSSH()

    
    








