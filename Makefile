current_directory = $(shell pwd)

local_assembly_files := $(shell find -name *.asm -not -path "./cmake-build-debug/*")
assembly_files := $(patsubst ./%, $(current_directory)/%, $(local_assembly_files))
assembly_obj_files := $(patsubst ./%.asm, $(current_directory)/output/%.o, $(local_assembly_files))

local_cpp_files := $(shell find -name *.cpp -path "./src/*")
cpp_files := $(patsubst ./%, $(current_directory)/%, $(local_cpp_files))
cpp_obj_files := $(patsubst ./%.cpp, $(current_directory)/output/%.o, $(local_cpp_files))

include_directories := $(addprefix -I, $(dir $(cpp_files)))  # -I flag for adding include directories

local_resource_files := $(shell find -not -name *.osfile -path "./resources/files/*")
local_image_resources_files = $(shell ls resources/images)
resource_obj_files := $(patsubst ./resources/files/%, $(current_directory)/output/resources/%.o, $(local_resource_files)) $(patsubst %.tga, $(current_directory)/output/resources/%.osfile.o, $(local_image_resources_files))

converter = resources/converter/Converter.exe

linker_file =  $(current_directory)/Linker.ld

iso_directory = $(current_directory)/output/iso
# Not sure if this boot and boot/grub directories are necessary but seem to be everywhere
boot_directory = $(iso_directory)/boot
os_elf_file = $(boot_directory)/os.elf
output_grub_cfg = $(boot_directory)/grub/grub.cfg
output_fs = $(boot_directory)/fs.initrd
run_graphics = "GRAPHICS"
run_text = "TEXT"
run_mode = $(run_text)
$(current_directory)/output/src/cpp/%.o: flags = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -fno-exceptions -fno-rtti -c -D $(run_mode)

output:
	mkdir -p output

$(current_directory)/output/src/asm/%.o: $(current_directory)/src/asm/%.asm
    # compiles assembly into object files
	mkdir -p $(dir $@)
	nasm -f elf32 $^ -o $@

$(current_directory)/output/src/cpp/%.o: $(current_directory)/src/cpp/%.cpp
	# Compiles C++ files one by one into object file, -g to preserve debugger info
	mkdir -p $(dir $@)
	if test $(findstring Interrupt, $^); then \
		g++ $(flags) $(include_directories) -mgeneral-regs-only $^ -o $@; \
	else \
		g++ $(flags) $(include_directories) $^ -o $@; \
	fi

$(converter):
	cp src/cpp/drivers/graphics/VGAColor.h resources/converter/
	cp src/cpp/drivers/graphics/VGAColor.cpp resources/converter/
	cp src/cpp/drivers/graphics/ColorPalette.h resources/converter/
	cp src/cpp/drivers/graphics/ColorPalette.cpp resources/converter/
	cp src/cpp/utilities/Math.h resources/converter/
	cp src/cpp/utilities/Math.cpp resources/converter/

	g++ -o $(converter) $(shell find -name *.cpp -path "./resources/converter/*")

resources/files/%.osfile: resources/images/%.tga $(converter)
	$(converter) $(firstword $^) $@

$(current_directory)/output/resources/%.o: resources/files/%
	# Turns all resources into object files
	mkdir -p $(dir $@)
	ld -melf_i386 -r -b binary -o $@ $^

resources/initrd/fs.initrd: resources/initrd/initrdfiles/
	cd resources/initrd; \
	./Initrd $(realpath .)/resources/initrd/initrdfiles/

os.elf: $(assembly_obj_files) $(cpp_obj_files) $(resource_obj_files) resources/initrd/fs.initrd
    # Generates kernel elf file
	mkdir -p $(boot_directory)/grub
	cp grub.cfg $(output_grub_cfg)
	cp resources/initrd/fs.initrd $(output_fs)
	ld -T $(linker_file) -melf_i386 $(assembly_obj_files) $(cpp_obj_files) $(resource_obj_files) -o $(os_elf_file)

kerneliso: os.elf
    # Creates an iso file from the kernel.elf
	grub-mkrescue -o output/OS.iso $(iso_directory)

all: kerneliso

emulate: export SDL_VIDEO_X11_DGAMOUSE=0
emulate_debug: export SDL_VIDEO_X11_DGAMOUSE=0

emulate: kerneliso
    # Emulates the ISO file https://wiki.osdev.org/QEMU
	qemu-system-i386 -cdrom output/OS.iso -no-shutdown -no-reboot -serial stdio

emulate_debug: kerneliso
    # Important commands: "display/i $pc" to show assembly and "stepi"/"nexti" to move in assembly
	qemu-system-i386 -cdrom output/OS.iso -no-shutdown -no-reboot -serial stdio -s -S

clean:
	rm -r output
