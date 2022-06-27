using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "ConsoleWindow.h"

namespace jpcsp::Debugger
{
	using BufferedWriter = java::io::BufferedWriter;
	using ByteArrayOutputStream = java::io::ByteArrayOutputStream;
	using File = java::io::File;
	using FileWriter = java::io::FileWriter;
	using FilterOutputStream = java::io::FilterOutputStream;
	using IOException = java::io::IOException;
	using OutputStream = java::io::OutputStream;
	using PrintStream = java::io::PrintStream;
	using JFileChooser = javax::swing::JFileChooser;
	using JOptionPane = javax::swing::JOptionPane;
	using Settings = jpcsp::Settings;

	ConsoleWindow::ConsoleWindow()
	{
		initComponents();
		System::setOut(m_stdoutPS);

	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") private void initComponents()
	void ConsoleWindow::initComponents()
	{

		jScrollPane1 = new javax::swing::JScrollPane();
		talogging = new javax::swing::JTextArea();
		ClearMessageButton = new javax::swing::JButton();
		SaveMessageToFileButton = new javax::swing::JButton();

		setTitle("Logger");
		setResizable(false);
		WindowAdapterAnonymousInnerClass tempVar(this);
		addWindowListener(&tempVar);

		talogging->setColumns(20);
		java::awt::Font tempVar2("Courier New", 0, 12);
		talogging->setFont(&tempVar2);
		talogging->setRows(5);
		jScrollPane1->setViewportView(talogging);

		ClearMessageButton->setText("Clear Messages");
		ActionListenerAnonymousInnerClass tempVar3(this);
		ClearMessageButton->addActionListener(&tempVar3);

		SaveMessageToFileButton->setText("Save Messages To File");
		ActionListenerAnonymousInnerClass2 tempVar4(this);
		SaveMessageToFileButton->addActionListener(&tempVar4);

		javax::swing::GroupLayout *layout = new javax::swing::GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout->setHorizontalGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addGroup(layout->createSequentialGroup().addContainerGap(317, numeric_limits<signed char>::max()).addComponent(SaveMessageToFileButton).addGap(18, 18, 18).addComponent(ClearMessageButton)).addComponent(jScrollPane1, javax::swing::GroupLayout::Alignment::TRAILING, javax::swing::GroupLayout::DEFAULT_SIZE, 583, numeric_limits<signed char>::max()));
		layout->setVerticalGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addGroup(javax::swing::GroupLayout::Alignment::TRAILING, layout->createSequentialGroup().addComponent(jScrollPane1, javax::swing::GroupLayout::DEFAULT_SIZE, 226, numeric_limits<signed char>::max()).addPreferredGap(javax::swing::LayoutStyle::ComponentPlacement::RELATED).addGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::BASELINE).addComponent(ClearMessageButton).addComponent(SaveMessageToFileButton))));

		pack();

//JAVA TO C++ CONVERTER TODO TASK: A 'delete layout' statement was not added since layout was passed to a method or constructor. Handle memory management manually.
	} // </editor-fold>//GEN-END:initComponents

	ConsoleWindow::WindowAdapterAnonymousInnerClass::WindowAdapterAnonymousInnerClass(ConsoleWindow *outerInstance) : outerInstance(outerInstance)
	{
	}

	void ConsoleWindow::WindowAdapterAnonymousInnerClass::windowDeactivated(java::awt::event::WindowEvent *evt)
	{
		outerInstance->formWindowDeactivated(evt);
	}

	ConsoleWindow::ActionListenerAnonymousInnerClass::ActionListenerAnonymousInnerClass(ConsoleWindow *outerInstance) : outerInstance(outerInstance)
	{
	}

	void ConsoleWindow::ActionListenerAnonymousInnerClass::actionPerformed(java::awt::event::ActionEvent *evt)
	{
		outerInstance->ClearMessageButtonActionPerformed(evt);
	}

	ConsoleWindow::ActionListenerAnonymousInnerClass2::ActionListenerAnonymousInnerClass2(ConsoleWindow *outerInstance) : outerInstance(outerInstance)
	{
	}

	void ConsoleWindow::ActionListenerAnonymousInnerClass2::actionPerformed(java::awt::event::ActionEvent *evt)
	{
		outerInstance->SaveMessageToFileButtonActionPerformed(evt);
	}

	void ConsoleWindow::ClearMessageButtonActionPerformed(java::awt::event::ActionEvent *evt)
	{ //GEN-FIRST:event_ClearMessageButtonActionPerformed
	   clearScreenMessages();
	} //GEN-LAST:event_ClearMessageButtonActionPerformed

	void ConsoleWindow::SaveMessageToFileButtonActionPerformed(java::awt::event::ActionEvent *evt)
	{ //GEN-FIRST:event_SaveMessageToFileButtonActionPerformed
			JFileChooser *m_fileChooser = new JFileChooser();
			File tempVar("logoutput.txt");
			m_fileChooser->setSelectedFile(&tempVar);
			m_fileChooser->setDialogTitle("Save logging output");
			File tempVar2(".");
			m_fileChooser->setCurrentDirectory(&tempVar2);
			int returnVal = m_fileChooser->showSaveDialog(this);
			if (returnVal == JFileChooser::APPROVE_OPTION)
			{
				File *f = m_fileChooser->getSelectedFile();

				try
				{
					if (f->exists())
					{
						int res = JOptionPane::showConfirmDialog(this, "File already Exists! Do you want to override?", "Already Exists Message", JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE);

						if (res != 0)
						{
							delete m_fileChooser;
							return;
						}
					}

					//IOHelper.saveTxtFile(f, ta_messages.getText(), false);
					BufferedWriter *out = nullptr;
					try
					{
						 FileWriter tempVar3(f);
						 out = new BufferedWriter(&tempVar3);
						 out->write(talogging->getText());
					}
					 catch (const IOException &e)
					 {
					  delete out;
					  delete m_fileChooser;
					  throw (e);
					 }
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the exception 'finally' clause:
					finally
					{
					   if (out != nullptr)
					   {
						 try
						 {
						 out->close();
						 }
					   catch (const IOException &ex)
					   {
						//throw( ex );
						ex->printStackTrace();
					   }
					   }
					}

					delete out;
				}
				catch (const runtime_error &e)
				{
					e.printStackTrace();
				}
			}

		delete m_fileChooser;
	} //GEN-LAST:event_SaveMessageToFileButtonActionPerformed

	void ConsoleWindow::formWindowDeactivated(java::awt::event::WindowEvent *evt)
	{ //GEN-FIRST:event_formWindowDeactivated
		//Called when the mainWindow is closed
		if (Settings::get_instance()->readBoolOptions("guisettings/saveWindowPos"))
		{
			Settings::get_instance()->writeWindowPos("logwindow", getLocation());
		}
	} //GEN-LAST:event_formWindowDeactivated

	void ConsoleWindow::clearScreenMessages()
	{
		scoped_lock<mutex> lock(lock_object);
		talogging->setText("");
	}

	ConsoleWindow::JTextAreaOutStream::JTextAreaOutStream(ConsoleWindow *outerInstance, OutputStream *aStream) : java::io::FilterOutputStream(aStream), outerInstance(outerInstance)
	{
	}


//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
