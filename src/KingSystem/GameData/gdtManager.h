#pragma once

#include <container/seadRingBuffer.h>
#include <container/seadSafeArray.h>
#include <filedevice/seadArchiveFileDevice.h>
#include <framework/seadMethodTree.h>
#include <heap/seadDisposer.h>
#include <prim/seadDelegateEventSlot.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadMutex.h>
#include <type_traits>
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/GameData/gdtTriggerParam.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/System/KingEditor.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/Types.h"

namespace sead {
class Framework;
class MethodTreeMgr;
}  // namespace sead

namespace ksys::map {
class MubinIter;
}

namespace ksys::gdt {

namespace detail {

template <typename T>
struct SetterTraits {
    static constexpr bool isVectorType() {
        return std::is_same_v<T, sead::Vector2f> || std::is_same_v<T, sead::Vector3f> ||
               std::is_same_v<T, sead::Vector4f>;
    }

    static constexpr bool isStringType() { return std::is_same_v<T, const char*>; }

    static constexpr bool isInlineType() {
        return std::is_same_v<T, bool> || std::is_same_v<T, s32> || std::is_same_v<T, f32> ||
               isStringType();
    }

    using ArgType = std::conditional_t<isInlineType(), T, const T&>;
    using WrapperArgType = std::conditional_t<isStringType(), const sead::SafeString&, ArgType>;
    using NoCheckForceArgType = T;

    static ArgType convertValue(WrapperArgType v) {
        if constexpr (isStringType())
            return v.cstr();
        else
            return v;
    }
};

}  // namespace detail

class TriggerParamRef {
public:
    TriggerParamRef(TriggerParam** param_1, TriggerParam** param, bool check_permissions,
                    bool propagate_param_1_changes, bool change_only_once)
        : mParam1(param_1), mParam(param), mCheckPermissions(check_permissions),
          mPropagateParam1Changes(propagate_param_1_changes), mChangeOnlyOnce(change_only_once) {}

    virtual ~TriggerParamRef() = default;

    class Proxy {
    public:
        TriggerParam* getBuffer() const { return mUseParam1 ? *mRef.mParam1 : *mRef.mParam; }
        TriggerParam* getBuffer0() const { return *mRef.mParam; }
        TriggerParam* getBuffer1() const { return *mRef.mParam1; }

