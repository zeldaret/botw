#include "KingSystem/GameData/gdtTriggerParam.h"
#include <algorithm>
#include <devenv/seadStackTrace.h>
#include <mc/seadCoreInfo.h>
#include <time/seadTickTime.h>
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/GameData/gdtFlagProxy.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Resource/resResourceGameData.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Debug.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::gdt {

TriggerParam::TriggerParam() {
    for (auto& buffer : mFlagChangeRecords)
        buffer.constructDefault();
    for (auto& cs : mCriticalSections)
        cs.constructDefault();
    mBitFlags.constructDefault();
    mFlagChangeRecordIndices.fill(0);
    mNumBoolFlagsPerCategory0.fill(0);
    mNumBoolFlagsPerCategory.fill(0);
}

namespace {
struct TriggerParamConfig {
    bool shouldLog(const sead::SafeString& flag_name, u8 event_type) const {
        if (enabled_events.isOffBit(event_type))
            return false;

        return flag_to_log.isEmpty() || flag_name.include(flag_to_log);
    }

    bool shouldPrintStackTrace(const sead::SafeString& flag_name) const {
        return !flag_to_log.isEmpty() && flag_name.include(flag_to_log) &&
               enabled_events.isOnBit(5);
    }

    sead::SafeString& getCurrentRupeeFlagName() { return current_rupee_flag_name; }

    sead::BitFlag8 enabled_events;
    s32 foo = 90;
    s32 index = 32;
    sead::FixedSafeString<128> flag_to_log{""};
    s32 num_current_rupee_flag_name_changes = 0;
    sead::SafeString current_rupee_flag_name;
};
KSYS_CHECK_SIZE_NX150(TriggerParamConfig, 0xc0);

util::InitTimeInfoEx sInitTimeInfo;
TriggerParamConfig sConfig;

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

inline FlagBase* getFlagByIndexBase(const sead::PtrArray<FlagBase>& flags, s32 index) {
    if (index < 0 || index >= flags.size())
        return nullptr;
    return flags[index];
}

template <typename T>
inline Flag<T>* getFlagByIndex(const sead::PtrArray<FlagBase>& flags, s32 index) {
    return static_cast<Flag<T>*>(getFlagByIndexBase(flags, index));
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

template <typename T>
inline Flag<T>* getFlagAndIndex(s32* idx, const sead::PtrArray<FlagBase>& flags, u32 name_hash) {
    *idx = getFlagIndex(flags, name_hash);
    return getFlagByIndex<T>(flags, *idx);
}

template <typename T, typename FlagValueType = T>
inline bool getFlagValue(const sead::PtrArray<FlagBase>& array, T* out_value, s32 index,
                         bool check_permissions) {
    static_assert(isValidFlagValueType<FlagValueType>());

    const auto* flag = getFlagByIndex<FlagValueType>(array, index);
    if (!flag)
        return false;

    if (check_permissions && !flag->isProgramReadable())
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

    if (check_permissions && !flag->isProgramReadable())
        return false;

    if constexpr (std::is_same<T, const char*>())
        *out_value = flag->getValueRef().cstr();
    else
        *out_value = flag->getValue();

    return true;
}

/// Modifies the value of a flag.
/// @param success A non-null pointer to a boolean that is set to true if an attempt was made to
///                change the value.
/// @return whether the flag contains the specified value at the end of this function.
template <typename T>
bool doSetFlagValue(bool* success, const T& value, const sead::PtrArray<FlagBase>& flags, s32 idx,
                    bool check_permissions, bool bypass_one_trigger_check) {
    *success = false;

    auto* flag = getFlagByIndex<T>(flags, idx);
    if (!flag)
        return false;

    if (check_permissions && !flags[idx]->isProgramWritable())
        return false;

    if constexpr (IsAnyOfType<T, s32, f32>()) {
        if (!flags[idx]->isOneTrigger() || bypass_one_trigger_check || flag->isInitialValue())
            *success = flag->setValue(value);
        else if (!flag->hasValue(value))
            return false;
        return true;
    } else {
        bool can_set_value = false;
        if (!flags[idx]->isOneTrigger() || bypass_one_trigger_check || flag->isInitialValue()) {
            can_set_value = true;
            *success = flag->setValue(value);
        } else if (flag->hasValue(value)) {
            return true;
        }
        return can_set_value;
    }
}

void sendFlagChangePlayReport(const sead::SafeString& name, const FlagBase* flag) {
    if (!PlayReportMgr::instance())
        return;

    for (s32 i = 0; i < sConfig.num_current_rupee_flag_name_changes; ++i) {
        if (name == sConfig.current_rupee_flag_name) {
            sead::FixedSafeString<64> value_str;
            switch (s32(flag->getType())) {
            case FlagType::Bool:
            case FlagType::BoolArray:
                if (static_cast<const FlagBool*>(flag)->getValue())
                    value_str.format("true");
                else
                    value_str.format("false");
                break;
            case FlagType::S32:
            case FlagType::S32Array:
                value_str.format("%d", static_cast<const FlagS32*>(flag)->getValue());
                break;
            case FlagType::F32:
            case FlagType::F32Array:
                value_str.format("%f", static_cast<const FlagF32*>(flag)->getValue());
                break;
            case FlagType::String:
            case FlagType::StringArray:
                value_str.format("%s", static_cast<const FlagString*>(flag)->getValueRef().cstr());
                break;
            case FlagType::String64:
            case FlagType::String64Array:
                value_str.format("%s",
                                 static_cast<const FlagString64*>(flag)->getValueRef().cstr());
                break;
            case FlagType::String256:
            case FlagType::String256Array:
                value_str.format("%s",
                                 static_cast<const FlagString256*>(flag)->getValueRef().cstr());
                break;
            case FlagType::Vector2f:
            case FlagType::Vector2fArray: {
                const auto& vector = static_cast<const FlagVector2f*>(flag)->getValueRef();
                value_str.format("%f %f", vector.x, vector.y);
                break;
            }
            case FlagType::Vector3f:
            case FlagType::Vector3fArray: {
                const auto& vector = static_cast<const FlagVector3f*>(flag)->getValueRef();
                value_str.format("%f %f %f", vector.x, vector.y, vector.z);
                break;
            }
            case FlagType::Vector4f:
            case FlagType::Vector4fArray: {
                const auto& vector = static_cast<const FlagVector4f*>(flag)->getValueRef();
                value_str.format("%f %f %f %f", vector.x, vector.y, vector.z, vector.w);
                break;
            }
            default:
                break;
            }
            PlayReportMgr::instance()->reportDebug(name, value_str);
            break;
        }
    }
}

template <typename T>
void reportFlagChange(const FlagBase* flag, s32 sub_idx = -1) {
    auto* flag_ = static_cast<const Flag<T>*>(flag);

    const sead::SafeString& name = flag->getName();
    const FlagType type = flag->getType();

    if constexpr (std::is_same<T, bool>()) {
        if ((s32(type) == FlagType::Bool || s32(type) == FlagType::BoolArray) &&
            PlayReportMgr::instance()) {
            if (flag_->getValue())
                PlayReportMgr::instance()->reportDebug("FlagOn", name);
            else
                PlayReportMgr::instance()->reportDebug("FlagOff", name);
        }
    } else {
        sendFlagChangePlayReport(name, flag);
    }

    if (sConfig.shouldPrintStackTrace(name)) {
        sead::StackTrace<50> stack_trace;
        stack_trace.trace(nullptr);
    }

    if (!shouldLogFlagChange(name, type))
        return;

    if constexpr (std::is_same<T, bool>()) {
        sead::FixedSafeString<128> message;
        const char* name_cstr = flag->getName().cstr();
        const auto type_ = flag->getType();
        if (sub_idx < 0 || type_ != FlagType::BoolArray)
            message.format("%s", name_cstr);
        else
            message.format("%s [%3d]", name_cstr, sub_idx);

        switch (s32(flag->getType())) {
        case FlagType::Bool:
        case FlagType::BoolArray:
            if (flag_->getValue())
                message.append(" : true");
            else
                message.append(" : false");
            break;
        default:
            break;
        }
        util::PrintDebug(message);
    } else {
        const char* name_cstr = flag->getName().cstr();
        sead::FixedSafeString<128> message;
        const s32 type_ = flag->getType();
        if (sub_idx >= 0 && type_ >= FlagType::BoolArray)
            message.format("%s [%3d] :", name_cstr, sub_idx);
        else
            message.format("%s :", name_cstr);

        sead::FixedSafeString<64> value_str;
        switch (s32(flag->getType())) {
        case FlagType::Bool:
        case FlagType::BoolArray:
            if (static_cast<const FlagBool*>(flag)->getValue())
                value_str.format("true");
            else
                value_str.format("false");
            break;
        case FlagType::S32:
        case FlagType::S32Array:
            value_str.format("%d", static_cast<const FlagS32*>(flag)->getValue());
            break;
        case FlagType::F32:
        case FlagType::F32Array:
            value_str.format("%f", static_cast<const FlagF32*>(flag)->getValue());
            break;
        case FlagType::String:
        case FlagType::StringArray:
            value_str.format("%s", static_cast<const FlagString*>(flag)->getValueRef().cstr());
            break;
        case FlagType::String64:
        case FlagType::String64Array:
            value_str.format("%s", static_cast<const FlagString64*>(flag)->getValueRef().cstr());
            break;
        case FlagType::String256:
        case FlagType::String256Array:
            value_str.format("%s", static_cast<const FlagString256*>(flag)->getValueRef().cstr());
            break;
        case FlagType::Vector2f:
        case FlagType::Vector2fArray: {
            const auto& vector = static_cast<const FlagVector2f*>(flag)->getValueRef();
            value_str.format("%f %f", vector.x, vector.y);
            break;
        }
        case FlagType::Vector3f:
        case FlagType::Vector3fArray: {
            const auto& vector = static_cast<const FlagVector3f*>(flag)->getValueRef();
            value_str.format("%f %f %f", vector.x, vector.y, vector.z);
            break;
        }
        case FlagType::Vector4f:
        case FlagType::Vector4fArray: {
            const auto& vector = static_cast<const FlagVector4f*>(flag)->getValueRef();
            value_str.format("%f %f %f %f", vector.x, vector.y, vector.z, vector.w);
            break;
        }
        default:
            break;
        }
        message.append(value_str);
        util::PrintDebug(message);
    }

    static_cast<void>(getFlagColor(type));
    sConfig.index = sConfig.index >= 32 ? 0 : sConfig.index + 1;
}

bool getFlagArraySize(const sead::PtrArray<sead::PtrArray<FlagBase>>& arrays, s32 index, s32* out) {
    if (index < 0 || index >= arrays.size())
        return false;
    *out = arrays[index]->size();
    return true;
}

bool resetFlag(bool* was_reset, const sead::PtrArray<FlagBase>& flags, s32 idx,
               bool check_permissions) {
    *was_reset = false;

    auto* flag = getFlagByIndexBase(flags, idx);
    if (!flag)
        return false;

    if (check_permissions && !flag->isProgramWritable())
        return false;

    if (flag->isInitialValue())
        return true;

    flag->resetToInitialValue();
    *was_reset = true;
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

template <typename T>
void addFlagCopyRecord(sead::ObjArray<TriggerParam::FlagCopyRecord>& records, Flag<T>* flag,
                       s32 sub_index, bool find_existing_record) {
    if (records.isFull())
        return;

    TriggerParam::FlagCopyRecord* record;

    s32 record_idx = -1;
    if (find_existing_record) {
        const u32 hash = flag->getHash();
        for (s32 i = 0; i < records.size(); ++i) {
            if (records[i]->name_hash == hash && records[i]->sub_index == s16(sub_index)) {
                record_idx = i;
                break;
            }
        }
    }

    if (record_idx != -1) {
        record = records[record_idx];
    } else {
        record = records.emplaceBack();
        record->name_hash = flag->getHash();
        record->sub_index = sub_index;
    }
    record->bf.makeAllZero();
}

constexpr bool IsString256ArrayType(FlagType::ValueType type) {
    return type == FlagType::String256Array;
}
}  // namespace

/**
 * @param dest  Destination flag array
 * @param src   Source flag array
 * @param records  Copy records (only used if add_records is true)
 * @param counts   Boolean flag counts per category (only used if T = bool)
 * @param record_copies  Whether copies should be recorded
 * @param ignore_temp_flags  Whether temporary flags (i.e. flags that aren't saved)
 *                           should be ignored
 * @param find_existing_record  See addFlagCopyRecord.
 * @param is_array  Whether the flag arrays are associated with an array-type flag (e.g. bool array)
 */
template <typename T>
void copyFlags(sead::PtrArray<FlagBase>& dest, const sead::PtrArray<FlagBase>& src,
               sead::ObjArray<TriggerParam::FlagCopyRecord>& records,
               sead::SafeArray<s32, 15>& counts, bool record_copies, bool ignore_temp_flags,
               bool find_existing_record, bool is_array) {
    // This function only handles two cases:
    //
    // 1. If both the source and destination have the same number of flags, we assume that
    //    both arrays store the same flags in the exact same order.
    //
    // 2. If the source has fewer flags than the destination, it is assumed that src is a subset of
    //    dest (i.e. every flag that is in src is also in dest) and src forms a subsequence of dest.
    //    Any flag in dest that isn't in src will be reset to its initial value.

    const auto update_records = [&](Flag<T>* flag, const Flag<T>* flag_src, s32 i) {
        flag->setValue(flag_src->getValue());

        s32 category, category_idx;
        if constexpr (std::is_same<T, bool>()) {
            category = flag->getCategory();
            category_idx = category - 1;
        }

        if (record_copies) {
            addFlagCopyRecord<T>(records, flag, is_array ? i : -1, find_existing_record);
            if constexpr (std::is_same<T, bool>()) {
                if (category > 0) {
                    if (flag->getValue())
                        ++counts[category_idx];
                    else if (counts[category_idx] > 0)
                        --counts[category_idx];
                }
            }
        } else {
            if constexpr (std::is_same<T, bool>()) {
                if (category > 0 && flag->getValue())
                    ++counts[category_idx];
            }
        }
    };

    const auto dest_size = dest.size();
    const auto src_size = src.size();

    if (dest_size == src_size) {
        for (s32 i = 0; i < dest_size; ++i) {
            if (!dest[i])
                continue;
            if (ignore_temp_flags && !dest[i]->isSave())
                continue;
            if (record_copies && dest[i]->isSave())
                continue;

            if (!src[i]) {
                if (!dest[i]->isSave())
                    dest[i]->resetToInitialValue();
            } else {
                auto* flag = static_cast<Flag<T>*>(dest[i]);
                auto* flag_src = static_cast<Flag<T>*>(src[i]);
                update_records(flag, flag_src, i);
            }
        }

    } else if (src_size < dest_size) {
        s32 j = 0;
        for (s32 i = 0; i < dest_size; ++i) {
            if (ignore_temp_flags && !dest[i]->isSave())
                continue;
            if (record_copies && dest[i]->isSave())
                continue;

            if (j >= src_size || src[j]->getHash() != dest[i]->getHash()) {
                if (!dest[i]->isSave())
                    dest[i]->resetToInitialValue();
            } else if (src[j]->getHash() == dest[i]->getHash()) {
                auto* flag = static_cast<Flag<T>*>(dest[i]);
                auto* flag_src = static_cast<Flag<T>*>(src[j]);
                update_records(flag, flag_src, i);
                ++j;
            }
        }
    }
}

template <typename T>
void copyFlagArrays(sead::PtrArray<sead::PtrArray<FlagBase>>& dest,
                    const sead::PtrArray<sead::PtrArray<FlagBase>>& src,
                    sead::ObjArray<TriggerParam::FlagCopyRecord>& records,
                    sead::SafeArray<s32, 15>& counts, bool record_copies, bool ignore_temp_flags,
                    bool find_existing_record) {
    const auto dest_size = dest.size();
    const auto src_size = src.size();

    if (src_size == dest_size) {
        for (s32 i = 0; i < dest_size; ++i) {
            if (!src[i]) {
                const auto n = dest[i]->size();
                if (!dest[i]->at(0)->isSave()) {
                    for (s32 j = 0; j < n; ++j)
                        dest[i]->at(j)->resetToInitialValue();
                }
            } else {
                copyFlags<T>(*dest[i], *src[i], records, counts, record_copies, ignore_temp_flags,
                             find_existing_record, true);
            }
        }

    } else {
        s32 j = 0;
        for (s32 i = 0; i < dest_size; ++i) {
            if (j >= src_size) {
                const auto n = dest[i]->size();
                if (!dest[i]->at(0)->isSave()) {
                    for (s32 k = 0; k < n; ++k)
                        dest[i]->at(k)->resetToInitialValue();
                }
            } else if (src[j]->at(0)->getHash() != dest[i]->at(0)->getHash()) {
                const auto n = dest[i]->size();
                if (!dest[i]->at(0)->isSave()) {
                    for (s32 k = 0; k < n; ++k)
                        dest[i]->at(k)->resetToInitialValue();
                }
            } else {
                copyFlags<T>(*dest[i], *src[j], records, counts, record_copies, ignore_temp_flags,
                             find_existing_record, true);
                ++j;
            }
        }
    }
}

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
    allocCopyRecordArrays(heap);
    updateBoolFlagCounts();
    mHeap = heap;
}

void TriggerParam::allocCopyRecordArrays(sead::Heap* heap) {
#define ALLOC_ARRAY_(FLAGS, FLAG_ARRAYS, DEST)                                                     \
    {                                                                                              \
        s32 size = FLAGS.size();                                                                   \
        for (s32 i = 0; i < FLAG_ARRAYS.size(); ++i)                                               \
            size += FLAG_ARRAYS[i]->size();                                                        \
                                                                                                   \
        DEST.allocBuffer(size, heap);                                                              \
    }

    ALLOC_ARRAY_(mBoolFlags, mBoolArrayFlags, mCopiedBoolFlags);
    ALLOC_ARRAY_(mS32Flags, mS32ArrayFlags, mCopiedS32Flags);
    ALLOC_ARRAY_(mF32Flags, mF32ArrayFlags, mCopiedF32Flags);
    ALLOC_ARRAY_(mStringFlags, mStringArrayFlags, mCopiedStringFlags);
    ALLOC_ARRAY_(mString64Flags, mString64ArrayFlags, mCopiedString64Flags);
    ALLOC_ARRAY_(mString256Flags, mString256ArrayFlags, mCopiedString256Flags);
    ALLOC_ARRAY_(mVector2fFlags, mVector2fArrayFlags, mCopiedVector2fFlags);
    ALLOC_ARRAY_(mVector3fFlags, mVector3fArrayFlags, mCopiedVector3fFlags);
    ALLOC_ARRAY_(mVector4fFlags, mVector4fArrayFlags, mCopiedVector4fFlags);

#undef ALLOC_ARRAY_
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
            if constexpr (IsString256ArrayType(TYPE))                                              \
                mResetEntries[reset_entry_idx].index = s16(i);                                     \
            else                                                                                   \
                mResetEntries[reset_entry_idx].index = i;                                          \
                                                                                                   \
            mResetEntries[reset_entry_idx].reset_type = (*ARRAYS[i])[0]->getResetType();           \
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
        for (auto& array : mFlagChangeRecords)
            array.ref().allocBufferAssert(num_flags, heap);
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

bool TriggerParam::getBool(bool* value, const sead::SafeString& name, bool check_permissions,
                           bool x) const {
    return getBool(value, getBoolIdx(name), check_permissions);
}

bool TriggerParam::getBool2(bool* value, const sead::SafeString& name, bool check_permissions,
                            bool x) const {
    return getBool(value, getBoolIdx(name), check_permissions);
}

bool TriggerParam::getS32(s32* value, const sead::SafeString& name, bool check_permissions,
                          bool x) const {
    return getS32(value, getS32Idx(name), check_permissions);
}

bool TriggerParam::getF32(f32* value, const sead::SafeString& name, bool check_permissions,
                          bool x) const {
    return getF32(value, getF32Idx(name), check_permissions);
}

bool TriggerParam::getStr(const char** value, const sead::SafeString& name, bool check_permissions,
                          bool x) const {
    return getStr(value, getStrIdx(name), check_permissions);
}

bool TriggerParam::getStr64(const char** value, const sead::SafeString& name,
                            bool check_permissions, bool x) const {
    return getStr64(value, getStr64Idx(name), check_permissions);
}

bool TriggerParam::getStr256(const char** value, const sead::SafeString& name,
                             bool check_permissions, bool x) const {
    return getStr256(value, getStr256Idx(name), check_permissions);
}

bool TriggerParam::getVec2f(sead::Vector2f* value, const sead::SafeString& name,
                            bool check_permissions, bool x) const {
    return getVec2f(value, getVec2fIdx(name), check_permissions);
}

bool TriggerParam::getVec3f(sead::Vector3f* value, const sead::SafeString& name,
                            bool check_permissions, bool x) const {
    return getVec3f(value, getVec3fIdx(name), check_permissions);
}

bool TriggerParam::getVec4f(sead::Vector4f* value, const sead::SafeString& name,
                            bool check_permissions, bool x) const {
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
                           bool check_permissions, bool x) const {
    return getBool(value, getBoolArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getS32(s32* value, const sead::SafeString& name, s32 index,
                          bool check_permissions, bool x) const {
    return getS32(value, getS32ArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getF32(f32* value, const sead::SafeString& name, s32 index,
                          bool check_permissions, bool x) const {
    return getF32(value, getF32ArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getStr(const char** value, const sead::SafeString& name, s32 index,
                          bool check_permissions, bool x) const {
    return getStr(value, getStrArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getStr64(const char** value, const sead::SafeString& name, s32 index,
                            bool check_permissions, bool x) const {
    return getStr64(value, getStr64ArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getStr256(const char** value, const sead::SafeString& name, s32 index,
                             bool check_permissions, bool x) const {
    return getStr256(value, getStr256ArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getVec2f(sead::Vector2f* value, const sead::SafeString& name, s32 index,
                            bool check_permissions, bool x) const {
    return getVec2f(value, getVec2fArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getVec3f(sead::Vector3f* value, const sead::SafeString& name, s32 index,
                            bool check_permissions, bool x) const {
    return getVec3f(value, getVec3fArrayIdx(name), index, check_permissions);
}

bool TriggerParam::getVec4f(sead::Vector4f* value, const sead::SafeString& name, s32 index,
                            bool check_permissions, bool x) const {
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

#define SET_FLAG_VALUE_IMPL_(FUNCTION_NAME, ARG_VALUE_TYPE, FLAGS, T, VALUE)                       \
    bool FUNCTION_NAME(ARG_VALUE_TYPE value, s32 idx, bool check_permissions,                      \
                       bool bypass_one_trigger_check) {                                            \
        bool success = false;                                                                      \
        const bool ret = doSetFlagValue<T>(&success, VALUE, FLAGS, idx, check_permissions,         \
                                           bypass_one_trigger_check);                              \
        if (!success)                                                                              \
            return ret;                                                                            \
                                                                                                   \
        recordFlagChange(FLAGS[idx], idx);                                                         \
        reportFlagChange<T>(FLAGS[idx]);                                                           \
                                                                                                   \
        if constexpr (std::is_same<T, bool>()) {                                                   \
            if (FLAGS[idx]->getProperties().isEventAssociated())                                   \
                mBitFlags.ref().set(BitFlag::EventAssociatedFlagModified);                         \
        }                                                                                          \
                                                                                                   \
        return ret;                                                                                \
    }

#define SET_FLAG_VALUE_BY_KEY_IMPL_(FUNCTION_NAME, GET_INDEX_FN, ARG_VALUE_TYPE)                   \
    bool FUNCTION_NAME(ARG_VALUE_TYPE value, const sead::SafeString& name, bool check_permissions, \
                       bool, bool bypass_one_trigger_check) {                                      \
        return FUNCTION_NAME(value, GET_INDEX_FN(name), check_permissions,                         \
                             bypass_one_trigger_check);                                            \
    }

#define SET_ARRAY_FLAG_VALUE_IMPL_(FUNCTION_NAME, ARG_VALUE_TYPE, FLAGS, T, VALUE)                 \
    bool FUNCTION_NAME(ARG_VALUE_TYPE value, s32 idx, s32 sub_idx, bool check_permissions,         \
                       bool bypass_one_trigger_check) {                                            \
        bool success = false;                                                                      \
                                                                                                   \
        if (idx < 0 || idx >= FLAGS.size())                                                        \
            return false;                                                                          \
                                                                                                   \
        const auto* array = FLAGS[idx];                                                            \
        if (!array)                                                                                \
            return false;                                                                          \
                                                                                                   \
        const bool ret = doSetFlagValue<T>(&success, VALUE, *array, sub_idx, check_permissions,    \
                                           bypass_one_trigger_check);                              \
        if (!success)                                                                              \
            return ret;                                                                            \
                                                                                                   \
        const auto* flag = (*FLAGS[idx])[sub_idx];                                                 \
        recordFlagChange(flag, idx, sub_idx);                                                      \
        reportFlagChange<T>(flag, sub_idx);                                                        \
                                                                                                   \
        return ret;                                                                                \
    }

#define SET_STRING_ARRAY_FLAG_VALUE_IMPL_(FUNCTION_NAME, FLAGS, T)                                 \
    bool FUNCTION_NAME(const char* value, s32 idx, s32 sub_idx, bool check_permissions,            \
                       bool bypass_one_trigger_check) {                                            \
        bool success = false;                                                                      \
        T value_{value};                                                                           \
        success = false;                                                                           \
                                                                                                   \
        if (idx < 0 || idx >= FLAGS.size())                                                        \
            return false;                                                                          \
                                                                                                   \
        const auto* array = FLAGS[idx];                                                            \
        if (!array)                                                                                \
            return false;                                                                          \
                                                                                                   \
        const bool ret = doSetFlagValue<T>(&success, value_, *array, sub_idx, check_permissions,   \
                                           bypass_one_trigger_check);                              \
        if (!success)                                                                              \
            return ret;                                                                            \
                                                                                                   \
        const auto* flag = (*FLAGS[idx])[sub_idx];                                                 \
        recordFlagChange(flag, idx, sub_idx);                                                      \
        reportFlagChange<T>(flag, sub_idx);                                                        \
                                                                                                   \
        return ret;                                                                                \
    }

#define SET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(FUNCTION_NAME, GET_INDEX_FN, ARG_VALUE_TYPE)             \
    bool FUNCTION_NAME(ARG_VALUE_TYPE value, const sead::SafeString& name, s32 sub_idx,            \
                       bool check_permissions, bool, bool bypass_one_trigger_check) {              \
        return FUNCTION_NAME(value, GET_INDEX_FN(name), sub_idx, check_permissions,                \
                             bypass_one_trigger_check);                                            \
    }

SET_FLAG_VALUE_IMPL_(TriggerParam::setBool, bool, mBoolFlags, bool, value)

void TriggerParam::recordFlagChange(const FlagBase* flag, s32 idx, s32 sub_idx) {
    const auto core = sead::CoreInfo::getCurrentCoreId();
    const u32 platform_core_id = sead::CoreInfo::getPlatformCoreId(core);

    auto& buffer = mFlagChangeRecords[platform_core_id].ref();
    if (buffer.size() < 1)
        return;

    auto lock = sead::makeScopedLock(mCriticalSections[platform_core_id].ref());

    buffer[mFlagChangeRecordIndices[platform_core_id]].type.mValue = u8(flag->getType());
    buffer[mFlagChangeRecordIndices[platform_core_id]].index = idx;
    buffer[mFlagChangeRecordIndices[platform_core_id]].sub_index = sub_idx;
    ++mFlagChangeRecordIndices[platform_core_id];

    if (flag->getType() == FlagType::Bool)
        mBitFlags.ref().set(BitFlag::_8);
}

SET_FLAG_VALUE_IMPL_(TriggerParam::setS32, s32, mS32Flags, s32, value)
SET_FLAG_VALUE_IMPL_(TriggerParam::setF32, f32, mF32Flags, f32, value)
SET_FLAG_VALUE_IMPL_(TriggerParam::setStr, const char*, mStringFlags, sead::FixedSafeString<32>,
                     sead::FixedSafeString<32>(value))
SET_FLAG_VALUE_IMPL_(TriggerParam::setStr64, const char*, mString64Flags, sead::FixedSafeString<64>,
                     sead::FixedSafeString<64>(value))
SET_FLAG_VALUE_IMPL_(TriggerParam::setStr256, const char*, mString256Flags,
                     sead::FixedSafeString<256>, sead::FixedSafeString<256>(value))
SET_FLAG_VALUE_IMPL_(TriggerParam::setVec2f, const sead::Vector2f&, mVector2fFlags, sead::Vector2f,
                     value)
SET_FLAG_VALUE_IMPL_(TriggerParam::setVec3f, const sead::Vector3f&, mVector3fFlags, sead::Vector3f,
                     value)
SET_FLAG_VALUE_IMPL_(TriggerParam::setVec4f, const sead::Vector4f&, mVector4fFlags, sead::Vector4f,
                     value)

SET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setBool, getBoolIdx, bool)
SET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setS32, getS32Idx, s32)
SET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setF32, getF32Idx, f32)
SET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setStr, getStrIdx, const char*)
SET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setStr64, getStr64Idx, const char*)
SET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setStr256, getStr256Idx, const char*)
SET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setVec2f, getVec2fIdx, const sead::Vector2f&)
SET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setVec3f, getVec3fIdx, const sead::Vector3f&)
SET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setVec4f, getVec4fIdx, const sead::Vector4f&)

SET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::setBool, bool, mBoolArrayFlags, bool, value)
SET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::setS32, s32, mS32ArrayFlags, s32, value)
SET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::setF32, f32, mF32ArrayFlags, f32, value)
SET_STRING_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::setStr, mStringArrayFlags,
                                  sead::FixedSafeString<32>)
SET_STRING_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::setStr64, mString64ArrayFlags,
                                  sead::FixedSafeString<64>)
SET_STRING_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::setStr256, mString256ArrayFlags,
                                  sead::FixedSafeString<256>)
SET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::setVec2f, const sead::Vector2f&, mVector2fArrayFlags,
                           sead::Vector2f, value)
SET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::setVec3f, const sead::Vector3f&, mVector3fArrayFlags,
                           sead::Vector3f, value)
SET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::setVec4f, const sead::Vector4f&, mVector4fArrayFlags,
                           sead::Vector4f, value)

