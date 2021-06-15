#pragma once

#include <array>
#include <basis/seadTypes.h>
#include <codec/seadHashCRC32.h>
#include <container/seadBuffer.h>
#include <container/seadObjArray.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <gfx/seadColor.h>
#include <prim/seadBitFlag.h>
#include <prim/seadStorageFor.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/GameData/gdtFlag.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class GameData;
}

namespace ksys::gdt {

class TriggerParam {
public:
    struct ResetEntry {
        sead::SizedEnum<FlagType::ValueType, s8> type;
        sead::SizedEnum<ResetType, s8> reset_type;
        s16 sub_index;
        s32 index;
    };
    KSYS_CHECK_SIZE_NX150(ResetEntry, 0x8);

    struct FlagChangeRecord {
        sead::SizedEnum<FlagType::ValueType, u8> type;
        sead::SizedEnum<ResetType, u8> reset_type;
        /// If the flag that was modified was an array, this is the index of the modified element.
        /// Otherwise, this is -1.
        s16 sub_index;
        /// Index of the flag that was modified.
        s32 index;
    };
    KSYS_CHECK_SIZE_NX150(FlagChangeRecord, 0x8);

    struct FlagCopyRecord {
        enum class BitFlag : u8 {
            _1 = 1,
            _2 = 2,
            _4 = 4,
            _7 = _1 | _2 | _4,
            _8 = 8,
        };

        bool checkBitFlags(bool x, bool y) const {
            return bf.isOn(BitFlag::_8) || !(bf.isOn(BitFlag::_4) || (bf.isOn(BitFlag::_1) && !x) ||
                                             (bf.isOn(BitFlag::_2) && !y));
        }

        sead::TypedBitFlag<BitFlag> bf;
        s16 sub_index;
        u32 name_hash;
    };
    KSYS_CHECK_SIZE_NX150(FlagCopyRecord, 0x8);

    TriggerParam();

    void copyFromGameDataRes(res::GameData* gdata, sead::Heap* heap);
    void init(sead::Heap* heap);
    void destroyHeap();
    void allocBools(s32 size, sead::Heap* heap);
    void allocS32s(s32 size, sead::Heap* heap);
    void copyAllFlags(const TriggerParam& src, sead::Heap* heap, bool init_reset_data);
    void copyPermanentFlags(const TriggerParam& src, sead::Heap* heap);

    FlagType getFlagType(const sead::SafeString& name) const;

    void setCurrentRupeeFlagName(const sead::SafeString& name);

    // region Value getters (by index)

    bool getBool(bool* value, s32 index, bool check_permissions) const;
    bool getS32(s32* value, s32 index, bool check_permissions) const;
    bool getF32(f32* value, s32 index, bool check_permissions) const;
    bool getStr(const char** value, s32 index, bool check_permissions) const;
    bool getStr64(const char** value, s32 index, bool check_permissions) const;
    bool getStr256(const char** value, s32 index, bool check_permissions) const;
    bool getVec2f(sead::Vector2f* value, s32 index, bool check_permissions) const;
    bool getVec3f(sead::Vector3f* value, s32 index, bool check_permissions) const;
    bool getVec4f(sead::Vector4f* value, s32 index, bool check_permissions) const;

    bool getBool(bool* value, s32 array_index, s32 index, bool check_permissions) const;
    bool getS32(s32* value, s32 array_index, s32 index, bool check_permissions) const;
    bool getF32(f32* value, s32 array_index, s32 index, bool check_permissions) const;
    bool getStr(const char** value, s32 array_index, s32 index, bool check_permissions) const;
    bool getStr64(const char** value, s32 array_index, s32 index, bool check_permissions) const;
    bool getStr256(const char** value, s32 array_index, s32 index, bool check_permissions) const;
    bool getVec2f(sead::Vector2f* value, s32 array_index, s32 index, bool check_permissions) const;
    bool getVec3f(sead::Vector3f* value, s32 array_index, s32 index, bool check_permissions) const;
    bool getVec4f(sead::Vector4f* value, s32 array_index, s32 index, bool check_permissions) const;

    // endregion

    // region Value getters (by name)

