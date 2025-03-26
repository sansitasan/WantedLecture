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
                vertices.emplace_back(positions[v1 - 1], Vector3::One, texCoords[t1 - 1], normals[n1 - 1]);
                vertices.emplace_back(positions[v2 - 1], Vector3::One, texCoords[t2 - 1], normals[n2 - 1]);
                vertices.emplace_back(positions[v3 - 1], Vector3::One, texCoords[t3 - 1], normals[n3 - 1]);
            }
        }

        fclose(file);

        std::vector<uint32> indices;
        indices.reserve(vertices.size());

        for (uint32 i = 0; i < (uint32)vertices.size(); ++i) {
            indices.emplace_back(i);
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