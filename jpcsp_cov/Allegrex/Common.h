#pragma once

#include "../Processor.h"
#include "../util/Utilities.h"
#include "../Syscallv15.h"
#include <string>
#include <regex>
#include "../stringhelper.h"

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
namespace jpcsp::Allegrex
{

	using Processor = jpcsp::Processor;

	/**
	 *
	 * @author hli
	 */
	class Common
	{

	public:
		class Instruction
		{

		private:
			int m_count = 0;

		public:
			virtual void interpret(Processor *processor, int insn) = 0;

			virtual void compile(Processor *processor, int insn) = 0;

			virtual std::string disasm(int address, int insn) = 0;

			virtual std::string name() = 0;

			virtual std::string category() = 0;

			virtual void resetCount();

			virtual void increaseCount();

			virtual int getCount();

			virtual int count();

			virtual Instruction *instance(int insn);

			Instruction(int index);

			Instruction();
		};

	public:
		class STUB : public Instruction
		{

		public:
			void interpret(Processor *processor, int insn) override;

			void compile(Processor *processor, int insn) override;

			std::string disasm(int address, int insn) override;

			Instruction *instance(int insn) = 0; override override;

			std::string name() final override;

			std::string category() final override;
		};
	public:
		static const Instruction *UNK;

	private:
		class InstructionAnonymousInnerClass : public Instruction
		{

		public:
			void interpret(Processor *processor, int insn) override;

			void compile(Processor *processor, int insn) override;

			std::string disasm(int address, int insn) override;

			std::string name() final override;

			std::string category() final override;
		};
	public:
		static std::string *gprNames;
		static std::string *fprNames;
		static std::string **vprNames;
		static std::string *fcrNames;
		static std::string *cop0Names;
		static std::string *vsuffix;
		static const std::string *ccondsNames;

		static std::string disasmRDRTSA(const std::string &opname, int rd, int rt, int sa);

		static std::string disasmRDRTRS(const std::string &opname, int rd, int rt, int rs);

		static std::string disasmRS(const std::string &opname, int rs);

		static std::string disasmRT(const std::string &opname, int rt);

		static std::string disasmRDRS(const std::string &opname, int rd, int rs);

		static std::string disasmRDRT(const std::string &opname, int rd, int rt);

		static std::string disasmRD(const std::string &opname, int rd);

		static std::string disasmRSRT(const std::string &opname, int rs, int rt);

		static std::string disasmEXT(int rt, int rs, int rd, int sa);

		static std::string disasmINS(int rt, int rs, int rd, int sa);

		static std::string disasmRDRSRT(const std::string &opname, int rd, int rs, int rt);

		static std::string disasmRSOFFSET(const std::string &opname, int rs, int simm16, int opcode_address);

		static std::string disasmRSRTOFFSET(const std::string &opname, int rs, int rt, int simm16, int opcode_address);

		static std::string disasmOFFSET(const std::string &opname, int simm16, int opcode_address);

		static std::string disasmRTRSIMM(const std::string &opname, int rt, int rs, int imm16);

		static std::string disasmSYSCALL(int code);

		static std::string disasmBREAK(int code);

		static std::string disasmJUMP(const std::string &opname, int uimm26, int opcode_address);

		static std::string disasmRTIMM(const std::string &opname, int rt, int imm);

		static std::string disasmRTIMMRS(const std::string &opname, int rt, int rs, int imm);

		static std::string disasmCODEIMMRS(const std::string &opname, int code, int rs, int imm);

		static std::string disasmFTIMMRS(const std::string &opname, int ft, int rs, int imm);

		static std::string disasmFDFSFT(const std::string &opname, int fd, int fs, int ft);

		static std::string disasmFDFS(const std::string &opname, int fd, int fs);

		static std::string disasmRTFS(const std::string &opname, int rt, int fs);

		static std::string disasmRTFC(const std::string &opname, int rt, int fc);

		static std::string disasmCcondS(int cconds, int fs, int ft);

		static std::string disasmFSFT(const std::string &opname, int fs, int ft);

		static std::string disasmVD(const std::string &opname, int vsize, int vd);

		static std::string disasmVS(const std::string &opname, int vsize, int vs);

		static std::string disasmVDVS(const std::string &opname, int vsize, int vd, int vs);

		static std::string disasmVD1VS(const std::string &opname, int vsize, int vd, int vs);

		static std::string disasmVTIMMRS(const std::string &opname, int vsize, int vt, int rs, int imm);

		static std::string disasmVDVSVT(const std::string &opname, int vsize, int vd, int vs, int vt);

		static std::string disasmVDVSVT1(const std::string &opname, int vsize, int vd, int vs, int vt);

		static std::string disasmVD1VSVT(const std::string &opname, int vsize, int vd, int vs, int vt);
	protected:
		static Instruction **m_instances;

	public:
		static Instruction **instructions() final;
	};

}
