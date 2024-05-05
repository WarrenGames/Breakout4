#ifndef COPY_EDIT_KYS_CONFIG_H
#define COPY_EDIT_KYS_CONFIG_H

#include "fileSystem/fileSystem.h"

struct AppLogFiles;

namespace copyFs{

enum{FsCopyCreated, FsCopyExists, FsCopyError, FsCopyMax};

unsigned fileWithLogNoErase(AppLogFiles& logs, const fs::path& srcFilePath, const fs::path& destFilePath);

void directoriesRecursively(AppLogFiles& logs, const fs::path& srcPath, const fs::path& destPath);

}
#endif //COPY_EDIT_KYS_CONFIG_H