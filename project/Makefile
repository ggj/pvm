PROJECT=pvm.exe
include Objects.in
TARGET = ../workdir/$(PROJECT)

SEEDSDK=D:/Projetos/seed

GCC = g++
CDEFS = -D_SDL_ -DDEBUG -DSEED_USE_COMMERCIAL
CFLAGS = -Wall -g $(CDEFS) -I$(SEEDSDK)/include -I..
LIBS = -lmingw32 -mwindows -lSeed -lSDLmain -lSDL.dll -lSDL_image -lOpenAL32 -lopengl32 -logg -lvorbis -lvorbisfile -loggz -loggplay -ltheora -lBox2D
CPPFLAGS = $(CFLAGS)
LFLAGS = -L$(SEEDSDK)/bin

all:	$(TARGET)

$(TARGET): $(OBJECTS)
	$(GCC) -o $(TARGET) $(OBJECTS) $(CPPFLAGS) $(LFLAGS) $(LIBS)

clean:
	C:/MinGW/msys/1.0/bin/rm -f $(OBJECTS) $(TARGET) *~
