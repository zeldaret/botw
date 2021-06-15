#pragma once

#include <basis/seadTypes.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace ksys::res {
class Demo;
}

namespace ksys::evt {

class DemoInfo {
public:
    struct NoEntryActors {
        enum Value : u8 {
            kDefault = 0,
            kAllPause = 1,
        };
        virtual ~NoEntryActors() = default;
        void set(const sead::SafeString& val);
        Value value = kDefault;
    };

    struct ProductFormat {
        enum Value {
            kRealTime = 0,
            kMovieFile = 1,
            kOther = 2,
        };
        virtual ~ProductFormat() = default;
        void set(const sead::SafeString& val);
        Value value = kOther;
    };

    struct Progress {
        enum Value {
            kInitialize = 0,
            kTemp = 1,
            kConte = 2,
            kAnimatics = 3,
            kProduct = 4,
            kOther = 5,
        };
        virtual ~Progress() = default;
        void set(const sead::SafeString& val);
        Value value = kOther;
    };

    struct SaveType {
        enum Value : u8 {
            kNoAutoSave = 0,
            kAutoSave = 1,
        };
        virtual ~SaveType() = default;
        void set(const sead::SafeString& val);
        Value value = kNoAutoSave;
    };

    struct StartType {
        enum Value {
            kSeamless = 0,
            kLoad = 1,
            kLoadNotWaitPlacement = 2,
            kOther = 3,
        };
        virtual ~StartType() = default;
        void set(const sead::SafeString& val);
        Value value = kOther;
    };

    struct Extension {
        enum Value {
            kEvfl = 0,
            kEvtm = 1,
            kOther = 2,
        };
        virtual ~Extension() = default;
        void set(const sead::SafeString& val);
        Value value = kOther;
    };

    struct EventMode {
        enum Value {
            kSeamless = 0,
            kLoad = 1,
            kFullPackage = 2,
            kContinue = 3,
            kOther = 4,
        };
        virtual ~EventMode() = default;
        void set(const sead::SafeString& val);
        Value value = kOther;
    };

    struct StartLocationType {
        enum Value {
            kStarter = 0,
            kStarterPositionOnly = 1,
            kPlayer = 2,
            kSetWorldPos = 3,
            kMapUnitStartPos = 4,
            kSearchSafetyPos = 5,
            kOther = 6,
        };
        virtual ~StartLocationType() = default;
        void set(const sead::SafeString& val);
        Value value = kOther;
    };

    struct TraverseType {
        enum Value {
            kDefault = 0,
            kSetPos = 1,
            kOther = 2,
        };
        virtual ~TraverseType() = default;
        void set(const sead::SafeString& val);
        Value value = kOther;
    };

    DemoInfo();
    virtual ~DemoInfo() = default;

    bool init(const res::Demo* resource);

    bool isValid() const { return mRes != nullptr; }

    const sead::Vector3f& getLocation() const;
    const sead::SafeString& getMapProjectName() const;
    float getTime() const;
    const sead::SafeString& getWeather() const;
    bool isStopChemical() const;
    bool isWithTransAnimation() const;
    float getStartLocationRotY() const;
    const sead::SafeString& getStartPosName() const;
    bool isForbidSkip() const;
    bool isSkipPolicyMoveLastFrame() const;
    const sead::SafeString& getDispName() const;
    bool isForceEnableIK() const;
    bool isUseNakedSound() const;
    const sead::SafeString& getWorldMuteType() const;
    const sead::Vector3f& getTraversePos() const;
    const sead::SafeString& getWaitLoadActorNames() const;
    float getTraverseLimit() const;

private:
    const res::Demo* mRes = nullptr;
    NoEntryActors mNoEntryActors;
    ProductFormat mProductFormat;
    Progress mProgress;
    SaveType mSaveType;
    StartType mStartType;
    Extension mExtension;
    EventMode mEventMode;
    StartLocationType mStartLocationType;
    TraverseType mTraverseType;
};

}  // namespace ksys::evt