SET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setBool, getBoolArrayIdx, bool)
SET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setS32, getS32ArrayIdx, s32)
SET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setF32, getF32ArrayIdx, f32)
SET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setStr, getStrArrayIdx, const char*)
SET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setStr64, getStr64ArrayIdx, const char*)
SET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setStr256, getStr256ArrayIdx, const char*)
SET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setVec2f, getVec2fArrayIdx, const sead::Vector2f&)
SET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setVec3f, getVec3fArrayIdx, const sead::Vector3f&)
SET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::setVec4f, getVec4fArrayIdx, const sead::Vector4f&)

#define RESET_FLAG_VALUE_IMPL_(FUNCTION_NAME, FLAGS, T)                                            \
    bool FUNCTION_NAME(s32 idx, bool check_permissions) {                                          \
        bool was_reset = false;                                                                    \
        const bool ok = resetFlag(&was_reset, FLAGS, idx, check_permissions);                      \
        if (was_reset) {                                                                           \
            recordFlagChange(FLAGS[idx], idx);                                                     \
            reportFlagChange<T>(FLAGS[idx]);                                                       \
        }                                                                                          \
        return ok;                                                                                 \
    }

#define RESET_FLAG_VALUE_BY_KEY_IMPL_(FUNCTION_NAME, FLAGS, GET_IDX_FN)                            \
    bool FUNCTION_NAME(const sead::SafeString& name, bool check_permissions, bool) {               \
        return FUNCTION_NAME(GET_IDX_FN(name), check_permissions);                                 \
    }

