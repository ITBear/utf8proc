#include "utf8proc.hpp"

#include "utf8proc_impl.hpp"

namespace GPlatform {

GP_ENUM_IMPL(UTF8NFType)

count_t UTF8Proc::S_MaxCountUTF32 (const UTF8NFType::EnumT  aType,
                                   std::string_view         aStr)
{
    THROW_GPE_COND_CHECK_M(!aStr.empty(), "String is empty"_sv);

    const utf8proc_ssize_t maxCount = utf8proc_decompose_custom(reinterpret_cast<const utf8proc_uint8_t*>(aStr.data()),
                                                                NumOps::SConvert<utf8proc_ssize_t>(aStr.size()),
                                                                nullptr,
                                                                0,
                                                                utf8proc_option_t(STypeToFlags(aType)),
                                                                nullptr,
                                                                nullptr);

    THROW_GPE_COND_CHECK_M(maxCount > 0, "utf8proc_decompose_custom return error"_sv);

    return count_t::SMake(maxCount) + 1_cnt;
}

size_byte_t UTF8Proc::S_Process (const UTF8NFType::EnumT    aType,
                                 std::string_view           aStrIn,
                                 GpRawPtrSI32_RW            aStrOut)
{
    const count_t maxCountUTF32 = S_MaxCountUTF32(aType, aStrIn);

    THROW_GPE_COND_CHECK_M(aStrOut.CountLeft() >= maxCountUTF32, "String_out are too small"_sv);

    const utf8proc_option_t options = utf8proc_option_t(STypeToFlags(aType));

    const utf8proc_ssize_t countUTF32 = utf8proc_decompose_custom(reinterpret_cast<const utf8proc_uint8_t*>(aStrIn.data()),
                                                                  NumOps::SConvert<utf8proc_ssize_t>(aStrIn.size()),
                                                                  aStrOut.Ptr(),
                                                                  maxCountUTF32.As<utf8proc_ssize_t>(),
                                                                  options,
                                                                  nullptr,
                                                                  nullptr);

    THROW_GPE_COND_CHECK_M(countUTF32 > 0, "utf8proc_decompose_custom return error"_sv);

    const utf8proc_ssize_t actualCountUTF8 = utf8proc_reencode(aStrOut.Ptr(),
                                                               countUTF32,
                                                               options);

    THROW_GPE_COND_CHECK_M(actualCountUTF8 > 0, "utf8proc_reencode return error"_sv);

    return size_byte_t::SMake(actualCountUTF8);
}

size_t  UTF8Proc::STypeToFlags (const UTF8NFType::EnumT aType) noexcept
{
    static const GpArray<utf8proc_option_t, UTF8NFType::SCount().As<size_t>()> sFlags =
    {
        utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_DECOMPOSE),//NFD
        utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_COMPOSE),//NFC
        utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_DECOMPOSE | UTF8PROC_COMPAT),//NFKD
        utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_COMPOSE | UTF8PROC_COMPAT)//NFKC
    };

    return sFlags.at(aType);
}

}//namespace GPlatform
