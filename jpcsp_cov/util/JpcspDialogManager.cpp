using namespace std;

#include "JpcspDialogManager.h"
#include "MetaInformation.h"

namespace jpcsp::util
{
	using Component = java::awt::Component;
	using JOptionPane = javax::swing::JOptionPane;

	void JpcspDialogManager::showInformation(Component *compo, const string &message)
	{
		JOptionPane::showMessageDialog(compo, message, MetaInformation::FULL_NAME, JOptionPane::INFORMATION_MESSAGE);
	}

	void JpcspDialogManager::showWarning(Component *compo, const string &message)
	{
		JOptionPane::showMessageDialog(compo, message, MetaInformation::FULL_NAME, JOptionPane::WARNING_MESSAGE);
	}

	void JpcspDialogManager::showError(Component *compo, const string &message)
	{
		JOptionPane::showMessageDialog(compo, message, MetaInformation::FULL_NAME, JOptionPane::ERROR_MESSAGE);
	}
}
