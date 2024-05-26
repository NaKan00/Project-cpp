@echo off

cd .\object
echo [INFO] create object files
g++ -c ..\code\parser.cpp ..\code\entity.cpp ..\code\cluster.cpp ..\code\silhouette.cpp ..\code.\k_means.cpp
cd ..

echo [INFO] create exe files
g++ object\parser.o object\entity.o object\cluster.o object\silhouette.o object\k_means.o -o k_means


IF %ERRORLEVEL% NEQ 0 GOTO :failure
GOTO SUCCESS


:success
echo [INFO] COMPILE [32mSUCCESS[0m
GOTO END

:failure
echo COMPILE [31mFAILURE[0m
GOTO END

:END
:: .\k_means.exe -ifile marketing_campaign.csv.xls -ofile clusters.txt -ncl 4 -stat stat.csv.xls