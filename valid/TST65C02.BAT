..\dsm tst65c02
if errorlevel 1 goto ex
diff tst65c02.asm tst65c02.sav
:ex
