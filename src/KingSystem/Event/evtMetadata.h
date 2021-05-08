#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

class OrderParam;

class Metadata {
public:
    enum class Flag {
        _1 = 1,
        _2 = 2,
        _4 = 4,
        _8 = 8,
        _10 = 0x10,
        _20 = 0x20,
        _40 = 0x40,
        _80 = 0x80,
        _100 = 0x100,

        DefaultFlags = _4 | _20 | _40,
    };
    friend constexpr Flag operator|(Flag a, Flag b) { return Flag(u32(a) | u32(b)); }

    Metadata();
    Metadata(const char* event, const char* entry_point, const char* type = "");
    explicit Metadata(const char* event) : Metadata(event, event) {}
    virtual ~Metadata();

    Metadata(const Metadata& other) { *this = other; }
    Metadata& operator=(const Metadata& other);

    void init(const char* event, const char* entry_point, const char* type = "");
    void reset();

    act::Actor* getCurrentActor() const { return mCurrentActor; }
    void setCurrentActor(act::Actor* actor) { mCurrentActor = actor; }

    bool isSetNoDeleteCurrentActor() const { return mSetNoDeleteCurrentActor; }
    bool isSkipIsStartableAirCheck() const { return mSkipIsStartableAirCheck; }
    bool isForceNoChild() const { return mForceNoChild; }
    bool is13() const { return _13; }
    void* get18() const { return _18; }
    u32 get20() const { return _20; }
    int getEventStartWaitFrame() const { return mEventStartWaitFrame; }
    const sead::SafeString& getEventName() const { return mEventName; }
    const sead::SafeString& getEntryPointName() const { return mEntryPointName; }
    const sead::SafeString& getType() const { return mType; }
    const sead::TypedBitFlag<Flag>& getFlags() const { return mFlags; }
    OrderParam* getOrderParam() const { return mOrderParam; }
    bool isAsync() const { return mIsAsync; }

private:
    void initOrderParam_();
    void initFlags_();
    void doAssign_(const Metadata& other);

    act::Actor* mCurrentActor;
    bool mSetNoDeleteCurrentActor;
    bool mSkipIsStartableAirCheck;
    bool mForceNoChild;
    bool _13;
    void* _18;
    u32 _20;
    int mEventStartWaitFrame;
    sead::FixedSafeString<64> mEventName;
    sead::FixedSafeString<128> mEntryPointName;
    sead::FixedSafeString<16> mType;
    sead::TypedBitFlag<Flag> mFlags = Flag::DefaultFlags;
    OrderParam* mOrderParam{};
    bool mIsAsync;
};
KSYS_CHECK_SIZE_NX150(Metadata, 0x158);

}  // namespace ksys::evt
