using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "Settings.h"

namespace jpcsp
{
	using Point = java::awt::Point;
	using KeyEvent = java::awt::event::KeyEvent;
	using File = java::io::File;
	using FileNotFoundException = java::io::FileNotFoundException;
	using FileOutputStream = java::io::FileOutputStream;
	using IOException = java::io::IOException;
	using HashMap = java::util::HashMap;
	using Iterator = java::util::Iterator;
	using Map = java::util::Map;
	using DocumentBuilder = javax::xml::parsers::DocumentBuilder;
	using DocumentBuilderFactory = javax::xml::parsers::DocumentBuilderFactory;
	using ParserConfigurationException = javax::xml::parsers::ParserConfigurationException;
	using Transformer = javax::xml::transform::Transformer;
	using TransformerConfigurationException = javax::xml::transform::TransformerConfigurationException;
	using TransformerException = javax::xml::transform::TransformerException;
	using TransformerFactory = javax::xml::transform::TransformerFactory;
	using DOMSource = javax::xml::transform::dom::DOMSource;
	using StreamResult = javax::xml::transform::stream::StreamResult;
	using XPath = javax::xml::xpath::XPath;
	using XPathConstants = javax::xml::xpath::XPathConstants;
	using XPathFactory = javax::xml::xpath::XPathFactory;
	using keyCode = jpcsp::Controller::keyCode;
	using Document = org::w3c::dom::Document;
	using Element = org::w3c::dom::Element;
	using SAXException = org::xml::sax::SAXException;
const string Settings::SETTINGS_FILE_NAME = "Settings.xml";
const string Settings::DEFAULT_SETTINGS_FILE_NAME = "/jpcsp/DefaultSettings.xml";
Settings *Settings::instance = nullptr;

	Settings *Settings::get_instance()
	{
		if (instance == nullptr)
		{
			instance = new Settings();
		}
		return instance;
	}

	void Settings::NullSettings()
	{
		instance = nullptr;
	}

	string Settings::readXmlSetting(const string &path)
	{
	   try
	   {
		  XPathFactory *xpathFactory = XPathFactory::newInstance();
		  XPath *xpath = xpathFactory->newXPath();
		  string value = xpath->evaluate(path, getSettingsDocument());

		  // System.out.println(path + " = " + value);

		  return value;
	   }
	   catch (const runtime_error &e)
	   {
		  e.printStackTrace();
		  return "";
	   }
	}

	Document *Settings::getSettingsDocument()
	{
		if (doc == nullptr)
		{
			DocumentBuilderFactory *dbFactory = DocumentBuilderFactory::newInstance();
			DocumentBuilder *builder = dbFactory->newDocumentBuilder();
			try
			{

				File tempVar(SETTINGS_FILE_NAME);
				doc = builder->parse(&tempVar);

			}
			catch (const runtime_error &e)
			{
				cout << "Error while loading existing settings. Restoring default settings." << endl;
				e.printStackTrace();
				try
				{
					doc = builder->parse(getClass().getResourceAsStream(DEFAULT_SETTINGS_FILE_NAME));
					cout << "Default settings loaded successfully" << endl;
				}
				catch (const runtime_error &e1)
				{
					e1.printStackTrace();
					cout << "Unable to load default settings" << endl;
				}
			}


		}
		return doc;
	}

	void Settings::writeSettings()
	{
	   try
	   {
			FileOutputStream *fileOutputStream = new FileOutputStream(SETTINGS_FILE_NAME);
			TransformerFactory *tFactory = TransformerFactory::newInstance();
			Transformer *transformer = tFactory->newTransformer();
			DOMSource tempVar(doc);
			StreamResult tempVar2(fileOutputStream);
			transformer->transform(&tempVar, &tempVar2);
			fileOutputStream->close();

//JAVA TO C++ CONVERTER TODO TASK: A 'delete fileOutputStream' statement was not added since fileOutputStream was passed to a method or constructor. Handle memory management manually.
	   }
		catch (const FileNotFoundException &e)
		{
			e->printStackTrace();
		}
		catch (const IOException &e)
		{
			e->printStackTrace();
		}
		catch (const TransformerConfigurationException &e)
		{
		 e->printStackTrace();
		}
	  catch (const TransformerException &e)
	  {
		 e->printStackTrace();
	  }
	}

	int *Settings::readWindowPos(const string &windowname)
	{
		int *coord = new int[2];
		try
		{
		   string x = readXmlSetting("//guisettings/windowspos/" + windowname + "/x");
		   string y = readXmlSetting("//guisettings/windowspos/" + windowname + "/y");
			coord[0] = x != "" ? stoi(x) : 0;
			coord[1] = y != "" ? stoi(y) : 0;
		}
		catch (const runtime_error &e)
		{
			e.printStackTrace();
		}
		return coord;
	}

	int *Settings::readWindowSize(const string &windowname)
	{
		 int *dimension = new int[2];
		 try
		 {
			string x = readXmlSetting("//guisettings/windowsize/" + windowname + "/x");
			string y = readXmlSetting("//guisettings/windowsize/" + windowname + "/y");
			dimension[0] = x != "" ? stoi(x) : 0;
			dimension[1] = y != "" ? stoi(y) : 0;
		 }
		 catch (const runtime_error &e)
		 {
			 e.printStackTrace();
		 }
		 return dimension;
	}

	void Settings::writeWindowPos(const string &windowname, Point *pos)
	{
		string *coord = new string[2];
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'toString':

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
