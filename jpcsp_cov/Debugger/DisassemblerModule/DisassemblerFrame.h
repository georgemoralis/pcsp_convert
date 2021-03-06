#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "../../Emulator.h"
#include "../../Memory.h"
#include "../../Settings.h"
#include "../../util/JpcspDialogManager.h"
#include "../../util/OptionPaneMultiple.h"
#include "../../Allegrex/Decoder.h"
#include "../../Allegrex/Common.h"
#include "DisasmOpcodes.h"
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <any>
#include <typeinfo>
#include "exceptionhelper.h"
#include "../../vectorhelper.h"

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

namespace jpcsp::Debugger::DisassemblerModule
{

	using Clipboard = java::awt::datatransfer::Clipboard;
	using ClipboardOwner = java::awt::datatransfer::ClipboardOwner;
	using Transferable = java::awt::datatransfer::Transferable;
	using ArrayList = java::util::ArrayList;
	using DefaultListModel = javax::swing::DefaultListModel;
	using Emulator = jpcsp::Emulator;

	/**
	 *
	 * @author  shadow
	 */
	class DisassemblerFrame : public javax::swing::JFrame, public ClipboardOwner
	{
	private:
		int DebuggerPC = 0;
		Emulator *emu;
		DefaultListModel *listmodel = new DefaultListModel();
		int opcode_address = 0; // store the address of the opcode used for offsetdecode
		DisasmOpcodes *disOp = new DisasmOpcodes();
		std::vector<int> breakpoints = std::vector<int>();
		/** Creates new form DisassemblerFrame */
	public:
		virtual ~DisassemblerFrame()
		{
			delete emu;
			delete listmodel;
			delete disOp;
			delete AddBreakpoint;
			delete BranchOrJump;
			delete CopyAddress;
			delete CopyAll;
			delete DeleteAllBreakpoints_Conflict;
			delete DeleteBreakpoint;
			delete DisMenu;
			delete DisasmToolbar;
			delete DumpCodeToText;
			delete JumpToAddress;
			delete PauseDebugger;
			delete ResetToPCbutton;
			delete RunDebugger;
			delete StepInto;
			delete disasmList;
			delete jButton2;
			delete jButton3;
			delete jSeparator1;
			delete jSeparator2;
			delete jSeparator3;
			delete jSeparator4;
			delete jTabbedPane1;
			delete jTable1;
			delete jTable2;
			delete jTable3;
		}

		DisassemblerFrame(Emulator *emu);

		/** Delete breakpoints and reset to PC */
		virtual void resetDebugger();

		virtual void RefreshDebugger();
		/** This method is called from within the constructor to
		 * initialize the form.
		 * WARNING: Do NOT modify this code. The content of this method is
		 * always regenerated by the Form Editor.
		 */
	private:
//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") private void initComponents()
		void initComponents();

	private:
		class ActionListenerAnonymousInnerClass : public java::awt::event::ActionListener
		{
		private:
			DisassemblerFrame *outerInstance;

		public:
			virtual ~ActionListenerAnonymousInnerClass()
			{
				delete outerInstance;
			}

			ActionListenerAnonymousInnerClass(DisassemblerFrame *outerInstance);

			void actionPerformed(java::awt::event::ActionEvent *evt);
		};

	private:
		class ActionListenerAnonymousInnerClass2 : public java::awt::event::ActionListener
		{
		private:
			DisassemblerFrame *outerInstance;

		public:
			virtual ~ActionListenerAnonymousInnerClass2()
			{
				delete outerInstance;
			}

			ActionListenerAnonymousInnerClass2(DisassemblerFrame *outerInstance);

			void actionPerformed(java::awt::event::ActionEvent *evt);
		};

	private:
		class ActionListenerAnonymousInnerClass3 : public java::awt::event::ActionListener
		{
		private:
			DisassemblerFrame *outerInstance;

		public:
			virtual ~ActionListenerAnonymousInnerClass3()
			{
				delete outerInstance;
			}

			ActionListenerAnonymousInnerClass3(DisassemblerFrame *outerInstance);

			void actionPerformed(java::awt::event::ActionEvent *evt);
		};

	private:
		class WindowAdapterAnonymousInnerClass : public java::awt::event::WindowAdapter
		{
		private:
			DisassemblerFrame *outerInstance;

		public:
			virtual ~WindowAdapterAnonymousInnerClass()
			{
				delete outerInstance;
			}

			WindowAdapterAnonymousInnerClass(DisassemblerFrame *outerInstance);

			void windowDeactivated(java::awt::event::WindowEvent *evt);
		};

	private:
		class MouseWheelListenerAnonymousInnerClass : public java::awt::event::MouseWheelListener
		{
		private:
			DisassemblerFrame *outerInstance;

		public:
			virtual ~MouseWheelListenerAnonymousInnerClass()
			{
				delete outerInstance;
			}

			MouseWheelListenerAnonymousInnerClass(DisassemblerFrame *outerInstance);

			void mouseWheelMoved(java::awt::event::MouseWheelEvent *evt);
		};


//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
