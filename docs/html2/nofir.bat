@echo off
echo Running rawfile2stream...
..\..\bin\rawfile2stream ..\..\src\streamutils\thought.raw > thought.str
echo Running playstream.raw...
..\..\bin\playstream 1 44100 < thought.str
exit
