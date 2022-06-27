#pragma once

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

	// Based on soywiz/pspemulator
	class VertexState
	{
	public:
		float *boneWeights = new float[8];
		float r = 0, g = 0, b = 0, a = 0;
		float px = 0, py = 0, pz = 0;
		float nx = 0, ny = 0, nz = 0;
		float u = 0, v = 0;
		virtual ~VertexState()
		{
			delete[] boneWeights;
		}

	};

}
