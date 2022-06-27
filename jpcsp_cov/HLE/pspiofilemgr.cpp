using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "pspiofilemgr.h"
#include "../util/Utilities.h"
#include "SceUIDMan.h"
#include "ScePspDateTime.h"
#include "SceIoDirent.h"

namespace jpcsp::HLE
{
	using namespace jpcsp::filesystems;
	using File = java::io::File;
	using FileNotFoundException = java::io::FileNotFoundException;
	using IOException = java::io::IOException;
	using HashMap = java::util::HashMap;
	using Emulator = jpcsp::Emulator;
	using GeneralJpcspException = jpcsp::GeneralJpcspException;
	using Memory = jpcsp::Memory;
	using MemoryMap = jpcsp::MemoryMap;
	using namespace jpcsp::util;
//	import static jpcsp.util.Utilities.*;
pspiofilemgr *pspiofilemgr::instance;
unordered_map<int, IoInfo*> pspiofilemgr::filelist;
unordered_map<int, IoDirInfo*> pspiofilemgr::dirlist;

	pspiofilemgr *pspiofilemgr::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new pspiofilemgr();
		}
		return instance;
	}

	pspiofilemgr::pspiofilemgr()
	{
		filelist = unordered_map<int, IoInfo*>();
		dirlist = unordered_map<int, IoDirInfo*>();
	}

	string pspiofilemgr::getDeviceFilePath(const string &pspfilename)
	{
		string filename = "";

		// on PSP: device:/path
		// on PC: device/path
		int findcolon = (int)pspfilename.find(":");
		if (findcolon != -1)
		{
			// Device absolute
			filename = pspfilename.substr(0, findcolon) + pspfilename.substr(findcolon + 1);
			//if (debug) System.out.println("'" + pspfilename.substring(0, findcolon) + "' '" + pspfilename.substring(findcolon + 1) + "'");
		}
		else if (pspfilename.starts_with("/"))
		{
			// Relative
			filename = filepath + pspfilename;
		}
		else
		{
			// Relative
			filename = filepath + "/" + pspfilename;
		}

		//if (debug) System.out.println("getDeviceFilePath filename = " + filename);

		/* Old version
		if (pspfilename.startsWith("ms0")) { //found on fileio demo
		    int findslash = pspfilename.indexOf("/");
		    filename = "ms0/" + pspfilename.substring(findslash+1);
		} else if (pspfilename.startsWith("/")) { //relative to where EBOOT.PBP is
		    //that absolute way will work either it is from memstrick browser
		    // either if it is from openfile menu
		    filename = filepath + "/" + pspfilename.substring(1);
		}
		else if (!pspfilename.contains("/"))//maybe absolute path
		{
		    if(pspfilename.contains("'"))
		    {
		      if (debug) System.out.println("getDeviceFilePath removing ' character");
		      filename = filepath +"/"+ pspfilename.replace("'", ""); // remove '  //found on nesterj emu
		    }
		    else
		    {
		      filename= filepath +"/"+  pspfilename;
		    }
		
		} else {
		    System.out.println("pspiofilemgr - Unsupported device '" + pspfilename + "'");
		}
		*/

		return filename;
	}

	void pspiofilemgr::sceIoOpen(int filename_addr, int flags, int permissions)
	{
		string filename = Utilities::readStringZ(Memory::get_instance()->mainmemory, (filename_addr & 0x3fffffff) - MemoryMap::START_RAM);
		if (debug)
		{
			cout << "sceIoOpen filename = " << filename << " flags = " << Integer::toHexString(flags) << " permissions = " << Integer::toOctalString(permissions) << endl;
		}

		if (debug)
		{
			if ((flags & PSP_O_RDONLY) == PSP_O_RDONLY)
			{
				cout << "PSP_O_RDONLY" << endl;
			}
			if ((flags & PSP_O_WRONLY) == PSP_O_WRONLY)
			{
				cout << "PSP_O_WRONLY" << endl;
			}
			if ((flags & PSP_O_NBLOCK) == PSP_O_NBLOCK)
			{
				cout << "PSP_O_NBLOCK" << endl;
			}
			if ((flags & PSP_O_DIROPEN) == PSP_O_DIROPEN)
			{
				cout << "PSP_O_DIROPEN" << endl;
			}
			if ((flags & PSP_O_APPEND) == PSP_O_APPEND)
			{
				cout << "PSP_O_APPEND" << endl;
			}
			if ((flags & PSP_O_CREAT) == PSP_O_CREAT)
			{
				cout << "PSP_O_CREAT" << endl;
			}
			if ((flags & PSP_O_TRUNC) == PSP_O_TRUNC)
			{
				cout << "PSP_O_TRUNC" << endl;
			}
			if ((flags & PSP_O_EXCL) == PSP_O_EXCL)
			{
				cout << "PSP_O_EXCL" << endl;
			}
			if ((flags & PSP_O_NOWAIT) == PSP_O_NOWAIT)
			{
				cout << "PSP_O_NOWAIT" << endl;
			}
		}

		string mode;

		// PSP_O_RDWR check must come before the individual PSP_O_RDONLY and PSP_O_WRONLY checks
		if ((flags & PSP_O_RDWR) == PSP_O_RDWR)
		{
			mode = "rw";
		}
		else if ((flags & PSP_O_RDONLY) == PSP_O_RDONLY)
		{
			mode = "r";
		}
		else if ((flags & PSP_O_WRONLY) == PSP_O_WRONLY)
		{
			// SeekableRandomFile doesn't support write only
			mode = "rw";
		}
		else
		{
			cout << "sceIoOpen - unhandled flags " << Integer::toHexString(flags) << endl;
			Emulator::getProcessor()->gpr[2] = -1;
			return;
		}

		// TODO we may want to do something with PSP_O_CREAT and permissions
		// using java File and its setReadable/Writable/Executable.
		// Does PSP filesystem even support permissions?

		// TODO PSP_O_TRUNC flag. delete the file and recreate it?

		// This could get messy, is it even allowed?
		if ((flags & PSP_O_RDONLY) == PSP_O_RDONLY && (flags & PSP_O_APPEND) == PSP_O_APPEND)
		{
			cout << "sceIoOpen - read and append flags both set!" << endl;
		}

		try
		{
			string pcfilename = getDeviceFilePath(filename);
			if (pcfilename != "")
			{
				if (debug)
				{
					cout << "pspiofilemgr - opening file " << pcfilename << endl;
				}

				// First check if the file already exists
				File *file = new File(pcfilename);
				if (file->exists() && (flags & PSP_O_CREAT) == PSP_O_CREAT && (flags & PSP_O_EXCL) == PSP_O_EXCL)
				{
					// PSP_O_CREAT + PSP_O_EXCL + file already exists = error
					if (debug)
					{
						cout << "sceIoOpen - file already exists (PSP_O_CREAT + PSP_O_EXCL)" << endl;
					}
					Emulator::getProcessor()->gpr[2] = -1;
				}
				else
				{
					if (file->exists() && (flags & PSP_O_TRUNC) == PSP_O_TRUNC)
					{
						if (debug)
						{
							cout << "sceIoOpen - file already exists, deleting UNIMPLEMENT (PSP_O_TRUNC)" << endl;
						}
						//file.delete();
					}

					SeekableRandomFile *raf = new SeekableRandomFile(pcfilename, mode);
					IoInfo *info = new IoInfo(this, raf, mode, flags, permissions);
					Emulator::getProcessor()->gpr[2] = info->uid;

					delete info;
//JAVA TO C++ CONVERTER TODO TASK: A 'delete raf' statement was not added since raf was passed to a method or constructor. Handle memory management manually.
				}

				delete file;
			}
			else
			{
				Emulator::getProcessor()->gpr[2] = -1;
			}
		}
		catch (const FileNotFoundException &e)
		{
			// To be expected under mode="r" and file doesn't exist
			if (debug)
			{
				cout << "pspiofilemgr - file not found (ok to ignore this message, debug purpose only)" << endl;
			}
			Emulator::getProcessor()->gpr[2] = -1;
		}
	}

	void pspiofilemgr::sceIoClose(int uid)
	{
		if (debug)
		{
			cout << "sceIoClose - uid " << Integer::toHexString(uid) << endl;
		}

		try
		{
			SceUIDMan::get_instance()->checkUidPurpose(uid, "IOFileManager-File", true);

			IoInfo *info = filelist.erase(uid);
			if (info == nullptr)
			{
				if (uid != 1 && uid != 2) // stdin and stderr
				{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
