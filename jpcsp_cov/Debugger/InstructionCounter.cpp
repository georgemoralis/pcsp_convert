using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "InstructionCounter.h"

namespace jpcsp::Debugger
{
	using SwingWorker = com::jidesoft::utils::SwingWorker;
	using Cursor = java::awt::Cursor;
	using Toolkit = java::awt::Toolkit;
	using PropertyChangeEvent = java::beans::PropertyChangeEvent;
	using PropertyChangeListener = java::beans::PropertyChangeListener;
	using BufferedWriter = java::io::BufferedWriter;
	using File = java::io::File;
	using FileNotFoundException = java::io::FileNotFoundException;
	using FileWriter = java::io::FileWriter;
	using IOException = java::io::IOException;
	using JFileChooser = javax::swing::JFileChooser;
	using Emulator = jpcsp::Emulator;
	using Memory = jpcsp::Memory;
	using Decoder = jpcsp::Allegrex::Decoder;
	using Instruction = jpcsp::Allegrex::Common::Instruction;

	InstructionCounter::InstructionCounter(Emulator *emu)
	{
		this->emu = emu;
		initComponents();
		RefreshWindow();
	}

	void InstructionCounter::RefreshWindow()
	{
		resetcounts();
		initcheck->setSelected(false);
		finicheck->setSelected(false);
		textcheck->setSelected(false);
		stubtextcheck->setSelected(false);
		areastatus->setText("");
		if (emu->initsection[0] == 0)
		{
			initcheck->setEnabled(false);
		}
		else
		{
			initcheck->setEnabled(true);
		}
		if (emu->finisection[0] == 0)
		{
			finicheck->setEnabled(false);
		}
		else
		{
			finicheck->setEnabled(true);
		}
		if (emu->textsection[0] == 0)
		{
			textcheck->setEnabled(false);
		}
		else
		{
			textcheck->setEnabled(true);
		}
		if (emu->Stubtextsection[0] == 0)
		{
			stubtextcheck->setEnabled(false);
		}
		else
		{
			stubtextcheck->setEnabled(true);
		}
		areastatus->append("Found init section at " + Integer::toHexString(emu->initsection[0]) + " size " + emu->initsection[1] + "\n");
		areastatus->append("Found fini section at " + Integer::toHexString(emu->finisection[0]) + " size " + emu->finisection[1] + "\n");
		areastatus->append("Found text section at " + Integer::toHexString(emu->textsection[0]) + " size " + emu->textsection[1] + "\n");
		areastatus->append("Found stubtext section at " + Integer::toHexString(emu->Stubtextsection[0]) + " size " + emu->Stubtextsection[1] + "\n");
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") private void initComponents()
	void InstructionCounter::initComponents()
	{

		textcheck = new javax::swing::JCheckBox();
		initcheck = new javax::swing::JCheckBox();
		finicheck = new javax::swing::JCheckBox();
		jLabel1 = new javax::swing::JLabel();
		progressBar = new javax::swing::JProgressBar();
		startbutton = new javax::swing::JButton();
		jScrollPane1 = new javax::swing::JScrollPane();
		areastatus = new javax::swing::JTextArea();
		jScrollPane2 = new javax::swing::JScrollPane();
		OpcodeTable = new javax::swing::JTable();
		stubtextcheck = new javax::swing::JCheckBox();
		Save = new javax::swing::JButton();

		setTitle("Instruction Counter");
		setResizable(false);

		textcheck->setText(".text");

		initcheck->setText(".init");

		finicheck->setText(".fini");

		jLabel1->setText("Choose the sections you want to count:");

		startbutton->setText("Start Counting");
		ActionListenerAnonymousInnerClass tempVar(this);
		startbutton->addActionListener(&tempVar);

		areastatus->setColumns(20);
		java::awt::Font tempVar2("Courier New", 0, 12);
		areastatus->setFont(&tempVar2);
		areastatus->setRows(5);
		jScrollPane1->setViewportView(areastatus);

		DefaultTableModelAnonymousInnerClass tempVar3(this);
		OpcodeTable->setModel(&tempVar3);
		jScrollPane2->setViewportView(OpcodeTable);

		stubtextcheck->setText(".Stub.text");

		Save->setText("Save to file");
		ActionListenerAnonymousInnerClass2 tempVar4(this);
		Save->addActionListener(&tempVar4);

		javax::swing::GroupLayout *layout = new javax::swing::GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout->setHorizontalGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addGroup(layout->createSequentialGroup().addContainerGap().addGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addGroup(layout->createSequentialGroup().addComponent(startbutton).addGap(18, 18, 18).addComponent(progressBar, javax::swing::GroupLayout::DEFAULT_SIZE, 216, numeric_limits<signed char>::max())).addGroup(javax::swing::GroupLayout::Alignment::TRAILING, layout->createSequentialGroup().addComponent(jLabel1).addPreferredGap(javax::swing::LayoutStyle::ComponentPlacement::RELATED, 8, numeric_limits<signed char>::max()).addGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addComponent(stubtextcheck).addGroup(layout->createSequentialGroup().addComponent(textcheck).addPreferredGap(javax::swing::LayoutStyle::ComponentPlacement::RELATED).addComponent(initcheck).addPreferredGap(javax::swing::LayoutStyle::ComponentPlacement::UNRELATED).addComponent(finicheck)))).addComponent(jScrollPane1, javax::swing::GroupLayout::DEFAULT_SIZE, 337, numeric_limits<signed char>::max()).addComponent(jScrollPane2, javax::swing::GroupLayout::Alignment::TRAILING, javax::swing::GroupLayout::PREFERRED_SIZE, 332, javax::swing::GroupLayout::PREFERRED_SIZE).addComponent(Save, javax::swing::GroupLayout::Alignment::TRAILING)).addContainerGap()));
		layout->setVerticalGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addGroup(layout->createSequentialGroup().addContainerGap().addGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::BASELINE).addComponent(finicheck).addComponent(initcheck).addComponent(textcheck).addComponent(jLabel1)).addPreferredGap(javax::swing::LayoutStyle::ComponentPlacement::UNRELATED).addComponent(stubtextcheck).addGap(4, 4, 4).addGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING, false).addComponent(progressBar, javax::swing::GroupLayout::DEFAULT_SIZE, javax::swing::GroupLayout::DEFAULT_SIZE, numeric_limits<signed char>::max()).addComponent(startbutton, javax::swing::GroupLayout::DEFAULT_SIZE, javax::swing::GroupLayout::DEFAULT_SIZE, numeric_limits<signed char>::max())).addPreferredGap(javax::swing::LayoutStyle::ComponentPlacement::RELATED).addComponent(jScrollPane1, javax::swing::GroupLayout::PREFERRED_SIZE, 59, javax::swing::GroupLayout::PREFERRED_SIZE).addPreferredGap(javax::swing::LayoutStyle::ComponentPlacement::RELATED).addComponent(jScrollPane2, javax::swing::GroupLayout::PREFERRED_SIZE, 402, javax::swing::GroupLayout::PREFERRED_SIZE).addPreferredGap(javax::swing::LayoutStyle::ComponentPlacement::RELATED, 8, numeric_limits<signed char>::max()).addComponent(Save)));

		pack();

