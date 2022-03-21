#include <filedevice/seadMainFileDevice.h>
#include <prim/seadSafeString.h>

#ifdef cafe
#include <filedevice/cafe/seadCafeFSAFileDeviceCafe.h>
#elif defined(NNSDK)
#include <filedevice/nin/seadNinContentFileDeviceNin.h>
#endif

namespace sead
{
MainFileDevice::MainFileDevice(Heap* heap) : FileDevice("main"), mFileDevice(nullptr)
{
#ifdef cafe
    mFileDevice = new (heap, 4) CafeContentFileDevice();
#elif defined(NNSDK)
    mFileDevice = new (heap, 8) NinContentFileDevice();
#else
#error "Unknown platform"
#endif
    SEAD_ASSERT(mFileDevice);
}

MainFileDevice::~MainFileDevice()
{
    if (mFileDevice == NULL)
        return;

    delete mFileDevice;
    mFileDevice = NULL;
}

void MainFileDevice::traceFilePath(const SafeString& path) const
{
    mFileDevice->traceFilePath(path);
}

void MainFileDevice::traceDirectoryPath(const SafeString& path) const
{
    mFileDevice->traceDirectoryPath(path);
}

void MainFileDevice::resolveFilePath(BufferedSafeString* out, const SafeString& path) const
{
    mFileDevice->resolveFilePath(out, path);
}

void MainFileDevice::resolveDirectoryPath(BufferedSafeString* out, const SafeString& path) const
{
    mFileDevice->resolveDirectoryPath(out, path);
}
}  // namespace sead
