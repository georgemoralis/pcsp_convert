#pragma once

#include "../Emulator.h"
#include "../Memory.h"
#include "../MemoryMap.h"
#include "../Settings.h"
#include "../graphics/VideoEngine.h"
#include <iostream>

/*
Function:
- HLE everything in http://psp.jim.sh/pspsdk-doc/pspdisplay_8h.html


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
namespace jpcsp::HLE
{

	using ByteBuffer = java::nio::ByteBuffer;
	using GL = javax::media::opengl::GL;
	using GLAutoDrawable = javax::media::opengl::GLAutoDrawable;
	using GLCanvas = javax::media::opengl::GLCanvas;
	using GLEventListener = javax::media::opengl::GLEventListener;

	/**
	 * @author shadow, aisesal
	 */
	class pspdisplay final : public GLCanvas, public GLEventListener
	{
	private:
		static pspdisplay *instance;
	public:
		virtual ~pspdisplay()
		{
			delete pixels;
			delete temp;
		}

		static pspdisplay *get_instance();

		// PspDisplayPixelFormats enum
		static constexpr int PSP_DISPLAY_PIXEL_FORMAT_565 = 0;
		static constexpr int PSP_DISPLAY_PIXEL_FORMAT_5551 = 1;
		static constexpr int PSP_DISPLAY_PIXEL_FORMAT_4444 = 2;
		static constexpr int PSP_DISPLAY_PIXEL_FORMAT_8888 = 3;

		// PspDisplaySetBufSync enum
		static constexpr int PSP_DISPLAY_SETBUF_IMMEDIATE = 0;
		static constexpr int PSP_DISPLAY_SETBUF_NEXTFRAME = 1;

		// PspDisplayErrorCodes enum
		static constexpr int PSP_DISPLAY_ERROR_OK = 0;
		static constexpr int PSP_DISPLAY_ERROR_POINTER = 0x80000103;
		static constexpr int PSP_DISPLAY_ERROR_ARGUMENT = 0x80000107;

		bool disableGE = false;

		// current display mode
	private:
		int mode = 0;
		int width = 0;
		int height = 0;

		// current framebuffer settings
		int topaddr = 0;
		int bufferwidth = 0;
		int pixelformat = 0;
		int sync = 0;

		// additional variables
		int bottomaddr = 0;
		bool refreshRequired = false;
		long long lastUpdate = 0;

		// Canvas fields
		ByteBuffer *pixels;
		ByteBuffer *temp;
		int canvasWidth = 0;
		int canvasHeight = 0;
		bool createTex = false;
		int texFb = 0;
		float texS = 0;
		float texT = 0;

		// fps counter variables
		long long prevStatsTime = 0;
		long long frameCount = 0;
		long long actualframeCount = 0;
		long long reportCount = 0;
		double averageFPS = 0.0;

		pspdisplay();

	public:
		void Initialise();

		void step();

		void write8(int address, int data);

		void write16(int address, int data);

		void write32(int address, int data);

		void setDirty(bool dirty);

	private:
		static int getPixelFormatBytes(int pixelformat);

		static int getPixelFormatGL(int pixelformat);

		void getPixels();

		int makePow2(int n);

		void reportFPSStats();

		void drawFrameBuffer(GL *const gl, bool first, bool invert);

		// GLEventListener methods

	public:
		void init(GLAutoDrawable *drawable) override;

		void display(GLAutoDrawable *drawable) override;

		void reshape(GLAutoDrawable *drawable, int x, int y, int width, int height) override;

		void displayChanged(GLAutoDrawable *drawable, bool modeChanged, bool displayChanged) override;

		// HLE functions

		void sceDisplaySetMode(int mode, int width, int height);

		void sceDisplayGetMode(int pmode, int pwidth, int pheight);

		void sceDisplaySetFrameBuf(int topaddr, int bufferwidth, int pixelformat, int sync);

		void sceDisplayGetFrameBuf(int topaddr, int bufferwidth, int pixelformat, int sync);

		void sceDisplayGetVcount();

		void sceDisplayWaitVblankStart();

		void sceDisplayWaitVblankStartCB();

		void sceDisplayWaitVblank();

		void sceDisplayWaitVblankCB();
	};

}
