#!/bin/bash
export EngineDir='F:\UnrealEngine'
export ProjectName='StandaloneApp'

rm generate.exe
rm -rf $ProjectName
rm -rf $EngineDir/Engine/Source/Programs/$ProjectName
rm -rf $EngineDir/Engine/Binaries/Win64/$ProjectName*
rm -rf $EngineDir/Engine/Intermediate/ProjectFiles/$ProjectName*