//JAVA TO C++ CONVERTER TODO TASK: A 'delete layout' statement was not added since layout was passed to a method or constructor. Handle memory management manually.
	} // </editor-fold>//GEN-END:initComponents

	InstructionCounter::ActionListenerAnonymousInnerClass::ActionListenerAnonymousInnerClass(InstructionCounter *outerInstance) : outerInstance(outerInstance)
	{
	}

	void InstructionCounter::ActionListenerAnonymousInnerClass::actionPerformed(java::awt::event::ActionEvent *evt)
	{
		outerInstance->startbuttonActionPerformed(evt);
	}

//JAVA TO C++ CONVERTER NOTE: The following call to the 'RectangularArrays' helper class reproduces the rectangular array initialization that is automatic in Java:
//ORIGINAL LINE: public DefaultTableModelAnonymousInnerClass(InstructionCounter outerInstance)
	InstructionCounter::DefaultTableModelAnonymousInnerClass::DefaultTableModelAnonymousInnerClass(InstructionCounter *outerInstance) : javax::swing::table::DefaultTableModel(RectangularArrays::RectangularStdAnyArray((sizeof(jpcsp::Allegrex::Common::instructions()) / sizeof(jpcsp::Allegrex::Common::instructions()[0])), 3), new string [3] {"Opcode", "Category", "Count"}), outerInstance(outerInstance)
	{
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
		types = new type_info [3] {java::lang::String::class, java::lang::String::class, java::lang::Object::class};
		canEdit = new bool [3] {false, false, false};
	}

	type_info InstructionCounter::DefaultTableModelAnonymousInnerClass::getColumnClass(int columnIndex)
	{
		return types [columnIndex];
	}

	bool InstructionCounter::DefaultTableModelAnonymousInnerClass::isCellEditable(int rowIndex, int columnIndex)
	{
		return canEdit [columnIndex];
	}

	InstructionCounter::ActionListenerAnonymousInnerClass2::ActionListenerAnonymousInnerClass2(InstructionCounter *outerInstance) : outerInstance(outerInstance)
	{
	}

	void InstructionCounter::ActionListenerAnonymousInnerClass2::actionPerformed(java::awt::event::ActionEvent *evt)
	{
		outerInstance->SaveActionPerformed(evt);
	}


//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
