#include "KingSystem/GameData/gdtTriggerParam.h"
#include <algorithm>
#include "KingSystem/GameData/gdtFlagProxy.h"
#include "KingSystem/Resource/resResourceGameData.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::gdt {

TriggerParam::TriggerParam() {
    mUnkArray.constructDefault();
    mCriticalSections.constructDefault();
    mBitFlags.constructDefault();
    mCounts.fill(0);
    mNumBoolFlagsPerCategory.fill(0);
}

namespace {
// TODO (low-priority): implement this without using <algorithm> to match the original code
// The original code appears to perform a heapsort.
[[gnu::noinline]] void sortFlagPtrArray(sead::PtrArray<FlagBase>& array) {
    std::sort(array.dataBegin(), array.dataEnd(),
              [](const FlagBase* a, const FlagBase* b) { return a->getHash() < b->getHash(); });
}

inline s32 getFlagIndex(const sead::PtrArray<FlagBase>& flags, u32 name_hash) {
    s32 a = 0;
    s32 b = flags.size() - 1;
    while (a < b) {
        const s32 m = (a + b) / 2;
        if (flags[m]->getHash() == name_hash)
            return m;
        if (flags[m]->getHash() < name_hash)
            a = m + 1;
        else
            b = m;
    }

    if (flags[a]->getHash() == name_hash)
        return a;

    return -1;
}

inline s32 getFlagIndex(const sead::PtrArray<sead::PtrArray<FlagBase>>& flags, u32 name_hash) {
    for (s32 i = 0; i < flags.size(); ++i) {
        const auto& array = *flags[i];
        if (array.size() > 0 && array[0]->getHash() == name_hash)
            return i;
    }
    return -1;
}

template <typename T>
inline Flag<T>* getFlagByIndex(const sead::PtrArray<FlagBase>& flags, s32 index) {
    if (index < 0 || index >= flags.size())
        return nullptr;
    return static_cast<Flag<T>*>(flags[index]);
}

template <typename T>
inline Flag<T>* getFlag(const sead::PtrArray<FlagBase>& flags, u32 name_hash) {
    return getFlagByIndex<T>(flags, getFlagIndex(flags, name_hash));
}

template <typename T>
inline Flag<T>* getFlag(const sead::PtrArray<FlagBase>& flags, const sead::SafeString& name) {
    if (name.isEmpty())
        return nullptr;
    return getFlag<T>(flags, sead::HashCRC32::calcStringHash(name));
}

template <typename T, typename FlagValueType = T>
inline bool getFlagValue(const sead::PtrArray<FlagBase>& array, T* out_value, s32 index,
                         bool check_permissions) {
    static_assert(isValidFlagValueType<FlagValueType>());

    const auto* flag = getFlagByIndex<FlagValueType>(array, index);
    if (!flag)
        return false;

    if (check_permissions && !flag->getProperties().isProgramReadable())
        return false;

    if constexpr (std::is_same<T, const char*>())
        *out_value = flag->getValueRef().cstr();
    else
        *out_value = flag->getValue();

    return true;
}

template <typename T, typename FlagValueType = T>
inline bool getFlagValue(const sead::PtrArray<sead::PtrArray<FlagBase>>& arrays, T* out_value,
                         s32 array_index, s32 flag_index, bool check_permissions) {
    static_assert(isValidFlagValueType<FlagValueType>());

    if (array_index < 0 || array_index >= arrays.size())
        return false;

    const auto* array = arrays[array_index];
    if (!array)
        return false;

    const auto* flag = getFlagByIndex<FlagValueType>(*array, flag_index);
    if (!flag)
        return false;

    if (check_permissions && !flag->getProperties().isProgramReadable())
        return false;

    if constexpr (std::is_same<T, const char*>())
        *out_value = flag->getValueRef().cstr();
    else
        *out_value = flag->getValue();

    return true;
}

bool getFlagArraySize(const sead::PtrArray<sead::PtrArray<FlagBase>>& arrays, s32 index, s32* out) {
    if (index < 0 || index >= arrays.size())
        return false;
    *out = arrays[index]->size();
    return true;
}

template <typename T>
inline void copyGameDataResBuffer(sead::Buffer<T>& source, sead::PtrArray<FlagBase>& dest,
                                  sead::Heap* heap) {
    if (source.size() == 0)
        return;

    if (!dest.isBufferReady())
        dest.allocBuffer(source.size(), heap);

    for (auto& flag : source)
        dest.pushBack(&flag);
}

template <typename T>
inline void copyGameDataResBuffer(sead::PtrArray<sead::Buffer<T>>& source,
                                  sead::PtrArray<sead::PtrArray<FlagBase>>& dest,
                                  sead::Heap* heap) {
    const auto n = source.capacity();
    if (n < 1)
        return;

    if (!dest.isBufferReady())
        dest.allocBuffer(n, heap);

    for (s32 i = 0; i < n; ++i) {
        dest.pushBack(new (heap) sead::PtrArray<FlagBase>);
        const auto num_flags = source[i]->size();

        if (!dest[i]->isBufferReady())
            dest[i]->allocBuffer(num_flags, heap);

        for (s32 j = 0; j < num_flags; ++j)
            dest[i]->pushBack(std::addressof((*source[i])[j]));
    }
}

template <typename T>
void makeFlagProxies(sead::PtrArray<FlagBase>& dest, const sead::PtrArray<FlagBase>& src, s32 count,
                     sead::Heap* heap, bool permanent_flags_only) {
    for (s32 i = 0; i < count; ++i) {
        auto* flag = static_cast<Flag<T>*>(src[i]);
        if (!permanent_flags_only) {
            auto* proxy = new (heap) FlagProxy<T>;
            proxy->setFlag(flag);
            proxy->setValue(flag->getValue());
            proxy->setCategory(flag->getCategory());
            dest.pushBack(proxy);
        } else if (flag->isPermanent()) {
            auto* proxy = new (heap) FlagProxy<T>;
            proxy->setFlag(flag);
            proxy->setValue(flag->getValue());
            proxy->setCategory(flag->getCategory());
            dest.pushBack(proxy);
        }
    }
}
}  // namespace

