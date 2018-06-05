Needs["CCompilerDriver`"];
fielnameFull = \
{"/Users/ckorikov/_syntacore/projects/wolfram_russianhack18_scr1/cpp_\
bridge/test.cpp",
  "/Users/ckorikov/_syntacore/projects/wolfram_russianhack18_scr1/cpp_\
bridge/Vscr1_top_tb_axi.cpp",
  "/Users/ckorikov/_syntacore/projects/wolfram_russianhack18_scr1/cpp_\
bridge/Vscr1_top_tb_axi__ALLsup.cpp",
  "/Users/ckorikov/_syntacore/projects/wolfram_russianhack18_scr1/cpp_\
bridge/scr1_wrapper.cpp",
  "/usr/local/Cellar/verilator/3.922/share/verilator/include/\
verilated.cpp",
  "/usr/local/Cellar/verilator/3.922/share/verilator/include/\
verilated_cov.cpp",
  "/usr/local/Cellar/verilator/3.922/share/verilator/include/\
verilated_save.cpp",
  "/usr/local/Cellar/verilator/3.922/share/verilator/include/\
verilated_vcd_c.cpp",
  "/usr/local/Cellar/verilator/3.922/share/verilator/include/\
verilated_vpi.cpp"};
libhello = CreateLibrary[
  fielnameFull,
  "hello",
  (*"Debug"\[Rule]True,*)
   Language -> "C++",
  "IncludeDirectories" -> \
{"/usr/local/Cellar/verilator/3.922/share/verilator/include"}
  ]
reset = LibraryFunctionLoad[libhello, "reset", {String}, Integer];
reset["+mem=/Users/ckorikov/_syntacore/projects/wolfram_russianhack18_scr1/\
cpp_bridge/dhrystone.bin"]
run = LibraryFunctionLoad[libhello, "run", {}, Integer];
isFinished = LibraryFunctionLoad[libhello, "is_finished", {}, Boolean];
pc = LibraryFunctionLoad[libhello, "get_pc", {}, Integer];
nextpc = LibraryFunctionLoad[libhello, "next_pc", {}, Integer];
