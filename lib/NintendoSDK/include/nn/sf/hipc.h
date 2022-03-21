#pragma once

#include <nn/svc.h>

namespace nn::sf::hipc {
void* GetMessageBufferOnTls();

Result InitializeHipcServiceResolution();
Result ConnectToHipcService(svc::Handle*, const char*);
Result FinalizeHipcServiceResolution();

Result SendSyncRequest(svc::Handle, void*, u64);
Result CloseClientSessionHandle(svc::Handle);

}  // namespace nn::sf::hipc
