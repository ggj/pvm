@echo Building assets

del cache.sdl.txt
del StringCache.txt
sexport -i assets.xml -p sdl
copy assets.h ..\assets.h"
@echo Done!
pause