from enum import Enum     # for enum34, or the stdlib version
from tqdm import tnrange
import sys, getopt
import matplotlib
import matplotlib.pyplot as plt
from collections import namedtuple
import time
import helper_script_setup as helper
import chipwhisperer as cw
import csv
import re 
from datetime import datetime

SCOPETYPE = 'OPENADC'
PLATFORM = 'CWLITEARM'
sample_size = 5

default_bl_path   = r'..\..\bootloader\NEWAE_BL-CWLITEARM.hex'
default_fw_a_path = r'..\..\AppA\APP_A_SIGNED-CWLITEARM.hex'
default_fw_b_path = r'..\..\AppB\APP_B_SIGNED-CWLITEARM.hex'


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

def main(argv):
    hex_bl_path = default_bl_path
    hex_a_path = default_fw_a_path
    hex_b_path = default_fw_b_path
    print(hex_b_path)
    mon = True
    
    try:    
        opts,argv = getopt.getopt(argv,"hml:b:a:",["bootloader_path=","a_path=","b_path="])
        for opt, arg in opts:
            if opt in ("-h", "--help"):
                print ("firmware_loader.py -m -l <bl_path> -a <a_path> -b <b_path>")
                sys.exit()
            elif opt in ("m"):
                mon=False
            elif opt in ("-l", "--bootloader_path"):
                hex_bl_path = arg                       
            elif opt in ("-a", "--a_path"):
                hex_a_path = arg
            elif opt in ("-b", "--b_path"):
                hex_b_path = arg  
                print(hex_b_path)
    except getopt.GetoptError as e:
        print('Path error detected, using default paths instead' + str(e))
    

    time.sleep(1)        
    setup()
    time.sleep(1)
    write_app_a(hex_a_path)
    time.sleep(1)
    print(hex_b_path)
    write_app_b(hex_b_path)
    time.sleep(1)
    print(hex_bl_path)
    write_bootloader(hex_bl_path)
    if mon:
        monitor()
    
def setup():    

    scope = cw.scope()    
    time.sleep(0.05)
    scope.default_setup()
    helper.reset_target(scope)
    
def write_bootloader(fw_path):
    print("Programming bootloader...")
    prog = cw.programmers.STM32FProgrammer
    program_hex(scope, prog, fw_path)
    
def write_app_a(fw_path):
    print("Programming App A...")
    prog = cw.programmers.STM32FProgrammer
    program_hex(scope, prog, fw_path)
    
def write_app_b(fw_path):
    print("Programming App B...")
    prog = cw.programmers.STM32FProgrammer
    program_hex(scope, prog, fw_path, 0x10000)        

def program_hex(scope, prog_type, fw_path, offset=0, **kwargs):
    """Program the target using the programmer without erasing additional space <type>

    Programmers can be found in the programmers submodule

    Args:
       scope (ScopeTemplate): Connected scope object to use for programming
       prog_type (Programmer): Programmer to use. See chipwhisperer.programmers
           for available programmers
       fw_path (str): Path to hex file to program

    .. versionadded:: 5.0.1
        Simplified programming target
    """
    if prog_type is None: #[makes] automating notebooks much easier
        return
    prog = prog_type(**kwargs)
    prog.scope = scope
    prog._logging = None
    prog.open()
    prog.find()
    prog.erase(True, fw_path, offset=offset)
    prog.program(fw_path, memtype="flash", verify=True, offset=offset)
    prog.close()

def monitor():
    line = ""
    while(1):
        
        line += target.read()
        if('\n' in line):
            print(line)
            line = ""
            
if( __name__ == "__main__"):
    main(sys.argv[1:])
