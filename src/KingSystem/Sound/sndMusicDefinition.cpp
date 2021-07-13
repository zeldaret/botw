#include "KingSystem/Sound/sndMusicDefinition.h"

namespace ksys::snd {

static sead::SafeString str_EventBgm = "EventBgm";

void MusicDefinition::doCreate_(u8* data, u32 file_size, sead::Heap* heap) {
    auto archive = agl::utl::ResParameterArchive(data);
    auto root_list = archive.getRootList();

    auto MusicDefines = agl::utl::getResParameterList(root_list, "MusicDefines");
    if (MusicDefines) {
        s32 num_music_defines = MusicDefines.getResParameterObjNum();
        if (num_music_defines == 0) {
            return;
        }
        mMusicDefines.allocBufferAssert(num_music_defines, heap);

        for (auto it = mMusicDefines.begin(), end = mMusicDefines.end(); it != end; ++it) {
            auto param_obj = &it->param_obj;
            it->name.init("", "Name", "", param_obj);
            it->category.init("", "Category", "", param_obj);
            it->volume.init(1, "Volume", "", param_obj);
            it->is_enable_weather_filter.init(false, "IsEnableWeatherFilter", "", param_obj);
            it->is_indoor_ducking.init(false, "IsIndoorDucking", "", param_obj);

            mMusicList.addObj(param_obj,
                              sead::FormatFixedSafeString<32>("MusicDefine_%d", it.getIndex()));
        }

        addList(&mMusicList, "MusicDefines");
    }

    auto CategoryDefines = agl::utl::getResParameterList(root_list, "CategoryDefines");
    if (CategoryDefines) {
        s32 num_category_defines = CategoryDefines.getResParameterObjNum();
        if (num_category_defines == 0)
            return;
        mCategoryDefines.allocBufferAssert(num_category_defines, heap);

        for (auto it = mCategoryDefines.begin(), end = mCategoryDefines.end(); it != end; ++it) {
            it->name.init("", "Name", "", &it->param_obj);
            it->priority_value.init(0, "PriorityValue", "", &it->param_obj);

            mCategoryList.addObj(&it->param_obj, sead::FormatFixedSafeString<32>(
                                                     "CategoryDefine_%d", it.getIndex()));
        }

        addList(&mCategoryList, "CategoryDefines");
    }

    if (data)
        applyResParameterArchive(agl::utl::ResParameterArchive(data));

    for (auto& music : mMusicDefines) {
        if (music.category.ref() == str_EventBgm) {
            music.is_event_bgm = true;
            mEventBgmCount++;
        } else {
            music.is_event_bgm = false;
        }
    }
}

int MusicDefinition::getMusicIndexByName(const sead::SafeString& name) const {
    for (int i = 0; i < mMusicDefines.size(); i++) {
        if (mMusicDefines.get(i)->name.ref() == name) {
            return i;
        }
    }
    return -1;
}

const sead::SafeString&
MusicDefinition::getMusicCategoryByName(const sead::SafeString& name) const {
    for (int i = 0; i < mMusicDefines.size(); i++) {
        if (mMusicDefines.get(i)->name.ref() == name) {
            return mMusicDefines.get(i)->category.ref();
        }
    }
    return sead::SafeString::cEmptyString;
}

int MusicDefinition::getPriorityValueByCategoryName(const sead::SafeString& name) const {
    for (int i = 0; i < mCategoryDefines.size(); i++) {
        auto element = mCategoryDefines.get(i);
        if (element->name.ref() == name) {
            return element->priority_value.ref();
        }
    }
    return 0;
}

}  // namespace ksys::snd
