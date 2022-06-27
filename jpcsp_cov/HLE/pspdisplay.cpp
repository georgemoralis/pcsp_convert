using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "pspdisplay.h"
#include "ThreadMan.h"

namespace jpcsp::HLE
{
	using ByteBuffer = java::nio::ByteBuffer;
	using ByteOrder = java::nio::ByteOrder;
	using GL = javax::media::opengl::GL;
	using GLAutoDrawable = javax::media::opengl::GLAutoDrawable;
	using GLCanvas = javax::media::opengl::GLCanvas;
	using GLEventListener = javax::media::opengl::GLEventListener;
	using Emulator = jpcsp::Emulator;
	using Memory = jpcsp::Memory;
	using MemoryMap = jpcsp::MemoryMap;
	using Settings = jpcsp::Settings;
	using VideoEngine = jpcsp::graphics::VideoEngine;
pspdisplay *pspdisplay::instance;

	pspdisplay *pspdisplay::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new pspdisplay();
		}
		return instance;
	}

	pspdisplay::pspdisplay()
	{
		setSize(480, 272);
		addGLEventListener(this);
		texFb = -1;
	}

	void pspdisplay::Initialise()
	{
		mode = 0;
		width = 480;
		height = 272;
		topaddr = MemoryMap::START_VRAM;
		bufferwidth = 512;
		pixelformat = PSP_DISPLAY_PIXEL_FORMAT_8888;
		sync = PSP_DISPLAY_SETBUF_IMMEDIATE;

		bottomaddr = topaddr + bufferwidth * height * getPixelFormatBytes(pixelformat);

		refreshRequired = true;
		createTex = true;

		disableGE = Settings::get_instance()->readBoolOptions("emuoptions/disablege");

		getPixels();
	}

	void pspdisplay::step()
	{
		long long now = System::currentTimeMillis();
		if (now - lastUpdate > 1000 / 60)
		{
			if (refreshRequired)
			{
				display();
				refreshRequired = false;
			}
			lastUpdate = now;
		}
	}

	void pspdisplay::write8(int address, int data)
	{
		address &= 0x3FFFFFFF;
		if (address >= topaddr && address < bottomaddr)
		{
			setDirty(true);
		}
	}

	void pspdisplay::write16(int address, int data)
	{
		address &= 0x3FFFFFFF;
		if (address >= topaddr && address < bottomaddr)
		{
			setDirty(true);
		}
	}

	void pspdisplay::write32(int address, int data)
	{
		address &= 0x3FFFFFFF;
		if (address >= topaddr && address < bottomaddr)
		{
			setDirty(true);
		}
	}

	void pspdisplay::setDirty(bool dirty)
	{
		refreshRequired = dirty;
	}

	int pspdisplay::getPixelFormatBytes(int pixelformat)
	{
		return pixelformat == PSP_DISPLAY_PIXEL_FORMAT_8888 ? 4 : 2;
	}

	int pspdisplay::getPixelFormatGL(int pixelformat)
	{
		switch (pixelformat)
		{
		case PSP_DISPLAY_PIXEL_FORMAT_565:
			return GL::GL_UNSIGNED_SHORT_5_6_5_REV;
		case PSP_DISPLAY_PIXEL_FORMAT_5551:
			return GL::GL_UNSIGNED_SHORT_1_5_5_5_REV;
		case PSP_DISPLAY_PIXEL_FORMAT_4444:
			return GL::GL_UNSIGNED_SHORT_4_4_4_4_REV;
		default:
			return GL::GL_UNSIGNED_BYTE;
		}
	}

	void pspdisplay::getPixels()
	{
		Memory *memory = Emulator::getMemory();
		signed char *all = memory->videoram->array();
		pixels = ByteBuffer::wrap(all, topaddr - MemoryMap::START_VRAM + memory->videoram->arrayOffset(), bottomaddr - topaddr).slice();
		pixels->order(ByteOrder::LITTLE_ENDIAN);
	}

	int pspdisplay::makePow2(int n)
	{
		--n;
		n = (n >> 1) | n;
		n = (n >> 2) | n;
		n = (n >> 4) | n;
		n = (n >> 8) | n;
		n = (n >> 16) | n;
		return ++n;
	}

	void pspdisplay::reportFPSStats()
	{
		frameCount++;
		long long timeNow = System::nanoTime();
		long long realElapsedTime = (timeNow - prevStatsTime) / 1000000LL;

		if (realElapsedTime > 1000LL)
		{
			reportCount++;
			int lastFPS = static_cast<int>(frameCount - actualframeCount);
			averageFPS = static_cast<double>(frameCount) / reportCount;
			actualframeCount = frameCount;
			prevStatsTime = timeNow;

			Emulator::setFpsTitle("averageFPS: " + String::format("%.1f", averageFPS) + " lastFPS: " + to_string(lastFPS));
		}
	}

	void pspdisplay::drawFrameBuffer(GL *const gl, bool first, bool invert)
	{
		gl->glPushAttrib(GL::GL_ALL_ATTRIB_BITS);

		if (first)
		{
			gl->glViewport(0, 0, width, height);
		}
		else
		{
			gl->glViewport(0, 0, canvasWidth, canvasHeight);
		}

		gl->glDisable(GL::GL_DEPTH_TEST);

		gl->glMatrixMode(GL::GL_PROJECTION);
		gl->glPushMatrix();

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
