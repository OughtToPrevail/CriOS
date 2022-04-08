#ifndef CRIOS_MULTIBOOT_H
#define CRIOS_MULTIBOOT_H


// taken from https://www.gnu.org/software/grub/manual/multiboot/multiboot.html , http://www.jamesmolloy.co.uk/tutorial_html/8.-The%20VFS%20and%20the%20initrd.html
struct Multiboot
{
	unsigned int flags;
	unsigned int mem_lower;
	unsigned int mem_upper;
	unsigned int boot_device;
	unsigned int cmdline;
	unsigned int mods_count;
	unsigned int mods_addr;
	unsigned int num;
	unsigned int size;
	unsigned int addr;
	unsigned int shndx;
	unsigned int mmap_length;
	unsigned int mmap_addr;
	unsigned int drives_length;
	unsigned int drives_addr;
	unsigned int config_table;
	unsigned int boot_loader_name;
	unsigned int apm_table;
	unsigned int vbe_control_info;
	unsigned int vbe_mode_info;
	unsigned int vbe_mode;
	unsigned int vbe_interface_seg;
	unsigned int vbe_interface_off;
	unsigned int vbe_interface_len;
}  __attribute__((packed));

struct ModuleEntry
{
	unsigned int startAddress;
	unsigned int endAddress;
};

class MultibootUtility
{
public:
	static ModuleEntry getModule(Multiboot* multiboot, unsigned int index);
};

#endif //CRIOS_MULTIBOOT_H
