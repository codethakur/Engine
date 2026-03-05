#include "render/Mesh.h"
#include "graphics/GraphicsAPI.h"
#include "Engine.h"


namespace eng
{
    Mesh::Mesh(const VertexLayout &layout, const std::vector<float> &vertices, const std::vector<uint32_t> indices)
    {
        m_vertexLayout = layout;
        auto &graphicsAPI = Engine::GetInstance().GetGraphicsAPI();

        m_VBO = graphicsAPI.CreateVertexBuffer(vertices);
        m_EBO = graphicsAPI.CreateIndexBuffer(indices);

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        for (auto &element : m_vertexLayout.elements)
        {
            glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, m_vertexLayout.stride, (void *)(uintptr_t)element.offset);
            glEnableVertexAttribArray(element.index);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        m_vertexCount = (vertices.size() * sizeof(float)) / m_vertexLayout.stride;
        m_indexCount = indices.size();
    }
    Mesh::Mesh(const VertexLayout &layout, const std::vector<float> &vertices)
    {
        m_vertexLayout = layout;
        auto &graphicsAPI = Engine::GetInstance().GetGraphicsAPI();

        m_VBO = graphicsAPI.CreateVertexBuffer(vertices);

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        for (auto &element : m_vertexLayout.elements)
        {
            glVertexAttribPointer(element.index, element.size, element.type, GL_FALSE, m_vertexLayout.stride, (void *)(uintptr_t)element.offset);
            glEnableVertexAttribArray(element.index);
        }

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        m_vertexCount = (vertices.size() * sizeof(float)) / m_vertexLayout.stride;
    }

