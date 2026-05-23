#pragma once
#include <Engine/Explorer/Instance.h>
#include <vector>
#include <memory>

namespace Engine
{
	namespace Explorer
	{
		class Explorer
		{
		public:
			Explorer();
			virtual ~Explorer();
			virtual const std::vector<Instance*>& GetAllInstances() const;
			virtual void New(Instance*);

		private:
			std::vector<Instance*> m_Instances;

		};
	}
}
