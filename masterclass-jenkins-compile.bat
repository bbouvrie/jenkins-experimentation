echo Starting compilation
echo adding environment variables
set PATH=C:\Qt\5.11.1\mingw53_32\bin;C:/Qt/Tools/mingw530_32\bin;%PATH%
echo Adding and changing dir to build  
mkdir build
cd build
echo Setting qmake compiler 
qmake  "../src/all.pro" -spec win32-g++ "CONFIG+=qtquickcompiler"
echo Executing qmake
mingw32-make "qmake_all"
echo executing make 
mingw32-make
echo done building

       
