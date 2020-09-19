#pragma once

#include <container/seadBuffer.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamList : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(GParamList, Resource)
public:
    GParamList() : ParamIO("bgparamlist", 0) {}
    ~GParamList() override = default;

    bool ParamIO_m0() override { return false; }
    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;
    bool needsParse() const override { return true; }

protected:
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    void finalize_() override;

private:
    template <GParamListObjType Type>
    void add(const agl::utl::ResParameterList& list, const sead::SafeString& name, sead::Heap* heap,
             GParamList* dummy_list);

    sead::Buffer<GParamListObject*> mObjects;
};
KSYS_CHECK_SIZE_NX150(GParamList, 0x2c0);

class DummyGParamList : public GParamList {
    SEAD_RTTI_OVERRIDE(DummyGParamList, GParamList)
public:
    using GParamList::GParamList;
    ~DummyGParamList() override = default;

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;

private:
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
};

}  // namespace ksys::res
