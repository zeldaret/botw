#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectTraveler : public GParamListObject {
public:
    struct RoutePoint {
        RoutePoint();

        template <s32 I>
        KSYS_VISIBILITY_HIDDEN void initParameters_(agl::utl::ParameterObj* obj);

        struct DirectionInfo {
            template <s32 From, s32 To>
            KSYS_VISIBILITY_HIDDEN void initParameters_(agl::utl::ParameterObj* obj);

            agl::utl::Parameter<sead::SafeString> mEntryPoint;
            agl::utl::Parameter<f32> mWaitFrame;
            agl::utl::Parameter<sead::SafeString> mSchedule;
            agl::utl::Parameter<sead::SafeString> mMoveAS;
            agl::utl::Parameter<sead::SafeString> mWaitAS;
        };

        agl::utl::Parameter<sead::SafeString> mName;
        // i to i+1
        DirectionInfo mForward;
        // i+1 to i
        DirectionInfo mBackward;
    };
    static constexpr size_t NumRoutePoints = 29;

    GParamListObjectTraveler();
    const char* getName() const override { return "Traveler"; }

    agl::utl::Parameter<sead::SafeString> mAppearGameDataName;
    agl::utl::Parameter<sead::SafeString> mDeleteGameDataName;
    agl::utl::Parameter<sead::SafeString> mRouteType;
    agl::utl::Parameter<sead::SafeString> mRideHorseName;
    agl::utl::Parameter<bool> mIsLeadHorse;
    agl::utl::Parameter<s32> mHorseGearLevel;

    struct RoutePoints {
        RoutePoints();
        auto& operator[](s32 i) { return reinterpret_cast<RoutePoint&>(mStorage[i]); }
        auto& operator[](s32 i) const { return reinterpret_cast<const RoutePoint&>(mStorage[i]); }
        auto data() { return reinterpret_cast<RoutePoint*>(&mStorage[0]); }

    private:
        std::aligned_storage_t<sizeof(RoutePoint), alignof(RoutePoint)> mStorage[NumRoutePoints];
    };
    RoutePoints mRoutePoints;
    agl::utl::Parameter<sead::SafeString> mRoutePoint29Name;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectTraveler, 0x3148);

}  // namespace ksys::res
