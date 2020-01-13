echo Making bootloader

REM C:\
REM cd C:\Users\newae-admin\Dropbox\NewAE\Test\ca_bootloader\bootloader
REM make PLATFORM=CWLITEARM

pause

echo Making AppA
cd C:\Users\newae-admin\Dropbox\NewAE\Test\ca_bootloader\AppA
make PLATFORM=CWLITEARM
pause

echo Making AppB
cd C:\Users\newae-admin\Dropbox\NewAE\Test\ca_bootloader\AppB
make PLATFORM=CWLITEARM
pause

echo Signing AppA

cd C:\Users\newae-admin\Dropbox\NewAE\Test\ca_bootloader\Scripts 
rem python .\imgtool.py sign -k root-rsa-2048.pem -v 1.0.0 -S 0x10000 -d "(1, 1.0.0)" -e little --align 2 -H 32 -M 32 --overwrite-only ../AppA/APP_A-CWLITEARM.hex ../AppA/APP_A_SIGNED-CWLITEARM.hex     
python .\imgtool.py sign -k root-rsa-2048.pem -v 1.0.0 -S 0x10000 -d "(1, 1.0.0)" -e little --align 2 -H 32 -M 32 --pad ../AppA/APP_A-CWLITEARM.hex ../AppA/APP_A_SIGNED-CWLITEARM.hex     

pause

echo Signing AppB

cd C:\Users\newae-admin\Dropbox\NewAE\Test\ca_bootloader\Scripts 
rem python .\imgtool.py sign -k root-rsa-2048.pem -v 1.0.0 --pad -S 0x10000 -d "(1, 1.0.0)" -e little --align 2 -H 32 -M 32 ../AppB/APP_B-CWLITEARM.hex ../AppB/APP_B_SIGNED-CWLITEARM.hex     
python .\imgtool.py sign -k root-rsa-2048.pem -v 1.0.0 -S 0x10000 -d "(1, 1.0.0)" -e little --align 2 -H 32 -M 32 --pad ../AppB/APP_B-CWLITEARM.hex ../AppB/APP_B_SIGNED-CWLITEARM.hex     

pause

echo Programming applications
cd C:\Users\newae-admin\Dropbox\NewAE\Test\ca_bootloader\Scripts\FirmwareLoader
python .\firmware_loader.py
pause
