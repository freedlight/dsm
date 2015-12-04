@echo off
cls
echo tst6501
call tst6501
if errorlevel 1 goto bad
cls
echo tst6502
call tst6502
if errorlevel 1 goto bad
cls
echo tst6511
call tst6511
if errorlevel 1 goto bad
cls
echo tst65151
call tst65151
if errorlevel 1 goto bad
cls
echo tst65c00
call tst65c00
if errorlevel 1 goto bad
cls
echo tst65c02
call tst65c02
if errorlevel 1 goto bad
cls
echo tst6801
call tst6801
if errorlevel 1 goto bad
cls
echo tst6803
call tst6803
if errorlevel 1 goto bad
cls
echo tst6805
call tst6805
if errorlevel 1 goto bad
cls
echo tst6809
call tst6809
if errorlevel 1 goto bad
cls
echo tst8051
call tst8051
if errorlevel 1 goto bad
cls
echo tst8080
call tst8080
if errorlevel 1 goto bad
cls
echo tst8085
call tst8085
if errorlevel 1 goto bad
cls
echo tsth8
call tsth8
if errorlevel 1 goto bad
cls
echo tsth82
call tsth82
if errorlevel 1 goto bad
cls
echo tstz80
call tstz80
if errorlevel 1 goto bad
cls
echo dsm test passed
echo 
echo 
goto ex
:bad
echo dsm test failed
:ex
