#pragma once

#include <utf8proc/utf8proc_global.hpp>

#include <GpCore2/GpUtils/Types/Enums/GpEnum.hpp>
#include <GpCore2/GpUtils/Types/Strings/GpStringOps.hpp>
#include <GpCore2/GpUtils/Types/Containers/GpSpanNumerics.hpp>

namespace GPlatform {

GP_ENUM(UTF8PROC_API, UTF8NFType,
    NFD,
    NFC,
    NFKD,
    NFKC
);

class UTF8PROC_API UTF8Proc
{
    CLASS_REMOVE_CTRS_DEFAULT_MOVE_COPY(UTF8Proc)

public:
    /**
     * @brief S_MaxSizeW32
     * @param aType
     * @param aStr
     * @return Count of utf32 chars
     */
    static size_t               S_MaxCountUTF32 (const UTF8NFType::EnumT    aType,
                                                 std::string_view           aStr);

    /**
     * @brief S_Process
     * @param aType
     * @param aStrIn
     * @param aStrOut - utf8 string but aligned as utf32
     * @return Actual size in bytes
     */
    static size_t               S_Process       (const UTF8NFType::EnumT    aType,
                                                 std::string_view           aStrIn,
                                                 GpSpanSI32_RW              aStrOut);

private:
    static size_t               STypeToFlags    (const UTF8NFType::EnumT aType) noexcept;
};

}// namespace GPlatform
