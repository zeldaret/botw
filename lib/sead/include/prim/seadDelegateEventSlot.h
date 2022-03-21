#pragma once

// DelegateEvent is used to implement a Qt-style signal/slot mechanism.

#include <container/seadTList.h>
#include <heap/seadDisposer.h>
#include <prim/seadDelegate.h>
#include <prim/seadStorageFor.h>

namespace sead
{
/// Manages signal and slots for an event.
template <typename T>
class DelegateEvent
{
public:
    class Slot;
    using SlotList = TList<Slot*>;
    using SlotListNode = TListNode<Slot*>;

    /// A Slot is a wrapper around a Delegate that is invoked when a signal is emitted.
    class Slot : public IDisposer
    {
    public:
        template <typename TDelegate>
        Slot(TDelegate delegate)  // NOLINT(google-explicit-constructor)
        {
            mDelegate.construct(std::move(delegate));
            // NOLINTNEXTLINE(cppcoreguidelines-prefer-member-initializer)
            mDelegatePtr = mDelegate->getDelegate();
        }

        template <typename C>
        Slot(C* instance, void (C::*func)(T)) : Slot(Delegate1<C, T>(instance, func))
        {
        }

        ~Slot() override { release(); }

        void release()
        {
            if (mConnectedToDelegateEvent)
            {
                mNode.erase();
                mConnectedToDelegateEvent = false;
            }
        }

    private:
        friend class DelegateEvent;

        void invoke_(T arg)
        {
            if (mDelegatePtr)
                (*mDelegatePtr)(arg);
        }

        SlotListNode mNode{this};
        IDelegate1<T>* mDelegatePtr = nullptr;
        StorageFor<AnyDelegate1<T>, true> mDelegate;
        bool mConnectedToDelegateEvent = false;
    };

    virtual ~DelegateEvent()
    {
        auto it = mList.begin();
        while (it != mList.end())
        {
            Slot* ptr = *it;
            ++it;
            ptr->release();
        }
    }

    void connect(Slot& slot)
    {
        slot.release();
        mList.pushBack(&slot.mNode);
        slot.mConnectedToDelegateEvent = true;
    }

    void disconnect(Slot& slot) { slot.release(); }

    void emit(T arg)
    {
        for (auto& slot_node : mList.robustRange())
            slot_node.mData->invoke_(arg);
    }

    int getNumSlots() const { return mList.size(); }

protected:
    SlotList mList;
};

}  // namespace sead
