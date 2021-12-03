#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "Defines.h"
#include "IGame.h"
#include "InputManager.h"
#include "Window.h"

constexpr i32 WINDOW_X = SDL_WINDOWPOS_CENTERED;
constexpr i32 WINDOW_Y = SDL_WINDOWPOS_CENTERED;
constexpr i32 WINDOW_WIDTH = 450;
constexpr i32 WINDOW_HEIGHT = 800;


namespace engine {

	struct EngineState {
		bool isInitialized { false };
		bool isRunning { false };
		bool isPaused { false };
		IGame* game;
	};

	class Engine
	{
	public:
		explicit Engine() = default;
		~Engine() = default;

		/// <summary>
		/// Init everything in the engine
		/// </summary>
		void init(IGame& game);

		/// <summary>
		/// Run the engine. Game loop.
		/// </summary>
		void run();

		/// <summary>
		/// Shut down the engine
		/// </summary>
		void close();

		/// <summary>
		/// Process inputs with InputhManager
		/// </summary>
		/// <returns>Global inputs state</returns>
		InputState inputs();

		/// <summary>
		/// Update logic 
		/// </summary>
		/// <param name="time">Game time</param>
		void update(GameTime time);

		/// <summary>
		/// Draw everything
		/// </summary>
		void draw();

	private:
		EngineState state {};
		InputManager inputManager {};
		Window window{ "Dumb Knights " };
	};

}

#endif