using namespace std;

#include "AllegrexBasicBlock.h"

namespace jpcsp
{
	using Method = java::lang::reflect::Method;
	using ClassPool = javassist::ClassPool;
	using CtClass = javassist::CtClass;
	using CtNewMethod = javassist::CtNewMethod;
javassist::ClassPool *AllegrexBasicBlock::pool = javassist::ClassPool::getDefault();

	int AllegrexBasicBlock::getEntry()
	{
		return entry;
	}

	int AllegrexBasicBlock::getSize()
	{
		return entry;
	}

	AllegrexBasicBlock::AllegrexBasicBlock(Processor *processor, int entry)
	{
		this->processor = processor;
		this->entry = entry;

		creationTimestamp = System::currentTimeMillis();

		processor->tracked_gpr = new Processor::RegisterTracking*[32];
	}

	void AllegrexBasicBlock::emit(const string &javaCode)
	{
		if (!freezed)
		{
			if (javaCode.ends_with(";"))
			{
				buffer->append(javaCode + "\n");
			}
			else
			{
				buffer->append(javaCode);
			}
		}
	}

	void AllegrexBasicBlock::freeze()
	{

		processor->reset_register_tracking();

		cout << "Freezing basic block : " << Integer::toHexString(entry) << endl;

		StringBuilder *javaMethod = new StringBuilder("public static void execute");
		javaMethod->append("(jpcsp.Processor processor, Integer entry) {\n");
		javaMethod->append("jpcsp.Memory memory = jpcsp.Memory.get_instance();\n");
		javaMethod->append("while(processor.pc == entry.intValue()) {\n");
		javaMethod->append(buffer)->append("}; };");

		cout << javaMethod->toString() << endl;

		CtClass *dynaCtClass = pool->makeClass("BasicBlock" + Integer::toHexString(entry));
		try
		{
			dynaCtClass->addMethod(CtNewMethod::make(javaMethod->toString(), dynaCtClass));
			type_info dynaClass = dynaCtClass->toClass();
//JAVA TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the Java 'class' method:
			method = dynaClass.getDeclaredMethod("execute", Processor::class, Integer::class);
		}
		catch (const runtime_error &e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		freezed = true;

		delete javaMethod;
	}

	void AllegrexBasicBlock::execute()
	{
		try
		{
			method->invoke(nullptr, processor, entry);
		}
		catch (const runtime_error &e)
		{
			e.printStackTrace();
		}
	}
}
