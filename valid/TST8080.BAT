..\dsm tst8080
if errorlevel 1 goto ex
diff tst8080.asm tst8080.sav
:ex
