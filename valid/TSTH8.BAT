..\dsm tsth8
if errorlevel 1 goto ex
diff tsth8.asm tsth8.sav
:ex
