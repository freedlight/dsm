..\dsm tsth82
if errorlevel 1 goto ex
diff tsth82.asm tsth82.sav
:ex
