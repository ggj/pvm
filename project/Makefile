PROJECT=pvm.exe
include Objects.in
TARGET = ../workdir/$(PROJECT)

GCC = g++
CDEFS = -D_SDL_ -DDEBUG -DSEED_USE_COMMERCIAL
CFLAGS = -Wall -g $(CDEFS) -I$(SEEDSDK)/seed/include -I.. -I$(SEEDSDK)/dependency/common/include -I$(SEEDSDK)/dependency/mingwqt/include
LIBS = -lmingw32 -mwindows -lSeed -lSDLmain -lSDL.dll -lSDL_image -lOpenAL32 -lopengl32 -logg -lvorbis -lvorbisfile -loggz -loggplay -ltheora -lBox2D
CPPFLAGS = $(CFLAGS)
LFLAGS = -L$(SEEDSDK)/seed/bin -L$(SEEDSDK)/dependency/mingwqt/lib

all:	$(TARGET)

$(TARGET): $(OBJECTS)
	$(GCC) -o $(TARGET) $(OBJECTS) $(CPPFLAGS) $(LFLAGS) $(LIBS)

clean:
	$(SEEDSDK)/seedtools/rmw -f $(OBJECTS) $(TARGET) *~
