#ifndef INIT_WINDOW_AND_RENDERER_H
#define INIT_WINDOW_AND_RENDERER_H

#include <string>

struct AppLogFiles;
class PrefPathFinder;

namespace cntxt{

namespace windRend{
	void create(AppLogFiles& logs, const PrefPathFinder& prefPath, const std::string& chosenLang);
}

}

#endif //INIT_WINDOW_AND_RENDERER_H