void TriggerParam::copyFromGameDataRes(res::GameData* gdata, sead::Heap* heap) {
    if (!gdata)
        return;

    copyGameDataResBuffer(gdata->getBoolFlags(), mBoolFlags, heap);
    copyGameDataResBuffer(gdata->getS32Flags(), mS32Flags, heap);
    copyGameDataResBuffer(gdata->getF32Flags(), mF32Flags, heap);
    copyGameDataResBuffer(gdata->getStringFlags(), mStringFlags, heap);
    copyGameDataResBuffer(gdata->getString64Flags(), mString64Flags, heap);
    copyGameDataResBuffer(gdata->getString256Flags(), mString256Flags, heap);
    copyGameDataResBuffer(gdata->getVector2fFlags(), mVector2fFlags, heap);
    copyGameDataResBuffer(gdata->getVector3fFlags(), mVector3fFlags, heap);
    copyGameDataResBuffer(gdata->getVector4fFlags(), mVector4fFlags, heap);

    copyGameDataResBuffer(gdata->getBoolArrayFlags(), mBoolArrayFlags, heap);
    copyGameDataResBuffer(gdata->getS32ArrayFlags(), mS32ArrayFlags, heap);
    copyGameDataResBuffer(gdata->getF32ArrayFlags(), mF32ArrayFlags, heap);
    copyGameDataResBuffer(gdata->getStringArrayFlags(), mStringArrayFlags, heap);
    copyGameDataResBuffer(gdata->getString64ArrayFlags(), mString64ArrayFlags, heap);
    copyGameDataResBuffer(gdata->getString256ArrayFlags(), mString256ArrayFlags, heap);
    copyGameDataResBuffer(gdata->getVector2fArrayFlags(), mVector2fArrayFlags, heap);
    copyGameDataResBuffer(gdata->getVector3fArrayFlags(), mVector3fArrayFlags, heap);
    copyGameDataResBuffer(gdata->getVector4fArrayFlags(), mVector4fArrayFlags, heap);

    mResourceFlags = gdata->getField14();
}

void TriggerParam::init(sead::Heap* heap) {
    sortFlagPtrArray(mBoolFlags);
    sortFlagPtrArray(mS32Flags);
    sortFlagPtrArray(mF32Flags);
    sortFlagPtrArray(mStringFlags);
    sortFlagPtrArray(mString64Flags);
    sortFlagPtrArray(mString256Flags);
    sortFlagPtrArray(mVector2fFlags);
    sortFlagPtrArray(mVector3fFlags);
    sortFlagPtrArray(mVector4fFlags);
    allocCombinedFlagArrays(heap);
    updateBoolFlagCounts();
    mHeap = heap;
}

