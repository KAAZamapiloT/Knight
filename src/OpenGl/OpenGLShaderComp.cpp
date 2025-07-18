#include "OpenGLShaderComp.hpp"
//#include"glad/glad.h"
#include"fstream"

namespace KnightEngine {
	static GLenum ShaderTypeFromString(std::string& type) {
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment"||type=="pixel") return GL_FRAGMENT_SHADER;
		KE_TAG_ASSERT("shader types",true, "UNKOWN SHADER TYPE {} REACHED END ", type);
		return 0;
		
	}
}
OpenGLShaderComp::OpenGLShaderComp(const std::string& vertexSource, const std::string& fragmentSource)
{

	 std::unordered_map<GLenum, std::string> ShaderSources;
	ShaderSources[GL_VERTEX_SHADER] = vertexSource;
	ShaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
	Compile(ShaderSources);
}

OpenGLShaderComp::OpenGLShaderComp(const std::string& filepath)
{
	std::string ShaderSource=ReadFile(filepath);
	auto ShaderSources = Preprocess(ShaderSource);
	Compile(ShaderSources);
	
}

OpenGLShaderComp::~OpenGLShaderComp()
{
}

void OpenGLShaderComp::Bind() const
{
	glUseProgram(m_RendererID);
}

void OpenGLShaderComp::Unbind() const
{
	glUseProgram(0);
}

void OpenGLShaderComp::UploadUniformMat4(const std::string& name, const glm::mat4 Matrix)
{
	GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(Matrix));
}

void OpenGLShaderComp::UploadUniformMat3(const std::string& name, const glm::mat3 Matrix)
{
}

void OpenGLShaderComp::UploadUniformfloat4(const std::string& name, const glm::vec4 col)
{
	GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform4f(Location, col.x, col.y, col.z, col.w);
}

void OpenGLShaderComp::UploadUniformfloat3(const std::string& name, const glm::vec3 col)
{
	GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform3f(Location, col.x, col.y, col.z);
}

void OpenGLShaderComp::UploadUniformfloat2(const std::string& name, const glm::vec2 col)
{
	GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform2f(Location, col.x, col.y);
}



void OpenGLShaderComp::UploadUniformint(const std::string& name, const int col)
{
	GLint Location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1i(Location,col);
	
}

void OpenGLShaderComp::Compile(const std::unordered_map<GLenum, std::string>& ShaderSources)
{
	GLuint program = glCreateProgram();
	std::vector<GLuint> shaderIDs; // Changed from GLenum to GLuint and better naming
	shaderIDs.reserve(ShaderSources.size()); // Reserve space instead of sizing

	// Compile all shaders
	for (const auto& [shaderType, source] : ShaderSources) { // Structured binding for cleaner code
		GLuint shader = glCreateShader(shaderType);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, nullptr);
		glCompileShader(shader);

		// Check compilation status
		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

			// Log the compilation error
			KE_TAG_LOG_CRITICAL("Shader", "Shader compilation failed: {}",
				std::string(infoLog.begin(), infoLog.end()));

			// Clean up
			glDeleteShader(shader);
			// Clean up any previously compiled shaders
			for (GLuint id : shaderIDs) {
				glDeleteShader(id);
			}
			glDeleteProgram(program);
			return;
		}

		glAttachShader(program, shader);
		shaderIDs.push_back(shader);
	}

	// Link the program
	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());

		KE_TAG_LOG_CRITICAL("Shader", "Shader linking failed: {}",
			std::string(infoLog.begin(), infoLog.end()));

		// Clean up everything
		for (GLuint id : shaderIDs) {
			glDeleteShader(id);
		}
		glDeleteProgram(program);
		return;
	}

	// Success! Clean up shader objects (they're now part of the program)
	for (GLuint id : shaderIDs) {
		glDetachShader(program, id);
		glDeleteShader(id);
	}

	m_RendererID = program;
}

std::unordered_map<GLenum, std::string> OpenGLShaderComp::Preprocess(const std::string& shaderString)
{
	std::unordered_map<GLenum, std::string> shaderSources;
	const char* typeToken = "#type";
	const size_t typeTokenLength = strlen(typeToken);

	size_t pos = shaderString.find(typeToken, 0);
	while (pos != std::string::npos) {
		// Find end of line (handle different line ending types)
		size_t eol = shaderString.find_first_of("\r\n", pos);
		KE_CORE_ASSERT(eol != std::string::npos, "Syntax error: #type directive without newline");

		// Extract and trim the shader type
		size_t begin = pos + typeTokenLength;
		// Skip whitespace after #type
		begin = shaderString.find_first_not_of(" \t", begin);
		KE_CORE_ASSERT(begin != std::string::npos && begin < eol, "No shader type specified after #type");

		std::string type = shaderString.substr(begin, eol - begin);
		// Trim trailing whitespace
		size_t end = type.find_last_not_of(" \t\r\n");
		if (end != std::string::npos) {
			type = type.substr(0, end + 1);
		}

		// Validate shader type
		GLenum shaderType = KnightEngine::ShaderTypeFromString(type);

		KE_CORE_ASSERT(shaderType!=0, "Invalid shader type: " , type);

		// Find start of next line (skip all line ending characters)
		size_t nextLinePos = shaderString.find_first_not_of("\r\n", eol);
		if (nextLinePos == std::string::npos) {
			KE_TAG_LOG_WARN("Shader", "Empty shader section for type: {}", type);
			break;
		}

		// Find next #type directive
		size_t nextPos = shaderString.find(typeToken, nextLinePos);

		// Extract shader source
		std::string shaderSource;
		if (nextPos == std::string::npos) {
			// This is the last shader section
			shaderSource = shaderString.substr(nextLinePos);
		}
		else {
			shaderSource = shaderString.substr(nextLinePos, nextPos - nextLinePos);
		}

		// Trim trailing whitespace from shader source
		while (!shaderSource.empty() && std::isspace(shaderSource.back())) {
			shaderSource.pop_back();
		}

		KE_CORE_ASSERT(!shaderSource.empty(), "Empty shader source for type:{} " ,type);
		shaderSources[shaderType] = std::move(shaderSource);

		pos = nextPos;
	}

	KE_CORE_ASSERT(!shaderSources.empty(), "No shader sections found in file");
	return shaderSources;
}

std::string OpenGLShaderComp::ReadFile(const std::string& filepath) {
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if (!in) {
		KE_TAG_LOG_CRITICAL("OPENGL:ShaderComp", "Failed to open file: {}", filepath);
		return {};
	}

	in.seekg(0, std::ios::end);
	size_t size = static_cast<size_t>(in.tellg());
	in.seekg(0, std::ios::beg);

	std::string content;
	content.resize(size);
	in.read(&content[0], size);

	// strip UTF-8 BOM
	if (content.size() >= 3 &&
		static_cast<unsigned char>(content[0]) == 0xEF &&
		static_cast<unsigned char>(content[1]) == 0xBB &&
		static_cast<unsigned char>(content[2]) == 0xBF) {
		content.erase(0, 3);
	}
	return content;
}