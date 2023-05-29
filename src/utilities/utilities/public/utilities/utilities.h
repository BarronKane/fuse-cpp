#pragma once

#include <string>
#include <filesystem>

#include "utilities/platform.h"

#if defined WINDOWS || defined _WIN32 || defined _WIN64 || defined __CYGWIN_

	#include <Windows.h>

	inline std::filesystem::path GetEXE_()
	{
		char path[MAX_PATH];
		GetModuleFileName(NULL, path, MAX_PATH);
		std::filesystem::path exe_path(path);

		return exe_path;
	}
#endif

// TODO: Check freebsd.
#if defined  unix || defined __unix || defined __unix__ || \
	defined __linux__ || defined linux || defined __FreeBSD__ 

	#include <unistd.h>

	inline std::filesystem::path GetEXE_()
	{
		char path[FILENAME_MAX];
		size_t count = readlink("/proc/self/exe", path, FILENAME_MAX);
		std::filesystem::path exe_path(path);

		return exe_path;
	}
#endif

#if defined __APPLE__ || defined __MACH__ 

	#include <mach-o/dyld.h>
	#include <limits.h>

	inline std::filesystem::path GetEXE_()
	{
		char buffer [PATH_MAX];
		uint32 buffersize = PATH_MAX;
		if(!_NSGetExecutablePath(buf, &buffersize))
		{
			puts(buffer);
		}

		std::filesystem::path exe_path(buffer);

		return exe_path;
	}
#endif

inline std::filesystem::path GetEXE()
{
	return GetEXE_();
}
