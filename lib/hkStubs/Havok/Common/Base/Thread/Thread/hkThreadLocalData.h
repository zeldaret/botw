#pragma once

#include <nn/os.h>

template <typename T>
class hkThreadLocalData {
public:
    hkThreadLocalData() { nn::os::AllocateTlsSlot(&m_tls_slot, nullptr); }
    ~hkThreadLocalData() { nn::os::FreeTlsSlot(m_tls_slot); }

    T getData() const { return reinterpret_cast<T>(nn::os::GetTlsValue(m_tls_slot)); }
    void setData(T p) { nn::os::SetTlsValue(m_tls_slot, reinterpret_cast<unsigned long>(p)); }

private:
    nn::os::TlsSlot m_tls_slot{};
};

#define HK_THREAD_LOCAL(TYPE) hkThreadLocalData<TYPE>
#define HK_THREAD_LOCAL_SET(var, value) var.setData(value)
#define HK_THREAD_LOCAL_GET(var) var.getData()
