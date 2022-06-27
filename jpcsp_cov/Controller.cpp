using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "Controller.h"
#include "Settings.h"
#include "HLE/pspctrl.h"

namespace jpcsp
{
	using KeyEvent = java::awt::event::KeyEvent;
	using HashMap = java::util::HashMap;

	Controller::Controller()
	{
		/* load the button config */
		keys = unordered_map<int, keyCode>(22);
		loadKeyConfig();
		lastUpdate = System::currentTimeMillis();
	}

	void Controller::loadKeyConfig()
	{
		keys.clear();
		keys.putAll(Settings::get_instance()->loadKeys());
	}

	void Controller::loadKeyConfig(unordered_map<int, keyCode> &newLayout)
	{
		keys.clear();
		keys.putAll(newLayout);
	}

	void Controller::checkControllerState()
	{
		if (!changed)
		{
			return;
		}

		/* checkControllerState is called every cpu step,
		 * so we need to delay that a bit */
		long long now = System::currentTimeMillis();
		if (now - lastUpdate < 1000 / 30)
		{
			return;
		}

		jpcsp::HLE::pspctrl::get_instance()->setButtons(Lx, Ly, Buttons, pressed);
		changed = false;
		lastUpdate = now;
	}

	void Controller::keyPressed(KeyEvent *arg0)
	{
		keyCode key = keys[arg0->getKeyCode()];
		if (key == nullptr || key == lastKey)
		{
			return;
		}

		/* in digital mode, analoge keys behave as the digital keys (right?) */
		if (jpcsp::HLE::pspctrl::get_instance()->isModeDigital())
		{
			switch (key)
			{
				case jpcsp::Controller::keyCode::ANDOWN:
					key = keyCode::DOWN;
					break;
				case jpcsp::Controller::keyCode::ANUP:
					key = keyCode::UP;
					break;
				case jpcsp::Controller::keyCode::ANLEFT:
					key = keyCode::LEFT;
					break;
				case jpcsp::Controller::keyCode::ANRIGHT:
					key = keyCode::RIGHT;
					break;
			}
		}

		switch (key)
		{
			case jpcsp::Controller::keyCode::DOWN:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_DOWN;
				break;
			case jpcsp::Controller::keyCode::UP:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_UP;
				break;
			case jpcsp::Controller::keyCode::LEFT:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_LEFT;
				break;
			case jpcsp::Controller::keyCode::RIGHT:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_RIGHT;
				break;
			case jpcsp::Controller::keyCode::ANDOWN:
				this->Lx = 0;
				break;
			case jpcsp::Controller::keyCode::ANUP:
				this->Lx = static_cast<signed char>(255);
				break;
			case jpcsp::Controller::keyCode::ANLEFT:
				this->Ly = 0;
				break;
			case jpcsp::Controller::keyCode::ANRIGHT:
				this->Ly = static_cast<signed char>(255);
				break;

			case jpcsp::Controller::keyCode::TRIANGLE:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_TRIANGLE;
				break;
			case jpcsp::Controller::keyCode::SQUARE:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_SQUARE;
				break;
			case jpcsp::Controller::keyCode::CIRCLE:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_CIRCLE;
				break;
			case jpcsp::Controller::keyCode::CROSS:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_CROSS;
				break;
			case jpcsp::Controller::keyCode::L1:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_LTRIGGER;
				break;
			case jpcsp::Controller::keyCode::R1:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_RTRIGGER;
				break;
			case jpcsp::Controller::keyCode::START:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_START;
				break;
			case jpcsp::Controller::keyCode::SELECT:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_SELECT;
				break;

			case jpcsp::Controller::keyCode::HOME:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_HOME;
				break;
			case jpcsp::Controller::keyCode::HOLD:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_HOLD;
				break;
			case jpcsp::Controller::keyCode::VOLMIN:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_VOLDOWN;
				break;
			case jpcsp::Controller::keyCode::VOLPLUS:
				this->Buttons |= jpcsp::HLE::pspctrl::PSP_CTRL_VOLUP;

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
