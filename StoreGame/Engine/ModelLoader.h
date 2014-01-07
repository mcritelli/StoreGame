#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include "..\glm\glm.hpp"
#include "..\glm\gtx\string_cast.hpp"

using namespace std;

class ModelLoader{
public:
	static bool LoadOBJ(std::string, std::vector<glm::vec3>&, std::vector<glm::vec3>&);
};

#endif