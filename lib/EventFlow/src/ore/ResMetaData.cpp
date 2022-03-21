#include <ore/ResDic.h>
#include <ore/ResEndian.h>
#include <ore/ResMetaData.h>

namespace ore {

static void SwapEndianImpl(ResEndian* endian, ResMetaData* res) {
    auto* dictionary = res->dictionary.ToPtr(endian->base);
    if (dictionary)
        SwapEndian(endian, dictionary);

    switch (res->type) {
    case ResMetaData::DataType::kArgument:
    case ResMetaData::DataType::kString:
    case ResMetaData::DataType::kStringArray:
    case ResMetaData::DataType::kActorIdentifier: {
        if (res->num_items == 0)
            break;
        BinString* str = res->value.str.ToPtr(endian->base);
        if (endian->is_serializing) {
            for (int i = 0, n = res->num_items; i < n; ++i) {
                auto* next = str->NextString();
                SwapEndian(&str->length);
                str = next;
            }
        } else {
            for (int i = 0, n = res->num_items; i < n; ++i) {
                SwapEndian(&str->length);
                str = str->NextString();
            }
        }
        break;
    }
    case ResMetaData::DataType::kContainer: {
        for (int i = 0, n = res->num_items; i < n; ++i) {
            ResMetaData* ptr = (&res->value.container + i)->ToPtr(endian->base);
            if (ptr)
                SwapEndian(endian, ptr);
        }
        break;
    }
    case ResMetaData::DataType::kInt:
    case ResMetaData::DataType::kBool:
    case ResMetaData::DataType::kFloat:
    case ResMetaData::DataType::kIntArray:
    case ResMetaData::DataType::kFloatArray:
        for (int i = 0, n = res->num_items; i < n; ++i) {
            SwapEndian(&res->value.i + i);
        }
        break;
    case ResMetaData::DataType::kWString:
    case ResMetaData::DataType::kWStringArray: {
        if (res->num_items == 0)
            break;
        BinWString* str = res->value.wstr.ToPtr(endian->base);
        if (endian->is_serializing) {
            for (int i = 0, n = res->num_items; i < n; ++i) {
                for (auto& c : *str)
                    c = static_cast<wchar_t>(SwapEndian(static_cast<u32>(c)));
                auto* next = str->NextString();
                SwapEndian(&str->length);
                str = next;
            }
        } else {
            for (int i = 0, n = res->num_items; i < n; ++i) {
                SwapEndian(&str->length);
                for (auto& c : *str)
                    c = static_cast<wchar_t>(SwapEndian(static_cast<u32>(c)));
                str = str->NextString();
            }
        }
        break;
    }
    case ResMetaData::DataType::kBoolArray:
        break;
    }
}

void SwapEndian(ResEndian* endian, ResMetaData* res) {
    if (endian->is_serializing) {
        SwapEndianImpl(endian, res);
        SwapEndian(&res->num_items);
    } else {
        SwapEndian(&res->num_items);
        SwapEndianImpl(endian, res);
    }
}

}  // namespace ore