void TriggerParam::allocCombinedFlagArrays(sead::Heap* heap) {
#define ALLOC_COMBINED_ARRAY_(FLAGS, FLAG_ARRAYS, DEST)                                            \
    {                                                                                              \
        s32 size = FLAGS.size();                                                                   \
        for (s32 i = 0; i < FLAG_ARRAYS.size(); ++i)                                               \
            size += FLAG_ARRAYS[i]->size();                                                        \
                                                                                                   \
        DEST.allocBuffer(size, heap);                                                              \
    }

    ALLOC_COMBINED_ARRAY_(mBoolFlags, mBoolArrayFlags, mCombinedBoolFlags);
    ALLOC_COMBINED_ARRAY_(mS32Flags, mS32ArrayFlags, mCombinedS32Flags);
    ALLOC_COMBINED_ARRAY_(mF32Flags, mF32ArrayFlags, mCombinedF32Flags);
    ALLOC_COMBINED_ARRAY_(mStringFlags, mStringArrayFlags, mCombinedStringFlags);
    ALLOC_COMBINED_ARRAY_(mString64Flags, mString64ArrayFlags, mCombinedString64Flags);
    ALLOC_COMBINED_ARRAY_(mString256Flags, mString256ArrayFlags, mCombinedString256Flags);
    ALLOC_COMBINED_ARRAY_(mVector2fFlags, mVector2fArrayFlags, mCombinedVector2fFlags);
    ALLOC_COMBINED_ARRAY_(mVector3fFlags, mVector3fArrayFlags, mCombinedVector3fFlags);
    ALLOC_COMBINED_ARRAY_(mVector4fFlags, mVector4fArrayFlags, mCombinedVector4fFlags);

#undef ALLOC_COMBINED_ARRAY_
}

void TriggerParam::updateBoolFlagCounts() {
    for (s32 i = 0; i < mBoolFlags.size(); ++i) {
        const s32 category = mBoolFlags[i]->getCategory();
        if (category > 0)
            ++mNumBoolFlagsPerCategory[category - 1];
    }

    for (s32 array_i = 0; array_i < mBoolArrayFlags.size(); ++array_i) {
        for (s32 i = 0; i < mBoolArrayFlags[array_i]->size(); ++i) {
            const s32 category = (*mBoolArrayFlags[array_i])[i]->getCategory();
            if (category > 0)
                ++mNumBoolFlagsPerCategory[category - 1];
        }
    }
}

void TriggerParam::destroyHeap() {
    util::safeDeleteHeap(mHeap);
}

void TriggerParam::allocBools(s32 size, sead::Heap* heap) {
    mBoolFlags.allocBuffer(size, heap);
}

void TriggerParam::allocS32s(s32 size, sead::Heap* heap) {
    mS32Flags.allocBuffer(size, heap);
}

void TriggerParam::initResetData(sead::Heap* heap) {
    s32 num_reset_entries = 0;

#define COUNT_FLAGS_(FLAGS)                                                                        \
    do {                                                                                           \
        for (s32 i = 0; i < FLAGS.size(); ++i) {                                                   \
            if (FLAGS[i]->isResettable())                                                          \
                ++num_reset_entries;                                                               \
        }                                                                                          \
    } while (0)

#define COUNT_FLAGS_ARRAY_(ARRAYS)                                                                 \
    do {                                                                                           \
        for (s32 i = 0; i < ARRAYS.size(); ++i) {                                                  \
            if ((*ARRAYS[i])[0]->isResettable())                                                   \
                ++num_reset_entries;                                                               \
        }                                                                                          \
    } while (0)

    COUNT_FLAGS_(mBoolFlags);
    COUNT_FLAGS_(mS32Flags);
    COUNT_FLAGS_(mF32Flags);
    COUNT_FLAGS_(mStringFlags);
    COUNT_FLAGS_(mString64Flags);
    COUNT_FLAGS_(mString256Flags);
    COUNT_FLAGS_(mVector2fFlags);
    COUNT_FLAGS_(mVector3fFlags);
    COUNT_FLAGS_(mVector4fFlags);

    COUNT_FLAGS_ARRAY_(mBoolArrayFlags);
    COUNT_FLAGS_ARRAY_(mS32ArrayFlags);
    COUNT_FLAGS_ARRAY_(mF32ArrayFlags);
    COUNT_FLAGS_ARRAY_(mStringArrayFlags);
    COUNT_FLAGS_ARRAY_(mString64ArrayFlags);
    COUNT_FLAGS_ARRAY_(mString256ArrayFlags);
    COUNT_FLAGS_ARRAY_(mVector2fArrayFlags);
    COUNT_FLAGS_ARRAY_(mVector3fArrayFlags);
    COUNT_FLAGS_ARRAY_(mVector4fArrayFlags);

#undef COUNT_FLAGS_
#undef COUNT_FLAGS_ARRAY_

    if (num_reset_entries == 0)
        return;

    mResetEntries.allocBufferAssert(num_reset_entries, heap);

    s32 reset_entry_idx = 0;

#define ADD_ENTRIES_(TYPE, FLAGS)                                                                  \
    do {                                                                                           \
        for (s32 i = 0; i < FLAGS.size(); ++i) {                                                   \
            if (!FLAGS[i]->isResettable())                                                         \
                continue;                                                                          \
            mResetEntries[reset_entry_idx].type = TYPE;                                            \
            mResetEntries[reset_entry_idx].index = i;                                              \
            mResetEntries[reset_entry_idx].reset_type = FLAGS[i]->getProperties().getResetType();  \
            ++reset_entry_idx;                                                                     \
            if (reset_entry_idx == num_reset_entries)                                              \
                return;                                                                            \
        }                                                                                          \
    } while (0)

#define ADD_ENTRIES_ARRAY_(TYPE, ARRAYS)                                                           \
    do {                                                                                           \
        for (s32 i = 0; i < ARRAYS.size(); ++i) {                                                  \
            if (!(*ARRAYS[i])[0]->isResettable())                                                  \
                continue;                                                                          \
                                                                                                   \
            mResetEntries[reset_entry_idx].type = TYPE;                                            \
                                                                                                   \
            /* ??? */                                                                              \
            if constexpr (TYPE == FlagType::String256Array)                                        \
                mResetEntries[reset_entry_idx].index = s16(i);                                     \
            else                                                                                   \
                mResetEntries[reset_entry_idx].index = i;                                          \
                                                                                                   \
            mResetEntries[reset_entry_idx].reset_type =                                            \
                (*ARRAYS[i])[0]->getProperties().getResetType();                                   \
                                                                                                   \
            ++reset_entry_idx;                                                                     \
            if (reset_entry_idx == num_reset_entries)                                              \
                return;                                                                            \
        }                                                                                          \
    } while (0)

    ADD_ENTRIES_(FlagType::Bool, mBoolFlags);
    ADD_ENTRIES_(FlagType::S32, mS32Flags);
    ADD_ENTRIES_(FlagType::F32, mF32Flags);
    ADD_ENTRIES_(FlagType::String, mStringFlags);
    ADD_ENTRIES_(FlagType::String64, mString64Flags);
    ADD_ENTRIES_(FlagType::String256, mString256Flags);
    ADD_ENTRIES_(FlagType::Vector2f, mVector2fFlags);
    ADD_ENTRIES_(FlagType::Vector3f, mVector3fFlags);
    ADD_ENTRIES_(FlagType::Vector4f, mVector4fFlags);

    ADD_ENTRIES_ARRAY_(FlagType::BoolArray, mBoolArrayFlags);
    ADD_ENTRIES_ARRAY_(FlagType::S32Array, mS32ArrayFlags);
    ADD_ENTRIES_ARRAY_(FlagType::F32Array, mF32ArrayFlags);
    ADD_ENTRIES_ARRAY_(FlagType::StringArray, mStringArrayFlags);
    ADD_ENTRIES_ARRAY_(FlagType::String64Array, mString64ArrayFlags);
    ADD_ENTRIES_ARRAY_(FlagType::String256Array, mString256ArrayFlags);
    ADD_ENTRIES_ARRAY_(FlagType::Vector2fArray, mVector2fArrayFlags);
    ADD_ENTRIES_ARRAY_(FlagType::Vector3fArray, mVector3fArrayFlags);
    ADD_ENTRIES_ARRAY_(FlagType::Vector4fArray, mVector4fArrayFlags);

#undef ADD_ENTRIES_
#undef ADD_ENTRIES_ARRAY_
}

