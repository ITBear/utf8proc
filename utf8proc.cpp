#include <utf8proc/utf8proc.hpp>
#include <utf8proc/utf8proc_impl.hpp>

namespace GPlatform {

GP_ENUM_IMPL(UTF8NFType)

size_t  UTF8Proc::S_MaxCountUTF32
(
    const UTF8NFType::EnumT aType,
    std::string_view        aStr
)
{
    THROW_COND_GP(!aStr.empty(), "String is empty"_sv);

    const utf8proc_ssize_t maxCount = utf8proc_decompose_custom
    (
        reinterpret_cast<const utf8proc_uint8_t*>(std::data(aStr)),
        NumOps::SConvert<utf8proc_ssize_t>(std::size(aStr)),
        nullptr,
        0,
        utf8proc_option_t(STypeToFlags(aType)),
        nullptr,
        nullptr
    );

    THROW_COND_GP
    (
        maxCount > 0,
        "utf8proc_decompose_custom return error"_sv
    );

    return NumOps::SAdd(NumOps::SConvert<size_t>(maxCount), size_t(1));
}

size_t  UTF8Proc::S_Process
(
    const UTF8NFType::EnumT aType,
    std::string_view        aStrIn,
    GpSpanSI32_RW           aStrOut
)
{
    const size_t maxCountUTF32 = S_MaxCountUTF32(aType, aStrIn);

    THROW_COND_GP(aStrOut.Count() >= maxCountUTF32, "String_out are too small"_sv);

    const utf8proc_option_t options = utf8proc_option_t(STypeToFlags(aType));

    const utf8proc_ssize_t countUTF32 = utf8proc_decompose_custom
    (
        reinterpret_cast<const utf8proc_uint8_t*>(std::data(aStrIn)),
        NumOps::SConvert<utf8proc_ssize_t>(std::size(aStrIn)),
        aStrOut.Ptr(),
        NumOps::SConvert<utf8proc_ssize_t>(maxCountUTF32),
        options,
        nullptr,
        nullptr
    );

    THROW_COND_GP(countUTF32 > 0, "utf8proc_decompose_custom return error"_sv);

    const utf8proc_ssize_t actualCountUTF8 = utf8proc_reencode
    (
        aStrOut.Ptr(),
        countUTF32,
        options
    );

    THROW_COND_GP(actualCountUTF8 > 0, "utf8proc_reencode return error"_sv);

    return NumOps::SConvert<size_t>(actualCountUTF8);
}

size_t  UTF8Proc::STypeToFlags (const UTF8NFType::EnumT aType) noexcept
{
    static const std::array<utf8proc_option_t, UTF8NFType::SCount()> sFlags =
    {
        utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_DECOMPOSE),//NFD
        utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_COMPOSE),//NFC
        utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_DECOMPOSE | UTF8PROC_COMPAT),//NFKD
        utf8proc_option_t(UTF8PROC_STABLE | UTF8PROC_COMPOSE | UTF8PROC_COMPAT)//NFKC
    };

    return sFlags.at(size_t(aType));
}

}// namespace GPlatform
