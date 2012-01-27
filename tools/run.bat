@echo Building assets

del cache.sdl.txt
del StringCache.txt
sexporter.exe -i assets.xml -p sdl
copy assets.h ..\assets.h"
@echo Done!
pause