void TriggerParam::initRevivalRandomBools(sead::Heap* heap) {
    s32 count = 0;
    for (s32 i = 0; i < mBoolFlags.size(); ++i) {
        if (static_cast<FlagBool*>(mBoolFlags[i])->getRandomResetData())
            ++count;
    }

    if (count == 0)
        return;

    mRevivalRandomBools.allocBuffer(count, heap);
    for (s32 i = 0; i < mBoolFlags.size(); ++i) {
        if (static_cast<FlagBool*>(mBoolFlags[i])->getRandomResetData())
            mRevivalRandomBools.pushBack(static_cast<FlagBool*>(mBoolFlags[i]));
    }
}

void TriggerParam::copyAllFlags(const TriggerParam& src, sead::Heap* heap, bool init_reset_data) {
    mResourceFlags = src.mResourceFlags;

    s32 num_flags = 0;

#define COPY_(MEMBER, T)                                                                           \
    do {                                                                                           \
        const auto size = src.MEMBER.size();                                                       \
        if (size > 0) {                                                                            \
            MEMBER.allocBuffer(size, heap);                                                        \
            makeFlagProxies<T>(MEMBER, src.MEMBER, size, heap, false);                             \
            num_flags += size;                                                                     \
        }                                                                                          \
    } while (0)

    COPY_(mBoolFlags, bool);
    COPY_(mS32Flags, s32);
    COPY_(mF32Flags, f32);
    COPY_(mStringFlags, sead::FixedSafeString<32>);
    COPY_(mString64Flags, sead::FixedSafeString<64>);
    COPY_(mString256Flags, sead::FixedSafeString<256>);
    COPY_(mVector2fFlags, sead::Vector2f);
    COPY_(mVector3fFlags, sead::Vector3f);
    COPY_(mVector4fFlags, sead::Vector4f);

#undef COPY_

#define COPY_ARRAY_(MEMBER, T)                                                                     \
    do {                                                                                           \
        const auto size = src.MEMBER.size();                                                       \
        if (size > 0) {                                                                            \
            MEMBER.allocBuffer(size, heap);                                                        \
            for (s32 i = 0; i < size; ++i) {                                                       \
                const auto array_size = src.MEMBER[i]->size();                                     \
                if (array_size > 0) {                                                              \
                    MEMBER.pushBack(new (heap) sead::PtrArray<FlagBase>);                          \
                    MEMBER[i]->allocBuffer(std::max(1, array_size), heap);                         \
                    makeFlagProxies<T>(*MEMBER[i], *src.MEMBER[i], array_size, heap, false);       \
                    num_flags += size;                                                             \
                }                                                                                  \
            }                                                                                      \
        }                                                                                          \
    } while (0)

    COPY_ARRAY_(mBoolArrayFlags, bool);
    COPY_ARRAY_(mS32ArrayFlags, s32);
    COPY_ARRAY_(mF32ArrayFlags, f32);
    COPY_ARRAY_(mStringArrayFlags, sead::FixedSafeString<32>);
    COPY_ARRAY_(mString64ArrayFlags, sead::FixedSafeString<64>);
    COPY_ARRAY_(mString256ArrayFlags, sead::FixedSafeString<256>);
    COPY_ARRAY_(mVector2fArrayFlags, sead::Vector2f);
    COPY_ARRAY_(mVector3fArrayFlags, sead::Vector3f);
    COPY_ARRAY_(mVector4fArrayFlags, sead::Vector4f);

#undef COPY_
#undef COPY_ARRAY_

    if (init_reset_data) {
        for (auto& array : *mUnkArray.data())
            array.allocBufferAssert(num_flags, heap);
        initResetData(heap);
        initRevivalRandomBools(heap);
    }

    mHeap = heap;
}

