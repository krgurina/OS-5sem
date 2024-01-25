@echo off
echo строка параметров: %*
echo 1 параметр: %1
echo 2 параметр: %2
echo 3 параметр: %3

set p1=%1
set p2=%2
set p3=%3

set /a sum=p1+p2
set /a mult=p1*p2
set /a div=p3/p2
set /a dif=p2-p1
set /a expression = (p2-p1)*(p1-p2)

echo %p1% + %p2% = %sum%
echo %p1% * %p2% = %mult%
echo %p3% / %p2% = %div%
echo %p2% - %p1% = %dif%
echo (%p2% - %p1%) * (%p1% - %p2%) = %expression% 
