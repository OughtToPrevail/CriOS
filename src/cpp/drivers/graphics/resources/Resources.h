#ifndef OSTEST_RESOURCES_H
#define OSTEST_RESOURCES_H

#include "OSImage.h"
#include "PCFFont.h"

#define DECLARE_RESOURCE(type, file_name) static type file_name;

class Resources
{
public:
	DECLARE_RESOURCE(OSImage, thisisfine)
	DECLARE_RESOURCE(OSImage, MouseCursor)
	DECLARE_RESOURCE(OSImage, Notepad)
	DECLARE_RESOURCE(OSImage, NotepadSmall)
	DECLARE_RESOURCE(PCFFont, ProggyCleanSZ)

	static const PCFFont& DEFAULT_FONT;
};

#endif //OSTEST_RESOURCES_H
