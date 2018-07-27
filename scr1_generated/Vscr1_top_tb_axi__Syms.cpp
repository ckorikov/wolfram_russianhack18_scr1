// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vscr1_top_tb_axi__Syms.h"
#include "Vscr1_top_tb_axi.h"
#include "Vscr1_top_tb_axi___024unit.h"

// FUNCTIONS
Vscr1_top_tb_axi__Syms::Vscr1_top_tb_axi__Syms(Vscr1_top_tb_axi* topp, const char* namep)
	// Setup locals
	: __Vm_namep(namep)
	, __Vm_didInit(false)
	// Setup submodule names
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
}
