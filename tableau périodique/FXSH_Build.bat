@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist PERIODIQ.G1A  del PERIODIQ.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"C:\Users\mosnier\Desktop\projet avenger\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"C:\Users\mosnier\Desktop\projet avenger\Tools\MakeAddinHeader363.exe" "C:\Users\mosnier\Desktop\Periodiq\tableau p‚riodique"
if not exist PERIODIQ.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

