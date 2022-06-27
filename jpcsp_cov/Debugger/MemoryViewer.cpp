using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "MemoryViewer.h"

namespace jpcsp::Debugger
{
	using JOptionPane = javax::swing::JOptionPane;
	using Emulator = jpcsp::Emulator;
	using Memory = jpcsp::Memory;
	using Settings = jpcsp::Settings;

	MemoryViewer::MemoryViewer()
	{
		//this.cpu = c;
		startaddress = Emulator::getProcessor()->pc;
		initComponents();

		RefreshMemory();
	}

	char MemoryViewer::converttochar(int character)
	{
	  //char newone = (char)Memory.get_instance().read8(address);
	  //if(newone <32 || newone >127)
	  //    return (byte)32;
	 // else
		if (character < 0x020 || character >= 0x07f && character <= 0x0a0 || character == 0x0ad)
		{
			return static_cast<char>('.');
		}
		else
		{
		  return static_cast<char>(character & 0x0ff);
		}

	}

	signed char MemoryViewer::safeRead8(int address)
	{
		signed char value = 0;
		if (Memory::get_instance()->isAddressGood(address))
		{
			value = static_cast<signed char>(Memory::get_instance()->read8(address));
		}
		return value;
	}

	void MemoryViewer::RefreshMemory()
	{
		signed char *line = new signed char[16];
		int addr = startaddress;
		memoryview->setText("");
		for (int y = 0; y < 22; y++) //21 lines
		{
			for (int i = 0; i < line->length; i++)
			{
				line[i] = safeRead8(addr + i);
			}

			memoryview->append(String::format("%08x : %02x %02x %02x %02x %02x %02x " + "%02x %02x %02x %02x %02x %02x %02x %02x " + "%02x %02x %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c", addr, line[0], line[1], line[2], line[3], line[4], line[5], line[6], line[7], line[8], line[9], line[10], line[11], line[12], line[13], line[14], line[15], converttochar(line[0]), converttochar(line[1]), converttochar(line[2]), converttochar(line[3]), converttochar(line[4]), converttochar(line[5]), converttochar(line[6]), converttochar(line[7]), converttochar(line[8]), converttochar(line[9]), converttochar(line[10]), converttochar(line[11]), converttochar(line[12]), converttochar(line[13]), converttochar(line[14]), converttochar(line[15])));
			if (y != 21)
			{
				memoryview->append("\n");
			}
		// }
		addr += 16;

		}
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") private void initComponents()
	void MemoryViewer::initComponents()
	{

		jScrollPane1 = new javax::swing::JScrollPane();
		memoryview = new javax::swing::JTextArea();
		AddressField = new javax::swing::JTextField();
		GoToButton = new javax::swing::JButton();

		setTitle("Memory Viewer");
		setResizable(false);
		WindowAdapterAnonymousInnerClass tempVar(this);
		addWindowListener(&tempVar);

		memoryview->setColumns(20);
		memoryview->setEditable(false);
		java::awt::Font tempVar2("Courier New", 0, 12);
		memoryview->setFont(&tempVar2);
		memoryview->setRows(5);
		MouseWheelListenerAnonymousInnerClass tempVar3(this);
		memoryview->addMouseWheelListener(&tempVar3);
		KeyAdapterAnonymousInnerClass tempVar4(this);
		memoryview->addKeyListener(&tempVar4);
		jScrollPane1->setViewportView(memoryview);

		GoToButton->setText("Go to Address");
		ActionListenerAnonymousInnerClass tempVar5(this);
		GoToButton->addActionListener(&tempVar5);

		javax::swing::GroupLayout *layout = new javax::swing::GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout->setHorizontalGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addGroup(layout->createSequentialGroup().addContainerGap().addGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addGroup(layout->createSequentialGroup().addComponent(AddressField, javax::swing::GroupLayout::PREFERRED_SIZE, 216, javax::swing::GroupLayout::PREFERRED_SIZE).addPreferredGap(javax::swing::LayoutStyle::ComponentPlacement::RELATED).addComponent(GoToButton)).addComponent(jScrollPane1, javax::swing::GroupLayout::DEFAULT_SIZE, 646, numeric_limits<signed char>::max())).addContainerGap()));
		layout->setVerticalGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addGroup(javax::swing::GroupLayout::Alignment::TRAILING, layout->createSequentialGroup().addContainerGap(32, numeric_limits<signed char>::max()).addGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::BASELINE).addComponent(AddressField, javax::swing::GroupLayout::PREFERRED_SIZE, javax::swing::GroupLayout::DEFAULT_SIZE, javax::swing::GroupLayout::PREFERRED_SIZE).addComponent(GoToButton)).addPreferredGap(javax::swing::LayoutStyle::ComponentPlacement::UNRELATED).addComponent(jScrollPane1, javax::swing::GroupLayout::PREFERRED_SIZE, 314, javax::swing::GroupLayout::PREFERRED_SIZE).addContainerGap()));

		pack();

