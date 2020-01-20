echo Making bootloader
cd ..\bootloader
make PLATFORM=CWLITEARM

echo Making AppA
cd ..\AppA
make PLATFORM=CWLITEARM

echo Making AppB
cd ..\AppB
make PLATFORM=CWLITEARM

echo Signing AppA

cd ..\Scripts
python .\imgtool.py sign -k root-rsa-2048.pem -S 0x10000 -v 1.0.0 --align 8 -H 0x400 ../AppA/APP_A-CWLITEARM.hex ../AppA/APP_A_SIGNED-CWLITEARM.hex

echo Signing AppB

cd ..\Scripts
python .\imgtool.py sign -k root-rsa-2048.pem -S 0x10000 -v 1.0.0 --align 8 -H 0x400 --pad ../AppB/APP_B-CWLITEARM.hex ../AppB/APP_B_SIGNED-CWLITEARM.hex

pause 

echo Programming applications
cd FirmwareLoader
python .\firmware_loader.py

pause
