#include "scr1_wrapper.h"

#include <stdio.h>

uint64_t main_time;       // Current simulation time

double sc_time_stamp () {       // Called by $time in Verilog
   return main_time;           // converts to double, to match
}

namespace SCR1
{

    processor::processor()
    {
        this->top = new Vscr1_top_tb_axi;
    }

    processor::~processor()
    {
        this->top->final();
        delete this->top;
    }

    void processor::reset(const char * mem)
    {
        Verilated::commandArgs(1, &mem);
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

    void processor::run()
    {
        while(!Verilated::gotFinish())
        {
            this->step();
        }
    }

    bool processor::is_finished()
    {
        return Verilated::gotFinish();
    }

    int processor::get_pc()
    {
        return this->top->pc;
    }

    int processor::next_pc()
    {
        int pc = this->get_pc();
        while(!Verilated::gotFinish())
        {
            this->step();
            int current_pc = this->get_pc();
            if (current_pc != pc)
            {
                pc = current_pc;
                break;
            }
        }
        return pc;
    }
}
