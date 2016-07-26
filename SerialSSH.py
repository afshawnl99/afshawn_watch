import subprocess
import tempfile
import serial
import sys
import time
import os
import threading


class SerialSSH:
    def __init__(self):
        


        try:
            self.serial_port = serial.Serial('/dev/cu.usbmodem411', 9600)
            
            self.ssh_client()
        except:
            pass



    
    
    def ssh_client(self):
        serial_input = self.serial_port.readline()
        if "launch-serial" in serial_input:
            self.serial_port.write("stop")
        elif "show_home" in serial_input:
            self.serial_port.write("T1357041600")
        


        elif "ssh-command" in serial_input:
            serial_input = serial_input.replace("ssh-command ", "").strip()
            print serial_input
            try:
                cmd = [serial_input, '/Users/audatica/Documents']
                output = subprocess.Popen( cmd, stdout=subprocess.PIPE ).communicate()[0]
                print output.strip()
            except:
                pass
        self.ssh_client()



    

serial_class = SerialSSH()

    
    








