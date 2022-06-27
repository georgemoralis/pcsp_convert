#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

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
namespace jpcsp
{

	// 2008-8-5 [Hlide] Allegrex Opcodes
	class AllegrexOpcodes
	{

	// CPU: encoded by opcode field.
	// 
	//     31---------26---------------------------------------------------0
	//     |  opcode   |                                                   |
	//     ------6----------------------------------------------------------
	//     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
	// 000 | *1    | *2    | J     | JAL   | BEQ   | BNE   | BLEZ  | BGTZ  |
	// 001 | ADDI  | ADDIU | SLTI  | SLTIU | ANDI  | ORI   | XORI  | LUI   |
	// 010 | *3    | *4    | VFPU2 | ---   | BEQL  | BNEL  | BLEZL | BGTZL |
	// 011 | VFPU0 | VFPU1 |  ---  | VFPU3 | * 5   | ---   | ---   | *6    |
	// 100 | LB    | LH    | LWL   | LW    | LBU   | LHU   | LWR   | ---   |
	// 101 | SB    | SH    | SWL   | SW    | ---   | ---   | SWR   | CACHE |
	// 110 | LL    | LWC1  | LVS   | ---   | VFPU4 | ULVQ  | LVQ   | VFPU5 |
	// 111 | SC    | SWC1  | SVS   | ---   | VFPU6 | USVQ  | SVQ   | VFPU7 |
	//  hi |-------|-------|-------|-------|-------|-------|-------|-------|
	//  
	//      *1 = SPECIAL, see SPECIAL list    *2 = REGIMM, see REGIMM list
	//      *3 = COP0                         *4 = COP1  
	//      *5 = SPECIAL2 , see SPECIAL2      *6 = SPECAIL3 , see SPECIAL 3
	//      *ULVQ is buggy on PSP1000 PSP 
	//      *VFPU0 check VFPU0 table
	//      *VFPU1 check VFPU1 table
	//      *VFPU2 check VFPU2 table
	//      *VFPU3 check VFPU3 table
	//      *VFPU4 check VFPU4 table
	//      *VFPU5 check VFPU5 table
	//      *VFPU6 check VFPU6 table
	//      *VFPU7 check VFPU7 table
	public:
		static constexpr signed char SPECIAL = 0x0;
		static constexpr signed char REGIMM = 0x1;
		static constexpr signed char J = 0x2; // Jump
		static constexpr signed char JAL = 0x3; // Jump And Link
		static constexpr signed char BEQ = 0x4; // Branch on Equal
		static constexpr signed char BNE = 0x5; // Branch on Not Equal
		static constexpr signed char BLEZ = 0x6; // Branch on Less Than or Equal to Zero
		static constexpr signed char BGTZ = 0x7; // Branch on Greater Than Zero
		static constexpr signed char ADDI = 0x8; // Add Immediate
		static constexpr signed char ADDIU = 0x9; // Add Immediate Unsigned
		static constexpr signed char SLTI = 0xa; // Set on Less Than Immediate
		static constexpr signed char SLTIU = 0xb; // Set on Less Than Immediate Unsigned
		static constexpr signed char ANDI = 0xc; // AND Immediate
		static constexpr signed char ORI = 0xd; // OR Immediate
		static constexpr signed char XORI = 0xe; // Exclusive OR Immediate
		static constexpr signed char LUI = 0xf; // Load Upper Immediate
		static constexpr signed char COP0 = 0x10; // Coprocessor Operation
		static constexpr signed char COP1 = 0x11; // Coprocessor Operation
		static constexpr signed char VFPU2 = 0x12;
		/*  0x13 reserved or unsupported */
		static constexpr signed char BEQL = 0x14; // Branch on Equal Likely
		static constexpr signed char BNEL = 0x15; // Branch on Not Equal Likely
		static constexpr signed char BLEZL = 0x16; // Branch on Less Than or Equal to Zero Likely
		static constexpr signed char BGTZL = 0x17; // Branch on Greater Than Zero Likely
		static constexpr signed char VFPU0 = 0x18;
		static constexpr signed char VFPU1 = 0x19;
		/*  0x1a reserved or unsupported */
		static constexpr signed char VFPU3 = 0x1b;
		static constexpr signed char SPECIAL2 = 0x1c; // Allegrex table
		/*  0x1d reserved or unsupported */
		/*  0x1e reserved or unsupported */
		static constexpr signed char SPECIAL3 = 0x1f; //special3 table
		static constexpr signed char LB = 0x20; //Load Byte
		static constexpr signed char LH = 0x21; // Load Halfword
		static constexpr signed char LWL = 0x22; // Load Word Left
		static constexpr signed char LW = 0x23; // Load Word
		static constexpr signed char LBU = 0x24; // Load Byte Unsigned
		static constexpr signed char LHU = 0x25; // Load Halfword Unsigned
		static constexpr signed char LWR = 0x26; // Load Word Right
		/*  0x27 reserved or unsupported */
		static constexpr signed char SB = 0x28; // Store Byte
		static constexpr signed char SH = 0x29; // Store Halfword
		static constexpr signed char SWL = 0x2A; // Store Word Left
		static constexpr signed char SW = 0x2B; // Store Word
		/*  0x2c reserved or unsupported */
		/*  0x2d reserved or unsupported */
		static constexpr signed char SWR = 0x2E; // Store Word Right
		static constexpr signed char CACHE = 0x2f; // Allegrex Cache Operation
		static constexpr signed char LL = 0x30; // Load Linked
		static constexpr signed char LWC1 = 0x31; // Load FPU Register
		static constexpr signed char LVS = 0x32; // Load Scalar VFPU Register
		/*  0x32 reserved or unsupported */
		/*  0x33 reserved or unsupported */
		static constexpr signed char VFPU4 = 0x34;
		static constexpr signed char ULVQ = 0x35; // Load Quad VFPU Register (Unaligned)
		static constexpr signed char LVQ = 0x36; // Load Quad VFPU Register
		static constexpr signed char VFPU5 = 0x37;
		static constexpr signed char SC = 0x38; // Store Conditionaly
		static constexpr signed char SWC1 = 0x39; // Store FPU Register
		static constexpr signed char SVS = 0x3a; // Store Scalar VFPU Register
		/*  0x3b reserved or unsupported */
		static constexpr signed char VFPU6 = 0x3c;
		static constexpr signed char USVQ = 0x3d; // Store Quad VFPU Register (Unaligned)
		static constexpr signed char SVQ = 0x3e; // Store Quad VFPU Register
		static constexpr signed char VFPU7 = 0x3f; // SPECIAL: encoded by function field when opcode field = SPECIAL
	// 
	//     31---------26------------------------------------------5--------0
	//     |=   SPECIAL|                                         | function|
	//     ------6----------------------------------------------------6-----
	//     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
	// 000 | SLL   | ---   |SRLROR | SRA   | SLLV  |  ---  |SRLRORV| SRAV  |
	// 001 | JR    | JALR  | MOVZ  | MOVN  |SYSCALL| BREAK |  ---  | SYNC  |
	// 010 | MFHI  | MTHI  | MFLO  | MTLO  | ---   |  ---  |  CLZ  | CLO   |
	// 011 | MULT  | MULTU | DIV   | DIVU  | MADD  | MADDU | ----  | ----- |
	// 100 | ADD   | ADDU  | SUB   | SUBU  | AND   | OR    | XOR   | NOR   |
	// 101 | ---   |  ---  | SLT   | SLTU  | MAX   | MIN   | MSUB  | MSUBU |
	// 110 | ---   |  ---  | ---   | ---   | ---   |  ---  | ---   | ---   |
	// 111 | ---   |  ---  | ---   | ---   | ---   |  ---  | ---   | ---   |
	//  hi |-------|-------|-------|-------|-------|-------|-------|-------|
		static constexpr signed char SLL = 0x0; // Shift Left Logical
		/*  0x1 reserved or unsupported */
		static constexpr signed char SRLROR = 0x2; // Shift/Rotate Right Logical
		static constexpr signed char SRA = 0x3; // Shift Right Arithmetic
		static constexpr signed char SLLV = 0x4; // Shift Left Logical Variable
		/*  0x5 reserved or unsupported */
		static constexpr signed char SRLRORV = 0x6; // Shift/Rotate Right Logical Variable
		static constexpr signed char SRAV = 0x7; // Shift Right Arithmetic Variable
		static constexpr signed char JR = 0x8; // Jump Register
		static constexpr signed char JALR = 0x9; // Jump And Link Register
		static constexpr signed char MOVZ = 0xa; // Move If Zero
		static constexpr signed char MOVN = 0xb; // Move If Non-zero
		static constexpr signed char SYSCALL = 0xc; // System Call
		static constexpr signed char BREAK = 0xd; // Break
		/*  0xe reserved or unsupported */
		static constexpr signed char SYNC = 0xf; // Sync
		static constexpr signed char MFHI = 0x10; // Move From HI
		static constexpr signed char MTHI = 0x11; // Move To HI
		static constexpr signed char MFLO = 0x12; // Move From LO
		static constexpr signed char MTLO = 0x13; // Move To LO
		/*  0x14 reserved or unsupported */
		/*  0x15 reserved or unsupported */
		static constexpr signed char CLZ = 0x16; // Count Leading Zero
		static constexpr signed char CLO = 0x17; // Count Leading One
		static constexpr signed char MULT = 0x18; // Multiply
		static constexpr signed char MULTU = 0x19; // Multiply Unsigned
		static constexpr signed char DIV = 0x1a; // Divide
		static constexpr signed char DIVU = 0x1b; // Divide Unsigned
		static constexpr signed char MADD = 0x1c; // Multiply And Add
		static constexpr signed char MADDU = 0x1d; // Multiply And Add Unsigned
		/*  0x1e reserved or unsupported */
		/*  0x1f reserved or unsupported */
		static constexpr signed char ADD = 0x20; // Add
		static constexpr signed char ADDU = 0x21; // Add Unsigned
		static constexpr signed char SUB = 0x22; // Subtract
		static constexpr signed char SUBU = 0x23; // Subtract Unsigned
		static constexpr signed char AND = 0x24; // AND
		static constexpr signed char OR = 0x25; // OR
		static constexpr signed char XOR = 0x26; // Exclusive OR
		static constexpr signed char NOR = 0x27; // NOR
		/*  0x28 reserved or unsupported */
		/*  0x29 reserved or unsupported */
		static constexpr signed char SLT = 0x2a; // Set on Less Than
		static constexpr signed char SLTU = 0x2b; // Set on Less Than Unsigned
		static constexpr signed char MAX = 0x2c; // Move Max
		static constexpr signed char MIN = 0x2d; // Move Min
		static constexpr signed char MSUB = 0x2e; // Multiply And Substract
		static constexpr signed char MSUBU = 0x2f; // Multiply And Substract

	// SPECIAL rs : encoded by rs field when opcode/func field = SPECIAL/SRLROR
	// 
	//     31---------26-----21-----------------------------------5--------0
	//     |=   SPECIAL| rs  |                                    |= SRLROR|
	//     ------6--------5-------------------------------------------6-----
	//     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
	// 000 | SRL   | ROTR  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
	// 001 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
	// 010 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
	// 011 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
	//  hi |-------|-------|-------|-------|-------|-------|-------|-------|
		static constexpr signed char SRL = 0x0;
		static constexpr signed char ROTR = 0x1; // SPECIAL sa : encoded by sa field when opcode/func field = SPECIAL/SRLRORV
	// 
	//     31---------26------------------------------------10----5--------0
	//     |=   SPECIAL|                                    | sa  |=SRLRORV|
	//     ------6---------------------------------------------5------6-----
	//     |--000--|--001--|--010--|--011--|--100--|--101--|--110--|--111--| lo
	// 000 | SRLV  | ROTRV |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
	// 001 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
	// 010 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
	// 011 |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |  ---  |
	//  hi |-------|-------|-------|-------|-------|-------|-------|-------|
		static constexpr signed char SRLV = 0x0;

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
