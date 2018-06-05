(* ::Package:: *)

Needs["CCompilerDriver`"];
fielnameFull = {wd<>"test.cpp", wd<>"Vscr1_top_tb_axi.cpp", wd<>"Vscr1_top_tb_axi__ALLsup.cpp", wd<>"scr1_wrapper.cpp",
wd<>"include/verilated.cpp", wd<>"include/verilated_cov.cpp", wd<>"include/verilated_save.cpp", wd<>"include/verilated_vcd_c.cpp",
wd<>"include/verilated_vpi.cpp"};
libhello = CreateLibrary[
  fielnameFull,
  "hello",
  (*"Debug"\[Rule]True,*)
   Language -> "C++",
  "IncludeDirectories" -> {wd<>"include"}
  ]
reset = LibraryFunctionLoad[libhello, "reset", {String}, Integer];
reset[appPath];
step = LibraryFunctionLoad[libhello, "step", {}, Integer];
run = LibraryFunctionLoad[libhello, "run", {}, Integer];
isFinished = LibraryFunctionLoad[libhello, "is_finished", {}, Boolean];
pc = LibraryFunctionLoad[libhello, "get_pc", {}, Integer];
nextpc = LibraryFunctionLoad[libhello, "next_pc", {}, Integer];
getregister = LibraryFunctionLoad[libhello, "get_register", {Integer}, Integer];
reglist = LibraryFunctionLoad[libhello, "get_register_list", {},{ Integer,1}];
branchstate = LibraryFunctionLoad[libhello, "get_branch_state", {},{ Integer,1}];
readmem = LibraryFunctionLoad[libhello, "read_memory", {Integer,Integer},{ Integer,1}];
readdatabus = LibraryFunctionLoad[libhello, "read_dmem_bus", {}, { Integer,1}];
