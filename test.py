import subprocess
import tempfile
import serial
import sys
import time
import os
import threading            

cmd = ['ls', '/Users/audatica/Documents']
output = subprocess.Popen( cmd, stdout=subprocess.PIPE ).communicate()[0]
print output.strip()