        // region Value getters

#define PROXY_GET_SET_IMPL_(GET_NAME, SET_NAME, TYPE)                                              \
    bool GET_NAME(TYPE* value, s32 index) const {                                                  \
        return getBuffer()->GET_NAME(value, index, mRef.mCheckPermissions);                        \
    }                                                                                              \
    bool GET_NAME(TYPE* value, s32 array_index, s32 index) const {                                 \
        return getBuffer()->GET_NAME(value, array_index, index, mRef.mCheckPermissions);           \
    }                                                                                              \
    bool GET_NAME(TYPE* value, const sead::SafeString& name) const {                               \
        return getBuffer()->GET_NAME(value, name, mRef.mCheckPermissions);                         \
    }                                                                                              \
    bool GET_NAME(TYPE* value, const sead::SafeString& array_name, s32 index) const {              \
        return getBuffer()->GET_NAME(value, array_name, index, mRef.mCheckPermissions);            \
    }                                                                                              \
                                                                                                   \
    bool SET_NAME(TYPE const& value, s32 idx, bool bypass_one_trigger_check = false) {             \
        if (mRef.mChangeOnlyOnce)                                                                  \
            return false;                                                                          \
        if (!getBuffer1()->SET_NAME(value, idx, mRef.mCheckPermissions, bypass_one_trigger_check)) \
            return false;                                                                          \
        if (mRef.mPropagateParam1Changes)                                                          \
            getBuffer0()->SET_NAME(value, idx, mRef.mCheckPermissions, bypass_one_trigger_check);  \
        return true;                                                                               \
    }                                                                                              \
    bool SET_NAME(TYPE const& value, s32 array_idx, s32 idx,                                       \
                  bool bypass_one_trigger_check = false) {                                         \
        if (mRef.mChangeOnlyOnce)                                                                  \
            return false;                                                                          \
        if (!getBuffer1()->SET_NAME(value, array_idx, idx, mRef.mCheckPermissions,                 \
                                    bypass_one_trigger_check))                                     \
            return false;                                                                          \
        if (mRef.mPropagateParam1Changes)                                                          \
            getBuffer0()->SET_NAME(value, array_idx, idx, mRef.mCheckPermissions,                  \
                                   bypass_one_trigger_check);                                      \
        return true;                                                                               \
    }                                                                                              \
    bool SET_NAME(TYPE const& value, const sead::SafeString& name,                                 \
                  bool bypass_one_trigger_check = false) {                                         \
        if (mRef.mChangeOnlyOnce)                                                                  \
            return false;                                                                          \
        if (!getBuffer1()->SET_NAME(value, name, mRef.mCheckPermissions, true,                     \
                                    bypass_one_trigger_check))                                     \
            return false;                                                                          \
        if (mRef.mPropagateParam1Changes)                                                          \
            getBuffer0()->SET_NAME(value, name, mRef.mCheckPermissions, true,                      \
                                   bypass_one_trigger_check);                                      \
        return true;                                                                               \
    }                                                                                              \
    bool SET_NAME(TYPE const& value, const sead::SafeString& name, s32 idx,                        \
                  bool bypass_one_trigger_check = false) {                                         \
        if (mRef.mChangeOnlyOnce)                                                                  \
            return false;                                                                          \
        if (!getBuffer1()->SET_NAME(value, name, idx, mRef.mCheckPermissions, true,                \
                                    bypass_one_trigger_check))                                     \
            return false;                                                                          \
        if (mRef.mPropagateParam1Changes)                                                          \
            getBuffer0()->SET_NAME(value, name, idx, mRef.mCheckPermissions, true,                 \
                                   bypass_one_trigger_check);                                      \
        return true;                                                                               \
    }

        PROXY_GET_SET_IMPL_(getBool, setBool, bool)
        PROXY_GET_SET_IMPL_(getS32, setS32, s32)
        PROXY_GET_SET_IMPL_(getF32, setF32, f32)
        PROXY_GET_SET_IMPL_(getStr, setStr, char const*)
        PROXY_GET_SET_IMPL_(getStr64, setStr64, char const*)
        PROXY_GET_SET_IMPL_(getStr256, setStr256, char const*)
        PROXY_GET_SET_IMPL_(getVec2f, setVec2f, sead::Vector2f)
        PROXY_GET_SET_IMPL_(getVec3f, setVec3f, sead::Vector3f)
        PROXY_GET_SET_IMPL_(getVec4f, setVec4f, sead::Vector4f)

#undef PROXY_GET_SET_IMPL_

#define PROXY_RESET_IMPL_(NAME)                                                                    \
    bool NAME(s32 idx) { return getBuffer1()->NAME(idx, mRef.mCheckPermissions); }                 \
    bool NAME(s32 idx, s32 sub_idx) {                                                              \
        return getBuffer1()->NAME(idx, sub_idx, mRef.mCheckPermissions);                           \
    }                                                                                              \
    bool NAME(const sead::SafeString& name) {                                                      \
        return getBuffer1()->NAME(name, mRef.mCheckPermissions);                                   \
    }                                                                                              \
    bool NAME(const sead::SafeString& name, s32 sub_idx) {                                         \
        return getBuffer1()->NAME(name, sub_idx, mRef.mCheckPermissions);                          \
    }

        PROXY_RESET_IMPL_(resetBool)
        PROXY_RESET_IMPL_(resetS32)
        PROXY_RESET_IMPL_(resetF32)
        PROXY_RESET_IMPL_(resetStr)
        PROXY_RESET_IMPL_(resetStr64)
        PROXY_RESET_IMPL_(resetStr256)
        PROXY_RESET_IMPL_(resetVec2f)
        PROXY_RESET_IMPL_(resetVec3f)
        PROXY_RESET_IMPL_(resetVec4f)

#undef PROXY_RESET_IMPL_

    private:
        friend class TriggerParamRef;
        Proxy(const TriggerParamRef& ref, bool param1) : mUseParam1(param1), mRef(ref) {}