void TriggerParam::copyPermanentFlags(const TriggerParam& src, sead::Heap* heap) {
#define COPY_(MEMBER, T)                                                                           \
    do {                                                                                           \
        const auto size = src.MEMBER.size();                                                       \
        if (size > 0) {                                                                            \
            s32 num_permanent_flags = 0;                                                           \
            for (s32 i = 0; i < size; ++i) {                                                       \
                if (src.MEMBER[i]->isPermanent())                                                  \
                    ++num_permanent_flags;                                                         \
            }                                                                                      \
            MEMBER.allocBuffer(std::max(1, num_permanent_flags), heap);                            \
            makeFlagProxies<T>(MEMBER, src.MEMBER, size, heap, true);                              \
        }                                                                                          \
    } while (0)

    COPY_(mBoolFlags, bool);
    COPY_(mS32Flags, s32);
    COPY_(mF32Flags, f32);
    COPY_(mStringFlags, sead::FixedSafeString<32>);
    COPY_(mString64Flags, sead::FixedSafeString<64>);
    COPY_(mString256Flags, sead::FixedSafeString<256>);
    COPY_(mVector2fFlags, sead::Vector2f);
    COPY_(mVector3fFlags, sead::Vector3f);
    COPY_(mVector4fFlags, sead::Vector4f);

#undef COPY_

#define COPY_ARRAY_(MEMBER, T)                                                                     \
    do {                                                                                           \
        const auto size = src.MEMBER.size();                                                       \
        if (size > 0) {                                                                            \
            MEMBER.allocBuffer(size, heap);                                                        \
            for (s32 i = 0; i < size; ++i) {                                                       \
                const auto array_size = src.MEMBER[i]->size();                                     \
                if (array_size > 0) {                                                              \
                    auto* array = new (heap) sead::PtrArray<FlagBase>;                             \
                    MEMBER.pushBack(array);                                                        \
                    MEMBER[i]->allocBuffer(std::max(1, array_size), heap);                         \
                    makeFlagProxies<T>(*MEMBER[i], *src.MEMBER[i], array_size, heap, true);        \
                }                                                                                  \
            }                                                                                      \
        }                                                                                          \
    } while (0)

    COPY_ARRAY_(mBoolArrayFlags, bool);
    COPY_ARRAY_(mS32ArrayFlags, s32);
    COPY_ARRAY_(mF32ArrayFlags, f32);
    COPY_ARRAY_(mStringArrayFlags, sead::FixedSafeString<32>);
    COPY_ARRAY_(mString64ArrayFlags, sead::FixedSafeString<64>);
    COPY_ARRAY_(mString256ArrayFlags, sead::FixedSafeString<256>);
    COPY_ARRAY_(mVector2fArrayFlags, sead::Vector2f);
    COPY_ARRAY_(mVector3fArrayFlags, sead::Vector3f);
    COPY_ARRAY_(mVector4fArrayFlags, sead::Vector4f);

#undef COPY_
#undef COPY_ARRAY_

    mHeap = heap;
}

