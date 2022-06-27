using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "UmdBrowser.h"

namespace jpcsp::GUI
{
	using Component = java::awt::Component;
	using Frame = java::awt::Frame;
	using ActionEvent = java::awt::event::ActionEvent;
	using ActionListener = java::awt::event::ActionListener;
	using MouseAdapter = java::awt::event::MouseAdapter;
	using MouseEvent = java::awt::event::MouseEvent;
	using File = java::io::File;
	using FileFilter = java::io::FileFilter;
	using FileNotFoundException = java::io::FileNotFoundException;
	using IOException = java::io::IOException;
	using ByteBuffer = java::nio::ByteBuffer;
	using GroupLayout = javax::swing::GroupLayout;
	using Icon = javax::swing::Icon;
	using ImageIcon = javax::swing::ImageIcon;
	using JButton = javax::swing::JButton;
	using JDialog = javax::swing::JDialog;
	using JScrollPane = javax::swing::JScrollPane;
	using JTable = javax::swing::JTable;
	using ListSelectionModel = javax::swing::ListSelectionModel;
	using UIManager = javax::swing::UIManager;
	using WindowConstants = javax::swing::WindowConstants;
	using ListSelectionEvent = javax::swing::event::ListSelectionEvent;
	using ListSelectionListener = javax::swing::event::ListSelectionListener;
	using AbstractTableModel = javax::swing::table::AbstractTableModel;
	using DefaultTableCellRenderer = javax::swing::table::DefaultTableCellRenderer;
	using DefaultTableColumnModel = javax::swing::table::DefaultTableColumnModel;
	using JTableHeader = javax::swing::table::JTableHeader;
	using TableCellRenderer = javax::swing::table::TableCellRenderer;
	using TableColumn = javax::swing::table::TableColumn;
	using MainGUI = jpcsp::MainGUI;
	using UmdIsoFile = jpcsp::filesystems::umdiso::UmdIsoFile;
	using UmdIsoReader = jpcsp::filesystems::umdiso::UmdIsoReader;
	using PBP = jpcsp::format::PBP;
	using PSF = jpcsp::format::PSF;
	using MetaInformation = jpcsp::util::MetaInformation;

	UmdBrowser::MemStickTableColumnModel::CellRenderer::CellRenderer(UmdBrowser::MemStickTableColumnModel *outerInstance) : outerInstance(outerInstance)
	{
	}

	Component *UmdBrowser::MemStickTableColumnModel::CellRenderer::getTableCellRendererComponent(JTable *table, any obj, bool isSelected, bool hasFocus, int row, int column)
	{
		if (obj.type() == typeid(Icon))
		{
			setText("");
			setIcon(any_cast<Icon*>(obj));
			return this;
		}
		setIcon(nullptr);
		return javax::swing::table::DefaultTableCellRenderer::getTableCellRendererComponent(table, obj, isSelected, hasFocus, row, column);
	}

	UmdBrowser::MemStickTableColumnModel::MemStickTableColumnModel(UmdBrowser *outerInstance) : outerInstance(outerInstance)
	{
		setColumnMargin(0);
		CellRenderer *cellRenderer = new CellRenderer(this);
		TableColumn *tableColumn = new TableColumn(0, 144, cellRenderer, nullptr);
		tableColumn->setHeaderValue("Icon");
		tableColumn->setMaxWidth(154);
		tableColumn->setMinWidth(144);
		TableColumn *tableColumn2 = new TableColumn(1, 100, cellRenderer, nullptr);
		tableColumn2->setHeaderValue("Title");
					TableColumn *tableColumn3 = new TableColumn(2, 150, cellRenderer, nullptr);
		tableColumn3->setHeaderValue("DiscID");
					TableColumn *tableColumn4 = new TableColumn(3, 100, cellRenderer, nullptr);
		tableColumn4->setHeaderValue("Firmware");
		TableColumn *tableColumn5 = new TableColumn(4, 200, cellRenderer, nullptr);
		tableColumn5->setHeaderValue("Path");
		addColumn(tableColumn);
		addColumn(tableColumn2);
		addColumn(tableColumn3);
					addColumn(tableColumn4);
					addColumn(tableColumn5);

//JAVA TO C++ CONVERTER TODO TASK: A 'delete tableColumn5' statement was not added since tableColumn5 was passed to a method or constructor. Handle memory management manually.
//JAVA TO C++ CONVERTER TODO TASK: A 'delete tableColumn4' statement was not added since tableColumn4 was passed to a method or constructor. Handle memory management manually.
//JAVA TO C++ CONVERTER TODO TASK: A 'delete tableColumn3' statement was not added since tableColumn3 was passed to a method or constructor. Handle memory management manually.
//JAVA TO C++ CONVERTER TODO TASK: A 'delete tableColumn2' statement was not added since tableColumn2 was passed to a method or constructor. Handle memory management manually.
//JAVA TO C++ CONVERTER TODO TASK: A 'delete tableColumn' statement was not added since tableColumn was passed to a method or constructor. Handle memory management manually.
//JAVA TO C++ CONVERTER TODO TASK: A 'delete cellRenderer' statement was not added since cellRenderer was passed to a method or constructor. Handle memory management manually.
	}

	UmdBrowser::MemStickTableModel::MemStickTableModel(UmdBrowser *outerInstance, File *path) : outerInstance(outerInstance)
	{
		if (!path->isDirectory())
		{
			cout << path << " isn't a directory" << endl;
			return;
		}
		FileFilterAnonymousInnerClass tempVar(this);
		outerInstance->programs = path->listFiles(&tempVar);

		outerInstance->icons = new ImageIcon*[outerInstance->programs->length];
		outerInstance->pbps = new PBP*[outerInstance->programs->length];
		outerInstance->psfs = new PSF*[outerInstance->programs->length];

		for (int i = 0; i < outerInstance->programs->length; ++i)
		{
			try
			{
					if (outerInstance->programs[i]->isDirectory())
					{
							FileFilterAnonymousInnerClass2 tempVar2(this);
							File **eboot = outerInstance->programs[i]->listFiles(&tempVar2);
							outerInstance->programs[i] = eboot[0];
					}

					if (!outerInstance->programs[i]->isDirectory())
					{
						UmdIsoReader *iso = new UmdIsoReader(outerInstance->programs[i]->getPath());
						UmdIsoFile *paramSfo = iso->getFile("PSP_GAME/param.sfo");

						outerInstance->psfs[i] = new PSF(0);
						signed char *sfo = new signed char[static_cast<int>(paramSfo->length())];
						paramSfo->read(sfo);
						ByteBuffer *buf = ByteBuffer::wrap(sfo);
						outerInstance->psfs[i]->read(buf);

						UmdIsoFile *icon0umd = iso->getFile("PSP_GAME/ICON0.PNG");
						signed char *icon0 = new signed char[static_cast<int>(icon0umd->length())];
						icon0umd->read(icon0);
						outerInstance->icons[i] = new ImageIcon(icon0);

						delete iso;
					}
			}
			catch (const FileNotFoundException &e)
			{
				e->printStackTrace();
			}
			catch (const IOException &e)
			{
				e->printStackTrace();
			}
		}
	}

	UmdBrowser::MemStickTableModel::FileFilterAnonymousInnerClass::FileFilterAnonymousInnerClass(MemStickTableModel *outerInstance) : outerInstance(outerInstance)
	{
	}

	bool UmdBrowser::MemStickTableModel::FileFilterAnonymousInnerClass::accept(File *file)
	{
		string lower = file->getName()->toLowerCase();
		if (lower.ends_with(".cso") || lower.ends_with(".iso"))
		{

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
