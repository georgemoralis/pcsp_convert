using namespace std;

#include "ElfHeaderInfo.h"
#include "../FileManager.h"
#include "../Settings.h"

namespace jpcsp::Debugger
{
	using namespace jpcsp;

	ElfHeaderInfo::ElfHeaderInfo()
	{
		initComponents();
		ELFInfoArea->append(FileManager::PbpInfo);
		ELFInfoArea->append(FileManager::ElfInfo);
		ELFInfoArea->append(FileManager::ProgInfo);
		ELFInfoArea->append(FileManager::SectInfo);

	}

	void ElfHeaderInfo::RefreshWindow()
	{
	  ELFInfoArea->setText("");
	  ELFInfoArea->append(FileManager::PbpInfo);
	  ELFInfoArea->append(FileManager::ElfInfo);
	  ELFInfoArea->append(FileManager::ProgInfo);
	  ELFInfoArea->append(FileManager::SectInfo);
	}

//JAVA TO C++ CONVERTER TODO TASK: Most Java annotations will not have direct C++ equivalents:
//ORIGINAL LINE: @SuppressWarnings("unchecked") private void initComponents()
	void ElfHeaderInfo::initComponents()
	{

		jScrollPane1 = new javax::swing::JScrollPane();
		ELFInfoArea = new javax::swing::JTextArea();

		setTitle("Elf Header Info");
		setResizable(false);
		WindowAdapterAnonymousInnerClass tempVar(this);
		addWindowListener(&tempVar);

		ELFInfoArea->setColumns(20);
		ELFInfoArea->setEditable(false);
		java::awt::Font tempVar2("Courier New", 0, 12);
		ELFInfoArea->setFont(&tempVar2);
		ELFInfoArea->setLineWrap(true);
		ELFInfoArea->setRows(5);
		jScrollPane1->setViewportView(ELFInfoArea);

		javax::swing::GroupLayout *layout = new javax::swing::GroupLayout(getContentPane());
		getContentPane().setLayout(layout);
		layout->setHorizontalGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addComponent(jScrollPane1, javax::swing::GroupLayout::DEFAULT_SIZE, 253, numeric_limits<signed char>::max()));
		layout->setVerticalGroup(layout->createParallelGroup(javax::swing::GroupLayout::Alignment::LEADING).addComponent(jScrollPane1, javax::swing::GroupLayout::DEFAULT_SIZE, 329, numeric_limits<signed char>::max()));

		pack();

//JAVA TO C++ CONVERTER TODO TASK: A 'delete layout' statement was not added since layout was passed to a method or constructor. Handle memory management manually.
	} // </editor-fold>//GEN-END:initComponents

	ElfHeaderInfo::WindowAdapterAnonymousInnerClass::WindowAdapterAnonymousInnerClass(ElfHeaderInfo *outerInstance) : outerInstance(outerInstance)
	{
	}

	void ElfHeaderInfo::WindowAdapterAnonymousInnerClass::windowDeactivated(java::awt::event::WindowEvent *evt)
	{
		outerInstance->formWindowDeactivated(evt);
	}

	void ElfHeaderInfo::formWindowDeactivated(java::awt::event::WindowEvent *evt)
	{ //GEN-FIRST:event_formWindowDeactivated
		//Called when the mainWindow is closed
		if (Settings::get_instance()->readBoolOptions("guisettings/saveWindowPos"))
		{
			Settings::get_instance()->writeWindowPos("elfheader", getLocation());
		}
	} //GEN-LAST:event_formWindowDeactivated
}
