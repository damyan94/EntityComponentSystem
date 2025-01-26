newoption
{
	trigger = "os",
	value = "system",
	description = "Choose the target system",
	allowed =
	{
		{ "windows", "Windows" },
		{ "linux", "Linux" }
	}
}
local targetSystem = _OPTIONS["os"]
targetSystem = targetSystem:gsub("^%l", string.upper)

if not targetSystem then
	error("Error: You must provide the '--os' option to specify the target system (e.g., --os=windows or --os=linux).")
end

local baseDir 			= "../"
local buildDir 			= baseDir .. "Build/"
local projectDir 		= baseDir .. "Project/"
local sourceDir 		= baseDir .. "Source/"

local outputDir = buildDir .. targetSystem .. "_%{cfg.architecture}_%{cfg.buildcfg}/"

function setupCommonProjectSettings(_kind)

	location (projectDir .. targetSystem)
	kind (_kind)
	language "C++"
	cppdialect "C++20"
	warnings "Default"
	staticruntime "On"
	
	targetdir (outputDir)
	objdir (outputDir .. "/Temp/")
	
	files
	{
		sourceDir .. "**.h",
		sourceDir .. "**.cpp"
	}
	
	includedirs
	{
		baseDir,
		sourceDir
	}
	
	libdirs
	{
	}
	
	links
	{
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	
	pchheader "stdafx.h"
	pchsource (sourceDir .. "stdafx.cpp")

end

function setupConfigurationSpecificSettings()

	filter "configurations:Debug"
		symbols "On"
		
		defines
		{
			"_DEBUG",
			"DEBUG"
		}
	
	filter "configurations:Release"
		symbols "On"
		optimize "On"
		
		defines
		{
			"_RELEASE",
			"RELEASE"
		}
	
	filter {}

end

function setupPlatformSpecificSettings()

	if targetSystem == "Windows" then
		systemversion "latest"
		characterset ("ASCII")
		entrypoint "mainCRTStartup"
		
		defines
		{
			"_WIN32",
			"_WIN64",
			"WIN32",
			"WIN64",
			"_WINDOWS",
			"WINDOWS"
		}
	
	elseif targetSystem == "Linux" then
		defines
		{
			"__linux__",
			"_LINUX",
			"LINUX"
		}
		
		--[[buildoptions
		{
			"-fprofile-arcs",
			"-ftest-coverage",
			"-g0"
		}
		
		links
		{
			"gcov"
		}]]--
	
	end

end

--------------------------------------------------------------------------------

workspace "EntityComponentSystem"
	location (projectDir .. targetSystem .. "/")
	architecture "x64"
	startproject "ECS"

	configurations
	{
		"Debug",
		"Release"
	}

project "EntityComponentSystem"
	setupCommonProjectSettings("ConsoleApp")
	setupConfigurationSpecificSettings()
	setupPlatformSpecificSettings()