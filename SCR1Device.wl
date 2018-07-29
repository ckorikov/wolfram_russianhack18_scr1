(* ::Package:: *)

BeginPackage["SCR1Device`"]


Begin["`Private`"]


Needs["CCompilerDriver`"];


DeviceFramework`DeviceClassRegister["SCR1",
"DriverVersion"->1.0,
"OpenFunction"->open,
"CloseFunction"->close,
"ReadFunction"->read,
"GetPropertyFunction"->readProp,
"DeviceIconFunction"->logo,
"Properties"->{
	"ipc"->Null
	}
]


$string="abcde";


$positions=<||>;


$libscr1=Null;


funcOUT = Null;
funcIPC = Null;
funcRESET = Null;
funcSTEP = Null;
funcRUN = Null;
funcIsFinished = Null;
funcNextPC = Null;
funcGetRegister = Null;
funcGetRegisterList = Null;
funcGetBranchState = Null;
funcReadMem = Null;
funcReadDataBUS = Null;


logo[___]:=Import["logo.png"]


readProp[dev_,"ipc"]:=funcIPC[]


read[{_, h_}, cmd_] := Switch[cmd,
"RUN", funcRUN[],
"STEP", funcSTEP[],
"NEXT_IPC", funcNEXTIPC[],
"GET_REGS", funcGETREGS[],
"GET_STATE", funcGETSTATE[]
(*"get_branch_state", funcGetBranchState[],
"get_data_bus", funcReadDataBUS[]*)
]


read[{_, h_},cmd_, param_] := Switch[cmd,
"LOAD", funcLOAD[param],
"get_reg", funcGetRegister[param]
]


read[{_, h_},cmd_, param1_, param2_] := Switch[cmd,
"read_mem", funcReadMem[param1, param2]
]


open[___] := Module[
{
h = CreateUUID[],
fileList =
 {
 "cpp_bridge/cpp_bridge.cpp",
 "cpp_bridge/scr1_wrapper.cpp",
  "scr1_generated/Vscr1_top_tb_axi.cpp", 
  "scr1_generated/Vscr1_top_tb_axi__ALLsup.cpp", 
  "scr1_generated/verilator_system/verilated.cpp",
  "scr1_generated/verilator_system/verilated_cov.cpp",
  "scr1_generated/verilator_system/verilated_save.cpp", 
  "scr1_generated/verilator_system/verilated_vcd_c.cpp",
  "scr1_generated/verilator_system/verilated_vpi.cpp"
  }
  },
$libscr1 = CreateLibrary[
  fileList,
  "cpp_bridge",
   Language -> "C++",
   "Debug"->True,
   "CompileOptions"->"-std=c++11",
  "IncludeDirectories" -> {"/Users/ckorikov/_syntacore/projects/wolfram_russianhack18_scr1/scr1_generated/verilator_system/","/Users/ckorikov/_syntacore/projects/wolfram_russianhack18_scr1/scr1_generated/"}
  ];
  funcRESET = LibraryFunctionLoad[$libscr1, "scr1_reset", {}, Integer];
  funcLOAD = LibraryFunctionLoad[$libscr1, "scr1_load", {String}, Integer];
  funcRUN = LibraryFunctionLoad[$libscr1, "scr1_run", {}, Integer];
  funcSTEP = LibraryFunctionLoad[$libscr1, "scr1_step", {}, Integer];
  funcGETSTATE = LibraryFunctionLoad[$libscr1, "scr1_get_state", {},{Integer,1}];
  funcGETREGS = LibraryFunctionLoad[$libscr1, "scr1_get_register_list", {},{Integer,1}];
  funcNEXTIPC = LibraryFunctionLoad[$libscr1, "scr1_next_ipc", {}, Integer];
  funcGETBRANCH = LibraryFunctionLoad[$libscr1, "scr1_get_branch_state", {},{Integer,1}];
  funcREADMEM = LibraryFunctionLoad[$libscr1, "scr1_read_memory", {Integer,Integer},{Integer,1}];
  funcREADDMEMBUS = LibraryFunctionLoad[$libscr1, "scr1_get_dmem_bus_state", {}, {Integer,1}];
 h]


close[{_, h_}, ___] := LibraryUnload[$libscr1]


End[]


EndPackage[]
