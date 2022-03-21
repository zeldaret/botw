#ifndef SEAD_PATH_H_
#define SEAD_PATH_H_

#include <prim/seadSafeString.h>

namespace sead
{
class Path
{
public:
    static bool getDriveName(BufferedSafeString* drive_name, const SafeString& path);
    static void getPathExceptDrive(BufferedSafeString* out, const SafeString& path);
    static bool getExt(BufferedSafeString* ext, const SafeString& path);
    static bool getFileName(BufferedSafeString* name, const SafeString& path);
    static bool getBaseFileName(BufferedSafeString* name, const SafeString& path);
    static bool getDirectoryName(BufferedSafeString* name, const SafeString& path);
    static void join(BufferedSafeString* out, const char* path1, const char* path2);
    static void changeDelimiter(BufferedSafeString* out, char delimiter);
};
}  // namespace sead

#endif  // SEAD_PATH_H_
