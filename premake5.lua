
workspace "RobinTheEngine"
 architecture "x64"

 configurations
 {
  "Debug",
  "Release",
  "Dist"
 }

 outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

 project "RobinTheEngine"
 location "RobinTheEngine"
 kind "SharedLib"
 language "C++"

 targetdir ("bin/" .. outputdir .. "/%{prj.name}")
 objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

 pchheader "rtepch.h"
 pchsource "RobinTheEngine/src/rtepch.cpp"

 files
 {
  "%{prj.name}/src/**.h",
  "%{prj.name}/src/**.cpp"
 }

 includedirs
 {
  "%{prj.name}/vendor/spdlog/include"
 }

 filter "system:windows"
  cppdialect "C++17"
  staticruntime "On"
  systemversion "latest"

  defines
  {
   "RTE_PLATFORM_WINDOWS",
   "RTE_BUILD_DLL"
  }

  postbuildcommands
  {
   ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
  }

 filter "configurations:Debug"
  defines "RTE_DEBUG"
  symbols "On"

 filter "configurations:Release"
  defines "RTE_RELEASE"
  optimize "On"

 filter "configurations:Dist"
  defines "RTE_DIST"
  optimize "On"

project "Sandbox"
 location "Sandbox"
 kind "ConsoleApp"
 language "C++"

 targetdir ("bin/" .. outputdir .. "/%{prj.name}")
 objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

 files
 {
  "%{prj.name}/src/**.h",
  "%{prj.name}/src/**.cpp"
 }

 includedirs
 {
  "RobinTheEngine/vendor/spdlog/include",
  "RobinTheEngine/src"
 }

 links
 {
  "RobinTheEngine"
 }

 filter "system:windows"
  cppdialect "C++17"
  staticruntime "On"
  systemversion "latest"

  defines
  {
   "RTE_PLATFORM_WINDOWS"
  }

 filter "configurations:Debug"
  defines "RTE_DEBUG"
  symbols "On"

 filter "configurations:Release"
  defines "RTE_RELEASE"
  optimize "On"

 filter "configurations:Dist"
  defines "RTE_DIST"
  optimize "On"






