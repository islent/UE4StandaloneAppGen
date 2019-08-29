# UE4 Standalone Application

## Usage

Source code from [https://github.com/EpicGames/UnrealEngine](https://github.com/EpicGames/UnrealEngine) is recommanded.

```bash
$ g++ generate.cpp string_tools.cpp BaseProgramFile.cpp -o generate.exe
$ generate.exe $ProgramName
$ cp -rf $ProgramName/ $EngineDir/Engine/Source/Programs/  # or it will throw error
$ cd $EngineDir/Engine/Source/Programs/$ProjectName
$ cmd "/C GenerateProgramProject.bat"
```

Or run those commands in `generate.sh` and clear by `clear.sh` (first set `EngineDir` and `ProjectName` manually):

```bash
$ ./clear.sh
$ ./generate.sh
```

Set VS configuration as `Debug Editor, Win64`, set your standalone application as StartUp Project and have fun!

The default executable folder is `Engine/Binaries/Win64/`

Original work done by [hxhb](https://github.com/hxhb). Fixed minor errors and added show cases (SlateViewer).