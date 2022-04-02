#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterIO.h>
#include <agl/utl/aglParameterList.h>
#include <agl/utl/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <resource/seadResource.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {

class MusicDefinition : public sead::DirectResource, public agl::utl::IParameterIO {
    SEAD_RTTI_OVERRIDE(MusicDefinition, sead::DirectResource)

public:
    struct MusicDefine {
        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<sead::SafeString> category;
        agl::utl::Parameter<float> volume;
        agl::utl::Parameter<bool> is_enable_weather_filter;
        agl::utl::Parameter<bool> is_indoor_ducking;
        bool is_event_bgm;
        agl::utl::ParameterObj param_obj;
    };
    struct CategoryDefine {
        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<u32> priority_value;
        agl::utl::ParameterObj param_obj;
    };

    void doCreate_(u8* data, u32 file_size, sead::Heap* heap) override;
    int getMusicIndexByName(const sead::SafeString& name) const;
    const sead::SafeString& getMusicCategoryByName(const sead::SafeString& name) const;
    int getPriorityValueByCategoryName(const sead::SafeString& name) const;

private:
    sead::Buffer<MusicDefine> mMusicDefines;
    agl::utl::ParameterList mMusicList;
    int mEventBgmCount = 0;
    sead::Buffer<CategoryDefine> mCategoryDefines;
    agl::utl::ParameterList mCategoryList;
};
KSYS_CHECK_SIZE_NX150(MusicDefinition, 0x2A8);

}  // namespace ksys::snd