    bool getBool(bool* value, const sead::SafeString& name, bool check_permissions,
                 bool x = true) const;
    bool getBool2(bool* value, const sead::SafeString& name, bool check_permissions,
                  bool x = true) const;
    bool getS32(s32* value, const sead::SafeString& name, bool check_permissions,
                bool x = true) const;
    bool getF32(f32* value, const sead::SafeString& name, bool check_permissions,
                bool x = true) const;
    bool getStr(const char** value, const sead::SafeString& name, bool check_permissions,
                bool x = true) const;
    bool getStr64(const char** value, const sead::SafeString& name, bool check_permissions,
                  bool x = true) const;
    bool getStr256(const char** value, const sead::SafeString& name, bool check_permissions,
                   bool x = true) const;
    bool getVec2f(sead::Vector2f* value, const sead::SafeString& name, bool check_permissions,
                  bool x = true) const;
    bool getVec3f(sead::Vector3f* value, const sead::SafeString& name, bool check_permissions,
                  bool x = true) const;
    bool getVec4f(sead::Vector4f* value, const sead::SafeString& name, bool check_permissions,
                  bool x = true) const;

    bool getBool(bool* value, const sead::SafeString& name, s32 index, bool check_permissions,
                 bool x = true) const;
    bool getS32(s32* value, const sead::SafeString& name, s32 index, bool check_permissions,
                bool x = true) const;
    bool getF32(f32* value, const sead::SafeString& name, s32 index, bool check_permissions,
                bool x = true) const;
    bool getStr(const char** value, const sead::SafeString& name, s32 index, bool check_permissions,
                bool x = true) const;
    bool getStr64(const char** value, const sead::SafeString& name, s32 index,
                  bool check_permissions, bool x = true) const;
    bool getStr256(const char** value, const sead::SafeString& name, s32 index,
                   bool check_permissions, bool x = true) const;
    bool getVec2f(sead::Vector2f* value, const sead::SafeString& name, s32 index,
                  bool check_permissions, bool x = true) const;
    bool getVec3f(sead::Vector3f* value, const sead::SafeString& name, s32 index,
                  bool check_permissions, bool x = true) const;
    bool getVec4f(sead::Vector4f* value, const sead::SafeString& name, s32 index,
                  bool check_permissions, bool x = true) const;

    // endregion

    // region Index getters (by hash)

    s32 getBoolIdx(u32 name) const;
    s32 getS32Idx(u32 name) const;
    s32 getF32Idx(u32 name) const;
    s32 getStrIdx(u32 name) const;
    s32 getStr64Idx(u32 name) const;
    s32 getStr256Idx(u32 name) const;
    s32 getVec2fIdx(u32 name) const;
    s32 getVec3fIdx(u32 name) const;
    s32 getVec4fIdx(u32 name) const;
    s32 getBoolArrayIdx(u32 name) const;
    s32 getS32ArrayIdx(u32 name) const;
    s32 getF32ArrayIdx(u32 name) const;
    s32 getStrArrayIdx(u32 name) const;
    s32 getStr64ArrayIdx(u32 name) const;
    s32 getStr256ArrayIdx(u32 name) const;
    s32 getVec2fArrayIdx(u32 name) const;
    s32 getVec3fArrayIdx(u32 name) const;
    s32 getVec4fArrayIdx(u32 name) const;

    // endregion

    // region Index getters (by name)

    s32 getBoolIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getBoolIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getS32Idx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getS32Idx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getF32Idx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getF32Idx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStrIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStrIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStr64Idx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStr64Idx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStr256Idx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStr256Idx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec2fIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec2fIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec3fIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec3fIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec4fIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec4fIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getBoolArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getBoolArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getS32ArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getS32ArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getF32ArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getF32ArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStrArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStrArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStr64ArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStr64ArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStr256ArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStr256ArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec2fArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec2fArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec3fArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec3fArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec4fArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec4fArrayIdx(sead::HashCRC32::calcStringHash(name));
    }

    // endregion

    // region Array size getters

