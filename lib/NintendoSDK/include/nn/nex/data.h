/**
 * @file data.h
 * @brief NEX Data.
 */

#pragma once

#include <nn/nex/RootObject.h>

namespace nn {
namespace nex {
class Data : public nn::nex::RootObject {
public:
    Data();

    virtual ~Data();

    u8 _8;
};
};  // namespace nex
};  // namespace nn