        bool mUseParam1;
        const TriggerParamRef& mRef;
    };

    Proxy get() const { return Proxy(*this, false); }
    Proxy get1() const { return Proxy(*this, true); }

    void setBuffers(TriggerParam** param1, TriggerParam** param) {
        mParam1 = param1;
        mParam = param;
    }

    bool shouldCheckPermissions() const { return mCheckPermissions; }
    bool shouldPropagateParam1Changes() const { return mPropagateParam1Changes; }
    bool shouldChangeOnlyOnce() const { return mChangeOnlyOnce; }

    void setCheckPermissions(bool on) { mCheckPermissions = on; }
    void setPropagateParam1Changes(bool on) { mPropagateParam1Changes = on; }
    void setChangeOnlyOnce(bool on) { mChangeOnlyOnce = on; }

private:
    TriggerParam** mParam1;
    TriggerParam** mParam;
    bool mCheckPermissions;
    bool mPropagateParam1Changes;
    bool mChangeOnlyOnce;
};
KSYS_CHECK_SIZE_NX150(TriggerParamRef, 0x20);

class IManager {
public:
    virtual ~IManager() = 0;
};

inline IManager::~IManager() = default;

class Manager : public IManager, public KingEditorComponent {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    ~Manager() override;
    const char* getName() const override { return "GameData"; }
    void syncData(char* data) override;

public:
    struct ResetEvent {
        virtual ~ResetEvent() = default;
        TriggerParam* param = nullptr;
    };

    struct ReinitEvent {
        virtual ~ReinitEvent() = default;
    };

    using ResetSignal = sead::DelegateEvent<ResetEvent*>;
    using ReinitSignal = sead::DelegateEvent<ReinitEvent*>;

    void init(sead::Heap* heap, sead::Framework* framework);
    void calc();

    void addReinitCallback(ReinitSignal::Slot& slot);
    void removeReinitCallback(ReinitSignal::Slot& slot);

    void setCurrentRupeeFlagName(const sead::SafeString& name);
    void requestResetAllFlagsToInitial();

    /// Checks whether quest flags (e.g. Kass shrine quest flags) are set or cleared properly
    /// and takes any action necessary to fix them.
    void fixQuestFlags();
    void fixQuestFlagsDlc2();

    sead::Heap* getGameDataHeap() const { return mGameDataHeap; }
    sead::Heap* getSaveAreaHeap() const { return mSaveAreaHeap; }
    sead::Heap* getGameDataComHeap() const { return mGameDataComHeap; }

    TriggerParamRef& getParam() { return mParam; }
    TriggerParamRef& getParamBypassPerm() { return mParamBypassPerm; }

#define GDT_GET_HANDLE_(NAME, GET_IDX_NAME)                                                        \
    FlagHandle NAME(const sead::SafeString& name) const {                                          \
        const auto prefix = mCurrentFlagHandlePrefix;                                              \
        const auto hash = sead::HashCRC32::calcStringHash(name);                                   \
        return makeFlagHandle(prefix, mParam.get1().getBuffer()->GET_IDX_NAME(hash));              \
    }

    GDT_GET_HANDLE_(getBoolHandle, TriggerParam::getBoolIdx)
    GDT_GET_HANDLE_(getS32Handle, TriggerParam::getS32Idx)
    GDT_GET_HANDLE_(getF32Handle, TriggerParam::getF32Idx)
    GDT_GET_HANDLE_(getStrHandle, TriggerParam::getStrIdx)
    GDT_GET_HANDLE_(getStr64Handle, TriggerParam::getStr64Idx)
    GDT_GET_HANDLE_(getStr256Handle, TriggerParam::getStr256Idx)
    GDT_GET_HANDLE_(getVec2fHandle, TriggerParam::getVec2fIdx)
    GDT_GET_HANDLE_(getVec3fHandle, TriggerParam::getVec3fIdx)
    GDT_GET_HANDLE_(getVec4fHandle, TriggerParam::getVec4fIdx)

