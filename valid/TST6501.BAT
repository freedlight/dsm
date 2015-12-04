..\dsm tst6501
if errorlevel 1 goto ex
diff tst6501.asm tst6501.sav
:ex
