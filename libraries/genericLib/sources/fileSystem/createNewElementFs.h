#ifndef CREATE_DIRECTORY_FS_H
#define CREATE_DIRECTORY_FS_H

#include "fileSystem/fileSystem.h"

namespace createFs{

enum{FsNewCreated, FsNewExists, FsNewError, FsNewMax};

unsigned mkDirectoryIfMissing(const fs::path& baseDir, const fs::path& newDir);

unsigned mkNewFileIfMissing(const fs::path& fileDirectory, const fs::path& fileName);

unsigned mkNewFileIfMissing(const fs::path& fileFullPath);

}

#endif //CREATE_DIRECTORY_FS_H