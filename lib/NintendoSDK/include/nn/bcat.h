/**
 * @file bcat.h
 * @brief BCAT service implementation.
 */

#pragma once

#include <nn/os.h>
#include <nn/types.h>

namespace nn {

namespace bcat {

struct DirectoryName {
    void isValid();
};

struct FileName {
    void isValid();
};

class DeliveryCacheDirectory {
public:
    DeliveryCacheDirectory();
    ~DeliveryCacheDirectory();
    Result Open(nn::bcat::DirectoryName const&);
    Result GetCount();
    Result Close();
};

class DeliveryCacheFile {
public:
    DeliveryCacheFile();
    ~DeliveryCacheFile();
    Result Open(nn::bcat::DirectoryName const&, nn::bcat::FileName const&);
    Result Read(size_t file1, s64, void*, size_t file2);
    Result GetSize();
    Result GetDigest();
    Result Close();
};

class DeliveryCacheProgress {
public:
    DeliveryCacheProgress();
    ~DeliveryCacheProgress();
    Result Detach();
    Result Update();
    Result GetStatus();
    Result GetCurrentDirectoryName();
    Result GetCurrentFileName();
    Result GetCurrentDownloaded();
    Result GetCurrentTotale();
    Result GetWholeDownloaded();
    Result GetWholeTotal();
    Result GetResult();
    // void Attach(nn::bcat::detail::ipc::IDeliveryCacheProgressService*);
};

namespace detail {

namespace DeliveryCacheProgressImpl {
Result Clear();
Result NotifyStartConnect();
Result NotifyStartProcessList();
Result SetWholeDownloadSize(s64);
Result SetDownloadProgress(s64, nn::bcat::DirectoryName const&, nn::bcat::FileName const&, s64);
Result NotifyStartDownloadFile(nn::bcat::DirectoryName const&, nn::bcat::FileName const&, s64);
Result UpdateDownloadFileProgress(s64);
Result NotifyStartCommitDirectory(nn::bcat::DirectoryName const&);
Result NotifyDone(nn::Result);

}  // namespace DeliveryCacheProgressImpl
class ShimLibraryGlobal {
public:
    ShimLibraryGlobal();
    ~ShimLibraryGlobal();
    Result Initialize();
    Result GetSession();
    Result MountDeliveryCacheStorage();
    Result IsDeliveryCacheStorageMounted();
    Result UnmountDeliveryCacheStorage();
    // void CreateFileService(nn::bcat::detail::ipc::IDeliveryCacheFileService**);
    // void CreateDirectoryService(nn::bcat::detail::ipc::IDeliveryCacheDirectoryService**)
    Result IncrementDeliveryCacheFileCount();
    Result DecrementDeliveryCacheFileCount();
    Result IncrementDeliveryCacheDirectoryCount();
    Result DecrementDeliveryCacheFileCount();
    Result EnumerateDeliveryCacheDirectory(int*, nn::bcat::DirectoryName*, int);
};

namespace ipc {
Result Initialize();
// void CreateBcatService(nn::bcat::detail::ipc::IBcatService**);
Result Finalize();
// void CreateBcatService(nn::bcat::detail::ipc::IBcatService**);
// void CreateDeliveryCacheStorageService(nn::bcat::detail::ipc::IDeliveryCacheStorageService**);
// void CreateDeliveryCacheStorageService(nn::bcat::detail::ipc::IDeliveryCacheStorageService**,
// nn::ApplicationId);

}  // namespace ipc
}  // namespace detail

Result Initialize();
Result MountDeliveryCacheStorage();
Result UnmountDeliveryCacheStorage();
Result EnumerateDeliveryCacheDirectory(int*, nn::bcat::DirectoryName*, int);
Result RequestSyncDeliveryCache(nn::bcat::DeliveryCacheProgress*);
Result EnumerateDeliveryCacheDirectory(int*, nn::bcat::DirectoryName*, int);

}  // namespace bcat
}  // namespace nn