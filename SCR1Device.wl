(* ::Package:: *)

BeginPackage["SCR1Device`"];


Begin["`Private`"];


Needs["CCompilerDriver`"];


DeviceFramework`DeviceClassRegister["SCR1",
"Singleton"->True,
"DriverVersion"->1.0,
"OpenFunction"->open,
"CloseFunction"->close,
"ReadFunction"->read,
"WriteFunction"->write,
"ExecuteFunction"->exec,
"GetPropertyFunction"->readProp,
"DeviceIconFunction"->logo,
"Properties"->{
	"State"->Null,
	"Clock"->Null,
	"IPC"->Null
	}
];


logo[___]:=Import["logo.png"];


readProp[dev_,"State"]:=Which[#==0,"IDLE",#==1,"WORK",#==2,"FINISHED"]&@funcGETSTATE[][[1]];
readProp[dev_,"IPC"]:=funcGETSTATE[][[4]];
readProp[dev_,"Clock"]:=funcGETSTATE[][[3]];


exec[{_, h_}, "RUN"] := funcRUN[];
exec[{_, h_}, {"RUN_UNTIL_IPC",ipc_}] := funcRUNUNTIL[ipc];
exec[{_, h_}, "STEP"] := funcSTEP[];
exec[{_, h_}, "NEXT_IPC"] := funcNEXTIPC[];
exec[{_, h_}, {"LOAD", program_}] := funcLOAD[program];


read[{_, h_}, "REGS"] := funcGETREGS[];
read[{_, h_}, "STATE"] := funcGETSTATE[];
read[{_, h_}, "BRANCH"] := funcGETBRANCH[];
read[{_, h_}, "DBUS"] := funcREADDMEMBUS[];
read[{_, h_}, "MEM", addr_, num_] := funcREADMEM[addr,num];


write[{_, h_}, "MEM", addr_, value_] := funcWRITEMEM[addr,value];
write[{_, h_}, "REG", num_, value_] := funcSETREG[num,value];


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
funcRESET = LibraryFunctionLoad[$libscr1, "scr1_reset", {}, Integer];
funcLOAD = LibraryFunctionLoad[$libscr1, "scr1_load", {String}, Integer];
funcRUN = LibraryFunctionLoad[$libscr1, "scr1_run", {}, Integer];
funcRUNUNITL = LibraryFunctionLoad[$libscr1, "scr1_run_until_ipc", {Integer}, Integer];
funcSTEP = LibraryFunctionLoad[$libscr1, "scr1_step", {}, Integer];
funcGETSTATE = LibraryFunctionLoad[$libscr1, "scr1_get_state", {},{Integer,1}];
funcGETREGS = LibraryFunctionLoad[$libscr1, "scr1_get_register_list", {},{Integer,1}];
funcNEXTIPC = LibraryFunctionLoad[$libscr1, "scr1_next_ipc", {}, Integer];
funcGETBRANCH = LibraryFunctionLoad[$libscr1, "scr1_get_branch_state", {},{Integer,1}];
funcREADMEM = LibraryFunctionLoad[$libscr1, "scr1_read_memory", {Integer,Integer},{Integer,1}];
funcREADDMEMBUS = LibraryFunctionLoad[$libscr1, "scr1_get_dmem_bus_state", {}, {Integer,1}];
funcWRITEMEM = LibraryFunctionLoad[$libscr1, "scr1_write_memory", {Integer,Integer}, Integer];
funcSETREG = LibraryFunctionLoad[$libscr1, "scr1_set_register", {Integer,Integer}, Integer];
h];


close[{_, h_}, ___] := LibraryUnload[$libscr1];


End[];


EndPackage[];
