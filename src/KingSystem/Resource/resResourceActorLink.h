#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class ActorLink : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(ActorLink, Resource)
public:
    struct Users {
        agl::utl::Parameter<sead::SafeString> profile;
        agl::utl::Parameter<sead::SafeString> actor_capture;
        agl::utl::Parameter<sead::SafeString> as;
        agl::utl::Parameter<sead::SafeString> model;
        agl::utl::Parameter<sead::SafeString> anim;
        agl::utl::Parameter<sead::SafeString> ai_program;
        agl::utl::Parameter<sead::SafeString> gparam;
        agl::utl::Parameter<sead::SafeString> damage_param;
        agl::utl::Parameter<sead::SafeString> rg_config_list;
        agl::utl::Parameter<sead::SafeString> rg_blend_weight;
        agl::utl::Parameter<sead::SafeString> awareness;
        agl::utl::Parameter<sead::SafeString> physics;
        agl::utl::Parameter<sead::SafeString> chemical;
        agl::utl::Parameter<sead::SafeString> attention;
        agl::utl::Parameter<sead::SafeString> elink;
        agl::utl::Parameter<sead::SafeString> slink;
        agl::utl::Parameter<sead::SafeString> xlink;
        agl::utl::Parameter<sead::SafeString> drop_table;
        agl::utl::Parameter<sead::SafeString> shop_data;
        agl::utl::Parameter<sead::SafeString> recipe;
        agl::utl::Parameter<sead::SafeString> lod;
        agl::utl::Parameter<sead::SafeString> bone_control;
        agl::utl::Parameter<sead::SafeString> ai_schedule;
        agl::utl::Parameter<sead::SafeString> life_condition;
        agl::utl::Parameter<sead::SafeString> umii;
        agl::utl::Parameter<sead::SafeString> animation_info;
        agl::utl::ParameterObj obj;
    };

    ActorLink();

    void doCreate_(u8*, u32, sead::Heap*) override {}
    bool needsParse() const override { return true; }

    const Users& getUsers() const { return mUsers; }
    const sead::SafeString& getActorNameJpn() const { return mActorNameJpn.ref(); }
    const sead::SafeString& getPriority() const { return mPriority.ref(); }
    f32 getActorScale() const { return mActorScale.ref(); }

    bool hasTag(const char* tag_name) const;
    bool hasTag(act::Tag tag) const;

    const sead::Buffer<u32>& getTags() const { return mTags; }

private:
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    void m5_() override;

    Users mUsers;
    agl::utl::Parameter<sead::SafeString> mActorNameJpn;
    agl::utl::Parameter<sead::SafeString> mPriority;
    agl::utl::Parameter<f32> mActorScale;
    sead::Buffer<u32> mTags;
    sead::Heap* mHeap = nullptr;
};
KSYS_CHECK_SIZE_NX150(ActorLink, 0x778);

}  // namespace ksys::res
