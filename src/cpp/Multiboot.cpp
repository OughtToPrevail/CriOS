#include "Multiboot.h"

ModuleEntry MultibootUtility::getModule(Multiboot* multiboot, unsigned int index)
{
	return *((ModuleEntry*) (multiboot->mods_addr + index * sizeof(ModuleEntry)));
}
