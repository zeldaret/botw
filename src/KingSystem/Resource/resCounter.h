#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace sead {
class Heap;
}

namespace ksys::res {

class CounterBase {
public:
    class DataBase {
        SEAD_RTTI_BASE(DataBase)
    };

    class Data : public DataBase {
        SEAD_RTTI_OVERRIDE(Data, DataBase)
    public:
        explicit Data(void* data) : mData(data) {}
        virtual ~Data() = default;
        void* mData;
    };

    explicit CounterBase(sead::Heap* heap);
    virtual ~CounterBase();

    bool setData(const Data& data);

    void incrementRef();
    void decrementRef();

    void setFlag();
    void reset();
    bool isFlagSet() const;

private:
    virtual bool doSetData_(const Data& data) = 0;

    bool mFlag = true;
    sead::Atomic<s32> mRefCount;
};

class Counter : public CounterBase {
public:
    using CounterBase::CounterBase;
    ~Counter() override = default;

private:
    bool doSetData_(const Data& data) override;

    void* mData = nullptr;
};

}  // namespace ksys::res
