/**
 * @file nifm.h
 * @brief Network inferface module.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace nifm {
Result Initialize();
void SetLocalNetworkMode(bool);
void SubmitNetworkRequestAndWait();
bool IsNetworkAvailable();
Result HandleNetworkRequestResult();
void SubmitNetworkRequest();
bool IsNetworkRequestOnHold();
Result GetCurrentPrimaryIpAddress(u64* inAddr);
};  // namespace nifm
};  // namespace nn