#define RESET_ARRAY_FLAG_VALUE_IMPL_(FUNCTION_NAME, ARRAYS, T)                                     \
    bool FUNCTION_NAME(s32 idx, s32 sub_idx, bool check_permissions) {                             \
        if (idx < 0 || idx >= ARRAYS.size())                                                       \
            return false;                                                                          \
                                                                                                   \
        const auto* array = ARRAYS[idx];                                                           \
        if (!array)                                                                                \
            return false;                                                                          \
                                                                                                   \
        auto* flag = getFlagByIndexBase(*array, sub_idx);                                          \
        if (!flag)                                                                                 \
            return false;                                                                          \
                                                                                                   \
        if (check_permissions && !flag->isProgramWritable())                                       \
            return false;                                                                          \
                                                                                                   \
        if (flag->isInitialValue())                                                                \
            return true;                                                                           \
                                                                                                   \
        flag->resetToInitialValue();                                                               \
        const auto* flag_ = [&] { return ARRAYS.at(idx)->at(sub_idx); }();                         \
        recordFlagChange(flag_, idx, sub_idx);                                                     \
        reportFlagChange<T>(flag_, sub_idx);                                                       \
                                                                                                   \
        return true;                                                                               \
    }

#define RESET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(FUNCTION_NAME, FLAGS, GET_IDX_FN)                      \
    bool FUNCTION_NAME(const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool) {  \
        return FUNCTION_NAME(GET_IDX_FN(name), sub_idx, check_permissions);                        \
    }

