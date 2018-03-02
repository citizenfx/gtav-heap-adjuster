workspace 'gtav-heap-adjuster'
   configurations { "Release", "Debug" }
   architecture "x86_64"
   location "build"

project "gtav-heap-adjuster"
   kind "SharedLib"
   language "C++"
   targetdir "bin/x64/%{cfg.buildcfg}"
   targetname "GTAV.HeapAdjuster"
   targetextension ".asi"
   
   includedirs { "source" }
   includedirs { "vendor/patterns" }
   
   files { "source/dllmain.h", "source/dllmain.cpp", "vendor/patterns/Hooking.Patterns.cpp" }
   
   characterset ("Unicode")
   
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
      flags { "StaticRuntime" }
