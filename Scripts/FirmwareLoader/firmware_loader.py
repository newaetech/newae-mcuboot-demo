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
    #write_bootloader()
    time.sleep(1)
    write_app_a()
    time.sleep(1)
    write_app_b()
    
def setup():    

    scope = cw.scope()
    
    time.sleep(0.05)
    scope.default_setup()
    helper.reset_target(scope)
    
def write_bootloader():
    fw_path = r'..\..\bootloader\NEWAE_BL-CWLITEARM.hex'

    prog = cw.programmers.STM32FProgrammer
    program_bootloader(scope, prog, fw_path)
    
def write_app_a():
    fw_path = r'..\..\AppA\APP_A-CWLITEARM.hex'
    prog = cw.programmers.STM32FProgrammer
    program_bootloader(scope, prog, fw_path)
    
def write_app_b():
    fw_path = r'..\..\AppB\APP_B-CWLITEARM.hex'
    prog = cw.programmers.STM32FProgrammer
    program_bootloader(scope, prog, fw_path)        

def program_bootloader(scope, prog_type, fw_path, **kwargs):
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
    prog.program(fw_path, memtype="flash", verify=True)
    prog.close()

if( __name__ == "__main__"):
    main()

