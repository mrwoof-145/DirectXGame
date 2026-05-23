#pragma once
#include <Engine/Core/Base.h>
#include <Engine/Core/Core.h>
#include <chrono>

namespace Engine
{
	class Game
	{
		dx3d_disable_copy_and_move(Game)
	public:
		explicit Game(const GameDesc& desc);
		virtual ~Game();

		virtual Logger& getLogger() noexcept final;
		virtual void run() final;
	private:
		void onInternalUpdate();
	private:
		UniquePtr<Logger> m_logger{};
		UniquePtr<GraphicsEngine> m_graphicsEngine{};
		UniquePtr<Display> m_display{};
		bool m_isRunning{ true };

		std::chrono::steady_clock::time_point m_previousTime{};
	};
}