FlagType TriggerParam::getFlagType(const sead::SafeString& name) const {
    if (getBoolIdx(name) != -1)
        return FlagType::Bool;
    if (getBoolArrayIdx(name) != -1)
        return FlagType::BoolArray;

    if (getS32Idx(name) != -1)
        return FlagType::S32;
    if (getS32ArrayIdx(name) != -1)
        return FlagType::S32Array;

    if (getStrIdx(name) != -1)
        return FlagType::String;
    if (getStrArrayIdx(name) != -1)
        return FlagType::StringArray;

    if (getF32Idx(name) != -1)
        return FlagType::F32;
    if (getF32ArrayIdx(name) != -1)
        return FlagType::F32Array;

    if (getVec3fIdx(name) != -1)
        return FlagType::Vector3f;
    if (getVec3fArrayIdx(name) != -1)
        return FlagType::Vector3fArray;

    if (getStr64Idx(name) != -1)
        return FlagType::String64;

    if (getStr256ArrayIdx(name) != -1)
        return FlagType::String256Array;
    if (getStr256Idx(name) != -1)
        return FlagType::String256;

    if (getStr64ArrayIdx(name) != -1)
        return FlagType::String64Array;

    if (getVec2fIdx(name) != -1)
        return FlagType::Vector2f;
    if (getVec2fArrayIdx(name) != -1)
        return FlagType::Vector2fArray;

    if (getVec4fIdx(name) != -1)
        return FlagType::Vector4f;
    if (getVec4fArrayIdx(name) != -1)
        return FlagType::Vector4fArray;

    return FlagType::Invalid;
}

bool TriggerParam::getBool(bool* value, s32 index, bool check_permissions) const {
    return getFlagValue(mBoolFlags, value, index, check_permissions);
}

bool TriggerParam::getS32(s32* value, s32 index, bool check_permissions) const {
    return getFlagValue(mS32Flags, value, index, check_permissions);
}

bool TriggerParam::getF32(f32* value, s32 index, bool check_permissions) const {
    return getFlagValue(mF32Flags, value, index, check_permissions);
}

bool TriggerParam::getStr(const char** value, s32 index, bool check_permissions) const {
    return getFlagValue<const char*, sead::FixedSafeString<32>>(mStringFlags, value, index,
                                                                check_permissions);
}

bool TriggerParam::getStr64(const char** value, s32 index, bool check_permissions) const {
    return getFlagValue<const char*, sead::FixedSafeString<64>>(mString64Flags, value, index,
                                                                check_permissions);
}

bool TriggerParam::getStr256(const char** value, s32 index, bool check_permissions) const {
    return getFlagValue<const char*, sead::FixedSafeString<256>>(mString256Flags, value, index,
                                                                 check_permissions);
}

bool TriggerParam::getVec2f(sead::Vector2f* value, s32 index, bool check_permissions) const {
    return getFlagValue(mVector2fFlags, value, index, check_permissions);
}

bool TriggerParam::getVec3f(sead::Vector3f* value, s32 index, bool check_permissions) const {
    return getFlagValue(mVector3fFlags, value, index, check_permissions);
}

bool TriggerParam::getVec4f(sead::Vector4f* value, s32 index, bool check_permissions) const {
    return getFlagValue(mVector4fFlags, value, index, check_permissions);
}

bool TriggerParam::getBool(bool* value, const sead::SafeString& name,
                           bool check_permissions) const {
    return getBool(value, getBoolIdx(name), check_permissions);
}

bool TriggerParam::getBool2(bool* value, const sead::SafeString& name,
                            bool check_permissions) const {
    return getBool(value, getBoolIdx(name), check_permissions);
}

bool TriggerParam::getS32(s32* value, const sead::SafeString& name, bool check_permissions) const {
    return getS32(value, getS32Idx(name), check_permissions);
}

bool TriggerParam::getF32(f32* value, const sead::SafeString& name, bool check_permissions) const {
    return getF32(value, getF32Idx(name), check_permissions);
}

bool TriggerParam::getStr(const char** value, const sead::SafeString& name,
                          bool check_permissions) const {
    return getStr(value, getStrIdx(name), check_permissions);
}

bool TriggerParam::getStr64(const char** value, const sead::SafeString& name,
                            bool check_permissions) const {
    return getStr64(value, getStr64Idx(name), check_permissions);
}

bool TriggerParam::getStr256(const char** value, const sead::SafeString& name,
                             bool check_permissions) const {
    return getStr256(value, getStr256Idx(name), check_permissions);
}

bool TriggerParam::getVec2f(sead::Vector2f* value, const sead::SafeString& name,
                            bool check_permissions) const {
    return getVec2f(value, getVec2fIdx(name), check_permissions);
}

bool TriggerParam::getVec3f(sead::Vector3f* value, const sead::SafeString& name,
                            bool check_permissions) const {
    return getVec3f(value, getVec3fIdx(name), check_permissions);
}

bool TriggerParam::getVec4f(sead::Vector4f* value, const sead::SafeString& name,
                            bool check_permissions) const {
    return getVec4f(value, getVec4fIdx(name), check_permissions);
}

