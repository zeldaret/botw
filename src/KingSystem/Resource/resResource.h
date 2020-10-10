#pragma once

#include <resource/seadResource.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class IResource {
public:
    virtual ~IResource() = default;
};

class Context {
public:
    virtual ~Context() = default;
};

class Resource : public sead::DirectResource, public IResource {
    SEAD_RTTI_OVERRIDE(Resource, sead::DirectResource)
public:
    Resource();

    void doCreate_(u8* buffer, u32 bufferSize, sead::Heap* heap) override;

    virtual bool needsParse() const { return false; }
    virtual bool m2_() { return true; }

    Context* getContext() const;
    void setContext(Context* context);

    void onDestroy();
    bool parse(Context*, sead::Heap* heap);
    bool finalize();
    bool finishParsing(Context* context);
    bool m7();

    static constexpr size_t cLoadDataAlignment = 4;

protected:
    virtual void onDestroy_() {}
    virtual bool parse_(u8* data, size_t size, sead::Heap* heap);
    virtual void finalize_() {}
    virtual bool finishParsing_() { return true; }
    virtual bool m7_() { return true; }
    virtual void m8_() {}

    u32 mAllocSize = 0;
    Context* mContext = nullptr;
};
KSYS_CHECK_SIZE_NX150(Resource, 0x38);

inline void Resource::doCreate_(u8*, u32, sead::Heap*) {}

inline bool Resource::parse_(u8*, size_t, sead::Heap*) {
    return true;
}

}  // namespace ksys::res
