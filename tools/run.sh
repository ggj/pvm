#!/bin/bash

PLAT=$1

if [ "x$1" = "x" ]
then
	PLAT=sdl
fi

echo $PLAT

echo Building assets
rm cache.sdl.txt 2> /dev/null
rm StringCache.txt 2> /dev/null
./sexporter -i assets.xml -p $PLAT -v
cp assets.h ../assets.h