    void Mesh::Bind()
    {
        glBindVertexArray(m_VAO);
    }
    void  Mesh::Unbind()
    {
       glBindVertexArray(0);
    }
    void Mesh::Draw()
    {

        if (m_indexCount > 0)
        {
            glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei> (m_vertexCount));
        }
    }
    std::shared_ptr<Mesh> Mesh::CreateBox(const glm::vec3& extents)
    {
        const glm::vec3 half = extents * 0.5f;
        std::vector<float> vertices =
        {
            // Front face
            half.x, half.y, half.z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -half.x, half.y, half.z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            -half.x, -half.y, half.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            half.x, -half.y, half.z, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

            // Top face 
            half.x, half.y, -half.z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -half.x, half.y, -half.z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -half.x, half.y, half.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            half.x, half.y, half.z, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

            // Right face
            half.x, half.y, -half.z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            half.x, half.y, half.z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            half.x, -half.y, half.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            half.x, -half.y, -half.z, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

            // Left face
            -half.x, half.y, half.z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -half.x, half.y, -half.z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -half.x, -half.y, -half.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            -half.x, -half.y, half.z, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

            // Bottom face
            half.x, -half.y, half.z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
            -half.x, -half.y, half.z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
            -half.x, -half.y, -half.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
            half.x, -half.y, -half.z, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

            // Back face
            -half.x, half.y, -half.z, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            half.x, half.y, -half.z, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
            half.x, -half.y, -half.z, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
            -half.x, -half.y, -half.z, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f
        };

        std::vector<unsigned int> indices =
        {
            // front
            0, 1, 2,
            0, 2, 3,

            // top
            4, 5, 6,
            4, 6, 7,

            // right
            8, 9, 10,
            8, 10, 11,

            // left
            12, 13, 14,
            12, 14, 15,

            // bottom
            16, 17, 18,
            16, 18, 19,

            // back
            20, 21, 22,
            20, 22, 23
        };
        eng::VertexLayout vertexLayout;

        // Postion
        vertexLayout.elements.push_back({
            VertexElement::PositionIndex,
            3, 
            GL_FLOAT,
            0
            });
        // Color
        vertexLayout.elements.push_back({
            VertexElement::ColorIndex,
            3,
            GL_FLOAT,
            sizeof(float) * 3
            });
        //uv
        vertexLayout.elements.push_back({
            VertexElement::UVIndex,
            2,
            GL_FLOAT,
            sizeof(float) * 6,

        });
        //normal
        vertexLayout.elements.push_back({
            VertexElement::NormalIndex,
            3,
            GL_FLOAT,
            sizeof(float) * 8,

        });
        vertexLayout.stride = sizeof(float) * 11; 

        auto result = std::make_shared<eng::Mesh>(vertexLayout, vertices, indices);
        return result;

    }
    std::shared_ptr<Mesh> Mesh::CreateSphere(float radius, int sectors, int stacks)
    {
        const float PI = 3.14159265358979323846f;

        std::vector<float> vertices((stacks + 1) * (sectors + 1) * 8);
        for (int i = 0; i <= stacks; ++i)
        {
            float stackAngle = PI / 2.0f - static_cast<float>(i) * (PI / static_cast<float>(stacks)); // From -π/2 to π/2
            float xy = radius * cosf(stackAngle); // x-y plane radius at this stack
            float z = radius * sinf(stackAngle);  // z coordinate

            for (int j = 0; j <= sectors; ++j) {
                float sectorAngle = static_cast<float>(j) * (2.0f * PI / static_cast<float>(sectors)); // From 0 to 2π

                float x = xy * cosf(sectorAngle);
                float y = xy * sinf(sectorAngle);

                size_t vertexStart = (i * (sectors + 1) + j) * 8;
                // Position
                vertices[vertexStart] = x;
                vertices[vertexStart + 1] = y;
                vertices[vertexStart + 2] = z;

                // Normal (normalized position vector)
                float length = sqrtf(x * x + y * y + z * z);
                vertices[vertexStart + 3] = x / length;
                vertices[vertexStart + 4] = y / length;
                vertices[vertexStart + 5] = z / length;

                // UV coordinates
                vertices[vertexStart + 6] = static_cast<float>(j) / static_cast<float>(sectors);
                vertices[vertexStart + 7] = static_cast<float>(i) / static_cast<float>(stacks);
            }
        }

        // Generate indices
        std::vector<unsigned int> indices;
        for (int i = 0; i < stacks; ++i)
        {
            int k1 = i * (sectors + 1);
            int k2 = k1 + sectors + 1;

            for (int j = 0; j < sectors; ++j, ++k1, ++k2)
            {
                if (i != 0)
                {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);
                }

                if (i != (stacks - 1))
                {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);
                }
            }
        }

        eng::VertexLayout vertexLayout;

        // Postion
        vertexLayout.elements.push_back({
            VertexElement::PositionIndex,
            3,
            GL_FLOAT,
            0
            });
        // Normal
        vertexLayout.elements.push_back({
            VertexElement::NormalIndex,
            3,
            GL_FLOAT,
            sizeof(float) * 3
            });
        // UV
        vertexLayout.elements.push_back({
            VertexElement::UVIndex,
            2,
            GL_FLOAT,
            sizeof(float) * 6
            });
        vertexLayout.stride = sizeof(float) * 8;

        auto result = std::make_shared<eng::Mesh>(vertexLayout, vertices, indices);

        return result;
    }
    #if 0
    std::shared_ptr<Mesh> Mesh::Load(const std::string &path)
    {
        auto contents = Engine::GetInstance().GetFileSystem().LoadAssetFileText(path);

        if (contents.empty())
        {
            return nullptr;
        }
        auto readFloat = [](const cgltf_accessor *acc, cgltf_size i, float *out, int n)
        {
            std::fill(out, out + n, 0.0f);
            return cgltf_accessor_read_float(acc, i, out, n) == 1;
        };
        auto readIndex = [](const cgltf_accessor *acc, cgltf_size i)
        {
            cgltf_uint out = 0;
            cgltf_bool ok = cgltf_accessor_read_uint(acc, i, &out, 1);
            return ok ? static_cast<uint32_t>(out) : 0;
        };
        cgltf_options options = {};
        cgltf_data *data = nullptr;
        cgltf_result res = cgltf_parse(&options, contents.data(), contents.size(), &data);
        if (res != cgltf_result_success)
        {
            //cgltf_free(data);
            return nullptr;
        }
        auto fullPath = Engine::GetInstance().GetFileSystem().GetAssetFolder() / path;

        res = cgltf_load_buffers(&options, data, fullPath.remove_filename().string().c_str());
        if (res != cgltf_result_success)
        {
            cgltf_free(data);
            return nullptr;
        }
        std::shared_ptr<Mesh> result = nullptr;
        for (cgltf_size meshIndex = 0; meshIndex < data->meshes_count; ++meshIndex)
        {
            auto &mesh = data->meshes[meshIndex];
            for (cgltf_size primitiveIndex = 0; primitiveIndex < mesh.primitives_count; ++primitiveIndex)
            {
                auto &primitive = mesh.primitives[primitiveIndex];
                if (primitive.type != cgltf_primitive_type_triangles)
                {
                    continue;
                }
                VertexLayout vertexLayout;
                cgltf_accessor *accessors[4] = {nullptr, nullptr, nullptr};

                for (cgltf_size attributIndex = 0; attributIndex < primitive.attributes_count; ++attributIndex)
                {
                    auto &attr = primitive.attributes[attributIndex];
                    auto acc = attr.data;
                    if (!acc)
                    {
                        continue;
                    }
                    VertexElement element;
                    element.type = GL_FLOAT;
                    switch (attr.type)
                    {
                    case cgltf_attribute_type_position:
                    {
                        accessors[VertexElement::PositionIndex] = acc;
                        element.index = VertexElement::PositionIndex;
                        
                        element.size = 3;
                    }
                    break;
                    case cgltf_attribute_type_color:
                    {
                        if (attr.index != 0)
                        {
                            continue;
                        }
                        accessors[VertexElement::ColorIndex] = acc;
                        element.index = VertexElement::ColorIndex;
                        element.size = 3;
                    }
                    break;
                    case cgltf_attribute_type_texcoord:
                    {
                        if (attr.index != 0)
                        {
                            continue;
                        }
                        accessors[VertexElement::UVIndex] = acc;
                        element.index = VertexElement::UVIndex;
                        element.size = 2;
                    }
                    break;
                    case cgltf_attribute_type_normal:
                    {
                        accessors[VertexElement::NormalIndex] = acc;
                        element.index = VertexElement::NormalIndex;
                        element.size = 3;
                    }
                    break;
                    default:
                        continue;
                    }

                    if (element.size > 0)
                    {
                        element.offset = vertexLayout.stride;
                        vertexLayout.stride += element.size * sizeof(float);
                        vertexLayout.elements.push_back(element);
                    }
                }

                if (!accessors[VertexElement::PositionIndex])
                {
                    continue;
                }

                auto vertexCount = accessors[VertexElement::PositionIndex]->count;
                std::vector<float> vertices;
                vertices.resize(vertexLayout.stride / sizeof(float) * vertexCount);

                for (cgltf_size vertexIndex = 0; vertexIndex < vertexCount; ++vertexIndex)
                {
                    for (auto &element : vertexLayout.elements)
                    {
                        if (!accessors[element.index])
                        {
                            continue;
                        }
                        auto index = (vertexIndex * vertexLayout.stride + element.offset) / sizeof(float);
                        float *outData = &vertices[index];
                        readFloat(accessors[element.index], vertexIndex, outData, element.size);
                    }
                }
                if(primitive.indices)
                {
                    auto indexCount = primitive.indices->count;
                    std::vector<uint32_t> indices(indexCount);
                    for(cgltf_size i = 0; i<indexCount; ++i)
                    {
                        indices[i] = readIndex(primitive.indices, i);
                    }
                    result = std::make_shared<Mesh>(vertexLayout, vertices, indices); 
                }
                else
                {
                    result = std::make_shared<Mesh>(vertexLayout, vertices);
                }
                if(result)
                {
                    break;
                }
            }
            if(result)
            {
                break;
            }
        }
        cgltf_free(data);
        return result;
    }
    #endif
}