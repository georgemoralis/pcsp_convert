using namespace std;

#include "OptionPaneMultiple.h"

namespace jpcsp::util
{
	using Component = java::awt::Component;

	OptionPaneMultiple::OptionPaneMultiple(Component *parentComponent, const string &start, const string &end)
	{
		startaddr = new JTextField(5);
		endaddr = new JTextField(5);
		filename = new JTextField(5);
		filename->setText("dump.txt");
		startaddr->setText(start);
		endaddr->setText(end);
		any *msg = new any[6] {"Start address:", startaddr, "End address:", endaddr, "File name:", filename};

		any *options = new any[2] {"Ok", "Cancel"};
		JOptionPane *op = new JOptionPane(msg, JOptionPane::PLAIN_MESSAGE, JOptionPane::OK_CANCEL_OPTION, nullptr, options);

		JDialog *dialog = op->createDialog(parentComponent, "dump code...");
		dialog->setVisible(true);
		any selectedValue = op->getValue();


		//int result = JOptionPane.OK_OPTION;

		//try {
		//    result = ((Integer) op.getValue()).intValue();
		//} catch (Exception uninitializedValue) {
	   // }
		//System.out.println(selectedValue);
		if (!selectedValue.has_value())
		{
			cout << "dump code window Closed" << endl;

		}
		else if (selectedValue.equals("Ok"))
		{
			//System.out.println("dump code returns " + startaddr.getText() + " : " + endaddr.getText() + " : " + filename.getText());
			completed_Conflict = true;

		}
		else
		{
			cout << "dump code window Canceled" << endl;

		}

		delete op;
	}

	string *OptionPaneMultiple::getInput()
	{
		string *i = new string[3] {startaddr->getText(), endaddr->getText(), filename->getText()};
		return i;
	}

	bool OptionPaneMultiple::completed()
	{

		return completed_Conflict;
	}
}
