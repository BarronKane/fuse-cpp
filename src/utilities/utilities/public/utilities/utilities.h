#pragma once

#include <string>

#include "utilities/platform.h"

#if defined WINDOWS || defined _WIN32 || defined _WIN64 || defined __CYGWIN_

#include <Windows.h>

std::string GetEXE_()
{
	// I'm keeping this around because every time it runs, it prints something different.
	/*
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	return std::string(buffer).substr(0, pos);
	*/

	char path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	std::string exe_path(path);

	return exe_path;
}
#endif

// TODO: Check freebsd.
#if defined  unix || defined __unix || defined __unix__ || \
	defined __linux__ || defined linux || defined __FreeBSD__ 

	#include <unistd.h>

	std::string GetEXE_()
	{
		char path[FILENAME_MAX];
		size_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
		std::string exe_path(path);

		return exe_path;
	}
#endif

#if defined __APPLE__ || defined __MACH__ 

	#include <mach-o/dyld.h>
	#include <limits.h>

	std::string GetEXE_()
	{
		char buffer [PATH_MAX];
		uint32 buffersize = PATH_MAX;
		if(!_NSGetExecutablePath(buf, &buffersize))
		{
			puts(buffer);
		}

		std::string exe_path(buffer);
	}
#endif

std::string GetEXE()
{
	return GetEXE_();
}