    GDT_GET_HANDLE_(getBoolArrayHandle, TriggerParam::getBoolArrayIdx)
    GDT_GET_HANDLE_(getS32ArrayHandle, TriggerParam::getS32ArrayIdx)
    GDT_GET_HANDLE_(getF32ArrayHandle, TriggerParam::getF32ArrayIdx)
    GDT_GET_HANDLE_(getStrArrayHandle, TriggerParam::getStrArrayIdx)
    GDT_GET_HANDLE_(getStr64ArrayHandle, TriggerParam::getStr64ArrayIdx)
    GDT_GET_HANDLE_(getStr256ArrayHandle, TriggerParam::getStr256ArrayIdx)
    GDT_GET_HANDLE_(getVec2fArrayHandle, TriggerParam::getVec2fArrayIdx)
    GDT_GET_HANDLE_(getVec3fArrayHandle, TriggerParam::getVec3fArrayIdx)
    GDT_GET_HANDLE_(getVec4fArrayHandle, TriggerParam::getVec4fArrayIdx)

#undef GDT_GET_HANDLE_

#define GDT_GET_(NAME, T)                                                                          \
    bool NAME(FlagHandle handle, T* value, bool debug = false,                                     \
              bool ignore_trigger_param_result = false) {                                          \
        return unwrapHandle<false>(handle, debug, [&](u32 idx, TriggerParamRef& ref) {             \
            const bool result = ref.get().NAME(value, idx);                                        \
            return ignore_trigger_param_result || result;                                          \
        });                                                                                        \
    }                                                                                              \
    bool NAME(FlagHandle handle, T* value, s32 sub_idx, bool debug = false,                        \
              bool ignore_trigger_param_result = false) {                                          \
        return unwrapHandle<false>(handle, debug, [&](u32 idx, TriggerParamRef& ref) {             \
            const bool result = ref.get().NAME(value, idx, sub_idx);                               \
            return ignore_trigger_param_result || result;                                          \
        });                                                                                        \
    }

