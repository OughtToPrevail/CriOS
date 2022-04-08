#include "Resources.h"

#define ASSIGN_RESOURCE(type, file_name, extension) \
    extern unsigned char _binary_resources_files_##file_name##_##extension##_start; \
    type Resources::file_name(&_binary_resources_files_##file_name##_##extension##_start); \

ASSIGN_RESOURCE(OSImage, thisisfine, osfile)
ASSIGN_RESOURCE(OSImage, MouseCursor, osfile)
ASSIGN_RESOURCE(OSImage, Notepad, osfile)
ASSIGN_RESOURCE(OSImage, NotepadSmall, osfile)
ASSIGN_RESOURCE(PCFFont, ProggyCleanSZ, pcf)

const PCFFont& Resources::DEFAULT_FONT = ProggyCleanSZ;