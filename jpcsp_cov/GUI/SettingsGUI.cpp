using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "SettingsGUI.h"
#include "../Settings.h"

namespace jpcsp::GUI
{
	using FolderChooser = com::jidesoft::swing::FolderChooser;
	using namespace jpcsp;
	using KeyEvent = java::awt::event::KeyEvent;
	using KeyListener = java::awt::event::KeyListener;
	using HashMap = java::util::HashMap;
	using Iterator = java::util::Iterator;
	using Map = java::util::Map;
	using JTextField = javax::swing::JTextField;
	using keyCode = jpcsp::Controller::keyCode;

	SettingsGUI::SettingsGUI()
	{
		initComponents();
		bool enabled = Settings::get_instance()->readBoolOptions("emuoptions/pbpunpack");
		pbpunpackcheck->setSelected(enabled);
		enabled = Settings::get_instance()->readBoolOptions("guisettings/saveWindowPos");
		saveWindowPosCheck->setSelected(enabled);
		enabled = Settings::get_instance()->readBoolOptions("guisettings/openLogwindow");
		openLogwindowCheck->setSelected(enabled);
		enabled = Settings::get_instance()->readBoolOptions("guisettings/snapLogwindow");
		snapConsoleCheck->setSelected(enabled);
		enabled = Settings::get_instance()->readBoolOptions("emuoptions/recompiler");
		recompilerCheck->setSelected(enabled);
		enabled = Settings::get_instance()->readBoolOptions("emuoptions/disablege");
		disableGECheck->setSelected(enabled);
		enabled = Settings::get_instance()->readBoolOptions("emuoptions/umdbrowser");
		if (enabled)
		{
			umdBrowser->setSelected(true);
		}
		else
		{
			ClassicOpenDialogumd->setSelected(true);
		}

		umdpath->setText(Settings::get_instance()->readStringOptions("emuoptions/umdpath"));
		/* load current config and set the config */
		loadKeys();

		/* add key listerners to the text fields */
		fieldCircle->addKeyListener(this);
		fieldCross->addKeyListener(this);
		fieldDown->addKeyListener(this);
		fieldLTrigger->addKeyListener(this);
		fieldLeft->addKeyListener(this);
		fieldRTrigger->addKeyListener(this);
		fieldRight->addKeyListener(this);
		fieldSelect->addKeyListener(this);
		fieldSquare->addKeyListener(this);
		fieldStart->addKeyListener(this);
		fieldTriangle->addKeyListener(this);
		fieldUp->addKeyListener(this);
		fieldHome->addKeyListener(this);
		fieldScreen->addKeyListener(this);
		fieldMusic->addKeyListener(this);
		fieldVolPlus->addKeyListener(this);
		fieldVolMin->addKeyListener(this);
		fieldHold->addKeyListener(this);
		fieldAnalogUp->addKeyListener(this);
		fieldAnalogDown->addKeyListener(this);
		fieldAnalogLeft->addKeyListener(this);
		fieldAnalogRight->addKeyListener(this);
	}

	void SettingsGUI::loadKeys()
	{
		currentKeys = Settings::get_instance()->loadKeys();
		revertKeys = unordered_map<keyCode, int>(22);

		unordered_map<int, keyCode>::const_iterator iter = currentKeys.begin();
		while (iter != currentKeys.end())
		{
			Map::Entry<int, keyCode> entry = (Map::Entry)*iter;
			keyCode key = static_cast<keyCode>(entry.getValue());
			int value = static_cast<int>(entry.getKey());

			revertKeys.emplace(key, value);

			switch (key)
			{
				case keyCode::DOWN:
					fieldDown->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::UP:
					fieldUp->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::LEFT:
					fieldLeft->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::RIGHT:
					fieldRight->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::ANDOWN:
					fieldAnalogDown->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::ANUP:
					fieldAnalogUp->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::ANLEFT:
					fieldAnalogLeft->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::ANRIGHT:
					fieldAnalogRight->setText(KeyEvent::getKeyText(value));
					break;

				case keyCode::TRIANGLE:
					fieldTriangle->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::SQUARE:
					fieldSquare->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::CIRCLE:
					fieldCircle->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::CROSS:
					fieldCross->setText(KeyEvent::getKeyText(value));
					break;
				case keyCode::L1:

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