    GDT_GET_(getBool, bool)
    GDT_GET_(getS32, s32)
    GDT_GET_(getF32, f32)
    GDT_GET_(getStr, char const*)
    GDT_GET_(getStr64, char const*)
    GDT_GET_(getStr256, char const*)
    GDT_GET_(getVec2f, sead::Vector2f)
    GDT_GET_(getVec3f, sead::Vector3f)
    GDT_GET_(getVec4f, sead::Vector4f)

#undef GDT_GET_

#define GDT_SET_(NAME, TRAITS)                                                                     \
    /* Setters (by handle) */                                                                      \
    KSYS_ALWAYS_INLINE bool NAME(TRAITS::ArgType value, FlagHandle handle, bool debug,             \
                                 bool force) {                                                     \
        if (mBitFlags.isOn(BitFlag::_40000))                                                       \
            return false;                                                                          \
        return unwrapHandle<true>(handle, debug, [&](u32 idx, TriggerParamRef& ref) {              \
            return ref.get().NAME(value, idx, force);                                              \
        });                                                                                        \
    }                                                                                              \
    bool NAME(TRAITS::ArgType value, FlagHandle handle) {                                          \
        return NAME(value, handle, false, false);                                                  \
    }                                                                                              \
    bool NAME##NoCheck(TRAITS::ArgType value, FlagHandle handle) {                                 \
        return NAME(value, handle, true, false);                                                   \
    }                                                                                              \
    bool NAME##NoCheckForce(TRAITS::NoCheckForceArgType value, FlagHandle handle) {                \
        return NAME(value, handle, true, true);                                                    \
    }                                                                                              \
    /* Setters for arrays (by handle) */                                                           \
    KSYS_ALWAYS_INLINE bool NAME(TRAITS::ArgType value, FlagHandle handle, bool debug, bool force, \
                                 s32 sub_idx) {                                                    \
        if (mBitFlags.isOn(BitFlag::_40000))                                                       \
            return false;                                                                          \
        return unwrapHandle<true>(handle, debug, [&](u32 idx, TriggerParamRef& ref) {              \
            return ref.get().NAME(value, idx, sub_idx, force);                                     \
        });                                                                                        \
    }                                                                                              \
    bool NAME(TRAITS::ArgType value, FlagHandle handle, s32 sub_idx) {                             \
        return NAME(value, handle, false, false, sub_idx);                                         \
    }                                                                                              \
    bool NAME##NoCheck(TRAITS::ArgType value, FlagHandle handle, s32 sub_idx) {                    \
        return NAME(value, handle, true, false, sub_idx);                                          \
    }                                                                                              \
    bool NAME##NoCheckForce(TRAITS::NoCheckForceArgType value, FlagHandle handle, s32 sub_idx) {   \
        return NAME(value, handle, true, true, sub_idx);                                           \
    }                                                                                              \
    /* Setters (by name) */                                                                        \
    KSYS_ALWAYS_INLINE bool NAME(TRAITS::ArgType value, const sead::SafeString& name, bool debug,  \
                                 bool force) {                                                     \
        if (mBitFlags.isOn(BitFlag::_40000))                                                       \
            return false;                                                                          \
        auto& ref = debug ? getParamBypassPerm() : getParam();                                     \
        return ref.get().NAME(value, name, force);                                                 \
    }                                                                                              \
    bool NAME(TRAITS::ArgType value, const sead::SafeString& name);                                \
    bool NAME##_(TRAITS::ArgType value, const sead::SafeString& name);                             \
    bool NAME##NoCheck(TRAITS::ArgType value, const sead::SafeString& name);                       \
    bool NAME##NoCheck_(TRAITS::ArgType value, const sead::SafeString& name);                      \
    bool NAME##NoCheckForce(TRAITS::NoCheckForceArgType value, const sead::SafeString& name);      \
    /* Setters for arrays (by name) */                                                             \
    KSYS_ALWAYS_INLINE bool NAME(TRAITS::ArgType value, const sead::SafeString& name, bool debug,  \
                                 bool force, s32 sub_idx) {                                        \
        if (mBitFlags.isOn(BitFlag::_40000))                                                       \
            return false;                                                                          \
        auto& ref = debug ? getParamBypassPerm() : getParam();                                     \
        return ref.get().NAME(value, name, sub_idx, force);                                        \
    }                                                                                              \
    bool NAME(TRAITS::ArgType value, const sead::SafeString& name, s32 sub_idx);                   \
    bool NAME##_(TRAITS::ArgType value, const sead::SafeString& name, s32 sub_idx);                \
    bool NAME##NoCheck(TRAITS::ArgType value, const sead::SafeString& name, s32 sub_idx);          \
    bool NAME##NoCheckForce(TRAITS::NoCheckForceArgType value, const sead::SafeString& name,       \
                            s32 sub_idx);                                                          \
                                                                                                   \
    bool NAME(TRAITS::WrapperArgType value, FlagHandle handle, bool debug) {                       \
        if (debug) {                                                                               \
            onChangedByDebug();                                                                    \
            return NAME##NoCheckForce(TRAITS::convertValue(value), handle);                        \
        }                                                                                          \
        return NAME(TRAITS::convertValue(value), handle);                                          \
    }                                                                                              \
    bool NAME(TRAITS::WrapperArgType value, const sead::SafeString& name, bool debug) {            \
        if (debug) {                                                                               \
            onChangedByDebug();                                                                    \
            return NAME##NoCheckForce(TRAITS::convertValue(value), name);                          \
        }                                                                                          \
        return NAME(TRAITS::convertValue(value), name);                                            \
    }                                                                                              \
    inline bool NAME##Special(TRAITS::WrapperArgType value, const sead::SafeString& name,          \
                              bool debug, bool force = false) {                                    \
        if (debug) {                                                                               \
            onChangedByDebug();                                                                    \
            auto& ref = debug ? getParamBypassPerm() : getParam();                                 \
            return ref.get().NAME(TRAITS::convertValue(value), name, force);                       \
        }                                                                                          \
        return NAME(TRAITS::convertValue(value), name);                                            \
    }                                                                                              \
                                                                                                   \
    bool NAME(TRAITS::WrapperArgType value, FlagHandle handle, bool debug, s32 sub_idx) {          \
        if (debug) {                                                                               \
            onChangedByDebug();                                                                    \
            return NAME##NoCheckForce(TRAITS::convertValue(value), handle, sub_idx);               \
        }                                                                                          \
        return NAME(TRAITS::convertValue(value), handle, sub_idx);                                 \
    }                                                                                              \
    bool NAME(TRAITS::WrapperArgType value, const sead::SafeString& name, bool debug,              \
              s32 sub_idx) {                                                                       \
        if (debug) {                                                                               \
            onChangedByDebug();                                                                    \
            return NAME##NoCheckForce(TRAITS::convertValue(value), name, sub_idx);                 \
        }                                                                                          \
        return NAME(TRAITS::convertValue(value), name, sub_idx);                                   \
    }

    GDT_SET_(setBool, detail::SetterTraits<bool>)
    GDT_SET_(setS32, detail::SetterTraits<s32>)
    GDT_SET_(setF32, detail::SetterTraits<f32>)
    GDT_SET_(setStr, detail::SetterTraits<const char*>)
    GDT_SET_(setStr64, detail::SetterTraits<const char*>)
    GDT_SET_(setStr256, detail::SetterTraits<const char*>)
    GDT_SET_(setVec2f, detail::SetterTraits<sead::Vector2f>)
    GDT_SET_(setVec3f, detail::SetterTraits<sead::Vector3f>)
    GDT_SET_(setVec4f, detail::SetterTraits<sead::Vector4f>)

