# Detours CMake template

[![Build status](https://ci.appveyor.com/api/projects/status/45y39vemm8foo7fc?svg=true)](https://ci.appveyor.com/project/hasherezade/detours-cmake-tpl)

A CMake template for projects using [MS Detours](https://github.com/microsoft/Detours).

Contains demo projects and helpers.
+ **[libdetours](libdetours) - a CMake wrapper for MS Detours**
+ Sample projects using Detours:
  + [project_tpl](project_tpl) - a project demonstrating how the API interception works. Hooks and unhooks itself (function `MessageBoxA`).
  + [hooking_dll_tpl](hooking_dll_tpl) - a Hooking DLL: performs hooking of the process where it was injected
+ Helpers:
  + [test_app](test_app) - a sample app to be hooked by the [Hooking DLL](hooking_dll_tpl) (for test purposes)

A DLL injector useful for testing is available [here](https://github.com/hasherezade/dll_injector)

Clone:
-
Use recursive clone to get the repo together with the Detours submodule:

```console
git clone --recursive https://github.com/hasherezade/detours_cmake_tpl.git
```
