# stin
stin-chatbout

## buid:
#### required software:
cmake
#### commands:
###### windows
```powershell
cmake -B build/.dump -S . -G 'MinGW Makefiles'
cmake --build build/.dump
```
###### linux
```bash
cmake -B build/.dump -S .
cmake --build build/.dump
```
#### Vscode
###### utils 
Cmake Test Explorer
###### tasks
debug - builds Debug and Test
release - builds Release nad Test
debugTest - buidlds TestCover runs all test and generates all TestcoverFiles
test - runs all Test

