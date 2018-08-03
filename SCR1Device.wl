(* ::Package:: *)

BeginPackage["SCR1Device`"];


Begin["`Private`"];


Needs["CCompilerDriver`"];


$libscr1=Null;


DeviceFramework`DeviceClassRegister["SCR1",
"Singleton" -> True,
"DriverVersion" -> 1.0,
"OpenFunction" -> open,
"CloseFunction" -> close,
"ReadFunction" -> read,
"WriteFunction" -> w rite,
"ExecuteFunction" -> exec,
"GetPropertyFunction" -> readProp,
"DeviceIconFunction" -> logo,
"Properties" -> {
	"State" -> Null,
	"Clock" -> Null,
	"IPC" -> Null, 
	"MAX MEM" -> Null
	}
];


logo[{ih_,dh_}, ___]:=Import["logo.png"];


readProp[dev_,"State"]:=Which[#==0,"IDLE",#==1,"WORK",#==2,"FINISHED"]&@funcGETSTATE[][[1]];
readProp[dev_,"IPC"]:=funcGETSTATE[][[4]];
readProp[dev_,"Clock"]:=funcGETSTATE[][[3]];
readProp[dev_,"MAX_MEM"]:=funcGETMAXMEM[];


exec[{ih_,dh_}, "HARD_RESET"] := funcHARDRESET[];
exec[{ih_,dh_}, "RESET"] := funcRESET[];
exec[{ih_,dh_}, "RUN"] := funcRUN[];
exec[{ih_,dh_}, "RUN_UNTIL_IPC",ipc_] := funcRUNUNITL[ipc];
exec[{ih_,dh_}, "STEP"] := funcSTEP[];
exec[{ih_,dh_}, "NEXT_IPC"] := funcNEXTIPC[];
exec[{ih_,dh_}, "TRACE_IPC"] := funcTRACEIPC[];
exec[{ih_,dh_}, "LOAD", program_] := funcLOAD[program];


read[{ih_,dh_}, "REGS"] := funcGETREGS[];
read[{ih_,dh_}, "STATE"] := 
Inner[
	#1->#2&,
	{"State","Finished","Clock","IPC"}, 
	MapAt[
		Which[#==0,"IDLE",#==1,"WORK",#==2,"FINISHED"]&,
		funcGETSTATE[],
		1
	],
	Association
	];
read[{ih_,dh_}, "BRANCH"] := 
Inner[
	#1->#2&,
	{"IPC","Jump","Branch_taken","Branch_not_taken", "JB_addr"},
	funcGETBRANCH[],
	Association
	];
read[{ih_,dh_}, "DBUS"] := 
Inner[
	#1->#2&,
	{"Address","Bytes"},
	funcREADDMEMBUS[],
	Association
	];
read[{ih_,dh_}, "MEM", addr_, num_] := funcREADMEM[addr,num];


write[{ih_,dh_},"MEM", addr_, value_] := funcWRITEMEM[addr,value];
write[{ih_,dh_},"REGS",num_,value_] := funcSETREG[num,value];


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
 },
 incList =
 {
  NotebookDirectory[]<>"scr1_generated/verilator_system/",
  NotebookDirectory[]<>"scr1_generated/"
 }
},
$libscr1 = CreateLibrary[
  fileList,
  "cpp_bridge",
  Language -> "C++",
  "CompileOptions"->"-std=c++11",
  "IncludeDirectories" -> incList
];
funcHARDRESET = LibraryFunctionLoad[$libscr1, "scr1_hard_reset", {}, Integer];
funcRESET = LibraryFunctionLoad[$libscr1, "scr1_reset", {}, Integer];
funcLOAD = LibraryFunctionLoad[$libscr1, "scr1_load", {String}, Integer];
funcRUN = LibraryFunctionLoad[$libscr1, "scr1_run", {}, Integer];
funcRUNUNITL = LibraryFunctionLoad[$libscr1, "scr1_run_until_ipc", {Integer}, Integer];
funcSTEP = LibraryFunctionLoad[$libscr1, "scr1_step", {}, Integer];
funcGETSTATE = LibraryFunctionLoad[$libscr1, "scr1_get_state", {},{Integer,1}];
funcGETREGS = LibraryFunctionLoad[$libscr1, "scr1_get_register_list", {},{Integer,1}];
funcNEXTIPC = LibraryFunctionLoad[$libscr1, "scr1_next_ipc", {}, Integer];
funcTRACEIPC = LibraryFunctionLoad[$libscr1, "scr1_trace_ipc", {},{Integer,1}];
funcGETBRANCH = LibraryFunctionLoad[$libscr1, "scr1_get_branch_state", {},{Integer,1}];
funcREADMEM = LibraryFunctionLoad[$libscr1, "scr1_read_memory", {Integer,Integer},{Integer,1}];
funcREADDMEMBUS = LibraryFunctionLoad[$libscr1, "scr1_get_dmem_bus_state", {}, {Integer,1}];
funcWRITEMEM = LibraryFunctionLoad[$libscr1, "scr1_write_memory", {Integer,Integer}, Integer];
funcSETREG = LibraryFunctionLoad[$libscr1, "scr1_set_register", {Integer,Integer}, Integer];
funcGETMAXMEM = LibraryFunctionLoad[$libscr1, "scr1_get_max_memory", {}, Integer];
h];


close[{ih_,dh_}] := LibraryUnload[$libscr1];


End[];


EndPackage[];