#undef GDT_SET_

#define GDT_RESET_(NAME)                                                                           \
    bool NAME(const sead::SafeString& name);                                                       \
    bool NAME##_(const sead::SafeString& name);                                                    \
    bool NAME(const sead::SafeString& name, int sub_idx);                                          \
    KSYS_ALWAYS_INLINE bool NAME##_(FlagHandle handle, bool debug) {                               \
        if (mBitFlags.isOn(BitFlag::_40000))                                                       \
            return false;                                                                          \
        return unwrapHandle<false>(                                                                \
            handle, debug, [&](u32 idx, TriggerParamRef& ref) { return ref.get().NAME(idx); });    \
    }                                                                                              \
    inline bool NAME(FlagHandle handle) { return NAME##_(handle, false); }                         \
    inline bool NAME##NoCheck(FlagHandle handle) { return NAME##_(handle, true); }                 \
                                                                                                   \
    KSYS_ALWAYS_INLINE bool NAME##_(FlagHandle handle, bool debug, s32 sub_idx) {                  \
        if (mBitFlags.isOn(BitFlag::_40000))                                                       \
            return false;                                                                          \
        return unwrapHandle<false>(handle, debug, [&](u32 idx, TriggerParamRef& ref) {             \
            return ref.get().NAME(idx, sub_idx);                                                   \
        });                                                                                        \
    }                                                                                              \
    inline bool NAME(FlagHandle handle, s32 sub_idx) { return NAME##_(handle, false, sub_idx); }   \
    inline bool NAME##NoCheck(FlagHandle handle, s32 sub_idx) {                                    \
        return NAME##_(handle, true, sub_idx);                                                     \
    }                                                                                              \
                                                                                                   \
    inline bool NAME(FlagHandle handle, bool debug) {                                              \
        if (debug) {                                                                               \
            onChangedByDebug();                                                                    \
            return NAME##NoCheck(handle);                                                          \
        }                                                                                          \
        return NAME(handle);                                                                       \
    }                                                                                              \
    inline bool NAME(FlagHandle handle, bool debug, s32 sub_idx) {                                 \
        if (debug) {                                                                               \
            onChangedByDebug();                                                                    \
            return NAME##NoCheck(handle, sub_idx);                                                 \
        }                                                                                          \
        return NAME(handle, sub_idx);                                                              \
    }

    GDT_RESET_(resetBool)
    GDT_RESET_(resetS32)
    GDT_RESET_(resetF32)
    GDT_RESET_(resetStr)
    GDT_RESET_(resetStr64)
    GDT_RESET_(resetStr256)
    GDT_RESET_(resetVec2f)
    GDT_RESET_(resetVec3f)
    GDT_RESET_(resetVec4f)

