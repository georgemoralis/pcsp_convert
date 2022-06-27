using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "VideoEngine.h"
#include "VertexState.h"

namespace jpcsp::graphics
{
	using Iterator = java::util::Iterator;
	using GL = javax::media::opengl::GL;
	using Emulator = jpcsp::Emulator;
	using namespace jpcsp::graphics;
//	import static jpcsp.graphics.GeCommands.*;
VideoEngine *VideoEngine::instance;
GeCommands *VideoEngine::helper;

	void VideoEngine::log(const string &msg)
	{
		if (isDebugMode)
		{
			cout << "sceGe DEBUG > " << msg << endl;
		}
	}

	VideoEngine *VideoEngine::getEngine(GL *gl, bool fullScreen, bool hardwareAccelerate)
	{
		VideoEngine *engine = getEngine();
		engine->setFullScreenShoot(fullScreen);
		engine->setHardwareAcc(hardwareAccelerate);
		engine->gl = gl;
		return engine;
	}

	VideoEngine *VideoEngine::getEngine()
	{
		if (instance == nullptr)
		{
			instance = new VideoEngine();
			helper = new GeCommands();
		}
		return instance;
	}

	VideoEngine::VideoEngine()
	{
	}

	void VideoEngine::update()
	{
		//System.err.println("update start");
		DisplayList::Lock();
		Iterator<DisplayList*> it = DisplayList::begin();
		while (it->hasNext() && !Emulator::pause)
		{
			DisplayList *list = it->next();
			if (list->status == DisplayList::QUEUED)
			{
				//System.err.println("executeList");
				executeList(list);

				if (list->status == DisplayList::DONE)
				{
					it->remove();
				}
			}
		}
		DisplayList::Unlock();
		//System.err.println("update done");
	}

	void VideoEngine::executeList(DisplayList *list)
	{
		actualList = list;
		listIsOver = false;

		log("executeList id " + to_string(list->id));

		while (!listIsOver && actualList->pc != actualList->stallAddress && !Emulator::pause)
		{
			int ins = Emulator::getMemory()->read32(actualList->pc);
			actualList->pc += 4;
			executeCommand(ins);
		}

		if (actualList->pc == actualList->stallAddress)
		{
			actualList->status = DisplayList::STALL_REACHED;
			log("list " + to_string(actualList->id) + " stalled at " + String::format("%08x", actualList->stallAddress));
		}

		if (listIsOver)
		{
			// Set list for deferred remove
			actualList->status = DisplayList::DONE;
			actualList = nullptr;
		}
	}

	int VideoEngine::command(int instruction)
	{
		return (static_cast<int>(static_cast<unsigned int>(instruction) >> 24));
	}

	int VideoEngine::intArgument(int instruction)
	{
		return (instruction & 0x00FFFFFF);
	}

	float VideoEngine::floatArgument(int instruction)
	{
		return Float::intBitsToFloat(instruction << 8);
	}

	void VideoEngine::executeCommand(int instruction)
	{
		int normalArgument = intArgument(instruction);
		float floatArgument = floatArgument(instruction);

		switch (command(instruction))
		{
			case GeCommands::END:
				listIsOver = true;
				log(helper->getCommandString(GeCommands::END));
				break;
			case GeCommands::FINISH:
				listIsOver = true;
				log(helper->getCommandString(GeCommands::FINISH));
				break;
			case GeCommands::BASE:
				actualList->base = normalArgument << 8;
				log(helper->getCommandString(GeCommands::BASE) + " " + String::format("%08x", actualList->base));
				break;
			case GeCommands::IADDR:
				vinfo->ptr_index = actualList->base | normalArgument;
				log(helper->getCommandString(GeCommands::IADDR) + " " + String::format("%08x", vinfo->ptr_index));
				break;
			case GeCommands::VADDR:
				vinfo->ptr_vertex = actualList->base | normalArgument;
				log(helper->getCommandString(GeCommands::VADDR) + " " + String::format("%08x", vinfo->ptr_vertex));
				break;
			case GeCommands::VTYPE:
				vinfo->processType(normalArgument);
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':
				log(helper->getCommandString(GeCommands::VTYPE) + " " + vinfo->toString());
				break;

			case GeCommands::TME:
				if (normalArgument != 0)
				{
					gl->glEnable(GL::GL_TEXTURE_2D);
					log("sceGuEnable(GU_TEXTURE_2D)");
				}
				else
				{
					gl->glDisable(GL::GL_TEXTURE_2D);
					log("sceGuDisable(GU_TEXTURE_2D)");
				}
				break;

			case GeCommands::WMS:
				// TODO figure out how to handle the separate MODEL and VIEW/WORLD matrix stacks
				gl->glMatrixMode(GL::GL_MODELVIEW);
				world_upload_start = true;
				log("sceGumMatrixMode GU_MODEL");
				break;

			case GeCommands::WORLD:
				if (world_upload_start)
				{
					world_upload_x = 0;
					world_upload_y = 0;
					world_upload_start = false;
				}

				if (world_upload_y < 4)
				{
					if (world_upload_x < 3)
					{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
