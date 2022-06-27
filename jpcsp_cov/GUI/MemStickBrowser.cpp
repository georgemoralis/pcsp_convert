using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "MemStickBrowser.h"

namespace jpcsp::GUI
{
	using namespace jpcsp;
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
	using RandomAccessFile = java::io::RandomAccessFile;
	using ByteBuffer = java::nio::ByteBuffer;
	using FileChannel = java::nio::channels::FileChannel;
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
	using UmdIsoFile = jpcsp::filesystems::umdiso::UmdIsoFile;
	using UmdIsoReader = jpcsp::filesystems::umdiso::UmdIsoReader;
	using PBP = jpcsp::format::PBP;
	using PSF = jpcsp::format::PSF;
	using MetaInformation = jpcsp::util::MetaInformation;

	MemStickBrowser::MemStickTableColumnModel::CellRenderer::CellRenderer(MemStickBrowser::MemStickTableColumnModel *outerInstance) : outerInstance(outerInstance)
	{
	}

	Component *MemStickBrowser::MemStickTableColumnModel::CellRenderer::getTableCellRendererComponent(JTable *table, any obj, bool isSelected, bool hasFocus, int row, int column)
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

	MemStickBrowser::MemStickTableColumnModel::MemStickTableColumnModel(MemStickBrowser *outerInstance) : outerInstance(outerInstance)
	{
		setColumnMargin(0);
		CellRenderer *cellRenderer = new CellRenderer(this);
		TableColumn *tableColumn = new TableColumn(0, 144, cellRenderer, nullptr);
		tableColumn->setHeaderValue("Icon");
		tableColumn->setMaxWidth(154);
		tableColumn->setMinWidth(144);
		TableColumn *tableColumn2 = new TableColumn(1, 100, cellRenderer, nullptr);
		tableColumn2->setHeaderValue("Title");
		TableColumn *tableColumn3 = new TableColumn(2, 200, cellRenderer, nullptr);
		tableColumn3->setHeaderValue("Path");
		addColumn(tableColumn);
		addColumn(tableColumn2);
		addColumn(tableColumn3);

//JAVA TO C++ CONVERTER TODO TASK: A 'delete tableColumn3' statement was not added since tableColumn3 was passed to a method or constructor. Handle memory management manually.
//JAVA TO C++ CONVERTER TODO TASK: A 'delete tableColumn2' statement was not added since tableColumn2 was passed to a method or constructor. Handle memory management manually.
//JAVA TO C++ CONVERTER TODO TASK: A 'delete tableColumn' statement was not added since tableColumn was passed to a method or constructor. Handle memory management manually.
//JAVA TO C++ CONVERTER TODO TASK: A 'delete cellRenderer' statement was not added since cellRenderer was passed to a method or constructor. Handle memory management manually.
	}

	MemStickBrowser::MemStickTableModel::MemStickTableModel(MemStickBrowser *outerInstance, File *path) : outerInstance(outerInstance)
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
				File *metapbp = outerInstance->programs[i];
				if (outerInstance->programs[i]->isDirectory())
				{
					FileFilterAnonymousInnerClass2 tempVar2(this);
					File **eboot = outerInstance->programs[i]->listFiles(&tempVar2);

					metapbp = outerInstance->programs[i] = eboot[0];

					File *metadir = new File(outerInstance->programs[i]->getParentFile().getParentFile().getPath() + FileSystem::preferredSeparator() + "%" + outerInstance->programs[i]->getParentFile().getName());
					if (metadir->exists())
					{
						FileFilterAnonymousInnerClass3 tempVar3(this);
						eboot = metadir->listFiles(&tempVar3);
						if (eboot->length > 0)
						{
							metapbp = eboot[0];
						}
					}

					metadir = new File(outerInstance->programs[i]->getParentFile().getParentFile().getPath() + FileSystem::preferredSeparator() + outerInstance->programs[i]->getParentFile().getName() + "%");
					if (metadir->exists())
					{
						FileFilterAnonymousInnerClass4 tempVar4(this);
						eboot = metadir->listFiles(&tempVar4);
						if (eboot->length > 0)
						{
							metapbp = eboot[0];
						}
					}

					delete metadir;
				}
				if (outerInstance->programs[i]->getName()->toLowerCase().endsWith(".pbp"))
				{
					RandomAccessFile tempVar5(metapbp, "r");
					FileChannel *roChannel = (&tempVar5)->getChannel();
					ByteBuffer *readbuffer = roChannel->map(FileChannel::MapMode::READ_ONLY, 0, static_cast<int>(roChannel->size()));
					outerInstance->pbps[i] = new PBP(readbuffer);
					outerInstance->psfs[i] = outerInstance->pbps[i]->readPSF(readbuffer);
					if (outerInstance->pbps[i]->getSizeIcon0() > 0)
					{
						signed char *icon0 = new signed char[outerInstance->pbps[i]->getSizeIcon0()];
						readbuffer->position(static_cast<int>(outerInstance->pbps[i]->getOffsetIcon0()));
						readbuffer->get(icon0);
						outerInstance->icons[i] = new ImageIcon(icon0);
					}
				}
			}

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
