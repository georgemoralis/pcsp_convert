using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "MainGUI.h"
#include "Settings.h"
#include "filesystems/umdiso/UmdIsoReader.h"
#include "filesystems/umdiso/UmdIsoFile.h"

namespace jpcsp
{
	using SettingsGUI = jpcsp::GUI::SettingsGUI;
	using MemStickBrowser = jpcsp::GUI::MemStickBrowser;
	using Dimension = java::awt::Dimension;
	using Insets = java::awt::Insets;
	using Point = java::awt::Point;
	using ComponentEvent = java::awt::event::ComponentEvent;
	using ComponentListener = java::awt::event::ComponentListener;
	using KeyEvent = java::awt::event::KeyEvent;
	using KeyListener = java::awt::event::KeyListener;
	using File = java::io::File;
	using IOException = java::io::IOException;
	using RandomAccessFile = java::io::RandomAccessFile;
	using ByteBuffer = java::nio::ByteBuffer;
	using FileChannel = java::nio::channels::FileChannel;
	using JFileChooser = javax::swing::JFileChooser;
	using JOptionPane = javax::swing::JOptionPane;
	using JPopupMenu = javax::swing::JPopupMenu;
	using ToolTipManager = javax::swing::ToolTipManager;
	using UIManager = javax::swing::UIManager;
	using ConsoleWindow = jpcsp::Debugger::ConsoleWindow;
	using DisassemblerFrame = jpcsp::Debugger::DisassemblerModule::DisassemblerFrame;
	using ElfHeaderInfo = jpcsp::Debugger::ElfHeaderInfo;
	using InstructionCounter = jpcsp::Debugger::InstructionCounter;
	using MemoryViewer = jpcsp::Debugger::MemoryViewer;
	using UmdBrowser = jpcsp::GUI::UmdBrowser;
	using pspdisplay = jpcsp::HLE::pspdisplay;
	using pspiofilemgr = jpcsp::HLE::pspiofilemgr;
	using JpcspDialogManager = jpcsp::util::JpcspDialogManager;
	using MetaInformation = jpcsp::util::MetaInformation;
	using namespace jpcsp::filesystems::umdiso;
	using PSF = jpcsp::format::PSF;

	MainGUI::MainGUI()
	{
		emulator = new Emulator(this);

		/*next two lines are for overlay menus over joglcanvas*/
		JPopupMenu::setDefaultLightWeightPopupEnabled(false);
		ToolTipManager::sharedInstance().setLightWeightPopupEnabled(false);
		//end of

		initComponents();
		int *pos = Settings::get_instance()->readWindowPos("mainwindow");
		setLocation(pos[0], pos[1]);
		setTitle(version);

		/*add glcanvas to frame and pack frame to get the canvas size*/
		getContentPane()->add(pspdisplay::get_instance(), java::awt::BorderLayout::CENTER);
		pspdisplay::get_instance()->addKeyListener(this);
		this->addComponentListener(this);
		pack();

		Insets *insets = this->getInsets();
		Dimension *minSize = new Dimension(480 + insets->left + insets->right, 272 + insets->top + insets->bottom);
		this->setMinimumSize(minSize);

		//logging console window stuff
		consolewin = new ConsoleWindow();
		snapConsole = Settings::get_instance()->readBoolOptions("guisettings/snapLogwindow");
		if (snapConsole)
		{
			mainwindowPos = getLocation();
			consolewin->setLocation(mainwindowPos->x, mainwindowPos->y + getHeight());
		}
		else
		{
			pos = Settings::get_instance()->readWindowPos("logwindow");
			consolewin->setLocation(pos[0], pos[1]);
		}

//JAVA TO C++ CONVERTER TODO TASK: A 'delete minSize' statement was not added since minSize was passed to a method or constructor. Handle memory management manually.
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") private void initComponents()
	void MainGUI::initComponents()
	{

		jToolBar1 = new javax::swing::JToolBar();
		RunButton = new javax::swing::JToggleButton();
		PauseButton = new javax::swing::JToggleButton();
		ResetButton = new javax::swing::JButton();
		MenuBar = new javax::swing::JMenuBar();
		FileMenu = new javax::swing::JMenu();
		openUmd = new javax::swing::JMenuItem();
		OpenFile = new javax::swing::JMenuItem();
		OpenMemStick = new javax::swing::JMenuItem();
		ExitEmu = new javax::swing::JMenuItem();
		EmulationMenu = new javax::swing::JMenu();
		RunEmu_Conflict = new javax::swing::JMenuItem();
		PauseEmu_Conflict = new javax::swing::JMenuItem();
		ResetEmu = new javax::swing::JMenuItem();
		OptionsMenu = new javax::swing::JMenu();
		SetttingsMenu = new javax::swing::JMenuItem();
		DebugMenu = new javax::swing::JMenu();
		EnterDebugger = new javax::swing::JMenuItem();
		EnterMemoryViewer = new javax::swing::JMenuItem();
		ToggleConsole = new javax::swing::JMenuItem();
		ElfHeaderViewer = new javax::swing::JMenuItem();
		InstructionCounter = new javax::swing::JMenuItem();
		HelpMenu = new javax::swing::JMenu();
		About = new javax::swing::JMenuItem();

		setDefaultCloseOperation(javax::swing::WindowConstants::EXIT_ON_CLOSE);
		Dimension tempVar(480, 272);
		setMinimumSize(&tempVar);
		WindowAdapterAnonymousInnerClass tempVar2(this);
		addWindowListener(&tempVar2);

		jToolBar1->setFloatable(false);
		jToolBar1->setRollover(true);

		javax::swing::ImageIcon tempVar3(getClass().getResource("/jpcsp/icons/PlayIcon.png"));
		RunButton->setIcon(&tempVar3); // NOI18N
		RunButton->setText("Run");
		RunButton->setFocusable(false);
		RunButton->setHorizontalTextPosition(javax::swing::SwingConstants::RIGHT);
		RunButton->setIconTextGap(2);
		RunButton->setVerticalTextPosition(javax::swing::SwingConstants::BOTTOM);
		ActionListenerAnonymousInnerClass tempVar4(this);
		RunButton->addActionListener(&tempVar4);
		jToolBar1->add(RunButton);

		javax::swing::ImageIcon tempVar5(getClass().getResource("/jpcsp/icons/PauseIcon.png"));
		PauseButton->setIcon(&tempVar5); // NOI18N
		PauseButton->setText("Pause");

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
