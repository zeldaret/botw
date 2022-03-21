#pragma once

#include <type_traits>

#include "basis/seadTypes.h"
#include "heap/seadDisposer.h"
#ifdef SEAD_DEBUG
#include "prim/seadStorageFor.h"
#endif

namespace sead
{
namespace hostio
{
class NodeEvent;
class PropertyEvent;

// These classes always exist (even in release builds, as can be seen in SMO's RTTI) but
// their functions are only defined in debug or develop builds.

class LifeCheckable
{
#ifdef SEAD_DEBUG
public:
    LifeCheckable()
    {
        mDisposer = mDisposerBuf.construct(this);
        initialize_();
    }

    LifeCheckable(Heap* disposer_heap, IDisposer::HeapNullOption option)
    {
        mDisposer = mDisposerBuf.construct(this, disposer_heap, option);
        initialize_();
    }

    virtual ~LifeCheckable()
    {
        DisposeHostIOCaller* disposer = mDisposer;
        if (disposer && disposer->hasInstance())
        {
            mDisposer->clearInstance();
            mDisposer->~DisposeHostIOCaller();
            disposeHostIOImpl_();
        }
        mDisposer = nullptr;
    }

    u32 getCreateID() const { return mCreateID; }
    static LifeCheckable* searchInstanceFromCreateID(u32 createID);

    LifeCheckable(const LifeCheckable&) = delete;
    LifeCheckable& operator=(const LifeCheckable&) = delete;

protected:
    virtual void disposeHostIO() { disposeHostIOImpl_(); }

private:
    class DisposeHostIOCaller : public IDisposer
    {
    public:
        explicit DisposeHostIOCaller(LifeCheckable* instance) : mInstance(instance) {}
        DisposeHostIOCaller(LifeCheckable* instance, Heap* disposer_heap, HeapNullOption option)
            : IDisposer(disposer_heap, option), mInstance(instance)
        {
        }

        ~DisposeHostIOCaller() override;

        bool hasInstance() const { return mInstance != nullptr; }
        void clearInstance() { mInstance = nullptr; }

    private:
        LifeCheckable* mInstance;
    };

    void initialize_();
    void disposeHostIOImpl_();

    u32 mCreateID = 0;
    LifeCheckable* mPrev = nullptr;
    LifeCheckable* mNext = nullptr;
    DisposeHostIOCaller* mDisposer = nullptr;
    StorageFor<DisposeHostIOCaller> mDisposerBuf;

    static u32 sCurrentCreateID;
    static LifeCheckable* sTopInstance;
#endif
};

class PropertyEventListener : public LifeCheckable
{
#ifdef SEAD_DEBUG
public:
    using LifeCheckable::LifeCheckable;

    virtual void listenPropertyEvent(const PropertyEvent* event) = 0;
#endif
};

class NodeEventListener : public PropertyEventListener
{
#ifdef SEAD_DEBUG
public:
    using PropertyEventListener::PropertyEventListener;

    void listenPropertyEvent([[maybe_unused]] const PropertyEvent* event) override {}
    virtual void listenNodeEvent([[maybe_unused]] const NodeEvent* event) {}
#endif
};
}  // namespace hostio
}  // namespace sead
