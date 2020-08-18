#pragma once

#include "utf8proc_impl.hpp"

class utf8proc_data
{
public:
    static const utf8proc_uint16_t utf8proc_sequences[];
    static const utf8proc_uint16_t utf8proc_stage1table[];
    static const utf8proc_uint16_t utf8proc_stage2table[];
    static const utf8proc_property_t utf8proc_properties[];
    static const utf8proc_uint16_t utf8proc_combinations[];
};
