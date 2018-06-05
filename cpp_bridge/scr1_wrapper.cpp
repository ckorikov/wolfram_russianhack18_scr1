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

    int processor::get_register(int num)
    {
        /* Rewrite it! */
        switch (num) {
            case 1: return this->top->gpr_x01;
            case 2: return this->top->gpr_x02;
            case 3: return this->top->gpr_x03;
            case 4: return this->top->gpr_x04;
            case 5: return this->top->gpr_x05;
            case 6: return this->top->gpr_x06;
            case 7: return this->top->gpr_x07;
            case 8: return this->top->gpr_x08;
            case 9: return this->top->gpr_x09;
            case 10: return this->top->gpr_x10;
            case 11: return this->top->gpr_x11;
            case 12: return this->top->gpr_x12;
            case 13: return this->top->gpr_x13;
            case 14: return this->top->gpr_x14;
            case 15: return this->top->gpr_x15;
            case 16: return this->top->gpr_x16;
            case 17: return this->top->gpr_x17;
            case 18: return this->top->gpr_x18;
            case 19: return this->top->gpr_x19;
            case 20: return this->top->gpr_x20;
            case 21: return this->top->gpr_x21;
            case 22: return this->top->gpr_x22;
            case 23: return this->top->gpr_x23;
            case 24: return this->top->gpr_x24;
            case 25: return this->top->gpr_x25;
            case 26: return this->top->gpr_x26;
            case 27: return this->top->gpr_x27;
            case 28: return this->top->gpr_x28;
            case 29: return this->top->gpr_x29;
            case 30: return this->top->gpr_x30;
            case 31: return this->top->gpr_x31;
            default: return 0;
        }
    }
}
