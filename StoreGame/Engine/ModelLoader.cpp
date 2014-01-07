#include "ModelLoader.h"


bool ModelLoader::LoadOBJ(std::string f, std::vector<glm::vec3> &out_vertexData, std::vector<glm::vec3> &out_normalData)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> vertexData, normalData;
	std::vector<glm::vec2> uvData;

	// Assume that all models are in the /Models folder
	std::string filename = "Models\\" + f;

	FILE* file;
	errno_t e = fopen_s(&file, filename.c_str(), "r");
	
	if (e != 0)
	{
		std::cout << "FILE FAILED TO LOAD: " << filename << "\n";
		return false;
	}

	while (true)
	{
		char lineHeader[512];
		int res = fscanf_s(file, "%s", lineHeader);
		
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertexData.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uvData.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normalData.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int vertexIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%i//%i %i//%i %i//%i\n", 
				&vertexIndex[0], &normalIndex[0],
				&vertexIndex[1], &normalIndex[1], 
				&vertexIndex[2], &normalIndex[2]);
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

			//delete[] vertexIndex;
			//delete[] normalIndex;

			//std::cout << "MATCHES: " << matches << "\n";
			//std::cout << vertexIndex[0] << "//" << normalIndex[0] << " " << vertexIndex[1] << "//" << normalIndex[1] << " " << vertexIndex[2] << "//" << normalIndex[2] << "\n";
		}

	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = vertexData[vertexIndex - 1];
		out_vertexData.push_back(vertex);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = normalData[normalIndex - 1];
		out_normalData.push_back(normal);
	}

	/*std::cout << "MODEL VERTICES: \n";
	for (std::vector<glm::vec3>::iterator it = vertexData.begin(); it != vertexData.end(); ++it)
	{
		std::cout << glm::to_string(*it) << "\n";
	}*/

	// Model loaded correctly
	return true;
}