RESET_FLAG_VALUE_IMPL_(TriggerParam::resetBool, mBoolFlags, bool)
RESET_FLAG_VALUE_IMPL_(TriggerParam::resetS32, mS32Flags, s32)
RESET_FLAG_VALUE_IMPL_(TriggerParam::resetF32, mF32Flags, f32)
RESET_FLAG_VALUE_IMPL_(TriggerParam::resetStr, mStringFlags, sead::FixedSafeString<32>)
RESET_FLAG_VALUE_IMPL_(TriggerParam::resetStr64, mString64Flags, sead::FixedSafeString<64>)
RESET_FLAG_VALUE_IMPL_(TriggerParam::resetStr256, mString256Flags, sead::FixedSafeString<256>)
RESET_FLAG_VALUE_IMPL_(TriggerParam::resetVec2f, mVector2fFlags, sead::Vector2f)
RESET_FLAG_VALUE_IMPL_(TriggerParam::resetVec3f, mVector3fFlags, sead::Vector3f)
RESET_FLAG_VALUE_IMPL_(TriggerParam::resetVec4f, mVector4fFlags, sead::Vector4f)

RESET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetBool, mBoolFlags, getBoolIdx)
RESET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetS32, mS32Flags, getS32Idx)
RESET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetF32, mF32Flags, getF32Idx)
RESET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetStr, mStringFlags, getStrIdx)
RESET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetStr64, mString64Flags, getStr64Idx)
RESET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetStr256, mString256Flags, getStr256Idx)
RESET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetVec2f, mVector2fFlags, getVec2fIdx)
RESET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetVec3f, mVector3fFlags, getVec3fIdx)
RESET_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetVec4f, mVector4fFlags, getVec4fIdx)

RESET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::resetBool, mBoolArrayFlags, bool)
RESET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::resetS32, mS32ArrayFlags, s32)
RESET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::resetF32, mF32ArrayFlags, f32)
RESET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::resetStr, mStringArrayFlags, sead::FixedSafeString<32>)
RESET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::resetStr64, mString64ArrayFlags,
                             sead::FixedSafeString<64>)
RESET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::resetStr256, mString256ArrayFlags,
                             sead::FixedSafeString<256>)
RESET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::resetVec2f, mVector2fArrayFlags, sead::Vector2f)
RESET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::resetVec3f, mVector3fArrayFlags, sead::Vector3f)
RESET_ARRAY_FLAG_VALUE_IMPL_(TriggerParam::resetVec4f, mVector4fArrayFlags, sead::Vector4f)

RESET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetBool, mBoolArrayFlags, getBoolArrayIdx)
RESET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetS32, mS32ArrayFlags, getS32ArrayIdx)
RESET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetF32, mF32ArrayFlags, getF32ArrayIdx)
RESET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetStr, mStringArrayFlags, getStrArrayIdx)
RESET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetStr64, mString64ArrayFlags, getStr64ArrayIdx)
RESET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetStr256, mString256ArrayFlags,
                                    getStr256ArrayIdx)
