goto ex
..\dsm tst6809
if errorlevel 1 goto ex
diff tst6809.asm tst6809.sav
:ex