    bool getBoolArraySize(s32* size, s32 index) const;
    bool getS32ArraySize(s32* size, s32 index) const;
    bool getF32ArraySize(s32* size, s32 index) const;
    bool getStrArraySize(s32* size, s32 index) const;
    bool getStr64ArraySize(s32* size, s32 index) const;
    bool getStr256ArraySize(s32* size, s32 index) const;
    bool getVec2fArraySize(s32* size, s32 index) const;
    bool getVec3fArraySize(s32* size, s32 index) const;
    bool getVec4fArraySize(s32* size, s32 index) const;

    bool getBoolArraySizeByHash(s32* size, u32 name) const;
    bool getS32ArraySizeByHash(s32* size, u32 name) const;
    bool getF32ArraySizeByHash(s32* size, u32 name) const;
    bool getStrArraySizeByHash(s32* size, u32 name) const;
    bool getStr64ArraySizeByHash(s32* size, u32 name) const;
    bool getStr256ArraySizeByHash(s32* size, u32 name) const;
    bool getVec2fArraySizeByHash(s32* size, u32 name) const;
    bool getVec3fArraySizeByHash(s32* size, u32 name) const;
    bool getVec4fArraySizeByHash(s32* size, u32 name) const;

    bool getS32ArraySize(s32* size, const sead::SafeString& name) const;
    bool getStr64ArraySize(s32* size, const sead::SafeString& name) const;
    bool getVec3fArraySize(s32* size, const sead::SafeString& name) const;

    // endregion

    bool getMinValueForS32(s32* min, const sead::SafeString& name) const;
    bool getMaxValueForS32(s32* max, const sead::SafeString& name) const;

    // region Value setters

    bool setBool(bool value, s32 idx, bool check_permissions, bool bypass_one_trigger_check);
    bool setS32(s32 value, s32 idx, bool check_permissions, bool bypass_one_trigger_check);
    bool setF32(f32 value, s32 idx, bool check_permissions, bool bypass_one_trigger_check);
    bool setStr(const char* value, s32 idx, bool check_permissions, bool bypass_one_trigger_check);
    bool setStr64(const char* value, s32 idx, bool check_permissions,
                  bool bypass_one_trigger_check);
    bool setStr256(const char* value, s32 idx, bool check_permissions,
                   bool bypass_one_trigger_check);
    bool setVec2f(const sead::Vector2f& value, s32 idx, bool check_permissions,
                  bool bypass_one_trigger_check);
    bool setVec3f(const sead::Vector3f& value, s32 idx, bool check_permissions,
                  bool bypass_one_trigger_check);
    bool setVec4f(const sead::Vector4f& value, s32 idx, bool check_permissions,
                  bool bypass_one_trigger_check);

    bool setBool(bool value, const sead::SafeString& name, bool check_permissions, bool,
                 bool bypass_one_trigger_check);
    bool setS32(s32 value, const sead::SafeString& name, bool check_permissions, bool,
                bool bypass_one_trigger_check);
    bool setF32(f32 value, const sead::SafeString& name, bool check_permissions, bool,
                bool bypass_one_trigger_check);
    bool setStr(const char* value, const sead::SafeString& name, bool check_permissions, bool,
                bool bypass_one_trigger_check);
    bool setStr64(const char* value, const sead::SafeString& name, bool check_permissions, bool,
                  bool bypass_one_trigger_check);
    bool setStr256(const char* value, const sead::SafeString& name, bool check_permissions, bool,
                   bool bypass_one_trigger_check);
    bool setVec2f(const sead::Vector2f& value, const sead::SafeString& name, bool check_permissions,
                  bool, bool bypass_one_trigger_check);
    bool setVec3f(const sead::Vector3f& value, const sead::SafeString& name, bool check_permissions,
                  bool, bool bypass_one_trigger_check);
    bool setVec4f(const sead::Vector4f& value, const sead::SafeString& name, bool check_permissions,
                  bool, bool bypass_one_trigger_check);

    // endregion

    // region Value setters (array)

