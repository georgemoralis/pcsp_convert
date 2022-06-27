#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "../filesystems/umdiso/UmdIsoFile.h"
#include "../filesystems/umdiso/UmdIsoReader.h"
#include "../format/PBP.h"
#include "../format/PSF.h"
#include "../util/MetaInformation.h"
#include "../MainGUI.h"
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <any>
#include "exceptionhelper.h"
#include "../tangible_filesystem.h"

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
namespace jpcsp::GUI
{

	using namespace jpcsp;
	using Component = java::awt::Component;
	using File = java::io::File;


	using ImageIcon = javax::swing::ImageIcon;
	using JButton = javax::swing::JButton;
	using JDialog = javax::swing::JDialog;
	using JTable = javax::swing::JTable;
	using AbstractTableModel = javax::swing::table::AbstractTableModel;
	using DefaultTableCellRenderer = javax::swing::table::DefaultTableCellRenderer;
	using DefaultTableColumnModel = javax::swing::table::DefaultTableColumnModel;

	using PBP = jpcsp::format::PBP;
	using PSF = jpcsp::format::PSF;

	/**
	 * @author Orphis
	 * 
	 */
	class MemStickBrowser : public JDialog
	{

	private:
		class MemStickTableColumnModel final : public DefaultTableColumnModel
		{
		private:
			MemStickBrowser *outerInstance;

			static constexpr long long serialVersionUID = -6321946514015824875LL;

		private:
			class CellRenderer final : public DefaultTableCellRenderer
			{
			private:
				MemStickBrowser::MemStickTableColumnModel *outerInstance;

			public:
				virtual ~CellRenderer()
				{
					delete outerInstance;
				}

				CellRenderer(MemStickBrowser::MemStickTableColumnModel *outerInstance);

			private:
				static constexpr long long serialVersionUID = 6767267483048658105LL;

			public:
				Component *getTableCellRendererComponent(JTable *table, std::any obj, bool isSelected, bool hasFocus, int row, int column) override;
			};

		public:
			virtual ~MemStickTableColumnModel()
			{
				delete outerInstance;
			}

			MemStickTableColumnModel(MemStickBrowser *outerInstance);
		};

	private:
		class MemStickTableModel final : public AbstractTableModel
		{
		private:
			MemStickBrowser *outerInstance;

			static constexpr long long serialVersionUID = -1675488447176776560LL;



		public:
			virtual ~MemStickTableModel()
			{
				delete outerInstance;
			}

			MemStickTableModel(MemStickBrowser *outerInstance, File *path);

		private:
			class FileFilterAnonymousInnerClass : public FileFilter
			{
			private:
				MemStickTableModel *outerInstance;

			public:
				virtual ~FileFilterAnonymousInnerClass()
				{
					delete outerInstance;
				}

				FileFilterAnonymousInnerClass(MemStickTableModel *outerInstance);

				bool accept(File *file) override;

			private:
				class FileFilterAnonymousInnerClass5 : public FileFilter
				{
				private:
					FileFilterAnonymousInnerClass *outerInstance;

				public:
					virtual ~FileFilterAnonymousInnerClass5()
					{
						delete outerInstance;
					}

					FileFilterAnonymousInnerClass5(FileFilterAnonymousInnerClass *outerInstance);

					bool accept(File *arg0) override;
				};
			};

		private:
			class FileFilterAnonymousInnerClass2 : public FileFilter
			{
			private:
				MemStickTableModel *outerInstance;

			public:
				virtual ~FileFilterAnonymousInnerClass2()
				{
					delete outerInstance;
				}

				FileFilterAnonymousInnerClass2(MemStickTableModel *outerInstance);

				bool accept(File *arg0) override;
			};

		private:
			class FileFilterAnonymousInnerClass3 : public FileFilter
			{
			private:
				MemStickTableModel *outerInstance;

			public:
				virtual ~FileFilterAnonymousInnerClass3()
				{
					delete outerInstance;
				}

				FileFilterAnonymousInnerClass3(MemStickTableModel *outerInstance);

				bool accept(File *arg0) override;
			};

		private:
			class FileFilterAnonymousInnerClass4 : public FileFilter
			{
			private:
				MemStickTableModel *outerInstance;

			public:
				virtual ~FileFilterAnonymousInnerClass4()
				{
					delete outerInstance;
				}

				FileFilterAnonymousInnerClass4(MemStickTableModel *outerInstance);

				bool accept(File *arg0) override;
			};

		public:
			int getColumnCount() override;

			int getRowCount() override;

			std::any getValueAt(int rowIndex, int columnIndex) override;

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
