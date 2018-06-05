(* ::Package:: *)

BeginPackage["SCR1Device`"]


Begin["`Private`"]


Needs["CCompilerDriver`"];


DeviceFramework`DeviceClassRegister["SCR1",
"OpenFunction"->open,
"CloseFunction"->close,
"ReadFunction"->read,
"Properties"->{
	"Registers"->Null,
	"pc"->Null}
]


$string="abcde";


$positions=<||>;


$libscr1=Null;


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


read[{_, h_}, cmd_] := Switch[cmd,
"ipc", funcIPC[],
"run", funcRUN[],
"step", funcSTEP[],
"checkEnd", funcIsFinished[],
"next_ipc", funcNextPC[],
"get_reg_list", funcGetRegisterList[],
"get_branch_state", funcGetBranchState[],
"get_data_bus", funcReadDataBUS[]
]


read[{_, h_},cmd_, param_] := Switch[cmd,
"reset", funcRESET["+mem="<>param],
"get_reg", funcGetRegister[param]
]


read[{_, h_},cmd_, param1_, param2_] := Switch[cmd,
"read_mem", funcReadMem[param1, param2]
]


open[___] := Module[
{
h = CreateUUID[],
fileList = Map["./cpp_bridge/"<>#&,
 {
 "test.cpp",
  "Vscr1_top_tb_axi.cpp", 
  "Vscr1_top_tb_axi__ALLsup.cpp", 
  "scr1_wrapper.cpp",
  "include/verilated.cpp",
  "include/verilated_cov.cpp",
  "include/verilated_save.cpp", 
  "include/verilated_vcd_c.cpp",
  "include/verilated_vpi.cpp"
  }
 ]
 },
$libscr1 = CreateLibrary[
  fileList,
  "hello",
   Language -> "C++",
  "IncludeDirectories" -> {"/Users/ckorikov/_syntacore/projects/wolfram_russianhack18_scr1/cpp_bridge/include/"}
  ];
 funcIPC = LibraryFunctionLoad[$libscr1, "get_pc", {}, Integer];
 funcRESET = LibraryFunctionLoad[$libscr1, "reset", {String}, Integer];
 funcSTEP = LibraryFunctionLoad[$libscr1, "step", {}, Integer];
 funcRUN = LibraryFunctionLoad[$libscr1, "run", {}, Integer];
 funcIsFinished = LibraryFunctionLoad[$libscr1, "is_finished", {}, Boolean];
 funcNextPC = LibraryFunctionLoad[$libscr1, "next_pc", {}, Integer];
 funcGetRegister = LibraryFunctionLoad[$libscr1, "get_register", {Integer}, Integer];
 funcGetRegisterList = LibraryFunctionLoad[$libscr1, "get_register_list", {},{ Integer,1}];
 funcGetBranchState = LibraryFunctionLoad[$libscr1, "get_branch_state", {},{ Integer,1}];
 funcReadMem = LibraryFunctionLoad[$libscr1, "read_memory", {Integer,Integer},{ Integer,1}];
 funcReadDataBUS = LibraryFunctionLoad[$libscr1, "read_dmem_bus", {}, { Integer,1}];
 h]


close[{_, h_}, ___] := LibraryUnload[$libscr1]


End[]


EndPackage[]
