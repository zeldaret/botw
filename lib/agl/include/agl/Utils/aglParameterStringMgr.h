#pragma once

#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>

namespace agl::utl {

class ParameterStringMgr : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(ParameterStringMgr)
    ParameterStringMgr();
    virtual ~ParameterStringMgr();

public:
    void initialize(sead::Heap* heap);
    const char* appendString(const sead::SafeString& string);

#ifdef SEAD_DEBUG
    void listenPropertyEvent(const sead::hostio::PropertyEvent* event) override;
    void genMessage(sead::hostio::Context* context) override;
#endif

private:
    sead::Heap* mHeap = nullptr;
    sead::PtrArray<sead::SafeString> mStrings;
    sead::CriticalSection mCS;
};

}  // namespace agl::utl
