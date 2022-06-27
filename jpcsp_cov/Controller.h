#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <utility>

/*
This file is part of jpcsp.

Jpcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Jpcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Jpcsp.  If not, see <http://www.gnu.org/licenses/>.
 */

namespace jpcsp
{

	using KeyEvent = java::awt::event::KeyEvent;
	using HashMap = java::util::HashMap;


	class Controller
	{
	private:
		signed char Lx = 127;
		signed char Ly = 127;
		int Buttons = 0;
		keyCode lastKey = keyCode::RELEASED;
		long long lastUpdate = 0;
		bool pressed = false;
		bool changed = true;

		std::unordered_map<int, keyCode> keys;

	public:
		enum class keyCode
		{
			UP,
			DOWN,
			LEFT,
			RIGHT,
			ANUP,
			ANDOWN,
			ANLEFT,
			ANRIGHT,
			START,
			SELECT,
			TRIANGLE,
			SQUARE,
			CIRCLE,
			CROSS,
			L1,
			R1,
			HOME,
			HOLD,
			VOLMIN,
			VOLPLUS,
			SCREEN,
			MUSIC,
			RELEASED

		};

		class keyCodeHelper
		{
		private:
			static std::vector<std::pair<keyCode, std::string>> pairs()
			{
				return
				{
					{keyCode::UP, "UP"},
					{keyCode::DOWN, "DOWN"},
					{keyCode::LEFT, "LEFT"},
					{keyCode::RIGHT, "RIGHT"},
					{keyCode::ANUP, "ANUP"},
					{keyCode::ANDOWN, "ANDOWN"},
					{keyCode::ANLEFT, "ANLEFT"},
					{keyCode::ANRIGHT, "ANRIGHT"},
					{keyCode::START, "START"},
					{keyCode::SELECT, "SELECT"},
					{keyCode::TRIANGLE, "TRIANGLE"},
					{keyCode::SQUARE, "SQUARE"},
					{keyCode::CIRCLE, "CIRCLE"},
					{keyCode::CROSS, "CROSS"},
					{keyCode::L1, "L1"},
					{keyCode::R1, "R1"},
					{keyCode::HOME, "HOME"},
					{keyCode::HOLD, "HOLD"},
					{keyCode::VOLMIN, "VOLMIN"},
					{keyCode::VOLPLUS, "VOLPLUS"},
					{keyCode::SCREEN, "SCREEN"},
					{keyCode::MUSIC, "MUSIC"},
					{keyCode::RELEASED, "RELEASED"}
				};
			}

		public:
			static std::vector<keyCode> values()
			{
				std::vector<keyCode> temp;
				for (auto pair : pairs())
				{
					temp.push_back(pair.first);
				}
				return temp;
			}

			static std::string enumName(keyCode value)
			{
				for (auto pair : pairs())
				{
					if (pair.first == value)
						return pair.second;
				}

				throw std::runtime_error("Enum not found.");
			}

			static int ordinal(keyCode value)
			{
				std::vector<std::pair<keyCode, std::string>> temp = pairs();
				for (std::size_t i = 0; i < temp.size(); i++)
				{
					if (temp[i].first == value)
						return i;
				}

				throw std::runtime_error("Enum not found.");
			}

			static keyCode enumFromString(std::string value)
			{
				for (auto pair : pairs())
				{
					if (pair.second == value)
						return pair.first;
				}

				throw std::runtime_error("Enum not found.");
			}
		};

	public:
		Controller();

		virtual void loadKeyConfig();

		virtual void loadKeyConfig(std::unordered_map<int, keyCode> &newLayout);

		virtual void checkControllerState();

		virtual void keyPressed(KeyEvent *arg0);

		virtual void keyReleased(KeyEvent *arg0);
	};

}
