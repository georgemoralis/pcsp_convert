#pragma once

#include "../Settings.h"
#include <string>
#include <limits>
#include <stdexcept>
#include <mutex>
#include "exceptionhelper.h"

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
namespace jpcsp::Debugger
{

	using ByteArrayOutputStream = java::io::ByteArrayOutputStream;
	using FilterOutputStream = java::io::FilterOutputStream;
	using IOException = java::io::IOException;
	using OutputStream = java::io::OutputStream;
	using PrintStream = java::io::PrintStream;

	/**
	 *
	 * @author  shadow
	 */
	class ConsoleWindow : public javax::swing::JFrame
	{
		private:
			std::mutex lock_object;

		PrintStream *m_stdoutPS = new PrintStream(new JTextAreaOutStream(this, new ByteArrayOutputStream()));

		/**
		 * Display infinite characters in the textarea, no limit.
		 * <p>
		 * <b>NOTE:</b> Will slow down your application if a lot of messages
		 * are to be displayed to the textarea (more than a couple of Kbytes).
		 */
		int m_maxChars = -1;


		/** Creates new form LoggingWindow */
	public:
		virtual ~ConsoleWindow()
		{
			delete m_stdoutPS;
			delete ClearMessageButton;
			delete SaveMessageToFileButton;
			delete jScrollPane1;
			delete talogging;
		}

		ConsoleWindow();

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
		class WindowAdapterAnonymousInnerClass : public java::awt::event::WindowAdapter
		{
		private:
			ConsoleWindow *outerInstance;

		public:
			virtual ~WindowAdapterAnonymousInnerClass()
			{
				delete outerInstance;
			}

			WindowAdapterAnonymousInnerClass(ConsoleWindow *outerInstance);

			void windowDeactivated(java::awt::event::WindowEvent *evt);
		};

	private:
		class ActionListenerAnonymousInnerClass : public java::awt::event::ActionListener
		{
		private:
			ConsoleWindow *outerInstance;

		public:
			virtual ~ActionListenerAnonymousInnerClass()
			{
				delete outerInstance;
			}

			ActionListenerAnonymousInnerClass(ConsoleWindow *outerInstance);

			void actionPerformed(java::awt::event::ActionEvent *evt);
		};

	private:
		class ActionListenerAnonymousInnerClass2 : public java::awt::event::ActionListener
		{
		private:
			ConsoleWindow *outerInstance;

		public:
			virtual ~ActionListenerAnonymousInnerClass2()
			{
				delete outerInstance;
			}

			ActionListenerAnonymousInnerClass2(ConsoleWindow *outerInstance);

			void actionPerformed(java::awt::event::ActionEvent *evt);
		};

private:
	void ClearMessageButtonActionPerformed(java::awt::event::ActionEvent *evt);

	void SaveMessageToFileButtonActionPerformed(java::awt::event::ActionEvent *evt);

	void formWindowDeactivated(java::awt::event::WindowEvent *evt);
		/**
		 * Clears only the messages that are displayed in the textarea.
		 */
	public:
		virtual void clearScreenMessages();

		// Variables declaration - do not modify//GEN-BEGIN:variables
	private:
		javax::swing::JButton *ClearMessageButton;
		javax::swing::JButton *SaveMessageToFileButton;
		javax::swing::JScrollPane *jScrollPane1;
		javax::swing::JTextArea *talogging;
		// End of variables declaration//GEN-END:variables
	 /**
	     * Private inner class. Filter to redirect the data to the textarea.
	     */
	private:
		class JTextAreaOutStream final : public FilterOutputStream
		{
			private:
				std::mutex lock_object;

			ConsoleWindow *outerInstance;



			/**
			 * Constructor.
			 * <p>
			 * @param aStream   The <code>OutputStream</code>.
			 */
		public:
			virtual ~JTextAreaOutStream()
			{
				delete outerInstance;
			}

			JTextAreaOutStream(ConsoleWindow *outerInstance, OutputStream *aStream);


			/**
			 * Writes the messages.
			 * <p>
			 * @param b     The message in a <code>byte[]</code> array.
			 * <p>
			 * @throws IOException
			 */
			void write(signed char b[]);


			/**
			 * Writes the messages.
			 * <p>
			 * @param b     The message in a <code>byte[]</code> array.
			 * @param off   The offset.
			 * @param len   Length.
			 * <p>
			 * @throws IOException
			 */
			void write(signed char b[], int off, int len);


			/**
			 * Appends a message to the textarea and the 
			 * <p>
			 * @param s     The message.
			 */
		private:
			void appendMessage(const std::string &s);


			void flushTextArea();

		};
	};


}
