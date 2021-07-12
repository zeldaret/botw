#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <resource/seadResource.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::snd {

static sead::SafeString str_EventBgm = "EventBgm";

class MusicDefinition : public sead::DirectResource, public agl::utl::IParameterIO {
    SEAD_RTTI_OVERRIDE(MusicDefinition, sead::DirectResource)

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

public:
    void doCreate_(u8* data, u32 file_size, sead::Heap* heap) override;
    int getMusicIndexByName(const sead::SafeString& name);
    const sead::SafeString& getMusicCategoryByName(const sead::SafeString& name);
    int getPriorityValueByCategoryName(const sead::SafeString& name);

private:
    sead::Buffer<MusicDefine> mMusicBuffer;
    agl::utl::ParameterList mMusicList;
    int mEventBgmCount;
    sead::Buffer<CategoryDefine> mCategoryBuffer;
    agl::utl::ParameterList mCategoryList;
};
KSYS_CHECK_SIZE_NX150(MusicDefinition, 0x2A8);

}  // namespace ksys::snd