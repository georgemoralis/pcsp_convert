#pragma once

#include "../Emulator.h"
#include "GeCommands.h"
#include "VertexInfo.h"
#include "DisplayList.h"
#include <string>
#include <iostream>
#include "../stringhelper.h"

/*
Parts based on soywiz's pspemulator.

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

	using GL = javax::media::opengl::GL;
	using namespace jpcsp::graphics;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.graphics.GeCommands.*;

	class VideoEngine
	{

	private:
		static VideoEngine *instance;
		GL *gl;

		bool fullscreen = false;
		int mode = 0;
		int linesize = 0;
		int pixelsize = 0;
		int width = 0;
		int height = 0;
		bool ha = false;
		static constexpr bool isDebugMode = true;
		static GeCommands *helper;
		VertexInfo *vinfo = new VertexInfo();
		static constexpr char SPACE = ' ';

		// TODO these currently here for testing only
		int fbp = 0, fbw = 0; // frame buffer pointer and width
		int zbp = 0, zbw = 0; // depth buffer pointer and width
		int psm = 0; // pixel format

		bool proj_upload_start = false;
		int proj_upload_x = 0;
		int proj_upload_y = 0;
		float *proj_matrix = new float[4 * 4];


		bool world_upload_start = false;
		int world_upload_x = 0;
		int world_upload_y = 0;
		float *world_matrix = new float[4 * 4];

		bool listIsOver = false;
		DisplayList *actualList; // The currently executing list
		int clearFlags = 0;
	public:
		virtual ~VideoEngine()
		{
			delete gl;
			delete vinfo;
			delete[] proj_matrix;
			delete[] world_matrix;
			delete actualList;
		}

	private:
		static void log(const std::string &msg);

	public:
		static VideoEngine *getEngine(GL *gl, bool fullScreen, bool hardwareAccelerate);

	private:
		static VideoEngine *getEngine();

		VideoEngine();

		// call from GL thread
	public:
		virtual void update();

		// call from GL thread
	private:
		void executeList(DisplayList *list);

		//I guess here we use ubyte
		int command(int instruction);

		int intArgument(int instruction);

		float floatArgument(int instruction);

	public:
		virtual void executeCommand(int instruction);

		virtual void setFullScreenShoot(bool b);

		virtual void setLineSize(int linesize);

		virtual void setMode(int mode);

		virtual void setPixelSize(int pixelsize);

		virtual void setup(int mode, int xres, int yres);

		virtual void show();

		virtual void waitVBlank();

	private:
		void log(const std::string &commandString, float floatArgument);

		void log(const std::string &commandString, int value);

		void log(const std::string &commandString, float matrix[]);

		void setHardwareAcc(bool hardwareAccelerate);
	};

}