RESET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetVec2f, mVector2fArrayFlags, getVec2fArrayIdx)
RESET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetVec3f, mVector3fArrayFlags, getVec3fArrayIdx)
RESET_ARRAY_FLAG_VALUE_BY_KEY_IMPL_(TriggerParam::resetVec4f, mVector4fArrayFlags, getVec4fArrayIdx)

void TriggerParam::resetAllFlagsToInitialValues() {
    for (s32 i = 0; i < mBoolFlags.size(); ++i)
        resetBool(i, false);
    for (s32 i = 0; i < mS32Flags.size(); ++i)
        resetS32(i, false);
    for (s32 i = 0; i < mF32Flags.size(); ++i)
        resetF32(i, false);
    for (s32 i = 0; i < mStringFlags.size(); ++i)
        resetStr(i, false);
    for (s32 i = 0; i < mString64Flags.size(); ++i)
        resetStr64(i, false);
    for (s32 i = 0; i < mString256Flags.size(); ++i)
        resetStr256(i, false);
    for (s32 i = 0; i < mVector2fFlags.size(); ++i)
        resetVec2f(i, false);
    for (s32 i = 0; i < mVector3fFlags.size(); ++i)
        resetVec3f(i, false);
    for (s32 i = 0; i < mVector4fFlags.size(); ++i)
        resetVec4f(i, false);

    for (s32 i = 0; i < mBoolArrayFlags.size(); ++i) {
        for (s32 j = 0; j < mBoolArrayFlags[i]->size(); ++j)
            resetBool(i, j, false);
    }
    for (s32 i = 0; i < mS32ArrayFlags.size(); ++i) {
        for (s32 j = 0; j < mS32ArrayFlags[i]->size(); ++j)
            resetS32(i, j, false);
    }
    for (s32 i = 0; i < mF32ArrayFlags.size(); ++i) {
        for (s32 j = 0; j < mF32ArrayFlags[i]->size(); ++j)
            resetF32(i, j, false);
    }
    for (s32 i = 0; i < mStringArrayFlags.size(); ++i) {
        for (s32 j = 0; j < mStringArrayFlags[i]->size(); ++j)
            resetStr(i, j, false);
    }
    for (s32 i = 0; i < mString64ArrayFlags.size(); ++i) {
        for (s32 j = 0; j < mString64ArrayFlags[i]->size(); ++j)
            resetStr64(i, j, false);
    }
    for (s32 i = 0; i < mString256ArrayFlags.size(); ++i) {
        for (s32 j = 0; j < mString256ArrayFlags[i]->size(); ++j)
            resetStr256(i, j, false);
    }
    for (s32 i = 0; i < mVector2fArrayFlags.size(); ++i) {
        for (s32 j = 0; j < mVector2fArrayFlags[i]->size(); ++j)
            resetVec2f(i, j, false);
    }
    for (s32 i = 0; i < mVector3fArrayFlags.size(); ++i) {
        for (s32 j = 0; j < mVector3fArrayFlags[i]->size(); ++j)
            resetVec3f(i, j, false);
    }
    for (s32 i = 0; i < mVector4fArrayFlags.size(); ++i) {
        for (s32 j = 0; j < mVector4fArrayFlags[i]->size(); ++j)
            resetVec4f(i, j, false);
    }
}

int TriggerParam::resetFlagsAccordingToPolicy(sead::BitFlag32 policy, int skip) {
    [[maybe_unused]] sead::TickTime now;
    [[maybe_unused]] sead::TickTime time_end;

    auto it = mResetEntries.begin(skip);
    const auto end = mResetEntries.end();

    int arrows[6];
    int col1 = 0;
    int row1 = 0;
    int col2 = 0;
    int row2 = 0;
    const bool main_field = StageInfo::sIsMainField;

    if (policy.isOnBit(int(ResetType::ResetAtMidnight))) {
        act::getRevivalGridPosition(act::ActorSystem::instance()->getPlayerPos(), &col1, &row1,
                                    &col2, &row2);
        for (int i = 0; i < 6; ++i)
            arrows[i] = ui::getPorchNum(act::arrowTypeToString(static_cast<act::ArrowType>(i)));
    }
    sead::Buffer<int> arrow_counts(arrows);

    const auto skip_flag = [&](bool* is_shop_item, FlagBase* flag) {
        return flag && !flag->isInitialValue() &&
               shouldSkipRevivingShopItem(is_shop_item, flag->getHash(), main_field, arrow_counts,
                                          col1, row1, col2, row2);
    };

    for (int processed = 0; it != end; ++it) {
        const auto& entry = *it;
        if (!policy.isOnBit(entry.reset_type.mValue))
            continue;

        ++processed;

        switch (FlagType(entry.type)) {
        case FlagType::Bool: {
            if (entry.reset_type == ResetType::ResetAtMidnight) {
                auto* flag = getBoolFlag(entry.index);
                bool is_shop_item = false;
                if (!flag)
                    goto reset_bool;
                if (skip_flag(&is_shop_item, flag))
                    break;
                if (!is_shop_item)
                    goto reset_bool;

                al::ByamlIter iter;
                if (Manager::instance()->getShopSoldOutInfo(flag->getHash(), &iter)) {
                    al::ByamlIter flags;
                    if (!iter.tryGetIterByKey(&flags, "SoldOutFlags"))
                        goto reset_bool;

                    for (int k = 0, n = flags.getSize(); k < n; ++k) {
                        u32 name_hash;
                        if (!flags.tryGetUIntByIndex(&name_hash, k))
                            continue;

                        int flag_idx;
                        auto* sold_out_flag = getBoolFlagAndIdx(&flag_idx, name_hash);
                        if (sold_out_flag && !sold_out_flag->isInitialValue())
                            resetBool(flag_idx, false);
                    }
                }
            }
        reset_bool:
            resetBool(entry.index, false);
            break;
        }
        case FlagType::S32:
            if (entry.reset_type == ResetType::ResetAtMidnight) {
                auto* flag = getS32Flag(entry.index);
                bool is_shop_item = false;
                if (skip_flag(&is_shop_item, flag))
                    break;
            }
            resetS32(entry.index, false);
            break;
        case FlagType::F32:
            resetF32(entry.index, false);
            break;
        case FlagType::String:
            resetStr(entry.index, false);
            break;
        case FlagType::String64:
            resetStr64(entry.index, false);
            break;
        case FlagType::String256:
            resetStr256(entry.index, false);
            break;
        case FlagType::Vector2f:
            resetVec2f(entry.index, false);
            break;
        case FlagType::Vector3f:
            resetVec3f(entry.index, false);
            break;
        case FlagType::Vector4f:
            resetVec4f(entry.index, false);
            break;
        case FlagType::BoolArray: {
            int size = 0;
            getBoolArraySize(&size, entry.index);
            for (int j = 0; j < size; ++j)
                resetBool(entry.index, j, false);
            break;
        }
        case FlagType::S32Array: {
            int size = 0;
            getS32ArraySize(&size, entry.index);
            for (int j = 0; j < size; ++j)
                resetS32(entry.index, j, false);
            break;
        }
        case FlagType::F32Array: {
            int size = 0;
            getF32ArraySize(&size, entry.index);
            for (int j = 0; j < size; ++j)
                resetF32(entry.index, j, false);
            break;
        }
        case FlagType::StringArray: {
            int size = 0;
            getStrArraySize(&size, entry.index);
            for (int j = 0; j < size; ++j)
                resetStr(entry.index, j, false);
            break;
        }
        case FlagType::String64Array: {
            int size = 0;
            getStr64ArraySize(&size, entry.index);
            for (int j = 0; j < size; ++j)
                resetStr64(entry.index, j, false);
            break;
        }
        case FlagType::String256Array: {
            int size = 0;
            getStr256ArraySize(&size, entry.index);
            for (int j = 0; j < size; ++j)
                resetStr256(entry.index, j, false);
            break;
        }
        case FlagType::Vector2fArray: {
            int size = 0;
            getVec2fArraySize(&size, entry.index);
            for (int j = 0; j < size; ++j)
                resetVec2f(entry.index, j, false);
            break;
        }
        case FlagType::Vector3fArray: {
            int size = 0;
            getVec3fArraySize(&size, entry.index);
            for (int j = 0; j < size; ++j)
                resetVec3f(entry.index, j, false);
            break;
        }
        case FlagType::Vector4fArray: {
            int size = 0;
            getVec4fArraySize(&size, entry.index);
            for (int j = 0; j < size; ++j)
                resetVec4f(entry.index, j, false);
            break;
        }
        case FlagType::Invalid:
            break;
        }

        if (processed > 1024)
            return it.getIndex();
    }
    return 0;
}

