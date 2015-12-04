..\dsm tst8051
if errorlevel 1 goto ex
diff tst8051.asm tst8051.sav
:ex
