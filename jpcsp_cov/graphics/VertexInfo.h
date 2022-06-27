#pragma once

#include "../Emulator.h"
#include "../Memory.h"
#include "VertexState.h"
#include <string>
#include <iostream>
#include "../stringbuilder.h"

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
namespace jpcsp::graphics
{

	using Memory = jpcsp::Memory;

	// Based on soywiz/pspemulator
	class VertexInfo
	{
		// vtype
	public:
		int transform2D = 0;
		int skinningWeightCount = 0;
		int morphingVertexCount = 0;
		int texture = 0;
		int color = 0;
		int normal = 0;
		int position = 0;
		int weight = 0;
		int index = 0;

		// vaddr, iaddr
		int ptr_vertex = 0;
		int ptr_index = 0;

		// other data
		int vertexSize = 0;

	private:
		static int *size_mapping;

		static std::string *texture_info;
		static std::string *color_info;
		static std::string *normal_info;
		static std::string *vertex_info;
		static std::string *weight_info;
		static std::string *index_info;
		static std::string *transform_info;

	public:
		virtual void processType(int param);

		virtual int getAddress(int i);

		virtual VertexState *readVertex(Memory *mem, int addr);

		virtual std::string toString();
	};

}
