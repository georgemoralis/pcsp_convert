#pragma once

#include <string>
#include <regex>

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
namespace jpcsp::Debugger::DisassemblerModule
{

	/**
	 *
	 * @author shadow, hlide
	 */
	class DisHelper
	{

	public:
		static int signExtend(int value);

		static int signExtend8(int value);

		static int zeroExtend(int value);

		static int zeroExtend8(int value);

		static std::string *gprNames;
		static std::string *fprNames;
		static std::string **vprNames;
		static std::string *fcrNames;
		static std::string *cop0Names;
		static std::string *vsuffix;
	private:
		static const std::string *ccondsNames;


		//New helpers
	public:
		static std::string Dis_RDRTSA(const std::string &opname, int rd, int rt, int sa);

		static std::string Dis_RDRTRS(const std::string &opname, int rd, int rt, int rs);

		static std::string Dis_RS(const std::string &opname, int rs);

		static std::string Dis_RT(const std::string &opname, int rt);

		static std::string Dis_RDRS(const std::string &opname, int rd, int rs);

		static std::string Dis_RDRT(const std::string &opname, int rd, int rt);

		static std::string Dis_RD(const std::string &opname, int rd);

		static std::string Dis_RSRT(const std::string &opname, int rs, int rt);

		static std::string Dis_Ext(int rt, int rs, int rd, int sa);

		static std::string Dis_Ins(int rt, int rs, int rd, int sa);

		static std::string Dis_RDRSRT(const std::string &opname, int rd, int rs, int rt);

		static std::string Dis_RSOFFSET(const std::string &opname, int rs, int simm16, int opcode_address);

		static std::string Dis_RSRTOFFSET(const std::string &opname, int rs, int rt, int simm16, int opcode_address);

		static std::string Dis_OFFSET(const std::string &opname, int imm, int opcode_address);

		static std::string Dis_RTRSIMM(const std::string &opname, int rt, int rs, int imm16);

		static std::string Dis_Syscall(int code);

		static std::string Dis_Break(int code);

		static std::string Dis_JUMP(const std::string &opname, int uimm26, int opcode_address);

		static std::string Dis_RTIMM(const std::string &opname, int rt, int imm);

		static std::string Dis_RTIMMRS(const std::string &opname, int rt, int rs, int imm);

		static std::string Dis_CCIMMRS(const std::string &opname, int code, int rs, int imm);

		static std::string Dis_FTIMMRS(const std::string &opname, int rt, int rs, int imm);

		static std::string Dis_FDFSFT(const std::string &opname, int fd, int fs, int ft);

		static std::string Dis_FDFS(const std::string &opname, int fd, int fs);

		static std::string Dis_RTFS(const std::string &opname, int rt, int fs);

		static std::string Dis_RTFC(const std::string &opname, int rt, int fc);

		static std::string Dis_Cconds(int cconds, int fs, int ft);


		static std::string Dis_FSFT(const std::string &opname, int fs, int ft);

		static std::string Dis_VTIMMRS(const std::string &opname, int vsize, int vt, int rs, int imm);

		static std::string Dis_VDVSVT(const std::string &opname, int vsize, int vd, int vs, int vt);

		static std::string Dis_VDVSVT1(const std::string &opname, int vsize, int vd, int vs, int vt);

		static std::string Dis_VD1VSVT(const std::string &opname, int vsize, int vd, int vs, int vt);
	};

}
