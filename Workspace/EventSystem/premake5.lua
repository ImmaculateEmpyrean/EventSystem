project "EventSystem"
    location ""

	language "C++"
    cppdialect "C++17"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
	{
		"src/**.h",
		"include/**.h",
        "src/**.cpp"
	}

	includedirs
	{
		"include",
		"src"
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

    filter "configurations:DynamicLibRelease"
		kind "SharedLib"
		runtime "Release"
		optimize "on"
		staticruntime "off"
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/BuildHelper/\"")
		   }

	filter ""