#pragma once

#include "../Emulator.h"
#include "../MemoryMap.h"
#include "../graphics/DisplayList.h"
#include "../graphics/VideoEngine.h"
#include <string>
#include <iostream>

/*
Function:
- HLE everything in http://psp.jim.sh/pspsdk-doc/pspge_8h.html


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

	//import jpcsp.graphics.PspGeCallbackData;

	class pspge
	{

	private:
		static pspge *instance;
		/*
		private PspGeCallbackData cbdata;
		private int cbid = -1;
		*/

	public:
		static pspge *get_instance();

	private:
		pspge();

	public:
		virtual void Initialise();

		virtual void sceGeEdramGetAddr();

		virtual void sceGeListEnQueue(int list, int stall, int callbackId, int argument);

		virtual void sceGeListDeQueue(int qid);

		virtual void sceGeListUpdateStallAddr(int qid, int stallAddress);

		/* Not sure if this is correct
		public void sceGeSetCallback(int cbdata_addr) {
		    // TODO list of callbacks, for now we allow only 1
		    if (cbid == -1) {
		        cbdata = new PspGeCallbackData(Emulator.getMemory(), cbdata_addr);
		        cbid = 1;
		        Emulator.getProcessor().gpr[2] = cbid;
		    } else {
		        System.out.println("sceGeSetCallback failed");
		        Emulator.getProcessor().gpr[2] = -1;
		    }
		}
	
		public void sceGeUnsetCallback(int cbid) {
		    // TODO list of callbacks, for now we allow only 1
		    if (this.cbid == cbid) {
		        cbdata = null;
		        cbid = -1;
		        Emulator.getProcessor().gpr[2] = 0;
		    } else {
		        System.out.println("sceGeUnsetCallback failed");
		        Emulator.getProcessor().gpr[2] = -1;
		    }
		}
		*/

	private:
		void log(const std::string &msg);


	};

}
