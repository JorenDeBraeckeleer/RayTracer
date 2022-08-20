#pragma once
#include "EMath.h"
#include <vector>
#include <string>

class ObjParser final
{
public:
	ObjParser(const std::string& filepath);
	//Rule of five
	~ObjParser() = default;
	ObjParser(const ObjParser& objParser) = delete;
	ObjParser(ObjParser&& objParser) = delete;
	ObjParser& operator=(const ObjParser& objParser) = delete;
	ObjParser& operator=(ObjParser&& objParser) = delete;

	//Functions
	std::vector<Elite::FPoint3> GetVertexBuffer();
	std::vector<int> GetIndexBuffer();

private:
	//Private functions
	void ParseObject(const std::string& filepath);

	//Variables
	std::vector<Elite::FPoint3> m_VertexBuffer;
	std::vector<int> m_IndexBuffer;
};