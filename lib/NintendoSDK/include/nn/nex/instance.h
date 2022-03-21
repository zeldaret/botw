/**
 * @file instance.h
 * @brief NEX Instance Controllers.
 */
#pragma once

#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class InstanceTable;

class InstanceControl : public nn::nex::RootObject {
public:
    InstanceControl(u32, u32);

    u32 mInstanceContext;     // _8
    u32 mInstanceType;        // _C
    void* mDelegateInstance;  // _10
    bool mIsValidControl;     // _18
    u8 _19;                   // probably padding
    u8 _1A;
    u8 _1B;

    static nn::nex::InstanceTable* s_oInstanceTable;
};

class InstanceTable : public nn::nex::RootObject {
public:
    InstanceTable();

    virtual ~InstanceTable();

    bool AddInstance(nn::nex::InstanceControl*, u32, u32);
    void DelInstance(nn::nex::InstanceControl*, u32, u32);
    u32 CreateContext();
    bool DeleteContext(u32);
    void AllocateExtraContexts(u64 size);
    void FreeExtraContexts();
    u32 GetHighestID() const;
    u32 FindInstanceContext(nn::nex::InstanceControl*, u32);

    u8 _0[0x94];
};
};  // namespace nex
};  // namespace nn