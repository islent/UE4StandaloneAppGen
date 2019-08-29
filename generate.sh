#!/bin/bash
export EngineDir='F:\UnrealEngine'
export ProjectName='StandaloneApp'

g++ generate.cpp string_tools.cpp BaseProgramFile.cpp -o generate.exe
./generate.exe $ProjectName
cp -rf $ProjectName/ $EngineDir/Engine/Source/Programs/
cd $EngineDir/Engine/Source/Programs/$ProjectName
cmd "/C GenerateProgramProject.bat"