//JAVA TO C++ CONVERTER TODO TASK: A 'delete layout' statement was not added since layout was passed to a method or constructor. Handle memory management manually.
	} // </editor-fold>//GEN-END:initComponents

	MemoryViewer::WindowAdapterAnonymousInnerClass::WindowAdapterAnonymousInnerClass(MemoryViewer *outerInstance) : outerInstance(outerInstance)
	{
	}

	void MemoryViewer::WindowAdapterAnonymousInnerClass::windowDeactivated(java::awt::event::WindowEvent *evt)
	{
		outerInstance->formWindowDeactivated(evt);
	}

	MemoryViewer::MouseWheelListenerAnonymousInnerClass::MouseWheelListenerAnonymousInnerClass(MemoryViewer *outerInstance) : outerInstance(outerInstance)
	{
	}

	void MemoryViewer::MouseWheelListenerAnonymousInnerClass::mouseWheelMoved(java::awt::event::MouseWheelEvent *evt)
	{
		outerInstance->memoryviewMouseWheelMoved(evt);
	}

	MemoryViewer::KeyAdapterAnonymousInnerClass::KeyAdapterAnonymousInnerClass(MemoryViewer *outerInstance) : outerInstance(outerInstance)
	{
	}

	void MemoryViewer::KeyAdapterAnonymousInnerClass::keyPressed(java::awt::event::KeyEvent *evt)
	{
		outerInstance->memoryviewKeyPressed(evt);
	}

	MemoryViewer::ActionListenerAnonymousInnerClass::ActionListenerAnonymousInnerClass(MemoryViewer *outerInstance) : outerInstance(outerInstance)
	{
	}

	void MemoryViewer::ActionListenerAnonymousInnerClass::actionPerformed(java::awt::event::ActionEvent *evt)
	{
		outerInstance->GoToButtonActionPerformed(evt);
	}

	void MemoryViewer::memoryviewKeyPressed(java::awt::event::KeyEvent *evt)
	{ //GEN-FIRST:event_memoryviewKeyPressed
	   if (evt->getKeyCode() == java::awt::event::KeyEvent::VK_DOWN)
	   {
		   startaddress += 16;
		   evt->consume();
		   RefreshMemory();
	   }
	   else if (evt->getKeyCode() == java::awt::event::KeyEvent::VK_UP)
	   {
		   startaddress -= 16;
		   evt->consume();
		   RefreshMemory();
	   }
		else if (evt->getKeyCode() == java::awt::event::KeyEvent::VK_PAGE_UP)
		{
		   startaddress -= 352;
		   evt->consume();
		   RefreshMemory();
		}
		else if (evt->getKeyCode() == java::awt::event::KeyEvent::VK_PAGE_DOWN)
		{
		   startaddress += 352;
		   evt->consume();
		   RefreshMemory();
		}
	} //GEN-LAST:event_memoryviewKeyPressed

	void MemoryViewer::GoToButtonActionPerformed(java::awt::event::ActionEvent *evt)
	{ //GEN-FIRST:event_GoToButtonActionPerformed
			 string gettext = AddressField->getText();
			 int value;
			 try
			 {
				value = stoi(gettext, nullptr, 16);
			 }
			catch (const runtime_error &e)
			{
				JOptionPane::showMessageDialog(this, "The Number you enter is not correct");
				return;
			}
			 startaddress = value;
			 RefreshMemory();

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
