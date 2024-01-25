@echo off
echo строка параметров: %1 %2 %3
echo 1 параметр: %1
echo 2 параметр: %2
echo 3 параметр: %3

set /a result=%1 %3 %2

echo результат = %result%
