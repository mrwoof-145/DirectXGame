#pragma once
#include <Engine/Graphics/GraphicsDevice.h>
#include <Engine/Graphics/GraphicsEngine.h>
#include <Engine/Core/Core.h>
#include <Engine/Math/Vec3.h>
#include <Engine/Math/Vec4.h>
#include <Engine/Math/Mat4x4.h>

namespace Engine
{
	namespace Explorer
	{
		struct Vertex
		{
			Vec3 position;
			Vec4 color;
		};
		struct MeshData
		{
			const Vertex* vertexList;
			uint32_t vertexCount;

			const ui32* indexList;
			uint32_t indexCount;
		};
        class RenderMesh
        {
        public:
            RenderMesh(GraphicsDevice& device, const MeshData& Mesh)
            {
                // Используем данные из MeshData напрямую — без копирования и создания новых массивов
                VB = device.createVertexBuffer({
                    Mesh.vertexList,    // указатель на вершины
                    Mesh.vertexCount,   // количество вершин
                    sizeof(Vertex)      // размер одной вершины
                    });

                IB = device.createIndexBuffer({
                    Mesh.indexList,     // указатель на индексы
                    Mesh.indexCount     // количество индексов
                    });
            }
        public:
            RefPtr<VertexBuffer> VB;
            RefPtr<IndexBuffer> IB;
        };

	}
}