#undef GDT_RESET_

    void incrementS32NoCheck(s32 value, const sead::SafeString& name);
    void incrementS32(s32 value, const sead::SafeString& name);

    void increaseS32CommonFlag(s32 value, const sead::SafeString& name, s32 sub_idx, bool debug) {
        if (!mIncreaseLogger)
            return;

        mIncreaseLogger->addRecord(value, name, sub_idx, debug);
        if (debug)
            onChangedByDebug();
    }

    bool wasFlagCopied(const sead::SafeString& name);
    bool wasFlagNotCopied(const sead::SafeString& name);

    void copyParamToParam1();
    void allocParam1();

    FlagHandle getRevivalFlagHandle(const sead::SafeString& object_name,
                                    const map::MubinIter& iter);
    static bool getShopInfoIter(u32 hash, al::ByamlIter* out, const al::ByamlIter& iter,
                                const u32* hashes);
    bool getShopSoldOutInfo(u32 hash, al::ByamlIter* out) const {
        return getShopInfoIter(hash, out, getShopSoldOutInfoValues(), getShopSoldOutInfoHashes());
    }
    void resetBoolFlagForRadarMgr(FlagBool& flag);

    void allocRetryBuffer(sead::Heap* heap);
    void destroyRetryBuffer();

    void startSyncOnLoadEnd();

    const al::ByamlIter& getShopAreaInfoValues() const { return mShopAreaInfoValues; }
    const u32* getShopAreaInfoHashes() const { return mShopAreaInfoHashes; }
    const al::ByamlIter& getShopSoldOutInfoValues() const { return mShopSoldOutInfoValues; }
    const u32* getShopSoldOutInfoHashes() const { return mShopSoldOutInfoHashes; }

    void onAnimalMasterAppearance() {
        mBitFlags.set(BitFlag::_8);
        mResetFlags.set(ResetFlag::AnimalMaster);
    }

