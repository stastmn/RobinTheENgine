   workspace "RobinTheEngine"
      architecture "x64"

      configurations
      {
         "Debug",
         "Release",
         "Dist"
      }

   outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
 
   -- Include directories relative to root folder (solution directory)
   IncludeDir = {}
   IncludeDir["GLFW"] = "RobinTheEngine/vendor/GLFW/include"
   IncludeDir["ImGui"] = "RobinTheEngine/vendor/imgui"

   include "RobinTheEngine/vendor/GLFW"
   include "RobinTheEngine/vendor/imgui"


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
	  defines
	  {
	     "_CRT_SECURE_NO_WARNINGS",
		 "GLFW_INCLUDE_NONE"
	  }

      includedirs
      {
         "%{prj.name}/src",
         "%{prj.name}/vendor/spdlog/include",
         "%{prj.name}/vendor/DirectX12-Headers/include/directx",
         "%{IncludeDir.GLFW}",
		 "%{IncludeDir.ImGui}"
      }
 
      links
      {
         "GLFW",
		 "opengl32.lib",
		 "ImGui"
      }

      filter "system:windows"
         cppdialect "C++17"
         staticruntime "On"
         systemversion "latest"

         defines
         {
            "RTE_PLATFORM_WINDOWS",
            "RTE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
         }

         postbuildcommands
         {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
         }

      filter "configurations:Debug"
         defines "RTE_DEBUG"
         symbols "On"
		 buildoptions "/MDd"

      filter "configurations:Release"
         defines "RTE_RELEASE"
         optimize "On"
		 buildoptions "/MD"

      filter "configurations:Dist"
         defines "RTE_DIST"
         optimize "On"
		 buildoptions "/MD"


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
		 buildoptions "/MDd"

      filter "configurations:Release"
         defines "RTE_RELEASE"
         optimize "On"
		 buildoptions "/MD"

      filter "configurations:Dist"
         defines "RTE_DIST"
         optimize "On"
		 buildoptions "/MD"	






