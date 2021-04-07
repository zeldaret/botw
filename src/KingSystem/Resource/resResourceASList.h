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

    struct CFDefine {
        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::ParameterObj pre_obj;
        sead::Buffer<void*> posts;
        agl::utl::ParameterList posts_list;
        sead::Buffer<void*> excepts;
        agl::utl::ParameterObj obj;
        agl::utl::ParameterList excepts_list;
    };
    KSYS_CHECK_SIZE_NX150(CFDefine, 0x138);

    struct AddRes {
        agl::utl::Parameter<sead::SafeString> _0;
        agl::utl::Parameter<sead::SafeString> _28;
        agl::utl::Parameter<bool> _50;
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
    sead::StorageFor<Common> mCommon{sead::ZeroInitializeTag{}};
};
KSYS_CHECK_SIZE_NX150(ASList, 0x410);

}  // namespace ksys::res
