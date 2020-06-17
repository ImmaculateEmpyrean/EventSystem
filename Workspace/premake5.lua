workspace "EventSystem"
    architecture "x86_64"
    startproject "BuildHelper"

	configurations
	{
		"Debug",
        "StaticLibRelease",
        --"DynamicLibRelease" This Library Does Not Export Any Symbols Hence No lib will be generated .. please configure that dilema before attempting to genrate a dynamic library
	}
	
	flags
	{
		"MultiProcessorCompile"
    }
	
	outputdir = "%{cfg.buildcfg}-%{cfg.platform}-%{cfg.system}-%{cfg.architecture}"
    --outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- This is a string object ..

--Start Defining The Main Project

project "EventSystem"
    location "EventSystem"

	language "C++"
    cppdialect "C++17"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src"
	}

    defines
	{
        "_CRT_SECURE_NO_WARNINGS"
	}
	
    filter "configurations:Debug"
		kind "StaticLib"
		runtime "Debug"
		symbols "on"
		staticruntime "on"

    filter "configurations:StaticLibRelease"
		kind "StaticLib"
		runtime "Release"
		optimize "on"
		staticruntime "on"

    --[[filter "configurations:DynamicLibRelease"
		kind "SharedLib"
		runtime "Release"
		optimize "on"
		staticruntime "off"
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/BuildHelper/\"")
		   } --]] ---Enable This bit of code after fixing the problems with dynamic release library..


	filter ""

--BuildHelper Project

project "BuildHelper"
	location "BuildHelper"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"EventSystem/src"
	}

	links
	{
		"EventSystem"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		staticruntime "on"
		defines
		{
			"ER_DEBUG_DEVELOP"
		}

	filter "configurations:StaticLibRelease"
		runtime "Release"
		optimize "on"
		staticruntime "on"

	--[[ filter "configurations:DynamicLibRelease"
		 runtime "Release"
		 optimize "on"
		 staticruntime "off" --]] --Enable This bit of code after fixing the problems with dynamic release library..

	filter ""

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"USINGErmineEventSystem"
	}
