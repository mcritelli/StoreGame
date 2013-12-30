#include "BaseShader.h"
#define DEBUG false

// Default constructor
BaseShader::BaseShader(void)
{
}

// Copy constructor
BaseShader::BaseShader(const BaseShader& other)
{

}

// Destructor
BaseShader::~BaseShader(void)
{
}

bool BaseShader::InitializeShader(std::string vs, std::string fs, std::vector<string> params)
{

	// Load shader source
	if (DEBUG) std::cout << "vs: " << vs << "\n";
	if (DEBUG) std::cout << "fs: " << fs << "\n";
	std::string filename;
	filename = "Shaders\\";
	filename = filename + vs;
	
	if (DEBUG) std::cout << "filename: " << filename << "\n";
	
	m_vsSource = LoadSourceFile(filename.c_str());
	if (!m_vsSource)
	{
		if (DEBUG) std::cout << "VS FILE FAILED TO LOAD\n";
		return false;
	}
	if (DEBUG) std::cout << "m_vsSource: \n\n" << m_vsSource << "\n";

	filename = "Shaders\\" + fs;
	m_fsSource = LoadSourceFile(filename.c_str());
	if (!m_fsSource)
	{
		if (DEBUG) std::cout << "FS FILE FAILED TO LOAD\n";
		return false;
	}

	if (DEBUG) std::cout << "m_fsSource:\n\n" << m_fsSource << "\n";

	// Create shaders
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &m_vsSource, NULL);
	glCompileShader(vshader);
	
	// Make sure the VS compiled correctly
	if (!checkCompileStatus("Vertex", vshader))
		return false;

	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &m_fsSource, NULL);
	glCompileShader(fshader);

	// Make sure the FS compiled correctly
	if (!checkCompileStatus("Fragment", fshader))
		return false;

	// Create program w/ shaders
	m_program = glCreateProgram();
	glAttachShader(m_program, vshader);
	glAttachShader(m_program, fshader);
	glLinkProgram(m_program);

	// Check status
	GLint programStatus;
	glGetProgramiv(m_program, GL_LINK_STATUS, &programStatus);
	
	if (programStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(m_program, infoLogLength, NULL, strInfoLog);
		std::cout << "Program failed to link:\n" << strInfoLog << "\n";
		delete[] strInfoLog;
		return false;
	}

	// If the program linked correctly, we can detach & delete the shaders
	glDetachShader(m_program, vshader);
	glDeleteShader(vshader);
	glDetachShader(m_program, fshader);
	glDeleteShader(fshader);


	return true;
}

bool BaseShader::checkCompileStatus(std::string shaderType, GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char* strShaderType = NULL;

		std::cout << shaderType << " shader failed to compile:\n" << strInfoLog << "\n";
		delete[] strInfoLog;
		return false;
	}
	
	return true;
}


char* BaseShader::LoadSourceFile(const char* src)
{
	ifstream fin;
	int fileSize;
	char input;
	char* buffer;

	// Open file
	fin.open(src);

	// Check to make sure the file actually opened
	if (fin.fail())
		return 0;

	fileSize = 0;
	fin.get(input);

	while (!fin.eof())
	{
		fileSize++;
		fin.get(input);
	}

	fin.close();

	// Initialize the buffer that we're going to read the source into
	buffer = new char[fileSize+1];
	if (!buffer)
		return 0;

	fin.open(src);
	fin.read(buffer, fileSize);
	fin.close();
	
	// Null-terminate the buffer
	buffer[fileSize] = '\0';

	return buffer;
}