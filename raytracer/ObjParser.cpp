#include "ObjParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

//Constructor
ObjParser::ObjParser(const std::string& filepath)
    : m_VertexBuffer{}
    , m_IndexBuffer{}
{
    //Calculate vertex and index buffers
    ParseObject(filepath);
}

//Get vertex buffer
std::vector<Elite::FPoint3> ObjParser::GetVertexBuffer()
{
    return m_VertexBuffer;
}

//Get index buffer
std::vector<int> ObjParser::GetIndexBuffer()
{
    return m_IndexBuffer;
}

//Parse object from filepath
void ObjParser::ParseObject(const std::string& filepath)
{
    //If the filepath doesn't exist and can't be opened, give an error
    std::ifstream in(filepath, std::ios::in);
    if (!in)
    {
        std::cout << "Error: can't open " << filepath << std::endl;
        exit(1);
    }
    //While reading the file
    std::string line;
    while (std::getline(in, line))
    {
        //Search for 'v' to find the vertices
        if (line.substr(0, 2) == "v ")
        {
            std::istringstream v(line.substr(2));
            float x, y, z;
            v >> x; v >> y; v >> z;
            Elite::FPoint3 vert{x, y, z};
            //Add vertices to their buffer
            m_VertexBuffer.push_back(vert);
        }
        //Search for 'f' to find the vertices
        else if (line.substr(0, 2) == "f ")
        {
            std::istringstream v(line.substr(2));
            int a{}, b{}, c{};
            v >> a; v >> b; v >> c;
            a--; b--; c--;
            //Add indexes to their buffer
            m_IndexBuffer.push_back(a);
            m_IndexBuffer.push_back(b);
            m_IndexBuffer.push_back(c);
        }
    }

    //Online parser help
    //https://github.com/smokindinesh/Modern-OpenGL-Series/blob/master/9_OBJLoader/src/Mesh.cpp
}