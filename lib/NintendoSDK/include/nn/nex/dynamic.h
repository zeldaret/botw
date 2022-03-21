/**
 * @file dynamic.h
 * @brief NEX Dyamnic Runtime.
 */

#pragma once

#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class DynamicRunTimeInterface : public nn::nex::RootObject {
public:
    DynamicRunTimeInterface();

    virtual ~DynamicRunTimeInterface();

    u64* GetInstance();
};
};  // namespace nex
};  // namespace nn