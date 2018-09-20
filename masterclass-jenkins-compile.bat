echo Starting compilation
echo adding environment variables
set PATH=C:\Qt\5.11.1\mingw53_32\bin;C:/Qt/Tools/mingw530_32\bin;%PATH%
echo Adding and changing dir to build  
mkdir build
cd build
echo Setting qmake compiler 
"C:/Qt/5.11.1/mingw53_32/bin/qmake.exe"  "../src/all.pro" -spec win32-g++ "CONFIG+=qtquickcompiler"
echo Executing qmake
"C:/Qt/Tools/mingw530_32/bin/mingw32-make.exe" "qmake_all"
echo executing make 
"C:/Qt/Tools/mingw530_32/bin/mingw32-make.exe"
echo done building

       
