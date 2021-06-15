#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include <prim/seadStorageFor.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class AS;

class ASList : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(ASList, Resource)
public:
    struct ASDefine {
        const char* getFileName() const { return file_name.ref().cstr(); }

        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<sead::SafeString> file_name;
        agl::utl::ParameterObj obj;
        AS* as;
    };
    KSYS_CHECK_SIZE_NX150(ASDefine, 0x88);

    struct CFPost {
        static int compare(const CFPost& o, const sead::SafeString& n);

        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<float> frame;
        agl::utl::Parameter<float> start_frame_rate;
        agl::utl::ParameterObj obj;
    };
    KSYS_CHECK_SIZE_NX150(CFPost, 0x98);

    struct CFExcept {
        static int compare(const CFExcept& o, const sead::SafeString& n);

        agl::utl::Parameter<sead::SafeString> name;
    };
    KSYS_CHECK_SIZE_NX150(CFExcept, 0x28);

    struct CFDefine {
        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::ParameterObj pre_obj;
        sead::Buffer<CFPost> posts;
        agl::utl::ParameterList posts_list;
        sead::Buffer<CFExcept> excepts;
        agl::utl::ParameterObj excepts_obj;
        agl::utl::ParameterList list;
    };
    KSYS_CHECK_SIZE_NX150(CFDefine, 0x138);

    struct AddRes {
        agl::utl::Parameter<sead::SafeString> anim;
        agl::utl::Parameter<sead::SafeString> retarget_model;
        agl::utl::Parameter<bool> retarget_no_correct;
        agl::utl::ParameterObj obj;
    };
    KSYS_CHECK_SIZE_NX150(AddRes, 0xa0);

    struct Common {
        agl::utl::Parameter<f32> rate_all;
        agl::utl::ParameterObj obj;
    };
    KSYS_CHECK_SIZE_NX150(Common, 0x50);

    ASList();
    ~ASList() override;

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    const sead::Buffer<ASDefine>& getASDefines() const { return mASDefines; }
    const sead::Buffer<CFDefine>& getCFDefines() const { return mCFDefines; }
    const sead::Buffer<AddRes>& getAddReses() const { return mAddReses; }
    const Common& getCommon() const { return mCommon.ref(); }

    void addAS_(s32 index, AS* as);

    const char* getASFileName(const sead::SafeString& name) const;
    int findASDefine(const sead::SafeString& name) const;
    int findCFDefine(const sead::SafeString& name) const;
    bool getCFDefineInfo(float* frame, float* key, const sead::SafeString& name,
                         const sead::SafeString& post_name, bool* is_default) const;

protected:
    bool finishParsing_() override;
    bool m7_() override;

private:
    u8 _2b0 = 0;
    u8 _2b1 = 0;
    u8 _2b2 = 0;
    u8 _2b3 = 0;
    sead::Buffer<ASDefine> mASDefines;
    sead::Buffer<CFDefine> mCFDefines;
    sead::Buffer<AddRes> mAddReses;
    agl::utl::ParameterList mCFDefinesList;
    agl::utl::ParameterList mASDefinesList;
    agl::utl::ParameterList mAddResesList;
    sead::StorageFor<Common, true> mCommon{sead::ZeroInitializeTag{}};
};
KSYS_CHECK_SIZE_NX150(ASList, 0x410);

}  // namespace ksys::res
