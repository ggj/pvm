#!/bin/bash

echo Building SDL demo files
rm cache.sdl.txt 2> /dev/null
rm StringCache.txt 2> /dev/null
./sexporter -i assets.xml -p iph -v
cp assets.h ../assets.h
