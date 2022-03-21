#pragma once

#include <ore/BinaryFile.h>
#include <ore/EnumUtil.h>
#include <ore/ResDic.h>
#include <ore/StringView.h>
#include <ore/Types.h>

namespace ore {

struct ResDic;
struct ResEndian;

struct ResMetaData {
    struct ActorIdentifier {
        BinTPtr<BinString> name;
        BinTPtr<BinString> sub_name;
    };

    union Value {
        BinTPtr<ResMetaData> container;
        // Also used for booleans. Anything that is != 0 is treated as true.
        int i;
        float f;
        BinTPtr<BinString> str;
        BinTPtr<BinWString> wstr;
        ActorIdentifier actor;
    };

    ORE_ENUM(DataType, kArgument, kContainer, kInt, kBool, kFloat, kString, kWString, kIntArray, kBoolArray, kFloatArray, kStringArray, kWStringArray, kActorIdentifier)

    /// @warning Only usable if type == kContainer.
    const ResMetaData* Get(const StringView& key, DataType::Type expected_type) const {
        const int idx = dictionary.Get()->FindIndex(key);
        if (idx == -1)
            return nullptr;

        const auto* meta = (&value.container + idx)->Get();
        if (meta->type != expected_type)
            return nullptr;

        return meta;
    }

    SizedEnum<DataType::Type, u8> type;
    u16 num_items;
    BinTPtr<ResDic> dictionary;
    Value value;
};

// XXX: is this unused?
struct ResUserData {
    ORE_ENUM(DataType, kInt, kFloat, kString, kWString, kStream)
};

void SwapEndian(ResEndian* endian, ResMetaData* res);

}  // namespace ore
