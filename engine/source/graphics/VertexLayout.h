#pragma once
#include <glad/glad.h>
#include<vector>
#include<stdint.h>

namespace eng
{
    struct VertexElement
    {
        GLuint index;
        GLuint size; // no of componets
        GLuint type; // data types
       uint32_t offset;
    };
    struct VertexLayout
    {
        std::vector<VertexElement>elements;
        uint32_t stride = 0;//total size of single vertex
    };
    
}