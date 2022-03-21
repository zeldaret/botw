/**
 * @file reference.h
 * @brief Reference implementations for NEX.
 */
#pragma once

#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class RefCountedObject : public nn::nex::RootObject {
public:
    virtual ~RefCountedObject();

    u32 _8;
};
};  // namespace nex
};  // namespace nn