    bool setBool(bool value, s32 idx, s32 sub_idx, bool check_permissions,
                 bool bypass_one_trigger_check);
    bool setS32(s32 value, s32 idx, s32 sub_idx, bool check_permissions,
                bool bypass_one_trigger_check);
    bool setF32(f32 value, s32 idx, s32 sub_idx, bool check_permissions,
                bool bypass_one_trigger_check);
    bool setStr(const char* value, s32 idx, s32 sub_idx, bool check_permissions,
                bool bypass_one_trigger_check);
    bool setStr64(const char* value, s32 idx, s32 sub_idx, bool check_permissions,
                  bool bypass_one_trigger_check);
    bool setStr256(const char* value, s32 idx, s32 sub_idx, bool check_permissions,
                   bool bypass_one_trigger_check);
    bool setVec2f(const sead::Vector2f& value, s32 idx, s32 sub_idx, bool check_permissions,
                  bool bypass_one_trigger_check);
    bool setVec3f(const sead::Vector3f& value, s32 idx, s32 sub_idx, bool check_permissions,
                  bool bypass_one_trigger_check);
    bool setVec4f(const sead::Vector4f& value, s32 idx, s32 sub_idx, bool check_permissions,
                  bool bypass_one_trigger_check);

    bool setBool(bool value, const sead::SafeString& name, s32 sub_idx, bool check_permissions,
                 bool, bool bypass_one_trigger_check);
    bool setS32(s32 value, const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool,
                bool bypass_one_trigger_check);
    bool setF32(f32 value, const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool,
                bool bypass_one_trigger_check);
    bool setStr(const char* value, const sead::SafeString& name, s32 sub_idx,
                bool check_permissions, bool, bool bypass_one_trigger_check);
    bool setStr64(const char* value, const sead::SafeString& name, s32 sub_idx,
                  bool check_permissions, bool, bool bypass_one_trigger_check);
    bool setStr256(const char* value, const sead::SafeString& name, s32 sub_idx,
                   bool check_permissions, bool, bool bypass_one_trigger_check);
    bool setVec2f(const sead::Vector2f& value, const sead::SafeString& name, s32 sub_idx,
                  bool check_permissions, bool, bool bypass_one_trigger_check);
    bool setVec3f(const sead::Vector3f& value, const sead::SafeString& name, s32 sub_idx,
                  bool check_permissions, bool, bool bypass_one_trigger_check);
    bool setVec4f(const sead::Vector4f& value, const sead::SafeString& name, s32 sub_idx,
                  bool check_permissions, bool, bool bypass_one_trigger_check);

    // endregion

    // region Resetting values

    bool resetBool(s32 idx, bool check_permissions);
    bool resetS32(s32 idx, bool check_permissions);
    bool resetF32(s32 idx, bool check_permissions);
    bool resetStr(s32 idx, bool check_permissions);
    bool resetStr64(s32 idx, bool check_permissions);
    bool resetStr256(s32 idx, bool check_permissions);
    bool resetVec2f(s32 idx, bool check_permissions);
    bool resetVec3f(s32 idx, bool check_permissions);
    bool resetVec4f(s32 idx, bool check_permissions);

    bool resetBool(const sead::SafeString& name, bool check_permissions, bool = true);
    bool resetS32(const sead::SafeString& name, bool check_permissions, bool = true);
    bool resetF32(const sead::SafeString& name, bool check_permissions, bool = true);
    bool resetStr(const sead::SafeString& name, bool check_permissions, bool = true);
    bool resetStr64(const sead::SafeString& name, bool check_permissions, bool = true);
    bool resetStr256(const sead::SafeString& name, bool check_permissions, bool = true);
    bool resetVec2f(const sead::SafeString& name, bool check_permissions, bool = true);
    bool resetVec3f(const sead::SafeString& name, bool check_permissions, bool = true);
    bool resetVec4f(const sead::SafeString& name, bool check_permissions, bool = true);

    // endregion

    // region Resetting values (array)