bool TriggerParam::getBool(bool* value, s32 array_index, s32 index, bool check_permissions) const {
    return getFlagValue(mBoolArrayFlags, value, array_index, index, check_permissions);
}

bool TriggerParam::getS32(s32* value, s32 array_index, s32 index, bool check_permissions) const {
    return getFlagValue(mS32ArrayFlags, value, array_index, index, check_permissions);
}

bool TriggerParam::getF32(f32* value, s32 array_index, s32 index, bool check_permissions) const {
    return getFlagValue(mF32ArrayFlags, value, array_index, index, check_permissions);
}

bool TriggerParam::getStr(const char** value, s32 array_index, s32 index,
                          bool check_permissions) const {
    return getFlagValue<const char*, sead::FixedSafeString<32>>(
        mStringArrayFlags, value, array_index, index, check_permissions);
}

bool TriggerParam::getStr64(const char** value, s32 array_index, s32 index,
                            bool check_permissions) const {
    return getFlagValue<const char*, sead::FixedSafeString<64>>(
        mString64ArrayFlags, value, array_index, index, check_permissions);
}

bool TriggerParam::getStr256(const char** value, s32 array_index, s32 index,
                             bool check_permissions) const {
    return getFlagValue<const char*, sead::FixedSafeString<256>>(
        mString256ArrayFlags, value, array_index, index, check_permissions);
}

bool TriggerParam::getVec2f(sead::Vector2f* value, s32 array_index, s32 index,
                            bool check_permissions) const {
    return getFlagValue(mVector2fArrayFlags, value, array_index, index, check_permissions);
}

bool TriggerParam::getVec3f(sead::Vector3f* value, s32 array_index, s32 index,
                            bool check_permissions) const {
    return getFlagValue(mVector3fArrayFlags, value, array_index, index, check_permissions);
}

bool TriggerParam::getVec4f(sead::Vector4f* value, s32 array_index, s32 index,
                            bool check_permissions) const {
    return getFlagValue(mVector4fArrayFlags, value, array_index, index, check_permissions);
}

