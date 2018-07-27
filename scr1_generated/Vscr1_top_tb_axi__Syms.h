// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header

#ifndef _Vscr1_top_tb_axi__Syms_H_
#define _Vscr1_top_tb_axi__Syms_H_

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vscr1_top_tb_axi.h"
#include "Vscr1_top_tb_axi___024unit.h"

// SYMS CLASS
class Vscr1_top_tb_axi__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vscr1_top_tb_axi*              TOPp;
    
    // CREATORS
    Vscr1_top_tb_axi__Syms(Vscr1_top_tb_axi* topp, const char* namep);
    ~Vscr1_top_tb_axi__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(64);

#endif // guard
