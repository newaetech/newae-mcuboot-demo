echo Making bootloader
cd ..\bootloader
make PLATFORM=CWLITEARM -j4

#pause

#echo Making AppA
#cd ..\AppA
#make PLATFORM=CWLITEARM

#pause

echo Making AppB
cd ..\AppB
rm APP_B_SIGNED-CWLITEARM.hex
make PLATFORM=CWLITEARM
#pause

echo Signing AppA

#cd ..\Scripts
#python .\imgtool.py sign -k root-rsa-2048.pem -S 0x10000 -v 1.0.0 --align 8 -H 0x400 --pad ../AppA/APP_A-CWLITEARM.hex ../AppA/APP_A_SIGNED-CWLITEARM.hex
#pause

echo Signing AppB

cd ..\Scripts
python .\imgtool.py sign -k root-rsa-2048-bad.pem -S 0x10000 -v 1.0.0 --align 8 -H 0x400 --pad ../AppB/APP_B-CWLITEARM.hex ../AppB/APP_B_SIGNED-CWLITEARM.hex
#pause 

cd FirmwareLoader

echo Programming bad applications
python .\firmware_loader.py

pause
