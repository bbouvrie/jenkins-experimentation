echo adding environment variables
set PATH=C:\Qt\5.11.1\mingw53_32\bin;C:/Qt/Tools/mingw530_32\bin;%PATH%
echo Running test and storing results to testResults.xml
.\build\test_example\release\test_example.exe -xml > testResults.xml
echo Finished writing to xml
       
