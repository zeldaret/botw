#pragma once

#include "KingSystem/Chemical/chmRoot.h"
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"

namespace ksys::res {

class Chemical : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(Chemical, Resource)

public:
    Chemical();

    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;

    const chm::Root& getRoot() const { return mRoot; }

private:
    chm::Root mRoot;
};

}  // namespace ksys::res
