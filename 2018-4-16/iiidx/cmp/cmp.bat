:loop
rand > test.in
pro < test.in > pro.out
std < test.in > std.out
fc pro.out std.out 
if %errorlevel% == 0 goto loop
pause