    bool resetBool(s32 idx, s32 sub_idx, bool check_permissions);
    bool resetS32(s32 idx, s32 sub_idx, bool check_permissions);
    bool resetF32(s32 idx, s32 sub_idx, bool check_permissions);
    bool resetStr(s32 idx, s32 sub_idx, bool check_permissions);
    bool resetStr64(s32 idx, s32 sub_idx, bool check_permissions);
    bool resetStr256(s32 idx, s32 sub_idx, bool check_permissions);
    bool resetVec2f(s32 idx, s32 sub_idx, bool check_permissions);
    bool resetVec3f(s32 idx, s32 sub_idx, bool check_permissions);
    bool resetVec4f(s32 idx, s32 sub_idx, bool check_permissions);

    bool resetBool(const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool = true);
    bool resetS32(const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool = true);
    bool resetF32(const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool = true);
    bool resetStr(const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool = true);
    bool resetStr64(const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool = true);
    bool resetStr256(const sead::SafeString& name, s32 sub_idx, bool check_permissions,
                     bool = true);
    bool resetVec2f(const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool = true);
    bool resetVec3f(const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool = true);
    bool resetVec4f(const sead::SafeString& name, s32 sub_idx, bool check_permissions, bool = true);

    // endregion

    void resetAllFlagsToInitialValues();
    /// @param policy  A bitmask that indicates the reset policy to use.
    /// @param skip  The number of flags to skip processing.
    /// @return the number of flags that have been processed.
    int resetFlagsAccordingToPolicy(sead::BitFlag32 policy, int skip);

    // region Flag getters

    FlagBool* getBoolFlag(s32 idx) const;
    FlagS32* getS32Flag(s32 idx) const;
    FlagF32* getF32Flag(s32 idx) const;
    FlagString* getStrFlag(s32 idx) const;
    FlagString64* getStr64Flag(s32 idx) const;
    FlagString256* getStr256Flag(s32 idx) const;
    FlagVector2f* getVec2fFlag(s32 idx) const;
    FlagVector3f* getVec3fFlag(s32 idx) const;
    FlagVector4f* getVec4fFlag(s32 idx) const;

    // endregion

    // region Flag getters (array)

    FlagBool* getBoolFlag(s32 idx, s32 sub_idx) const;
    FlagS32* getS32Flag(s32 idx, s32 sub_idx) const;
    FlagF32* getF32Flag(s32 idx, s32 sub_idx) const;
    FlagString* getStrFlag(s32 idx, s32 sub_idx) const;
    FlagString64* getStr64Flag(s32 idx, s32 sub_idx) const;
    FlagString256* getStr256Flag(s32 idx, s32 sub_idx) const;
    FlagVector2f* getVec2fFlag(s32 idx, s32 sub_idx) const;
    FlagVector3f* getVec3fFlag(s32 idx, s32 sub_idx) const;
    FlagVector4f* getVec4fFlag(s32 idx, s32 sub_idx) const;

    // endregion

    // region Flag + index getters

    FlagBool* getBoolFlagAndIdx(s32* idx, u32 name_hash) const;
    FlagS32* getS32FlagAndIdx(s32* idx, u32 name_hash) const;
    FlagF32* getF32FlagAndIdx(s32* idx, u32 name_hash) const;
    FlagString* getStrFlagAndIdx(s32* idx, u32 name_hash) const;
    FlagString64* getStr64FlagAndIdx(s32* idx, u32 name_hash) const;
    FlagString256* getStr256FlagAndIdx(s32* idx, u32 name_hash) const;
    FlagVector2f* getVec2fFlagAndIdx(s32* idx, u32 name_hash) const;
    FlagVector3f* getVec3fFlagAndIdx(s32* idx, u32 name_hash) const;
    FlagVector4f* getVec4fFlagAndIdx(s32* idx, u32 name_hash) const;

    // endregion

    // region Flag + index getters (array)

    FlagBool* getBoolFlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const;
    FlagS32* getS32FlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const;
    FlagF32* getF32FlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const;
    FlagString* getStrFlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const;
    FlagString64* getStr64FlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const;
    FlagString256* getStr256FlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const;
    FlagVector2f* getVec2fFlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const;
    FlagVector3f* getVec3fFlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const;
    FlagVector4f* getVec4fFlagAndIdx(s32* idx, u32 name_hash, s32 sub_idx) const;

    // endregion

