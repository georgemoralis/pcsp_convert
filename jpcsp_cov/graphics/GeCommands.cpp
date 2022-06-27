using namespace std;

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include "GeCommands.h"

namespace jpcsp::graphics
{

	GeCommands::GeCommands()
	{
		commands = new string[0x100];
		commands[TRXSIZE] = "trxsize";
		commands[UNKNOWCOMMAND_0xED] = "unk 0xed";
		commands[TRXDPOS] = "trxdpos";
		commands[TRXPOS] = "trxpos";
		commands[TRXKICK] = "trxkick";
		commands[PMSKA] = "pmska";
		commands[PMSKC] = "pmskc";
		commands[ZMSK] = "zmsk";
		commands[LOP] = "lop";
		commands[DTH3] = "dth3";
		commands[DTH2] = "dth2";
		commands[DTH1] = "dth1";
		commands[DTH0] = "dth0";
		commands[DFIX] = "difx";
		commands[SFIX] = "sfix";
		commands[ALPHA] = "alpha";
		commands[ZTST] = "ztst";
		commands[SOP] = "sop";
		commands[STST] = "stst";
		commands[ATST] = "atst";
		commands[CMSK] = "cmsk";
		commands[CREF] = "cref";
		commands[CTST] = "ctst";
		commands[FARZ] = "farz";
		commands[NEARZ] = "nearz";
		commands[SCISSOR2] = "scissor2";
		commands[SCISSOR1] = "scissor1";
		commands[CLEAR] = "clear";
		commands[PSM] = "psm";
		commands[UNKNOWCOMMAND_0xD1] = "unk 0xd1";
		commands[TSLOPE] = "tslope";
		commands[FCOL] = "fcol";
		commands[FDIST] = "fdist";
		commands[FFAR] = "ffar";
		commands[TSYNC] = "tsync";
		commands[TFLUSH] = "tflush";
		commands[TEC] = "tec";
		commands[TFUNC] = "tfunc";
		commands[TBIAS] = "tbias";
		commands[TWRAP] = "twrap";
		commands[TFLT] = "tflt";
		commands[CMODE] = "cmode";
		commands[CLOAD] = "cload";
		commands[TPSM] = "tpsm";
		commands[TMODE] = "tmode";
		commands[TEXTURE_ENV_MAP_MATRIX] = "temm";
		commands[TMAP] = "tmap";
		commands[TSIZE7] = "tsize7";
		commands[TSIZE6] = "tsize6";
		commands[TSIZE5] = "tsize5";
		commands[TSIZE4] = "tsize4";
		commands[TSIZE3] = "tsize3";
		commands[TSIZE2] = "tsize2";
		commands[TSIZE1] = "tsize1";
		commands[TSIZE0] = "tsize0";
		commands[UNKNOWCOMMAND_0xB7] = "unk 0xB7";
		commands[UNKNOWCOMMAND_0xB6] = "unk 0xB6";
		commands[TRXDBW] = "trxdbw";
		commands[TRXDBP] = "trxdbp";
		commands[TRXSBW] = "trxsbw";
		commands[TRXSBP] = "trxsbp";
		commands[CBPH] = "cbph";
		commands[CBP] = "cbp";
		commands[TBW7] = "tbw7";
		commands[TBW6] = "tbw6";
		commands[TBW5] = "tbw5";
		commands[TBW4] = "tbw4";
		commands[TBW3] = "tbw3";
		commands[TBW2] = "tbw2";
		commands[TBW1] = "tbw1";
		commands[TBW0] = "tbw0";
		commands[TBP7] = "tbp7";
		commands[TBP6] = "tbp6";
		commands[TBP5] = "tbp5";
		commands[TBP4] = "tbp4";
		commands[TBP3] = "tbp3";
		commands[TBP2] = "tbp2";
		commands[TBP1] = "tbp1";
		commands[TBP0] = "tbp0";
		commands[ZBW] = "zbw";
		commands[ZBP] = "zbp";
		commands[FBW] = "fbw";
		commands[FBP] = "fbp";
		commands[FFACE] = "fface";
		commands[SLC3] = "slc3";
		commands[SLC2] = "slc2";
		commands[SLC1] = "slc1";
		commands[SLC0] = "slc0";
		commands[DLC3] = "dlc3";
		commands[DLC2] = "dlc2";
		commands[DLC1] = "dlc1";
		commands[DLC0] = "dlc0";
		commands[ALC3] = "alc3";
		commands[ALC2] = "alc2";
		commands[ALC1] = "alc1";
		commands[ALC0] = "alc0";
		commands[SLF3] = "slf3";

//====================================================================================================
//End of the allowed output for the Free Edition of Java to C++ Converter.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================
