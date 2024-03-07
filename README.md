# Win32 Window Template C (x64, C17)

* created with Visual Studio 2022 Community
* configured for x64
* Unicode (default) and ASCII compatible (e.g. using `WNDCLASSEX` macro instead of `WNDCLASSEXA` or `WNDCLASSEXW` directly)
* with basic error logging (`GetLastError` and `OutputDebugString`)
* DPI awareness: None

Using this template you will get the following window on `Windows 10` (without the gradient background color surrounding the window).

![preview hello world window](banner.png)

## Info

If this Visual Studio Solution is copied as a starting point for a new project some files should be changed:

* `Win32WindowTemplateC.sln`
* `Win32WindowTemplateC.vcxproj`

The file `Win32WindowTemplateC.sln` defines a [Guid (Wikipedia link)](https://en.wikipedia.org/wiki/Universally_unique_identifier) for the project which is `5041EAA9-76E3-40F5-968F-77DDE7A7116F`.
You should consider replacing all occurrences of the Guid `5041EAA9-76E3-40F5-968F-77DDE7A7116F` with a fresh Guid.

[Show Project Guid locations on GitHub Search](https://github.com/search?q=repo%3Aadotspooner%2FWin32WindowTemplateC+5041eaa9-76e3-40f5-968f-77dde7a7116f&type=code)

If the name of the solution and the project should be changed from `Win32WindowTemplate` to `NewSolutionAndProjectName` the following files and folder need to be changed:

File content changes:
* `Win32WindowTemplateC.sln`
* `Win32WindowTemplateC/Win32WindowTemplateC.vcxproj`

[Show Win32WindowTemplateC file content occurrences on GitHub Search](https://github.com/search?q=repo%3Aadotspooner%2FWin32WindowTemplateC+Win32WindowTemplateC&type=code)

File or folder renames:
* `Win32WindowTemplateC.sln`
* `Win32WindowTemplateC` (the project folder)
* `Win32WindowTemplateC/Win32WindowTemplateC.vcxproj`
* `Win32WindowTemplateC/Win32WindowTemplateC.vcxproj.filters`

**Alternatively** you can just create a new Visual Studio Solution and Project and copy the files `main.c` and `error.c` in your new project.
If you do this do not forget to set the version of the C compiler (e.g. C17) in your `Project Properties -> Configuration Properties -> General -> C Language Standard`
and also set `Project Properties -> Configuration Properties -> Linker -> System -> SubSystem` to `Windows (/SUBSYSTEM:WINDOWS)`.

## Create a fresh Guid on Windows

* Visual Studio 2022 (Community) is installed
* type `x64 Native Tools Command Prompt for VS 2022` in the windows start menu search
* open `x64 Native Tools Command Prompt for VS 2022`
* type `cd Common7\Tools` and hit <kbd>enter</kbd>
* type `guidgen.exe` and hit <kbd>enter</kbd>
* the `guidgen` program opens a new window with the title `Create GUID`
* select Guid Format `6. <Guid("xxxxxxx-xxxx ... xxxx")>`
* click on the button `New GUID`
* click on the button `Copy`
* you now have a fresh Guid in the clipboard
* paste it in for example notepad
* notepad should show something like this `<Guid("8B5CB3D0-6CF4-4CF6-98D8-2BB8EE6AB4ED")>`
* copy the Guid between the "" -> 8B5CB3D0-6CF4-4CF6-98D8-2BB8EE6AB4ED
* (optional) now you can replace all occurrences of `5041EAA9-76E3-40F5-968F-77DDE7A7116F` with `your-fresh-guid` as described in [Info](#info)
