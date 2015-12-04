..\dsm tst6502
if errorlevel 1 goto ex
diff tst6502.asm tst6502.sav
:ex
