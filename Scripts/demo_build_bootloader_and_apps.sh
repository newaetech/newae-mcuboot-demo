#!/bin/bash
# init

function pause(){
   read -p "$*"
}
 
echo Making bootloader
cd ../bootloader
make PLATFORM=CWLITEARM

pause "Press [Enter] key to continue.."

echo Making AppA
cd ../AppA
make PLATFORM=CWLITEARM

pause "Press [Enter] key to continue.."

echo Making AppB
cd ../AppB
make PLATFORM=CWLITEARM
pause "Press [Enter] key to continue.."

echo Signing AppA

cd ../Scripts
python ./imgtool.py sign -k root-rsa-2048.pem -S 0x10000 -v 1.0.0 --align 8 -H 0x400 ../AppA/APP_A-CWLITEARM.hex ../AppA/APP_A_SIGNED-CWLITEARM.hex
pause "Press [Enter] key to continue.."

echo Signing AppB

cd ../Scripts
python ./imgtool.py sign -k root-rsa-2048.pem -S 0x10000 -v 1.0.0 --align 8 -H 0x400 --pad ../AppB/APP_B-CWLITEARM.hex ../AppB/APP_B_SIGNED-CWLITEARM.hex
pause "Press [Enter] key to continue.."

echo Programming applications
cd FirmwareLoader
python ./firmware_loader.py

pause "Press [Enter] key to continue.."
