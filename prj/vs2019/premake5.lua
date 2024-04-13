workspace "EntityComponentSystem"
	architecture "x64"
	startproject "EntityComponentSystem"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "../../build/%{cfg.system}_%{cfg.architecture}_%{cfg.buildcfg}"

project "EntityComponentSystem"
	location "%{prj.name}"
	kind "ConsoleApp"
	language "C++"
	
	warnings "Default"
	characterset ("ASCII")
	entrypoint "mainCRTStartup"
	
	targetdir (outputdir)
	objdir (outputdir .. "/Temp/%{prj.name}")
	
	files
	{
		"../../source/**.h",
		"../../source/**.cpp"
	}
	
	includedirs
	{
		"../../",
		"../../source"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"_WIN32",
			"_WIN64",
			"WIN32",
			"WIN64"
		}
	
	filter "configurations:Debug"
		symbols "On"
		
		defines
		{
			"_DEBUG"
		}
		
	filter "configurations:Release"
		optimize "On"
		
		defines
		{
			"_RELEASE"
		}