#pragma once

class test
{
	public:

	test();
};

/**
 * Many compilers (*ahem*MSVC*ahem*) don't fully support all features of a c++ version.
 * Representations for character sets are needed for those deprivations.
 */
struct GenericTypes
{
	typedef unsigned char 				uint8;
	typedef unsigned short int			uint16;
	typedef unsigned int				uint32;
	typedef unsigned long long			uint64;

	typedef	signed char					int8;
	typedef signed short int			int16;
	typedef signed int	 				int32;
	typedef signed long long			int64;

	// 8-bit fixed-width representation of 7-bit characters.
	typedef char						ANSICHAR;	
	// ?-bit fixed-width representation of a wide character set. Differs per-platform.
	typedef wchar_t						WIDECHAR;

	// 8-bit representation, char8_t c++20 and up.
#if __cplusplus >= 202002L
	typedef char8_t						CHAR8;
	typedef char8_t						UTF8CHAR;
#else
	typedef unsigned char				CHAR8;
	typedef unsigned char				UTF8CHAR;
#endif

	// 16-bit representation. char16_t C++11 and up.
#if __cplusplus >= 201103L
	typedef char16_t					CHAR16;
	typedef char16_t					UTF16CHAR;
#else
	typedef uint16						CHAR16;
	typedef uint16						UTF16CHAR;
#endif

	// 32-bit representation. char32_t c++11 and up.
#if __cplusplus >= 201103L
	typedef char32_t					CHAR32;
	typedef char32_t					UTF32CHAR;
#else
	typedef uint32						CHAR32;
	typedef uint32						UTF32CHAR;
#endif

	// Switchable character. ANSICHAR or WIDECHAR depending on use case.
	typedef WIDECHAR					TCHAR;
	#define _TCHAR_DEFINED

	typedef int32						TYPE_OF_NULL;
	typedef decltype(nullptr)			TYPE_OF_NULLPTR;
};

// The above allows us to change the types globally.
// This should be fine for windows/linux 64 bit platforms on modern chips,
// but we will keep them on windows only to remind us later.

#if defined WINDOWS || defined _WIN32 || defined _WIN64 || defined __CYGWIN_
	typedef GenericTypes::uint8			uint8;
	typedef GenericTypes::uint16		uint16;
	typedef GenericTypes::uint32		uint32;
	typedef GenericTypes::uint64		uint64;

	typedef	GenericTypes::int8			int8;
	typedef GenericTypes::int16			int16;
	typedef GenericTypes::int32			int32;
	typedef GenericTypes::int64			int64;

	typedef GenericTypes::ANSICHAR		ANSICHAR;
	typedef GenericTypes::WIDECHAR		WIDECHAR;

	typedef GenericTypes::CHAR8			CHAR8;
	typedef GenericTypes::UTF8CHAR		UTF8CHAR;

	typedef GenericTypes::CHAR16		CHAR16;
	typedef GenericTypes::UTF16CHAR		UTF16CHAR;
	
	typedef GenericTypes::CHAR32		CHAR32;
	typedef GenericTypes::UTF32CHAR		UTF32CHAR;

	typedef GenericTypes::TCHAR			TCHAR;

	typedef GenericTypes::TYPE_OF_NULL		TYPE_OF_NULL;
	typedef GenericTypes::TYPE_OF_NULLPTR	TYPE_OF_NULLPTR;
#endif
