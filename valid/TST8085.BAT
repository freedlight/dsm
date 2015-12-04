..\dsm tst8085
if errorlevel 1 goto ex
diff tst8085.asm tst8085.sav
:ex
