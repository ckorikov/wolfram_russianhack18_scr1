#include "scr1_wrapper.h"

#include <iostream>
#include <fstream>
#include <string>

uint64_t main_time;       // Current simulation time

double sc_time_stamp () {       // Called by $time in Verilog
   return main_time;           // converts to double, to match
}

namespace SCR1
{

    processor::processor()
    {
        this->top = new Vscr1_top_tb_axi;
        // Verilated::commandArgs(0, NULL);
    }

    processor::~processor()
    {
        this->top->final();
        delete this->top;
    }

    void processor::reset()
    {
        this->top->rst_n=0;
        this->step();
        this->top->rst_n=1;
    }

    void processor::step()
    {
        for (size_t i = 0; i < 19; i++)
        {
            if(!Verilated::gotFinish())
            {
                if ((main_time % 10) == 1) {
                    this->top->clk = 1;
                }
                if ((main_time % 10) == 6) {
                    this->top->clk = 0;
                }
                this->top->eval();
                main_time++;
            }
        }
    }
}
