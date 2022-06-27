#pragma once

#include "../Emulator.h"
#include "../GeneralJpcspException.h"
#include "../Memory.h"
#include "../MemoryMap.h"
#include "SceIoStat.h"
#include "../filesystems/SeekableRandomFile.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include "exceptionhelper.h"

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace jpcsp::HLE { class IoInfo; }
namespace jpcsp::HLE { class IoDirInfo; }

/*
Function:
- HLE everything in http://psp.jim.sh/pspsdk-doc/pspiofilemgr_8h.html


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

	//import java.io.BufferedOutputStream;
	using namespace jpcsp::filesystems;
	using File = java::io::File;
	//import java.io.PrintStream;
	using HashMap = java::util::HashMap;
	using namespace jpcsp::util;
//JAVA TO C++ CONVERTER TODO TASK: The Java 'import static' statement cannot be converted to C++:
//	import static jpcsp.util.Utilities.*;
	/**
	 *
	 * @author George
	 */
	class pspiofilemgr
	{
	private:
		static pspiofilemgr *instance;
		static std::unordered_map<int, IoInfo*> filelist;
		static std::unordered_map<int, IoDirInfo*> dirlist;

	public:
		static constexpr int PSP_O_RDONLY = 0x0001;
		static constexpr int PSP_O_WRONLY = 0x0002;
		static const int PSP_O_RDWR = (PSP_O_RDONLY | PSP_O_WRONLY);
		static constexpr int PSP_O_NBLOCK = 0x0004;
		static constexpr int PSP_O_DIROPEN = 0x0008; // Internal use for dopen
		static constexpr int PSP_O_APPEND = 0x0100;
		static constexpr int PSP_O_CREAT = 0x0200;
		static constexpr int PSP_O_TRUNC = 0x0400;
		static constexpr int PSP_O_EXCL = 0x0800;
		static constexpr int PSP_O_NOWAIT = 0x8000;

		static constexpr int PSP_SEEK_SET = 0;
		static constexpr int PSP_SEEK_CUR = 1;
		static constexpr int PSP_SEEK_END = 2;

	private:
		const bool debug = true; //enable/disable debug

	public:
		static pspiofilemgr *get_instance();

		pspiofilemgr();

	private:
		std::string getDeviceFilePath(const std::string &pspfilename);

	public:
		virtual void sceIoOpen(int filename_addr, int flags, int permissions);

		virtual void sceIoClose(int uid);

		virtual void sceIoWrite(int uid, int data_addr, int size);

		virtual void sceIoRead(int uid, int data_addr, int size);

		// TODO sceIoLseek with 64-bit offset parameter and return value
		virtual void sceIoLseek32(int uid, int offset, int whence);

		virtual void sceIoMkdir(int dir_addr, int permissions);

		virtual void sceIoChdir(int path_addr);

		virtual void sceIoDopen(int dirname_addr);

		virtual void sceIoDread(int uid, int dirent_addr);

		virtual void sceIoDclose(int uid);

		/** @param pcfilename can be null for convenience
		 * @returns null on error */
	private:
		SceIoStat *stat(const std::string &pcfilename);

	public:
		virtual void sceIoGetstat(int file_addr, int stat_addr);

		//the following sets the filepath from memstick manager.
	private:
		std::string filepath;
	public:
		virtual void setfilepath(const std::string &filepath);

	public:
		class IoInfo
		{
		private:
			pspiofilemgr *outerInstance;

			// Internal settings
		public:
			SeekableRandomFile *const f;
			const std::string mode;

			// PSP settings
			const int flags;
			const int permissions;

			const int uid;

			virtual ~IoInfo()
			{
				delete f;
				delete outerInstance;
			}

			IoInfo(pspiofilemgr *outerInstance, SeekableRandomFile *f, const std::string &mode, int flags, int permissions);
		};

	public:
		class IoDirInfo
		{
		private:
			pspiofilemgr *outerInstance;

		public:
			const std::string path;
			const std::string *filenames;
			int position = 0;
			const int uid;

			virtual ~IoDirInfo()
			{
				delete[] filenames;
				delete outerInstance;
			}

			IoDirInfo(pspiofilemgr *outerInstance, const std::string &path, File *f);

			virtual bool hasNext();

			virtual std::string next();
		};

	/*
	    private class IOInfo{
	        private int uid;
	        File f;
	        public boolean fileappend=false;
	        public IOInfo(String name,int a1,int a2)
	        {
	
	            if(name.substring(0, 3).matches("ms0"))//found on fileio demo
	            {
	              int findslash = name.indexOf("/");
	              String filename = name.substring(findslash+1,name.length());
	              f = new File("ms0/" + filename);
	            }
	            else if(name.substring(0,1).matches("/"))
	            {
	               //that absolute way will work either it is from memstrick browser
	               // either if it is from openfile menu
	               int findslash = name.indexOf("/");
	                String filename = name.substring(findslash+1,name.length());
	                f = new File(filepath +"/"+ filename);
	            }
	            else
	            {
	             System.out.println("SceIoFilemgr - Unsupported device for open");
	             uid=-1;
	             return;
	            }
	            if((a1 & PSP_O_CREAT) ==0x0200 )
	            {
	               if(debug) System.out.println("sceIoOpen - create new file");
	               try{
	                 if(!f.createNewFile())//if already exists maybe that isn't important but do it anyway
	                 {
	                   f.delete();//delete it
	                   f.createNewFile(); //and recreate it
	                 }
	               }
	               catch(Exception e)
	               {
	                  e.printStackTrace();
	               }
	             }
	             if(((a1 & PSP_O_RDONLY) == 0x0001))
	             {
	                if(debug)System.out.println("sceIoOpen - readonly");
	                f.setReadable(true);
	             }
	             if(((a1 & PSP_O_WRONLY)  == 0x0002)){
	                if(debug) System.out.println("sceIoOpen - writeonly");
	                f.setWritable(true);
	             }
	             if(((a1 & PSP_O_TRUNC)  == 0x0400))
	             {
	                //Okay the is probably a very bad way to do this.. but works.. anyone with better idea?
	                if(debug) System.out.println("sceIoOpen - Truncates");
	                try
	                {
	                  FileOutputStream fop = new FileOutputStream(f);
	                  BufferedOutputStream bos = new BufferedOutputStream(fop);
	                  PrintStream b = new PrintStream(bos,true);
	                  b.close();
	                  bos.close();
	                  fop.close();
	                }
	                catch(IOException e)
	                {
	                  e.printStackTrace();
	                }
	
	             }
	             if(((a1 & PSP_O_RDWR)  == 0x0003))
	             {
	                if(debug) System.out.println("sceIoOpen - Read/Write");
	                f.setReadable(true);
	                f.setWritable(true);
	             }
	             if(((a1 & PSP_O_APPEND)  == 0x0100))
	             {
	                  if(debug) System.out.println("sceIoOpen - Append file");
	                  fileappend=true;
	             }
	             if(((a1 & PSP_O_NBLOCK)  == 0x0004))
	             {
	                  if(debug) System.out.println("sceIoOpen - nblock unsupported!!");
	             }
	             if(((a1 & PSP_O_DIROPEN)  == 0x0008))
	             {
	                  if(debug) System.out.println("sceIoOpen - diropen unsupported!!");
	             }
	             if(((a1 & PSP_O_EXCL)  == 0x0800))
	             {
	               if(debug) System.out.println("sceIoOpen - excl unsupported!!");
	             }
	             if(((a1 & PSP_O_NOWAIT)  == 0x8000))
	             {
	                  if(debug) System.out.println("sceIoOpen - nowait unsupported!!");
	             }
	            uid = SceUIDMan.get_instance().getNewUid("IOFileManager-File");
	            filelist.put(uid, this);
	        }
	
	    }
	    */

	};

}
