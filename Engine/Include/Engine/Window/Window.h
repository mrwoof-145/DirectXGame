#pragma once
#include <Engine/Core/Base.h>
#include <Engine/Core/Common.h>


namespace Engine
{
	class Window: public Base
	{
	public:
		explicit Window(const WindowDesc& desc);
		virtual ~Window() override;

	protected:
		void* m_handle{};
		Rect m_size{};
	};
}

