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
        if "ssh-command" in serial_input:
            serial_input = serial_input.replace("ssh-command ", "").strip()
            print serial_input
            cmd = [serial_input, '/Users/audatica/Documents']
            output = subprocess.Popen( cmd, stdout=subprocess.PIPE ).communicate()[0]
            print output.strip()
        self.ssh_client()


        #self.serial_port.write("T1357041600")
        

    #with tempfile.TemporaryFile() as tempf:
    #       proc = subprocess.Popen(['ls', '/Users/audatica/Documents'], stdout=tempf)
    #       proc.wait()
    #       tempf.seek(0)
    #       ser.write(tempf.read())
    #       print tempf.read()
    

serial_class = SerialSSH()

    
    








