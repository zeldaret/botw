#include "KingSystem/Resource/resResourceGameData.h"
#include <type_traits>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/HeapUtil.h"

namespace ksys::res {

GameData::GameData() = default;

GameData::~GameData() {
    ;
}

namespace {
template <typename FlagType, typename GetConfigFn>
KSYS_ALWAYS_INLINE inline void
loadFlags(const sead::SafeString& data_type, const al::ByamlIter& root_iter, sead::Heap* heap,
          sead::Buffer<FlagType>& flags, const sead::SafeString& wanted_data_type,
          gdt::FlagType flag_type, const GetConfigFn& get_config_fn) {
    constexpr bool IsBoolFlag = std::is_same<FlagType, gdt::FlagBool>();

    if (data_type != wanted_data_type)
        return;

    al::ByamlIter array_iter;
    if (!root_iter.tryGetIterByIndex(&array_iter, 0))
        return;

    const auto num_flags = array_iter.getSize();
    if (num_flags > 0)
        flags.allocBufferAssert(num_flags, heap);

    gdt::FlagProperties properties{};
    typename FlagType::ConfigType config{};

    for (s32 i = 0; i < num_flags; ++i) {
        al::ByamlIter iter;
        if (!array_iter.tryGetIterByIndex(&iter, i))
            continue;

        gdt::FlagDebugData* debug_data = nullptr;
        if (util::getDebugHeap())
            debug_data = new (util::getDebugHeap()) gdt::FlagDebugData();

        GameData::loadDebugData(debug_data, iter);

        s32 hash = 0;
        iter.tryGetIntByKey(&hash, "HashValue");
        const u32 hash_u = hash;

        GameData::loadFlagProperties(&properties, iter);
        get_config_fn(&config, iter);

        flags[i].setDebugData(debug_data);
        flags[i].setType(flag_type);
        flags[i].setHash(hash_u);
        flags[i].setConfig(config);
        flags[i].resetToInitialValue();
        flags[i].setProperties(properties);

        if constexpr (IsBoolFlag) {
            s32 category = 0;
            iter.tryGetIntByKey(&category, "Category");
            flags[i].setCategory(category);
        }
    }
}

template <typename FlagType, typename GetConfigFn, typename GetConfigForChildFlagFn>
KSYS_ALWAYS_INLINE inline void
loadArrayFlags(const sead::SafeString& data_type, const al::ByamlIter& root_iter, sead::Heap* heap,
               sead::PtrArray<sead::Buffer<FlagType>>& flags,
               const sead::SafeString& wanted_data_type, gdt::FlagType flag_type,
               const GetConfigFn& get_config_fn,
               const GetConfigForChildFlagFn& get_config_for_child_flag_fn) {
    if (data_type != wanted_data_type)
        return;

    al::ByamlIter array_iter;
    if (!root_iter.tryGetIterByIndex(&array_iter, 0))
        return;

    const auto num_flags = array_iter.getSize();
    flags.allocBuffer(num_flags, heap);

    gdt::FlagProperties properties{};
    typename FlagType::ConfigType config{};

    for (s32 i = 0; i < num_flags; ++i) {
        al::ByamlIter iter;
        if (!array_iter.tryGetIterByIndex(&iter, i))
            continue;

        gdt::FlagDebugData* debug_data = nullptr;
        if (util::getDebugHeap())
            debug_data = new (util::getDebugHeap()) gdt::FlagDebugData();

        GameData::loadDebugData(debug_data, iter);

        s32 hash = 0;
        iter.tryGetIntByKey(&hash, "HashValue");
        const u32 hash_u = hash;

        GameData::loadFlagProperties(&properties, iter);
        get_config_fn(&config, iter);

        al::ByamlIter values_iter;
        al::ByamlIter init_value_iter;
        if (iter.tryGetIterByKey(&init_value_iter, "InitValue")) {
            al::ByamlIter item;
            if (init_value_iter.tryGetIterByIndex(&item, 0))
                item.tryGetIterByKey(&values_iter, "Values");
        }

        const s32 num_items = values_iter.getSize();
        auto& buffer = *(new (heap) sead::Buffer<FlagType>);
        buffer.allocBufferAssert(u32(num_items > 1 ? num_items : 1u), heap);

        for (s32 value_idx = 0; value_idx < num_items; ++value_idx) {
            buffer[value_idx].setDebugData(debug_data);
            buffer[value_idx].setType(flag_type);
            buffer[value_idx].setHash(hash_u);
            if (get_config_for_child_flag_fn(&config, values_iter, value_idx)) {
                buffer[value_idx].setConfig(config);
                buffer[value_idx].resetToInitialValue();
            }
            buffer[value_idx].setProperties(properties);
        }

        flags.pushBack(&buffer);
    }
}

inline void tryGetFloatOrInt(const al::ByamlIter& iter, const char* key, f32* value) {
    if (iter.tryGetFloatByKey(value, key))
        return;

    s32 int_value{};
    iter.tryGetIntByKey(&int_value, key);
    *value = int_value;
}

inline void tryGetFloatOrIntByIndex(const al::ByamlIter& iter, s32 index, f32* value) {
    if (iter.tryGetFloatByIndex(value, index))
        return;

    s32 int_value{};
    iter.tryGetIntByIndex(&int_value, index);
    *value = int_value;
}

template <typename T>
KSYS_ALWAYS_INLINE inline bool tryGetVector(const al::ByamlIter& value_iter, T* vector) {
    al::ByamlIter array_iter;
    if (!value_iter.tryGetIterByIndex(&array_iter, 0))
        return false;

    for (size_t i = 0; i < vector->e.size(); ++i)
        tryGetFloatOrIntByIndex(array_iter, i, &vector->e[i]);

    return true;
}
}  // namespace

// NON_MATCHING:
// * stack layout and reordering (possibly caused by the stack differences).
// * In init_string_array_flag_config, some calls to memcpy (for string copies) are replaced
//   with memset and calcLength() is optimized out.
// * sead::Vector4<float>::operator= (the original code does 64-bit loads and stores)
void GameData::doCreate_(u8* data, u32, sead::Heap*) {
    auto* heap = gdt::Manager::instance()->getSaveAreaHeap();

    const al::ByamlIter root_iter{data};

    const char* key = nullptr;
    root_iter.getKeyName(&key, 0);
    const sead::SafeString data_type = key;

    loadFlags(data_type, root_iter, heap, mBoolFlags, "bool_data", gdt::FlagType::Bool,
              [](gdt::FlagBool::ConfigType* config, const al::ByamlIter& iter) {
                  bool min_value{};
                  bool max_value{};
                  s32 init_value{};
                  iter.tryGetIntByKey(&init_value, "InitValue");
                  config->initial_value = init_value;
                  iter.tryGetBoolByKey(&min_value, "MinValue");
                  iter.tryGetBoolByKey(&max_value, "MaxValue");
              });

    loadFlags(data_type, root_iter, heap, mS32Flags, "s32_data", gdt::FlagType::S32,
              [](gdt::FlagS32::ConfigType* config, const al::ByamlIter& iter) {
                  s32 init_value{};
                  s32 min_value{};
                  s32 max_value{};
                  iter.tryGetIntByKey(&init_value, "InitValue");
                  iter.tryGetIntByKey(&min_value, "MinValue");
                  iter.tryGetIntByKey(&max_value, "MaxValue");
                  config->initial_value = init_value;
                  config->min_value = min_value;
                  config->max_value = max_value;
              });

    loadFlags(data_type, root_iter, heap, mF32Flags, "f32_data", gdt::FlagType::F32,
              [](gdt::FlagF32::ConfigType* config, const al::ByamlIter& iter) {
                  f32 init_value{};
                  f32 min_value{};
                  f32 max_value{};
                  tryGetFloatOrInt(iter, "InitValue", &init_value);
                  tryGetFloatOrInt(iter, "MinValue", &min_value);
                  tryGetFloatOrInt(iter, "MaxValue", &max_value);
                  config->initial_value = init_value;
                  config->min_value = min_value;
                  config->max_value = max_value;
              });

    const auto init_string_flag_config = [](auto* config, const al::ByamlIter& iter) {
        using StringType = decltype(config->initial_value);

        const char* init_value = "";
        iter.tryGetStringByKey(&init_value, "InitValue");

        auto* debug_heap = util::getDebugHeap();
        if (debug_heap && !sead::SafeString(init_value).isEmpty()) {
            auto* copy = new (debug_heap) StringType;
            copy->copy(init_value);
            init_value = copy->cstr();
        }
        config->initial_value = StringType(init_value);
        config->min_value = StringType("");
        config->max_value = StringType("");
    };

    loadFlags(data_type, root_iter, heap, mStringFlags, "string_data", gdt::FlagType::String,
              init_string_flag_config);

    loadFlags(data_type, root_iter, heap, mString64Flags, "string64_data", gdt::FlagType::String64,
              init_string_flag_config);

    loadFlags(data_type, root_iter, heap, mString256Flags, "string256_data",
              gdt::FlagType::String256, init_string_flag_config);

    const auto init_vector_flag_config = [](auto* config, const al::ByamlIter& iter) {
        using VectorType = decltype(config->initial_value);

        VectorType init_value;
        al::ByamlIter init_value_iter;
        if (iter.tryGetIterByKey(&init_value_iter, "InitValue"))
            tryGetVector(init_value_iter, &init_value);

        VectorType min_value;
        al::ByamlIter min_value_iter;
        if (iter.tryGetIterByKey(&min_value_iter, "MinValue"))
            tryGetVector(min_value_iter, &min_value);

        VectorType max_value;
        al::ByamlIter max_value_iter;
        if (iter.tryGetIterByKey(&max_value_iter, "MaxValue"))
            tryGetVector(max_value_iter, &max_value);

        config->initial_value = init_value;
        config->min_value = min_value;
        config->max_value = max_value;
    };

    loadFlags(data_type, root_iter, heap, mVector2fFlags, "vector2f_data", gdt::FlagType::Vector2f,
              init_vector_flag_config);

    loadFlags(data_type, root_iter, heap, mVector3fFlags, "vector3f_data", gdt::FlagType::Vector3f,
              init_vector_flag_config);

    loadFlags(data_type, root_iter, heap, mVector4fFlags, "vector4f_data", gdt::FlagType::Vector4f,
              init_vector_flag_config);

    loadArrayFlags(
        data_type, root_iter, heap, mBoolArrayFlags, "bool_array_data", gdt::FlagType::BoolArray,
        [](gdt::FlagBool::ConfigType*, const al::ByamlIter& iter) {
            bool min_value;
            bool max_value;
            iter.tryGetBoolByKey(&min_value, "MinValue");
            iter.tryGetBoolByKey(&max_value, "MaxValue");
        },
        [](gdt::FlagBool::ConfigType* config, const al::ByamlIter& values_iter, s32 value_idx) {
            bool value;
            s32 int_value{};
            if (values_iter.tryGetIntByIndex(&int_value, value_idx))
                value = int_value & 1;
            else
                values_iter.tryGetBoolByIndex(&value, value_idx);
            config->initial_value = value;
            return true;
        });

    loadArrayFlags(
        data_type, root_iter, heap, mS32ArrayFlags, "s32_array_data", gdt::FlagType::S32Array,
        [](gdt::FlagS32::ConfigType* config, const al::ByamlIter& iter) {
            s32 min_value;
            s32 max_value;
            iter.tryGetIntByKey(&min_value, "MinValue");
            iter.tryGetIntByKey(&max_value, "MaxValue");
            config->min_value = min_value;
            config->max_value = max_value;
        },
        [](gdt::FlagS32::ConfigType* config, const al::ByamlIter& values_iter, s32 value_idx) {
            s32 value;
            values_iter.tryGetIntByIndex(&value, value_idx);
            config->initial_value = value;
            return true;
        });

    loadArrayFlags(
        data_type, root_iter, heap, mF32ArrayFlags, "f32_array_data", gdt::FlagType::F32Array,
        [](gdt::FlagF32::ConfigType* config, const al::ByamlIter& iter) {
            f32 min_value;
            f32 max_value;
            iter.tryGetFloatByKey(&min_value, "MinValue");
            iter.tryGetFloatByKey(&max_value, "MaxValue");
            config->min_value = min_value;
            config->max_value = max_value;
        },
        [](gdt::FlagF32::ConfigType* config, const al::ByamlIter& values_iter, s32 value_idx) {
            f32 value;
            tryGetFloatOrIntByIndex(values_iter, value_idx, &value);
            config->initial_value = value;
            return true;
        });

    const auto init_string_array_flag_config = [](auto* config, const al::ByamlIter&) {
        using StringType = decltype(config->initial_value);
        config->min_value = StringType("");
        config->max_value = StringType("");
    };

    const auto init_string_array_child_flag_config =
        [heap](auto* config, const al::ByamlIter& values_iter, s32 value_idx) {
            using StringType = decltype(config->initial_value);

            const char* init_value = "";
            values_iter.tryGetStringByIndex(&init_value, value_idx);

            if (!sead::SafeString(init_value).isEmpty()) {
                auto* copy = new (heap) StringType;
                copy->copy(init_value);
                init_value = copy->cstr();
            }
            config->initial_value = StringType(init_value);
            return true;
        };

    loadArrayFlags(data_type, root_iter, heap, mStringArrayFlags, "string32_array_data",
                   gdt::FlagType::StringArray, init_string_array_flag_config,
                   init_string_array_child_flag_config);

    loadArrayFlags(data_type, root_iter, heap, mString64ArrayFlags, "string64_array_data",
                   gdt::FlagType::String64Array, init_string_array_flag_config,
                   init_string_array_child_flag_config);

    loadArrayFlags(data_type, root_iter, heap, mString256ArrayFlags, "string256_array_data",
                   gdt::FlagType::String256Array, init_string_array_flag_config,
                   init_string_array_child_flag_config);

    const auto init_vector_array_flag_config = [](auto* config, const al::ByamlIter& iter) {
        using VectorType = decltype(config->initial_value);

        VectorType min_value;
        al::ByamlIter min_value_iter;
        if (iter.tryGetIterByKey(&min_value_iter, "MinValue"))
            tryGetVector(min_value_iter, &min_value);

        VectorType max_value;
        al::ByamlIter max_value_iter;
        if (iter.tryGetIterByKey(&max_value_iter, "MaxValue"))
            tryGetVector(max_value_iter, &max_value);

        config->min_value = min_value;
        config->max_value = max_value;
    };

    const auto init_vector_array_child_flag_config =
        [](auto* config, const al::ByamlIter& values_iter, s32 value_idx) {
            using VectorType = decltype(config->initial_value);

            VectorType value;
            al::ByamlIter value_iter;
            if (!values_iter.tryGetIterByIndex(&value_iter, value_idx))
                return false;

            if (!tryGetVector(value_iter, &value))
                return false;

            config->initial_value = value;
            return true;
        };

    loadArrayFlags(data_type, root_iter, heap, mVector2fArrayFlags, "vector2f_array_data",
                   gdt::FlagType::Vector2fArray, init_vector_array_flag_config,
                   init_vector_array_child_flag_config);

    loadArrayFlags(data_type, root_iter, heap, mVector3fArrayFlags, "vector3f_array_data",
                   gdt::FlagType::Vector3fArray, init_vector_array_flag_config,
                   init_vector_array_child_flag_config);

    loadArrayFlags(data_type, root_iter, heap, mVector4fArrayFlags, "vector4f_array_data",
                   gdt::FlagType::Vector4fArray, init_vector_array_flag_config,
                   init_vector_array_child_flag_config);
}

void GameData::loadDebugData(gdt::FlagDebugData* data, const al::ByamlIter& iter) {
    if (!data)
        return;

    const char* data_name = "";
    s32 delete_rev = -1;

    iter.tryGetStringByKey(&data_name, "DataName");
    iter.tryGetIntByKey(&delete_rev, "DeleteRev");

    data->name = "";
    if (util::getDebugHeap() && !sead::SafeString(data_name).isEmpty()) {
        const s32 len = sead::SafeString(data_name).calcLength();
        auto* ptr = new (util::getDebugHeap()) char[len + 1];
        std::strncpy(ptr, data_name, len);
        ptr[len] = sead::SafeString::cNullChar;
        data->name = ptr;
    }

    data->delete_rev = delete_rev;
}

void GameData::loadFlagProperties(gdt::FlagProperties* properties, const al::ByamlIter& iter) {
    bool is_one_trigger = false;
    bool is_program_readable = false;
    bool is_program_writable = false;
    bool is_save = false;
    bool is_event_associated = false;
    int reset_type = 0;

    iter.tryGetBoolByKey(&is_one_trigger, "IsOneTrigger");
    iter.tryGetBoolByKey(&is_program_readable, "IsProgramReadable");
    iter.tryGetBoolByKey(&is_program_writable, "IsProgramWritable");
    iter.tryGetBoolByKey(&is_save, "IsSave");
    iter.tryGetBoolByKey(&is_event_associated, "IsEventAssociated");
    iter.tryGetIntByKey(&reset_type, "ResetType");

    properties->setIsOneTrigger(is_one_trigger);
    properties->setIsProgramReadable(is_program_readable);
    properties->setIsProgramWritable(is_program_writable);
    properties->setIsSave(is_save);
    properties->setIsEventAssociated(is_event_associated);
    properties->setResetType(gdt::ResetType(reset_type));
}

}  // namespace ksys::res