bool TriggerParam::getBool(bool* value, const sead::SafeString& name, s32 index,
                           bool check_permissions) const {
    return getBool(value, getBoolArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getS32(s32* value, const sead::SafeString& name, s32 index,
                          bool check_permissions) const {
    return getS32(value, getS32ArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getF32(f32* value, const sead::SafeString& name, s32 index,
                          bool check_permissions) const {
    return getF32(value, getF32ArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getStr(const char** value, const sead::SafeString& name, s32 index,
                          bool check_permissions) const {
    return getStr(value, getStrArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getStr64(const char** value, const sead::SafeString& name, s32 index,
                            bool check_permissions) const {
    return getStr64(value, getStr64ArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getStr256(const char** value, const sead::SafeString& name, s32 index,
                             bool check_permissions) const {
    return getStr256(value, getStr256ArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getVec2f(sead::Vector2f* value, const sead::SafeString& name, s32 index,
                            bool check_permissions) const {
    return getVec2f(value, getVec2fArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getVec3f(sead::Vector3f* value, const sead::SafeString& name, s32 index,
                            bool check_permissions) const {
    return getVec3f(value, getVec3fArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getVec4f(sead::Vector4f* value, const sead::SafeString& name, s32 index,
                            bool check_permissions) const {
    return getVec4f(value, getVec4fArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getBoolArraySize(s32* size, s32 index) const {
    return getFlagArraySize(mBoolArrayFlags, index, size);
}

bool TriggerParam::getS32ArraySize(s32* size, s32 index) const {
    return getFlagArraySize(mS32ArrayFlags, index, size);
}

bool TriggerParam::getF32ArraySize(s32* size, s32 index) const {
    return getFlagArraySize(mF32ArrayFlags, index, size);
}

bool TriggerParam::getStrArraySize(s32* size, s32 index) const {
    return getFlagArraySize(mStringArrayFlags, index, size);
}

bool TriggerParam::getStr64ArraySize(s32* size, s32 index) const {
    return getFlagArraySize(mString64ArrayFlags, index, size);
}

bool TriggerParam::getStr256ArraySize(s32* size, s32 index) const {
    return getFlagArraySize(mString256ArrayFlags, index, size);
}

bool TriggerParam::getVec2fArraySize(s32* size, s32 index) const {
    return getFlagArraySize(mVector2fArrayFlags, index, size);
}

bool TriggerParam::getVec3fArraySize(s32* size, s32 index) const {
    return getFlagArraySize(mVector3fArrayFlags, index, size);
}

bool TriggerParam::getVec4fArraySize(s32* size, s32 index) const {
    return getFlagArraySize(mVector4fArrayFlags, index, size);
}

bool TriggerParam::getBoolArraySizeByHash(s32* size, u32 name) const {
    return getBoolArraySize(size, getBoolArrayIdx(name));
}

bool TriggerParam::getS32ArraySizeByHash(s32* size, u32 name) const {
    return getS32ArraySize(size, getS32ArrayIdx(name));
}

bool TriggerParam::getF32ArraySizeByHash(s32* size, u32 name) const {
    return getF32ArraySize(size, getF32ArrayIdx(name));
}

bool TriggerParam::getStrArraySizeByHash(s32* size, u32 name) const {
    return getStrArraySize(size, getStrArrayIdx(name));
}

bool TriggerParam::getStr64ArraySizeByHash(s32* size, u32 name) const {
    return getStr64ArraySize(size, getStr64ArrayIdx(name));
}

bool TriggerParam::getStr256ArraySizeByHash(s32* size, u32 name) const {
    return getStr256ArraySize(size, getStr256ArrayIdx(name));
}

bool TriggerParam::getVec2fArraySizeByHash(s32* size, u32 name) const {
    return getVec2fArraySize(size, getVec2fArrayIdx(name));
}

bool TriggerParam::getVec3fArraySizeByHash(s32* size, u32 name) const {
    return getVec3fArraySize(size, getVec3fArrayIdx(name));
}

bool TriggerParam::getVec4fArraySizeByHash(s32* size, u32 name) const {
    return getVec4fArraySize(size, getVec4fArrayIdx(name));
}

bool TriggerParam::getS32ArraySize(s32* size, const sead::SafeString& name) const {
    return getS32ArraySize(size, getS32ArrayIdx(name));
}

bool TriggerParam::getStr64ArraySize(s32* size, const sead::SafeString& name) const {
    return getStr64ArraySize(size, getStr64ArrayIdx(name));
}

bool TriggerParam::getVec3fArraySize(s32* size, const sead::SafeString& name) const {
    return getVec3fArraySize(size, getVec3fArrayIdx(name));
}

bool TriggerParam::getMinValueForS32(s32* min, const sead::SafeString& name) const {
    const auto* flag = getFlag<s32>(mS32Flags, name);
    if (!flag)
        return false;
    *min = flag->getConfig().min_value;
    return true;
}

bool TriggerParam::getMaxValueForS32(s32* max, const sead::SafeString& name) const {
    const auto* flag = getFlag<s32>(mS32Flags, name);
    if (!flag)
        return false;
    *max = flag->getConfig().max_value;
    return true;
}

s32 TriggerParam::getBoolIdx(u32 name) const {
    return getFlagIndex(mBoolFlags, name);
}

s32 TriggerParam::getS32Idx(u32 name) const {
    return getFlagIndex(mS32Flags, name);
}

s32 TriggerParam::getF32Idx(u32 name) const {
    return getFlagIndex(mF32Flags, name);
}

s32 TriggerParam::getStrIdx(u32 name) const {
    return getFlagIndex(mStringFlags, name);
}

s32 TriggerParam::getStr64Idx(u32 name) const {
    return getFlagIndex(mString64Flags, name);
}

s32 TriggerParam::getStr256Idx(u32 name) const {
    return getFlagIndex(mString256Flags, name);
}

s32 TriggerParam::getVec2fIdx(u32 name) const {
    return getFlagIndex(mVector2fFlags, name);
}

s32 TriggerParam::getVec3fIdx(u32 name) const {
    return getFlagIndex(mVector3fFlags, name);
}

s32 TriggerParam::getVec4fIdx(u32 name) const {
    return getFlagIndex(mVector4fFlags, name);
}

s32 TriggerParam::getBoolArrayIdx(u32 name) const {
    return getFlagIndex(mBoolArrayFlags, name);
}

s32 TriggerParam::getS32ArrayIdx(u32 name) const {
    return getFlagIndex(mS32ArrayFlags, name);
}

s32 TriggerParam::getF32ArrayIdx(u32 name) const {
    return getFlagIndex(mF32ArrayFlags, name);
}

s32 TriggerParam::getStrArrayIdx(u32 name) const {
    return getFlagIndex(mStringArrayFlags, name);
}

s32 TriggerParam::getStr64ArrayIdx(u32 name) const {
    return getFlagIndex(mString64ArrayFlags, name);
}

s32 TriggerParam::getStr256ArrayIdx(u32 name) const {
    return getFlagIndex(mString256ArrayFlags, name);
}

s32 TriggerParam::getVec2fArrayIdx(u32 name) const {
    return getFlagIndex(mVector2fArrayFlags, name);
}

s32 TriggerParam::getVec3fArrayIdx(u32 name) const {
    return getFlagIndex(mVector3fArrayFlags, name);
}

s32 TriggerParam::getVec4fArrayIdx(u32 name) const {
    return getFlagIndex(mVector4fArrayFlags, name);
}

}  // namespace ksys::gdt
