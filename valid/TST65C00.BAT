..\dsm tst65c00
if errorlevel 1 goto ex
diff tst65c00.asm tst65c00.sav
:ex