    FlagS32* getS32FlagByHash(u32 name_hash) const;
    void onResetBoolFlagForRadarMgr(FlagBase* flag, s32 sub_idx = -1);

    bool getBoolIfCopied(bool* value, const sead::SafeString& name, bool x, bool y) const;
    bool getS32IfCopied(s32* value, const sead::SafeString& name, bool x, bool y) const;
    bool getF32IfCopied(f32* value, const sead::SafeString& name, bool x, bool y) const;

    void copyChangedFlags(TriggerParam& other, bool set_all_flags, bool record_copies,
                          bool ignore_temp_flags);

private:
    friend class Manager;

    enum class BitFlag : u8 {
        _1 = 1,
        _2 = 2,
        _4 = 4,
        _7 = _1 | _2 | _4,
        _8 = 8,
        EventAssociatedFlagModified = 0x10,
    };

    void allocCopyRecordArrays(sead::Heap* heap);
    void updateBoolFlagCounts();
    void initResetData(sead::Heap* heap);
    void initRevivalRandomBools(sead::Heap* heap);

    void recordFlagChange(const FlagBase* flag, s32 idx, s32 sub_idx = -1);

    bool shouldFindExistingCopyRecord() const { return mBitFlags.ref().isOn(BitFlag::_7); }

    bool shouldSkipRevivingShopItem(bool* is_shop_item, u32 flag_hash, bool is_main_field,
                                    const sead::Buffer<s32>& arrow_counts, s32 col1, s32 row1,
                                    s32 col2, s32 row2) const;

    u32 mResourceFlags = 0;

    sead::PtrArray<FlagBase> mBoolFlags;
    sead::PtrArray<FlagBase> mS32Flags;
    sead::PtrArray<FlagBase> mF32Flags;
    sead::PtrArray<FlagBase> mStringFlags;
    sead::PtrArray<FlagBase> mString64Flags;
    sead::PtrArray<FlagBase> mString256Flags;
    sead::PtrArray<FlagBase> mVector2fFlags;
    sead::PtrArray<FlagBase> mVector3fFlags;
    sead::PtrArray<FlagBase> mVector4fFlags;

    sead::PtrArray<sead::PtrArray<FlagBase>> mBoolArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mS32ArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mF32ArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mStringArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mString64ArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mString256ArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mVector2fArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mVector3fArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mVector4fArrayFlags;

    sead::SafeArray<sead::StorageFor<sead::Buffer<FlagChangeRecord>>, 3> mFlagChangeRecords{};

    sead::ObjArray<FlagCopyRecord> mCopiedBoolFlags;
    sead::ObjArray<FlagCopyRecord> mCopiedS32Flags;
    sead::ObjArray<FlagCopyRecord> mCopiedF32Flags;
    sead::ObjArray<FlagCopyRecord> mCopiedStringFlags;
    sead::ObjArray<FlagCopyRecord> mCopiedString64Flags;
    sead::ObjArray<FlagCopyRecord> mCopiedString256Flags;
    sead::ObjArray<FlagCopyRecord> mCopiedVector2fFlags;
    sead::ObjArray<FlagCopyRecord> mCopiedVector3fFlags;
    sead::ObjArray<FlagCopyRecord> mCopiedVector4fFlags;

    sead::Buffer<ResetEntry> mResetEntries;
    sead::PtrArray<FlagBool> mRevivalRandomBools;

    sead::Heap* mHeap = nullptr;

    std::array<s32, 3> mFlagChangeRecordIndices;
    sead::SafeArray<s32, 15> mNumBoolFlagsPerCategory0;
    sead::SafeArray<s32, 15> mNumBoolFlagsPerCategory;
    sead::SafeArray<sead::StorageFor<sead::CriticalSection>, 3> mCriticalSections{};
    sead::StorageFor<sead::TypedBitFlag<BitFlag>> mBitFlags;
};
KSYS_CHECK_SIZE_NX150(TriggerParam, 0x3f0);

bool shouldLogFlagChange(const sead::SafeString& flag_name, FlagType flag_type);
sead::Color4f getFlagColor(FlagType type);

}  // namespace ksys::gdt
