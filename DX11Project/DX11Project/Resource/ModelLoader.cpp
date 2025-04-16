#include "ModelLoader.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include "Render/Vertex.h"
#include "Render/Mesh.h"

namespace SanDX {
    ModelLoader* ModelLoader::instance = nullptr;

    ModelLoader::ModelLoader()
    {
        if (instance) return;
        instance = this;
    }

    bool ModelLoader::Load(const std::string& name, std::weak_ptr<MeshData>& outData)
    {
        auto result = meshes.find(name);

        if (result != meshes.end()) {
            outData = result->second;
            return true;
        }
        char path[512] = {};
        sprintf_s(path, 512, "../Assets/Meshes/%s", name.c_str());

        FILE* file = nullptr;
        fopen_s(&file, path, "r");
        if (!file) __debugbreak();

        std::vector<Vector3> positions;
        std::vector<Vector2> texCoords;
        std::vector<Vector3> normals;
        std::vector<Vertex> vertices;

        char line[512] = {};

        while (!feof(file)) {
            if (!fgets(line, 512, file)) break;

            char header[3] = {};
            sscanf_s(line, "%s", header, 3);

            if (!strcmp(header, "v")) {
                Vector3 position;
                sscanf_s(line, "v %f %f %f", &position.x, &position.y, &position.z);
                positions.emplace_back(position);
            }

            else if (!strcmp(header, "vt")) {
                float x, y;
                sscanf_s(line, "vt %f %f", &x, &y);
                Vector2 texCoord(x, y);
                texCoords.emplace_back(texCoord);
            }

            else if (!strcmp(header, "vn")) {
                Vector3 normal;
                sscanf_s(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
                normals.emplace_back(normal);
            }

            else if (!strcmp(header, "f")) {
                int v1, v2, v3;
                int t1, t2, t3;
                int n1, n2, n3;
                sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &t1, &n1, &v2, &t2, &n2, &v3, &t3, &n3);
                vertices.emplace_back(positions[v1 - 1], Vector3::One, normals[n1 - 1], texCoords[t1 - 1]);
                vertices.emplace_back(positions[v2 - 1], Vector3::One, normals[n2 - 1], texCoords[t2 - 1]);
                vertices.emplace_back(positions[v3 - 1], Vector3::One, normals[n3 - 1], texCoords[t3 - 1]);
            }
        }

        fclose(file);

        std::vector<uint32> indices;
        indices.reserve(vertices.size());

        for (uint32 i = 0; i < (uint32)vertices.size(); ++i) {
            indices.emplace_back(i);
        }

        for (uint32 i = 0; i < (uint32)vertices.size(); i += 3) {
            Vertex& v0 = vertices[i];
            Vertex& v1 = vertices[i + 1];
            Vertex& v2 = vertices[i + 2];

            Vector3 edge1 = v1.position - v0.position;
            Vector3 edge2 = v2.position - v0.position;

            Vector2 deltaUV1 = v1.texCoord - v0.texCoord;
            Vector2 deltaUV2 = v2.texCoord - v0.texCoord;

            float denominator = 1.0f / (deltaUV1.GetX() * deltaUV2.GetY() - deltaUV2.GetX() * deltaUV1.GetY());

            Vector3 tangent = (edge1 * deltaUV2.GetY() - edge2 * deltaUV1.GetY()) * denominator;
            Vector3 binormal = (edge2 * deltaUV1.GetX() - edge1 * deltaUV2.GetX()) * denominator;

            v0.tangent += tangent;
            v1.tangent += tangent;
            v2.tangent += tangent;

            v0.bitangent += binormal;
            v1.bitangent += binormal;
            v2.bitangent += binormal;
        }

        for (auto& vertex : vertices)
        {
            vertex.tangent = (vertex.tangent - vertex.normal * Dot(vertex.normal, vertex.tangent)).Normalized();
            vertex.tangent = vertex.tangent.Normalized();
            vertex.bitangent = Cross(vertex.normal, vertex.tangent);
        }

        std::shared_ptr<MeshData> newData = std::make_shared<MeshData>(vertices, indices);
        meshes.insert(std::make_pair(name, newData));
        outData = newData;

        return true;
    }

    ModelLoader& ModelLoader::Get()
    {
        return *instance;
    }
}