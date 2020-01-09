from enum import Enum     # for enum34, or the stdlib version
from tqdm import tnrange
import matplotlib
import matplotlib.pyplot as plt
from collections import namedtuple
import time
import helper_script_setup as helper
import chipwhisperer as cw
import csv
import re 
import firmware_loader
from datetime import datetime

SCOPETYPE = 'OPENADC'
PLATFORM = 'CWLITEARM'
sample_size = 5

if "STM" in PLATFORM or PLATFORM == "CWLITEARM" or PLATFORM == "CWNANO":
    prog = cw.programmers.STM32FProgrammer
elif PLATFORM == "CW303" or PLATFORM == "CWLITEXMEGA":
    prog = cw.programmers.XMEGAProgrammer
else:
    prog = None
    
try:
    if not scope.connectStatus:
        scope.con()
except NameError:
    scope = cw.scope()
    
target = cw.target(scope)

def main():
    setup()
    firmware_loader.write_bootloader()
    scope.io.nrst = "high_z"
    monitor()

def setup():    

    scope = cw.scope()
    
    time.sleep(0.05)
    scope.default_setup()
    helper.reset_target(scope)
    
def monitor():
    line = ""
    while(1):
        
        line += target.read()
        if('\n' in line):
            print(line)
            line = ""
    

if( __name__ == "__main__"):
    main()

