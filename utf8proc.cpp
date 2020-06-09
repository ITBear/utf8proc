#include "utf8proc.hpp"

#include "utf8proc_impl.hpp"

namespace GPlatform {

void	UTF8Proc::S_NFD (std::string_view aStr, GpMemoryStorage& aStrOut)
{
	S_MapCustom(aStr,
				utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_DECOMPOSE),
				aStrOut);
}

void	UTF8Proc::S_NFC (std::string_view aStr, GpMemoryStorage& aStrOut)
{
	S_MapCustom(aStr,
				utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_COMPOSE),
				aStrOut);
}

void	UTF8Proc::S_NFKD (std::string_view aStr, GpMemoryStorage& aStrOut)
{
	S_MapCustom(aStr,
				utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_DECOMPOSE | UTF8PROC_COMPAT),
				aStrOut);
}

void	UTF8Proc::S_NFKC (std::string_view aStr, GpMemoryStorage& aStrOut)
{
	S_MapCustom(aStr,
				utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_COMPOSE | UTF8PROC_COMPAT),
				aStrOut);
}

GpMemoryStorage::SP	UTF8Proc::S_NFD (const GpMemoryStorage& aStr)
{
	return S_N(aStr, (UTF8PROC_STABLE | UTF8PROC_DECOMPOSE));
}

GpMemoryStorage::SP	UTF8Proc::S_NFC (const GpMemoryStorage& aStr)
{
	return S_N(aStr, (UTF8PROC_STABLE | UTF8PROC_COMPOSE));
}

GpMemoryStorage::SP	UTF8Proc::S_NFKD (const GpMemoryStorage& aStr)
{
	return S_N(aStr, (UTF8PROC_STABLE | UTF8PROC_DECOMPOSE | UTF8PROC_COMPAT));
}

GpMemoryStorage::SP	UTF8Proc::S_NFKC (const GpMemoryStorage& aStr)
{
	return S_N(aStr, (UTF8PROC_STABLE | UTF8PROC_COMPOSE | UTF8PROC_COMPAT));
}

void	UTF8Proc::S_MapCustom(std::string_view	aStr,
							  u_int_32			aOptions,
							  GpMemoryStorage&	aStringOut)
{
	THROW_GPE_COND_CHECK_M(!aStr.empty(), "aStr is empty"_sv);

	ssize_t newSize = utf8proc_decompose_custom(reinterpret_cast<const utf8proc_uint8_t*>(aStr.data()),
												NumOps::SConvert<utf8proc_ssize_t>(aStr.size()),
												nullptr,
												0,
												utf8proc_option_t(aOptions),
												nullptr,
												nullptr);

	THROW_GPE_COND_CHECK_M(newSize > 0, "utf8proc_decompose_custom return error"_sv);

	const count_t actualSize = count_t::SMake((newSize + 1) * sizeof(utf8proc_int32_t));

	aStringOut.Resize(actualSize);

	{
		GpMemoryStorageViewRW::SP	stringOutViewSP	= aStringOut.ViewReadWrite();
		GpMemoryStorageViewRW&		stringOutView	= stringOutViewSP.Vn();

		newSize = utf8proc_decompose_custom(reinterpret_cast<const utf8proc_uint8_t*>(aStr.data()),
											NumOps::SConvert<utf8proc_ssize_t>(aStr.size()),
											reinterpret_cast<utf8proc_int32_t*>(stringOutView.Data()),
											newSize * sizeof(utf8proc_int32_t) + 1,
											utf8proc_option_t(aOptions),
											nullptr,
											nullptr);

		THROW_GPE_COND_CHECK_M(newSize > 0, "utf8proc_decompose_custom return error"_sv);

		newSize = utf8proc_reencode(reinterpret_cast<utf8proc_int32_t*>(stringOutView.Data()),
									reinterpret_cast<utf8proc_ssize_t>(newSize),
									utf8proc_option_t(aOptions));

		THROW_GPE_COND_CHECK_M(newSize > 0, "utf8proc_reencode return error"_sv);
	}

	aStringOut.Resize(count_t::SMake(newSize));
}

GpMemoryStorage::SP	UTF8Proc::S_N (const GpMemoryStorage&	aStr,
								   const size_t				aFlags)
{
	GpMemoryStorage::SP		res		= aStr.New();
	auto					strView	= aStr.ViewRead();

	S_MapCustom(strView.VC().AsStringView(),
				utf8proc_option_t(aFlags),
				res.Vn());

	return res;
}

}//namespace GPlatform
