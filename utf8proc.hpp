#pragma once

#include "utf8proc_global.hpp"

namespace GPlatform {

class UTF8PROC_API UTF8Proc
{
	CLASS_REMOVE_CTRS(UTF8Proc);

public:
	static void					S_NFD		(std::string_view aStr, GpMemoryStorage& aStrOut);
	static void					S_NFC		(std::string_view aStr, GpMemoryStorage& aStrOut);
	static void					S_NFKD		(std::string_view aStr, GpMemoryStorage& aStrOut);
	static void					S_NFKC		(std::string_view aStr, GpMemoryStorage& aStrOut);

	static GpMemoryStorage::SP	S_NFD		(const GpMemoryStorage& aStr);
	static GpMemoryStorage::SP	S_NFC		(const GpMemoryStorage& aStr);
	static GpMemoryStorage::SP	S_NFKD		(const GpMemoryStorage& aStr);
	static GpMemoryStorage::SP	S_NFKC		(const GpMemoryStorage& aStr);

private:
	static void					S_MapCustom	(std::string_view	aStr,
											 u_int_32			aOptions,
											 GpMemoryStorage&	aStringOut);
	static GpMemoryStorage::SP	S_N			(const GpMemoryStorage& aStr,
											 const size_t			aFlags);
};

}//GPlatform
