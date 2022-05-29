#ifndef COPY_EDIT_KYS_CONFIG_H
#define COPY_EDIT_KYS_CONFIG_H

#include "fileSystem/fileSystem.h"

struct AppLogFiles;

enum{FS_COPY_CREATED, FS_COPY_EXIST, FS_COPY_ERROR, FS_COPY_MAX};

namespace copyFs{

unsigned fileWithLogNoErase(AppLogFiles& logs, const fs::path& srcFilePath, const fs::path& destFilePath);

void directoriesRecursively(AppLogFiles& logs, const fs::path& srcPath, const fs::path& destPath);

}
#endif //COPY_EDIT_KYS_CONFIG_H