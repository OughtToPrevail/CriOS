#include <iostream>
#include <fstream>
#include <dirent.h>
#include <cstring>
#include <vector>

int main(int argsCount, char** args)
{
	if(argsCount < 2)
	{
		std::cout << "Missing path argument" << std::endl;
		return 1;
	}
	char* path = args[1];
	std::cout << "Creating initrd..." << std::endl;

	std::ofstream initrd("fs.initrd", std::fstream::binary);

	DIR* dir = opendir(path);
	struct dirent* dirFile;
	std::vector<std::string> fileNames;
	while((dirFile = readdir(dir)) != nullptr)
	{
		if(strcmp(dirFile->d_name, ".") == 0 || strcmp(dirFile->d_name, "..") == 0)
		{
			continue;
		}
		fileNames.emplace_back(dirFile->d_name);
	}
	closedir(dir);

	std::cout << "Found files (" << fileNames.size() << ")" << std::endl;
	unsigned int size = fileNames.size();
	initrd.write((char*) &size, sizeof(unsigned int));
	for(const std::string& name : fileNames)
	{
		std::ifstream file(std::string(path) + name, std::ios::binary | std::ios::ate);
		size = file.tellg();
		initrd.write((char*) &size, sizeof(unsigned int));
		std::cout << "Writing file: " << name << " (size: " << file.tellg() << ")" << std::endl;
		initrd << name;
		initrd.write("\0", 1);
		file.seekg(0, std::ios::beg);
		initrd << file.rdbuf();
	}

	initrd.close();

	return 0;
}
