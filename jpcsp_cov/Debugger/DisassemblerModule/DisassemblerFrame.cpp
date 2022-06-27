using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "DisassemblerFrame.h"
#include "../../HLE/ThreadMan.h"
#include "../../HLE/pspdisplay.h"

namespace jpcsp::Debugger::DisassemblerModule
{
	using Toolkit = java::awt::Toolkit;
	using Clipboard = java::awt::datatransfer::Clipboard;
	using ClipboardOwner = java::awt::datatransfer::ClipboardOwner;
	using StringSelection = java::awt::datatransfer::StringSelection;
	using Transferable = java::awt::datatransfer::Transferable;
	using BufferedWriter = java::io::BufferedWriter;
	using FileNotFoundException = java::io::FileNotFoundException;
	using FileWriter = java::io::FileWriter;
	using IOException = java::io::IOException;
	using ArrayList = java::util::ArrayList;
	using DefaultListModel = javax::swing::DefaultListModel;
	using JOptionPane = javax::swing::JOptionPane;
	using SwingUtilities = javax::swing::SwingUtilities;
	using Emulator = jpcsp::Emulator;
	using Memory = jpcsp::Memory;
	using Settings = jpcsp::Settings;
	using JpcspDialogManager = jpcsp::util::JpcspDialogManager;
	using OptionPaneMultiple = jpcsp::util::OptionPaneMultiple;
	using Decoder = jpcsp::Allegrex::Decoder;
	using Instruction = jpcsp::Allegrex::Common::Instruction;

	DisassemblerFrame::DisassemblerFrame(Emulator *emu)
	{
		this->emu = emu;
		listmodel = new DefaultListModel();
		initComponents();

		DebuggerPC = 0;
		RefreshDebugger();
	}

	void DisassemblerFrame::resetDebugger()
	{
		DeleteAllBreakpoints();
		DebuggerPC = 0;
		RefreshDebugger();
	}

	void DisassemblerFrame::RefreshDebugger()
	{
		int pc;
		int cnt;
		if (DebuggerPC == 0)
		{
			DebuggerPC = Emulator::getProcessor()->pc;
		}
		listmodel->clear();

		for (pc = DebuggerPC, cnt = 0; pc < (DebuggerPC + 0x00000094); pc += 0x00000004, cnt++)
		{
			if (Memory::get_instance()->isAddressGood(pc))
			{
				int opcode = Memory::get_instance()->read32(pc);

				Instruction *insn = Decoder::instruction(opcode);

				if (VectorHelper::indexOf(breakpoints, pc) != -1)
				{
					listmodel->addElement(String::format("<*>%08X:[%08X]: %s", pc, opcode, insn->disasm(pc, opcode)));
				}
				else
				{
					listmodel->addElement(String::format("   %08X:[%08X]: %s", pc, opcode, insn->disasm(pc, opcode)));
				}
			}
			else
			{
				listmodel->addElement(String::format("   %08x: invalid address", pc));
			}
		}
	//refreshregisters
		jTable1->setValueAt(Integer::toHexString(Emulator::getProcessor()->pc), 0, 1);
		jTable1->setValueAt(Integer::toHexString(Emulator::getProcessor()->hi()), 1, 1);
		jTable1->setValueAt(Integer::toHexString(Emulator::getProcessor()->lo()), 2, 1);
		for (int i = 0; i < 32; i++)
		{
			jTable1->setValueAt(Integer::toHexString(Emulator::getProcessor()->gpr[i]), 3 + i, 1);
		}
		for (int i = 0; i < 32; i++)
		{
			jTable3->setValueAt(Emulator::getProcessor()->fpr[i], i, 1);
		}
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") private void initComponents()
	void DisassemblerFrame::initComponents()
	{

		DisMenu = new javax::swing::JPopupMenu();
		CopyAddress = new javax::swing::JMenuItem();
		CopyAll = new javax::swing::JMenuItem();
		BranchOrJump = new javax::swing::JMenuItem();
		disasmList = new javax::swing::JList(listmodel);
		DisasmToolbar = new javax::swing::JToolBar();
		RunDebugger = new javax::swing::JToggleButton();
		PauseDebugger = new javax::swing::JButton();
		jSeparator1 = new javax::swing::JToolBar::Separator();
		StepInto = new javax::swing::JButton();
		jButton2 = new javax::swing::JButton();
		jButton3 = new javax::swing::JButton();
		jSeparator2 = new javax::swing::JToolBar::Separator();
		ResetToPCbutton = new javax::swing::JButton();
		JumpToAddress = new javax::swing::JButton();
		jSeparator4 = new javax::swing::JToolBar::Separator();
		AddBreakpoint = new javax::swing::JButton();
		DeleteBreakpoint = new javax::swing::JButton();
		DeleteAllBreakpoints_Conflict = new javax::swing::JButton();
		jSeparator3 = new javax::swing::JToolBar::Separator();
		DumpCodeToText = new javax::swing::JButton();
		jTabbedPane1 = new javax::swing::JTabbedPane();
		jTable1 = new javax::swing::JTable();
		jTable2 = new javax::swing::JTable();
		jTable3 = new javax::swing::JTable();

		CopyAddress->setText("Copy Address");
		ActionListenerAnonymousInnerClass tempVar(this);
		CopyAddress->addActionListener(&tempVar);
		DisMenu->add(CopyAddress);

		CopyAll->setText("Copy All");
		ActionListenerAnonymousInnerClass2 tempVar2(this);
		CopyAll->addActionListener(&tempVar2);
		DisMenu->add(CopyAll);

		BranchOrJump->setText("Copy Branch Or Jump address");
		BranchOrJump->setEnabled(false); //disable as default
		ActionListenerAnonymousInnerClass3 tempVar3(this);
		BranchOrJump->addActionListener(&tempVar3);
		DisMenu->add(BranchOrJump);

		setTitle("Debugger");
		setResizable(false);
		WindowAdapterAnonymousInnerClass tempVar4(this);
		addWindowListener(&tempVar4);

		java::awt::Font tempVar5("Courier New", 0, 11);
		disasmList->setFont(&tempVar5);
		disasmList->setSelectionMode(javax::swing::ListSelectionModel::SINGLE_SELECTION);

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