private:
    enum class BitFlag {
        _1 = 0x1,
        _2 = 0x2,
        RequestResetAllFlagsToInitial = 0x4,
        _8 = 0x8,
        _10 = 0x10,
        _20 = 0x20,
        _40 = 0x40,
        _80 = 0x80,
        _100 = 0x100,
        _200 = 0x200,
        SyncFlags = _100 | _200,
        _400 = 0x400,
        _800 = 0x800,
        _1000 = 0x1000,
        _2000 = 0x2000,
        _4000 = 0x4000,
        _8000 = 0x8000,
        _10000 = 0x10000,
        _20000 = 0x20000,
        _40000 = 0x40000,
        _80000 = 0x80000,
    };

    enum class ResetFlag {
        AnimalMaster = 0x10,
    };

    struct MethodTreeNode {
        virtual ~MethodTreeNode() = default;
        sead::MethodTreeNode node{nullptr};
        sead::MethodTreeMgr* method_tree_mgr = nullptr;
    };

    struct IncreaseLogger {
        struct Record {
            bool debug = false;
            u32 name_hash = 0;
            s32 sub_idx = -1;
            s32 value = 0;
        };
        KSYS_CHECK_SIZE_NX150(Record, 0x10);

        void addRecord(s32 value, const sead::SafeString& name, s32 sub_idx, bool debug);

        u64 _0 = 0;
        sead::SafeArray<sead::FixedRingBuffer<Record, 64>, 3> ring_buffers[2];
        sead::SafeArray<Record, 0xc0> arrays[2]{};
    };

    static FlagHandle makeFlagHandle(u32 prefix, s32 idx) {
        return FlagHandle(idx | (prefix << 24));
    }

    /// Extracts a flag index out of a FlagHandle and passes it to the specified callable.
    /// fn must be callable with a u32 + TriggerParamRef&
    template <bool Write, bool BypassPerm, typename Fn>
    KSYS_ALWAYS_INLINE bool unwrapHandle(FlagHandle handle, const Fn& fn) {
        const u32 idx = static_cast<u32>(handle);
        auto& ref = BypassPerm ? getParamBypassPerm() : getParam();
        const auto check = [&] { return !Write || !ref.shouldChangeOnlyOnce(); };

        if (mBitFlags.isOff(BitFlag::_8000) && handle != InvalidHandle)
            return check() && fn(idx, ref);

        return idx >> 24 == mCurrentFlagHandlePrefix && check() && fn(idx & 0xFFFFFF, ref);
    }

    /// Extracts a flag index out of a FlagHandle and passes it to the specified callable.
    /// fn must be callable with a u32 + TriggerParamRef&
    template <bool Write, typename Fn>
    KSYS_ALWAYS_INLINE bool unwrapHandle(FlagHandle handle, bool debug, const Fn& fn) {
        return debug ? unwrapHandle<Write, true>(handle, fn) :
                       unwrapHandle<Write, false>(handle, fn);
    }

    void onChangedByDebug() {
        setBool(true, "IsChangedByDebug");
        mBitFlags.set(BitFlag::_800);
    }

    void loadGameData(const sead::SafeString& path);
    void loadShopGameDataInfo(const sead::SafeString& path);
    void unloadResources();

    void syncStart();
    void syncUpdate(const char* data);
    static void parseFloats(const sead::SafeString& str, f32* values, u32 n);
    static inline void recordFlagChange(u32 platform_core_id, TriggerParam* tparam, u8 type,
                                        const s32& idx, const s32& sub_idx = -1);

    template <typename T>
    void doSyncArray(const sead::PtrArray<FlagBase>& array, u8* buffer, const char* description);
    template <int N>
    void doSyncArrayStr(const sead::PtrArray<FlagBase>& array, u8* buffer, const char* description,
                        u32 n = N);
    template <typename T>
    void doSyncArrayVec(const sead::PtrArray<FlagBase>& array, u8* buffer, const char* description,
                        u32 n);

    template <typename T>
    void doSyncArray(const sead::PtrArray<sead::PtrArray<FlagBase>>& array, u8* buffer,
                     const char* description);
    template <int N>
    void doSyncArrayStr(const sead::PtrArray<sead::PtrArray<FlagBase>>& array, u8* buffer,
                        const char* description, u32 n = N);
    template <typename T>
    void doSyncArrayVec(const sead::PtrArray<sead::PtrArray<FlagBase>>& array, u8* buffer,
                        const char* description, u32 n);

    sead::Heap* mGameDataHeap = nullptr;
    sead::Heap* mSaveAreaHeap = nullptr;
    sead::Heap* mGameDataComHeap = nullptr;
    res::Handle mGameDataArcHandle;
    sead::SafeArray<res::Handle, 32> mBgdataHandles;
    sead::ArchiveFileDevice mGameDataArc{nullptr};

    res::Handle mShopGameDataInfoHandle;
    al::ByamlIter mShopAreaInfoValues;
    const u32* mShopAreaInfoHashes = nullptr;
    al::ByamlIter mShopSoldOutInfoValues;
    const u32* mShopSoldOutInfoHashes = nullptr;

    TriggerParamRef mParamBypassPerm{&mFlagBuffer1, &mFlagBuffer, false, false, false};
    TriggerParamRef mParam{&mFlagBuffer1, &mFlagBuffer, true, false, false};

    IncreaseLogger* mIncreaseLogger = nullptr;

    TriggerParam* mFlagBuffer1;
    TriggerParam* mFlagBuffer;
    TriggerParam* mRetryBuffer;
    TriggerParam* mGimmickResetBuffer;

    sead::TypedBitFlag<BitFlag> mBitFlags;
    sead::TypedBitFlag<ResetFlag> mResetFlags;
    u32 _c20 = 0;
    u32 mNumFlagsToReset = 0;
    u32 mCurrentFlagHandlePrefix = 0;

    ReinitSignal mReinitSignal;
    ResetSignal mResetSignal;

    MethodTreeNode mMethodTreeNode;

    void* mDelegate1 = nullptr;  // FIXME: figure out what this is
    sead::IDelegateR<const sead::SafeString&>* mGetMapNameDelegate = nullptr;

    sead::FixedSafeString<64> mStr;  // TODO: rename
    u32 mTrackerBlockSaveNumberFlagCrc32 = 0;
    u32 mSyncStep = 0;
    sead::Mutex mMutex;
};
KSYS_CHECK_SIZE_NX150(Manager, 0xdc8);

}  // namespace ksys::gdt