bool TriggerParam::shouldSkipRevivingShopItem(bool* is_shop_item, u32 flag_hash, bool is_main_field,
                                              const sead::Buffer<s32>& arrow_counts, s32 col1,
                                              s32 row1, s32 col2, s32 row2) const {
    al::ByamlIter info;
    if (!Manager::getShopInfoIter(flag_hash, &info, Manager::instance()->getShopAreaInfoValues(),
                                  Manager::instance()->getShopAreaInfoHashes())) {
        return false;
    }

    *is_shop_item = true;

    if (is_main_field) {
        // Check that the player is in none of the shop areas.
        // If there is no Area data, the area of the dealer will be used instead.
        int col = 0;
        int row = 0;
        int num = 1;
        al::ByamlIter iter;
        al::ByamlIter areas;
        if (!info.tryGetIterByKey(&areas, "Areas")) {
            const char* dealer = nullptr;
            if (!info.tryGetStringByKey(&dealer, "Dealer"))
                return false;

            sead::Vector3f pos;
            if (!act::ActorSystem::instance()->getAutoPlacementActorPos(dealer, &pos))
                return false;

            col = sead::clamp((int(pos.x) + 5000) / 1000, 0, 9);
            row = sead::clamp((int(pos.z) + 4000) / 1000, 0, 7);
        } else {
            num = areas.getSize();
            if (areas.tryGetIterByIndex(&iter, 0)) {
                iter.tryGetIntByIndex(&col, 0);
                iter.tryGetIntByIndex(&row, 1);
            }
        }

        int i = 1;
        while (true) {
            if (col >= col1 && col <= col2 && row >= row1 && row <= row2)
                return true;
            if (i >= num || !areas.tryGetIterByIndex(&iter, i))
                break;
            iter.tryGetIntByIndex(&col, 0);
            iter.tryGetIntByIndex(&row, 1);
            ++i;
        }
    }

    const char* item = nullptr;
    if (!info.tryGetStringByKey(&item, "Item"))
        return false;

    auto* info_data = act::InfoData::instance();
    if (!info_data)
        return false;

    if (info_data->hasTag(item, act::tags::Arrow)) {
        sead::FixedSafeString<64> group_name;
        act::getSameGroupActorName(&group_name, item);

        const auto arrow_type = act::arrowTypeFromString(group_name);
        if (arrow_type == act::ArrowType::Invalid)
            return false;

        const int revival_count = act::getItemSaleRevivalCount(info_data, item);
        if (revival_count <= 0)
            return false;

        if (arrow_counts[int(arrow_type)] >= revival_count)
            return true;
    }

    return false;
}

bool TriggerParam::getBoolIfCopied(bool* value, const sead::SafeString& name, bool x,
                                   bool y) const {
    if (mCopiedBoolFlags.isEmpty())
        return false;

    const u32 hash = sead::HashCRC32::calcStringHash(name);
    for (s32 i = 0; i < mCopiedBoolFlags.size(); ++i) {
        if (mCopiedBoolFlags[i]->name_hash == hash) {
            if (!mCopiedBoolFlags[i]->checkBitFlags(x, y))
                return false;

            *value = static_cast<FlagBool*>(mBoolFlags[getFlagIndex(mBoolFlags, hash)])->getValue();
            return true;
        }
    }
    return false;
}

bool TriggerParam::getS32IfCopied(s32* value, const sead::SafeString& name, bool x, bool y) const {
    if (mCopiedS32Flags.isEmpty())
        return false;

    const u32 hash = sead::HashCRC32::calcStringHash(name);
    for (s32 i = 0; i < mCopiedS32Flags.size(); ++i) {
        if (mCopiedS32Flags[i]->name_hash == hash) {
            if (!mCopiedS32Flags[i]->checkBitFlags(x, y))
                return false;

            *value = static_cast<FlagS32*>(mS32Flags[getFlagIndex(mS32Flags, hash)])->getValue();
            return true;
        }
    }
    return false;
}

bool TriggerParam::getF32IfCopied(f32* value, const sead::SafeString& name, bool x, bool y) const {
    if (mCopiedF32Flags.isEmpty())
        return false;

    const u32 hash = sead::HashCRC32::calcStringHash(name);
    for (s32 i = 0; i < mCopiedF32Flags.size(); ++i) {
        if (mCopiedF32Flags[i]->name_hash == hash) {
            if (!mCopiedF32Flags[i]->checkBitFlags(x, y))
                return false;

            *value = static_cast<FlagF32*>(mF32Flags[getFlagIndex(mF32Flags, hash)])->getValue();
            return true;
        }
    }
    return false;
}

