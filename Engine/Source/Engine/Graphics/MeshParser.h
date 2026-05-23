#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <cstdint>

struct Vec3 { float x, y, z; };
struct Vec2 { float u, v; };

struct MeshData {
    std::vector<Vec3> vertices;
    std::vector<Vec3> normals;
    std::vector<Vec2> uvs;
    std::vector<uint32_t> indices;
};

class RobloxMeshParser {
public:
    static MeshData Load(const std::string& path) {
        MeshData mesh;

        std::ifstream f(path, std::ios::binary);
        if (!f) throw std::runtime_error("Failed to open mesh file");

        auto read_u32 = [&](uint32_t& out) {
            f.read(reinterpret_cast<char*>(&out), 4);
        };

        auto read_f32 = [&](float& out) {
            f.read(reinterpret_cast<char*>(&out), 4);
        };

        uint32_t magic = 0;
        read_u32(magic);

        if (magic != 0xFF0A0A0A) {
            throw std::runtime_error("Invalid Roblox .mesh magic header");
        }

        uint32_t version = 0;
        read_u32(version);

        // --- Vertices ---
        uint32_t vertexCount = 0;
        read_u32(vertexCount);

        mesh.vertices.resize(vertexCount);
        for (uint32_t i = 0; i < vertexCount; i++) {
            read_f32(mesh.vertices[i].x);
            read_f32(mesh.vertices[i].y);
            read_f32(mesh.vertices[i].z);
        }

        // --- Normals ---
        uint32_t normalCount = 0;
        read_u32(normalCount);

        mesh.normals.resize(normalCount);
        for (uint32_t i = 0; i < normalCount; i++) {
            read_f32(mesh.normals[i].x);
            read_f32(mesh.normals[i].y);
            read_f32(mesh.normals[i].z);
        }

        // --- UVs ---
        uint32_t uvCount = 0;
        read_u32(uvCount);

        mesh.uvs.resize(uvCount);
        for (uint32_t i = 0; i < uvCount; i++) {
            read_f32(mesh.uvs[i].u);
            read_f32(mesh.uvs[i].v);
        }

        // --- Indices ---
        uint32_t indexCount = 0;
        read_u32(indexCount);

        mesh.indices.resize(indexCount);
        for (uint32_t i = 0; i < indexCount; i++) {
            read_u32(mesh.indices[i]);
        }

        return mesh;
    }
};