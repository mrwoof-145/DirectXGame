#pragma once
#include <Engine/Explorer/Mesh.h>
#include <Engine/Game/Game.h>

namespace Engine
{
	namespace Explorer
	{
		struct InstParams
		{
			Instance Parent;
			std::string ClassName;
			MeshData* Mesh;
		};
		class Instance
		{
		public:
			Instance();
			virtual ~Instance();
			bool IsA(const std::string& Class) const;
			
		public:
			const std::string  ClassName{};
			Instance* Parent;
		private:
			MeshData Mesh{};
		};
	};
};