// FIXME: very incomplete
void TriggerParam::copyChangedFlags(TriggerParam& other, bool set_all_flags, bool record_copies,
                                    bool ignore_temp_flags) {
    if (!set_all_flags) {
        for (s32 i = 0; i < 3; ++i) {
            auto lock = sead::makeScopedLock(other.mCriticalSections[i].ref());

            for (s32 j = 0; j < mFlagChangeRecordIndices[i]; ++i) {
                const FlagChangeRecord& record = mFlagChangeRecords[i].ref()[j];
                const auto idx = record.index;
                const auto sub_idx = record.sub_index;
                switch (record.type) {
                case FlagType::Bool: {
                    auto* flag = static_cast<FlagBool*>(mBoolFlags[idx]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(static_cast<FlagBool*>(other.mBoolFlags[idx])->getValue());
                    const auto category = flag->getCategory();
                    addFlagCopyRecord(mCopiedBoolFlags, flag, -1, find_existing);

                    if (category > 0) {
                        if (flag->getValue())
                            ++mNumBoolFlagsPerCategory[category - 1];
                        else
                            --mNumBoolFlagsPerCategory[category - 1];
                    }
                    break;
                }
                case FlagType::S32: {
                    auto* flag = static_cast<FlagS32*>(mS32Flags[idx]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(static_cast<FlagS32*>(other.mS32Flags[idx])->getValue());
                    addFlagCopyRecord(mCopiedS32Flags, flag, -1, find_existing);
                    break;
                }
                case FlagType::F32: {
                    auto* flag = static_cast<FlagF32*>(mF32Flags[idx]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(static_cast<FlagF32*>(other.mF32Flags[idx])->getValue());
                    addFlagCopyRecord(mCopiedF32Flags, flag, -1, find_existing);
                    break;
                }
                case FlagType::String: {
                    auto* flag = static_cast<FlagString*>(mStringFlags[idx]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(static_cast<FlagString*>(other.mStringFlags[idx])->getValue());
                    addFlagCopyRecord(mCopiedStringFlags, flag, -1, find_existing);
                    break;
                }
                case FlagType::String64: {
                    auto* flag = static_cast<FlagString64*>(mString64Flags[idx]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(
                        static_cast<FlagString64*>(other.mString64Flags[idx])->getValue());
                    addFlagCopyRecord(mCopiedString64Flags, flag, -1, find_existing);
                    break;
                }
                case FlagType::String256: {
                    auto* flag = static_cast<FlagString256*>(mString256Flags[idx]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(
                        static_cast<FlagString256*>(other.mString256Flags[idx])->getValue());
                    addFlagCopyRecord(mCopiedString256Flags, flag, -1, find_existing);
                    break;
                }
                case FlagType::Vector2f: {
                    auto* flag = static_cast<FlagVector2f*>(mVector2fFlags[idx]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(
                        static_cast<FlagVector2f*>(other.mVector2fFlags[idx])->getValue());
                    addFlagCopyRecord(mCopiedVector2fFlags, flag, -1, find_existing);
                    break;
                }
                case FlagType::Vector3f: {
                    auto* flag = static_cast<FlagVector3f*>(mVector3fFlags[idx]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(
                        static_cast<FlagVector3f*>(other.mVector3fFlags[idx])->getValue());
                    addFlagCopyRecord(mCopiedVector3fFlags, flag, -1, find_existing);
                    break;
                }
                case FlagType::Vector4f: {
                    auto* flag = static_cast<FlagVector4f*>(mVector4fFlags[idx]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(
                        static_cast<FlagVector4f*>(other.mVector4fFlags[idx])->getValue());
                    addFlagCopyRecord(mCopiedVector4fFlags, flag, -1, find_existing);
                    break;
                }

                case FlagType::BoolArray: {
                    auto* flag = static_cast<FlagBool*>((*mBoolArrayFlags[idx])[sub_idx]);
                    auto* flag2 = static_cast<FlagBool*>((*other.mBoolArrayFlags[idx])[sub_idx]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(flag2->getValue());
                    const auto category = flag->getCategory();
                    addFlagCopyRecord(mCopiedBoolFlags, flag, sub_idx, find_existing);

                    if (category > 0) {
                        if (flag->getValue())
                            ++mNumBoolFlagsPerCategory[category - 1];
                        else
                            --mNumBoolFlagsPerCategory[category - 1];
                    }
                    break;
                }
                case FlagType::S32Array: {
                    auto* flag = static_cast<FlagS32*>((*mS32ArrayFlags[idx])[record.sub_index]);
                    auto* flag2 =
                        static_cast<FlagS32*>((*other.mS32ArrayFlags[idx])[record.sub_index]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(flag2->getValue());
                    addFlagCopyRecord(mCopiedS32Flags, flag, sub_idx, find_existing);
                    break;
                }
                case FlagType::F32Array: {
                    auto* flag = static_cast<FlagF32*>((*mF32ArrayFlags[idx])[record.sub_index]);
                    auto* flag2 =
                        static_cast<FlagF32*>((*other.mF32ArrayFlags[idx])[record.sub_index]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(flag2->getValue());
                    addFlagCopyRecord(mCopiedF32Flags, flag, sub_idx, find_existing);
                    break;
                }
                case FlagType::StringArray: {
                    auto* flag =
                        static_cast<FlagString*>((*mStringArrayFlags[idx])[record.sub_index]);
                    auto* flag2 =
                        static_cast<FlagString*>((*other.mStringArrayFlags[idx])[record.sub_index]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(flag2->getValue());
                    addFlagCopyRecord(mCopiedStringFlags, flag, sub_idx, find_existing);
                    break;
                }
                case FlagType::String64Array: {
                    auto* flag =
                        static_cast<FlagString64*>((*mString64ArrayFlags[idx])[record.sub_index]);
                    auto* flag2 = static_cast<FlagString64*>(
                        (*other.mString64ArrayFlags[idx])[record.sub_index]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(flag2->getValue());
                    addFlagCopyRecord(mCopiedString64Flags, flag, sub_idx, find_existing);
                    break;
                }
                case FlagType::String256Array: {
                    auto* flag =
                        static_cast<FlagString256*>((*mString256ArrayFlags[idx])[record.sub_index]);
                    auto* flag2 = static_cast<FlagString256*>(
                        (*other.mString256ArrayFlags[idx])[record.sub_index]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(flag2->getValue());
                    addFlagCopyRecord(mCopiedString256Flags, flag, sub_idx, find_existing);
                    break;
                }
                case FlagType::Vector2fArray: {
                    auto* flag =
                        static_cast<FlagVector2f*>((*mVector2fArrayFlags[idx])[record.sub_index]);
                    auto* flag2 = static_cast<FlagVector2f*>(
                        (*other.mVector2fArrayFlags[idx])[record.sub_index]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(flag2->getValue());
                    addFlagCopyRecord(mCopiedVector2fFlags, flag, sub_idx, find_existing);
                    break;
                }
                case FlagType::Vector3fArray: {
                    auto* flag =
                        static_cast<FlagVector3f*>((*mVector3fArrayFlags[idx])[record.sub_index]);
                    auto* flag2 = static_cast<FlagVector3f*>(
                        (*other.mVector3fArrayFlags[idx])[record.sub_index]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(flag2->getValue());
                    addFlagCopyRecord(mCopiedVector3fFlags, flag, sub_idx, find_existing);
                    break;
                }
                case FlagType::Vector4fArray: {
                    auto* flag =
                        static_cast<FlagVector4f*>((*mVector4fArrayFlags[idx])[record.sub_index]);
                    auto* flag2 = static_cast<FlagVector4f*>(
                        (*other.mVector4fArrayFlags[idx])[record.sub_index]);
                    const bool find_existing = shouldFindExistingCopyRecord();
                    flag->setValue(flag2->getValue());
                    addFlagCopyRecord(mCopiedVector4fFlags, flag, sub_idx, find_existing);
                    break;
                }
                case FlagType::Invalid:
                    break;
                }
            }

            mFlagChangeRecordIndices[i] = 0;
            other.mBitFlags.ref().reset(BitFlag::_8);
        }
        return;
    }

    copyFlags<bool>(mBoolFlags, other.mBoolFlags, mCopiedBoolFlags, mNumBoolFlagsPerCategory0,
                    record_copies, ignore_temp_flags, shouldFindExistingCopyRecord(), false);
    copyFlags<s32>(mS32Flags, other.mS32Flags, mCopiedS32Flags, mNumBoolFlagsPerCategory0,
                   record_copies, ignore_temp_flags, shouldFindExistingCopyRecord(), false);
    copyFlags<f32>(mF32Flags, other.mF32Flags, mCopiedF32Flags, mNumBoolFlagsPerCategory0,
                   record_copies, ignore_temp_flags, shouldFindExistingCopyRecord(), false);
    copyFlags<sead::FixedSafeString<32>>(mStringFlags, other.mStringFlags, mCopiedStringFlags,
                                         mNumBoolFlagsPerCategory0, record_copies,
                                         ignore_temp_flags, shouldFindExistingCopyRecord(), false);
    copyFlags<sead::FixedSafeString<64>>(mString64Flags, other.mString64Flags, mCopiedString64Flags,
                                         mNumBoolFlagsPerCategory0, record_copies,
                                         ignore_temp_flags, shouldFindExistingCopyRecord(), false);
    copyFlags<sead::FixedSafeString<256>>(
        mString256Flags, other.mString256Flags, mCopiedString256Flags, mNumBoolFlagsPerCategory0,
        record_copies, ignore_temp_flags, shouldFindExistingCopyRecord(), false);
    copyFlags<sead::Vector2f>(mVector2fFlags, other.mVector2fFlags, mCopiedVector2fFlags,
                              mNumBoolFlagsPerCategory0, record_copies, ignore_temp_flags,
                              shouldFindExistingCopyRecord(), false);
    copyFlags<sead::Vector3f>(mVector3fFlags, other.mVector3fFlags, mCopiedVector3fFlags,
                              mNumBoolFlagsPerCategory0, record_copies, ignore_temp_flags,
                              shouldFindExistingCopyRecord(), false);
    copyFlags<sead::Vector4f>(mVector4fFlags, other.mVector4fFlags, mCopiedVector4fFlags,
                              mNumBoolFlagsPerCategory0, record_copies, ignore_temp_flags,
                              shouldFindExistingCopyRecord(), false);

    copyFlagArrays<bool>(mBoolArrayFlags, other.mBoolArrayFlags, mCopiedBoolFlags,
                         mNumBoolFlagsPerCategory0, record_copies, ignore_temp_flags,
                         shouldFindExistingCopyRecord());
    copyFlagArrays<s32>(mS32ArrayFlags, other.mS32ArrayFlags, mCopiedS32Flags,
                        mNumBoolFlagsPerCategory0, record_copies, ignore_temp_flags,
                        shouldFindExistingCopyRecord());
    copyFlagArrays<f32>(mF32ArrayFlags, other.mF32ArrayFlags, mCopiedF32Flags,
                        mNumBoolFlagsPerCategory0, record_copies, ignore_temp_flags,
                        shouldFindExistingCopyRecord());
    copyFlagArrays<sead::FixedSafeString<32>>(
        mStringArrayFlags, other.mStringArrayFlags, mCopiedStringFlags, mNumBoolFlagsPerCategory0,
        record_copies, ignore_temp_flags, shouldFindExistingCopyRecord());
    copyFlagArrays<sead::FixedSafeString<64>>(mString64ArrayFlags, other.mString64ArrayFlags,
                                              mCopiedString64Flags, mNumBoolFlagsPerCategory0,
                                              record_copies, ignore_temp_flags,
                                              shouldFindExistingCopyRecord());
    copyFlagArrays<sead::FixedSafeString<256>>(mString256ArrayFlags, other.mString256ArrayFlags,
                                               mCopiedString256Flags, mNumBoolFlagsPerCategory0,
                                               record_copies, ignore_temp_flags,
                                               shouldFindExistingCopyRecord());
    copyFlagArrays<sead::Vector2f>(mVector2fArrayFlags, other.mVector2fArrayFlags,
                                   mCopiedVector2fFlags, mNumBoolFlagsPerCategory0, record_copies,
                                   ignore_temp_flags, shouldFindExistingCopyRecord());
    copyFlagArrays<sead::Vector3f>(mVector3fArrayFlags, other.mVector3fArrayFlags,
                                   mCopiedVector3fFlags, mNumBoolFlagsPerCategory0, record_copies,
                                   ignore_temp_flags, shouldFindExistingCopyRecord());
    copyFlagArrays<sead::Vector4f>(mVector4fArrayFlags, other.mVector4fArrayFlags,
                                   mCopiedVector4fFlags, mNumBoolFlagsPerCategory0, record_copies,
                                   ignore_temp_flags, shouldFindExistingCopyRecord());
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

FlagBool* TriggerParam::getBoolFlag(s32 idx) const {
    return static_cast<FlagBool*>(mBoolFlags[idx]);
}

FlagS32* TriggerParam::getS32Flag(s32 idx) const {
    return static_cast<FlagS32*>(mS32Flags[idx]);
}

FlagF32* TriggerParam::getF32Flag(s32 idx) const {
    return static_cast<FlagF32*>(mF32Flags[idx]);
}

FlagString* TriggerParam::getStrFlag(s32 idx) const {
    return static_cast<FlagString*>(mStringFlags[idx]);
}

FlagString64* TriggerParam::getStr64Flag(s32 idx) const {
    return static_cast<FlagString64*>(mString64Flags[idx]);
}

FlagString256* TriggerParam::getStr256Flag(s32 idx) const {
    return static_cast<FlagString256*>(mString256Flags[idx]);
}

FlagVector2f* TriggerParam::getVec2fFlag(s32 idx) const {
    return static_cast<FlagVector2f*>(mVector2fFlags[idx]);
}

FlagVector3f* TriggerParam::getVec3fFlag(s32 idx) const {
    return static_cast<FlagVector3f*>(mVector3fFlags[idx]);
}

FlagVector4f* TriggerParam::getVec4fFlag(s32 idx) const {
    return static_cast<FlagVector4f*>(mVector4fFlags[idx]);
}

FlagBool* TriggerParam::getBoolFlagAndIdx(s32* idx, u32 name_hash) const {
    return getFlagAndIndex<bool>(idx, mBoolFlags, name_hash);
}

FlagS32* TriggerParam::getS32FlagAndIdx(s32* idx, u32 name_hash) const {
    return getFlagAndIndex<s32>(idx, mS32Flags, name_hash);
}

FlagF32* TriggerParam::getF32FlagAndIdx(s32* idx, u32 name_hash) const {
    return getFlagAndIndex<f32>(idx, mF32Flags, name_hash);
}

FlagString* TriggerParam::getStrFlagAndIdx(s32* idx, u32 name_hash) const {
    return getFlagAndIndex<sead::FixedSafeString<32>>(idx, mStringFlags, name_hash);
}

FlagString64* TriggerParam::getStr64FlagAndIdx(s32* idx, u32 name_hash) const {
    return getFlagAndIndex<sead::FixedSafeString<64>>(idx, mString64Flags, name_hash);
}

FlagString256* TriggerParam::getStr256FlagAndIdx(s32* idx, u32 name_hash) const {
    return getFlagAndIndex<sead::FixedSafeString<256>>(idx, mString256Flags, name_hash);
}

FlagVector2f* TriggerParam::getVec2fFlagAndIdx(s32* idx, u32 name_hash) const {
    return getFlagAndIndex<sead::Vector2f>(idx, mVector2fFlags, name_hash);
}

FlagVector3f* TriggerParam::getVec3fFlagAndIdx(s32* idx, u32 name_hash) const {
    return getFlagAndIndex<sead::Vector3f>(idx, mVector3fFlags, name_hash);
}

FlagVector4f* TriggerParam::getVec4fFlagAndIdx(s32* idx, u32 name_hash) const {
    return getFlagAndIndex<sead::Vector4f>(idx, mVector4fFlags, name_hash);
}

FlagS32* TriggerParam::getS32FlagByHash(u32 name_hash) const {
    const s32 idx = getS32Idx(name_hash);
    if (idx < 0 || mS32Flags.size() <= idx)
        return nullptr;
    return getS32Flag(idx);
}

FlagBool* TriggerParam::getBoolFlag(s32 idx, s32 sub_idx) const {
    return static_cast<FlagBool*>(mBoolArrayFlags[idx]->at(sub_idx));
}

FlagS32* TriggerParam::getS32Flag(s32 idx, s32 sub_idx) const {
    return static_cast<FlagS32*>(mS32ArrayFlags[idx]->at(sub_idx));
}

FlagF32* TriggerParam::getF32Flag(s32 idx, s32 sub_idx) const {
    return static_cast<FlagF32*>(mF32ArrayFlags[idx]->at(sub_idx));
}

FlagString* TriggerParam::getStrFlag(s32 idx, s32 sub_idx) const {
    return static_cast<FlagString*>(mStringArrayFlags[idx]->at(sub_idx));
}

FlagString64* TriggerParam::getStr64Flag(s32 idx, s32 sub_idx) const {
    return static_cast<FlagString64*>(mString64ArrayFlags[idx]->at(sub_idx));
}

FlagString256* TriggerParam::getStr256Flag(s32 idx, s32 sub_idx) const {
    return static_cast<FlagString256*>(mString256ArrayFlags[idx]->at(sub_idx));
}

FlagVector2f* TriggerParam::getVec2fFlag(s32 idx, s32 sub_idx) const {
    return static_cast<FlagVector2f*>(mVector2fArrayFlags[idx]->at(sub_idx));
}

FlagVector3f* TriggerParam::getVec3fFlag(s32 idx, s32 sub_idx) const {
    return static_cast<FlagVector3f*>(mVector3fArrayFlags[idx]->at(sub_idx));
}

FlagVector4f* TriggerParam::getVec4fFlag(s32 idx, s32 sub_idx) const {
    return static_cast<FlagVector4f*>(mVector4fArrayFlags[idx]->at(sub_idx));
}

FlagBool* TriggerParam::getBoolFlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const {
    *idx = getBoolArrayIdx(name_hash);
    if (*idx < 0 || mBoolArrayFlags.size() <= *idx || sub_idx < 0)
        return nullptr;
    return getFlagByIndex<bool>(*mBoolArrayFlags[*idx], sub_idx);
}

FlagS32* TriggerParam::getS32FlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const {
    *idx = getS32ArrayIdx(name_hash);
    if (*idx < 0 || mS32ArrayFlags.size() <= *idx || sub_idx < 0)
        return nullptr;
    return getFlagByIndex<s32>(*mS32ArrayFlags[*idx], sub_idx);
}

FlagF32* TriggerParam::getF32FlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const {
    *idx = getF32ArrayIdx(name_hash);
    if (*idx < 0 || mF32ArrayFlags.size() <= *idx || sub_idx < 0)
        return nullptr;
    return getFlagByIndex<f32>(*mF32ArrayFlags[*idx], sub_idx);
}

FlagString* TriggerParam::getStrFlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const {
    *idx = getStrArrayIdx(name_hash);
    if (*idx < 0 || mStringArrayFlags.size() <= *idx || sub_idx < 0)
        return nullptr;
    return getFlagByIndex<sead::FixedSafeString<32>>(*mStringArrayFlags[*idx], sub_idx);
}

FlagString64* TriggerParam::getStr64FlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const {
    *idx = getStr64ArrayIdx(name_hash);
    if (*idx < 0 || mString64ArrayFlags.size() <= *idx || sub_idx < 0)
        return nullptr;
    return getFlagByIndex<sead::FixedSafeString<64>>(*mString64ArrayFlags[*idx], sub_idx);
}

FlagString256* TriggerParam::getStr256FlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const {
    *idx = getStr256ArrayIdx(name_hash);
    if (*idx < 0 || mString256ArrayFlags.size() <= *idx || sub_idx < 0)
        return nullptr;
    return getFlagByIndex<sead::FixedSafeString<256>>(*mString256ArrayFlags[*idx], sub_idx);
}

FlagVector2f* TriggerParam::getVec2fFlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const {
    *idx = getVec2fArrayIdx(name_hash);
    if (*idx < 0 || mVector2fArrayFlags.size() <= *idx || sub_idx < 0)
        return nullptr;
    return getFlagByIndex<sead::Vector2f>(*mVector2fArrayFlags[*idx], sub_idx);
}

FlagVector3f* TriggerParam::getVec3fFlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const {
    *idx = getVec3fArrayIdx(name_hash);
    if (*idx < 0 || mVector3fArrayFlags.size() <= *idx || sub_idx < 0)
        return nullptr;
    return getFlagByIndex<sead::Vector3f>(*mVector3fArrayFlags[*idx], sub_idx);
}

FlagVector4f* TriggerParam::getVec4fFlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const {
    *idx = getVec4fArrayIdx(name_hash);
    if (*idx < 0 || mVector4fArrayFlags.size() <= *idx || sub_idx < 0)
        return nullptr;
    return getFlagByIndex<sead::Vector4f>(*mVector4fArrayFlags[*idx], sub_idx);
}

void TriggerParam::onResetBoolFlagForRadarMgr(FlagBase* flag, s32 sub_idx) {
    reportFlagChange<bool>(flag, sub_idx);
}

void TriggerParam::setCurrentRupeeFlagName(const sead::SafeString& name) {
    if (sConfig.num_current_rupee_flag_name_changes <= 0) {
        sConfig.getCurrentRupeeFlagName() = name;
        ++sConfig.num_current_rupee_flag_name_changes;
    }
}

bool shouldLogFlagChange(const sead::SafeString& flag_name, FlagType type) {
    u8 event_type;

    if (s32(type) == FlagType::Bool || s32(type) == FlagType::BoolArray)
        event_type = 0;

    else if (s32(type) == FlagType::S32 || s32(type) == FlagType::S32Array)
        event_type = 1;

    else if (s32(type) == FlagType::F32 || s32(type) == FlagType::F32Array)
        event_type = 2;

    else if (s32(type) == FlagType::Vector2f || s32(type) == FlagType::Vector2fArray ||
             s32(type) == FlagType::Vector3f || s32(type) == FlagType::Vector3fArray ||
             s32(type) == FlagType::Vector4f || s32(type) == FlagType::Vector4fArray)
        event_type = 4;

    else if (s32(type) == FlagType::String || s32(type) == FlagType::StringArray ||
             s32(type) == FlagType::String64 || s32(type) == FlagType::String64Array ||
             s32(type) == FlagType::String256 || s32(type) == FlagType::String256Array)
        event_type = 3;

    else
        event_type = 7;

    return sConfig.shouldLog(flag_name, event_type);
}

// NON_MATCHING: reorderings (which result in other small differences)
sead::Color4f getFlagColor(FlagType type) {
    if (s32(type) == FlagType::Bool || s32(type) == FlagType::BoolArray)
        return sead::Color4f::cRed;

    if (s32(type) == FlagType::F32 || s32(type) == FlagType::F32Array ||
        s32(type) == FlagType::Vector2f || s32(type) == FlagType::Vector2fArray ||
        s32(type) == FlagType::Vector3f || s32(type) == FlagType::Vector3fArray ||
        s32(type) == FlagType::Vector4f || s32(type) == FlagType::Vector4fArray)
        return sead::Color4f::cYellow;

    if (s32(type) == FlagType::String || s32(type) == FlagType::StringArray ||
        s32(type) == FlagType::String64 || s32(type) == FlagType::String64Array ||
        s32(type) == FlagType::String256 || s32(type) == FlagType::String256Array)
        return sead::Color4f::cWhite;

    return sead::Color4f::cBlue;
}

}  // namespace ksys::gdt
