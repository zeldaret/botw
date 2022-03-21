#ifndef SEAD_DISPOSER_H_
#define SEAD_DISPOSER_H_

#include <basis/seadNew.h>
#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>
#include <container/seadListImpl.h>

namespace sead
{
class Heap;

class IDisposer
{
public:
    enum class HeapNullOption
    {
        // disposer_heap must not be nullptr for this option.
        AlwaysUseSpecifiedHeap = 0,
        UseSpecifiedOrContainHeap = 1,
        DoNotAppendDisposerIfNoHeapSpecified = 2,
        UseSpecifiedOrCurrentHeap = 3,
    };

    IDisposer();
    explicit IDisposer(Heap* disposer_heap,
                       HeapNullOption option = HeapNullOption::UseSpecifiedOrCurrentHeap);
    virtual ~IDisposer();

    static u32 getListNodeOffset() { return offsetof(IDisposer, mListNode); }

protected:
    Heap* getDisposerHeap_() const { return mDisposerHeap; }

private:
    friend class Heap;

    Heap* mDisposerHeap;
    ListNode mListNode;
};

}  // namespace sead

#define SEAD_INSTANCE(CLASS) (CLASS::instance())

#define SEAD_SINGLETON_DISPOSER(CLASS)                                                             \
public:                                                                                            \
    class SingletonDisposer_ : public sead::IDisposer                                              \
    {                                                                                              \
    public:                                                                                        \
        using sead::IDisposer::IDisposer;                                                          \
        virtual ~SingletonDisposer_();                                                             \
                                                                                                   \
        static SingletonDisposer_* sStaticDisposer;                                                \
    };                                                                                             \
                                                                                                   \
    static CLASS* instance() { return sInstance; }                                                 \
    static CLASS* createInstance(sead::Heap* heap);                                                \
    static void deleteInstance();                                                                  \
                                                                                                   \
    CLASS(const CLASS&) = delete;                                                                  \
    CLASS& operator=(const CLASS&) = delete;                                                       \
    CLASS(CLASS&&) = delete;                                                                       \
    CLASS& operator=(CLASS&&) = delete;                                                            \
                                                                                                   \
protected:                                                                                         \
    static CLASS* sInstance;                                                                       \
                                                                                                   \
    friend class SingletonDisposer_;                                                               \
                                                                                                   \
    /* FIXME: this should just use std::aligned_storage_t with a proper alignment value. */        \
    u32 mSingletonDisposerBuf_[sizeof(SingletonDisposer_) / sizeof(u32)];

#define SEAD_CREATE_SINGLETON_INSTANCE(CLASS)                                                      \
    CLASS* CLASS::createInstance(sead::Heap* heap)                                                 \
    {                                                                                              \
        if (!sInstance)                                                                            \
        {                                                                                          \
            auto* buffer = new (heap, alignof(CLASS)) u8[sizeof(CLASS)];                           \
            SEAD_ASSERT_MSG(!SingletonDisposer_::sStaticDisposer, "Create Singleton Twice (%s).",  \
                            #CLASS);                                                               \
            auto* disposer_buffer = buffer + offsetof(CLASS, mSingletonDisposerBuf_);              \
                                                                                                   \
            /* FIXME: do this after creating the instance to ensure the disposer is not clobbered  \
             * by CLASS's constructor */                                                           \
            SingletonDisposer_::sStaticDisposer = new (disposer_buffer) SingletonDisposer_(heap);  \
            /* Note: When compiling as C++03 (or a newer standard), this must not be `new CLASS()` \
             * as that will value initialize (C++17 [dcl.init]/11), which eventually leads to zero \
             * initialisation when CLASS has no user-provided constructor (C++17 [dcl.init]/8).    \
             * This is dangerous because the singleton disposer would get clobbered.               \
             */                                                                                    \
            sInstance = new (buffer) CLASS;                                                        \
        }                                                                                          \
        else                                                                                       \
        {                                                                                          \
            SEAD_ASSERT_MSG(false, "Create Singleton Twice (%s) : addr %p", #CLASS, sInstance);    \
        }                                                                                          \
                                                                                                   \
        return CLASS::sInstance;                                                                   \
    }

#define SEAD_DELETE_SINGLETON_INSTANCE(CLASS)                                                      \
    void CLASS::deleteInstance()                                                                   \
    {                                                                                              \
        SingletonDisposer_* staticDisposer = SingletonDisposer_::sStaticDisposer;                  \
        if (SingletonDisposer_::sStaticDisposer != NULL)                                           \
        {                                                                                          \
            SingletonDisposer_::sStaticDisposer = NULL;                                            \
            staticDisposer->~SingletonDisposer_();                                                 \
                                                                                                   \
            delete sInstance;                                                                      \
                                                                                                   \
            sInstance = NULL;                                                                      \
        }                                                                                          \
    }

#define SEAD_SINGLETON_DISPOSER_IMPL(CLASS)                                                        \
    CLASS::SingletonDisposer_::~SingletonDisposer_()                                               \
    {                                                                                              \
        if (this == sStaticDisposer)                                                               \
        {                                                                                          \
            sStaticDisposer = nullptr;                                                             \
            CLASS::sInstance->~CLASS();                                                            \
            CLASS::sInstance = nullptr;                                                            \
        }                                                                                          \
    }                                                                                              \
    SEAD_CREATE_SINGLETON_INSTANCE(CLASS)                                                          \
    SEAD_DELETE_SINGLETON_INSTANCE(CLASS)                                                          \
    CLASS* CLASS::sInstance = NULL;                                                                \
    CLASS::SingletonDisposer_* CLASS::SingletonDisposer_::sStaticDisposer = NULL;

#endif  // SEAD_DISPOSER_H_
