#include "scr1_wrapper.h"

uint64_t g_sim_time; // Current simulation time

// Called by $time in Verilog
double sc_time_stamp()
{
    return static_cast<double>(g_sim_time);
}

namespace SCR1
{
    Processor::Processor()
    {
        this->scr1 = new Vscr1_top_tb_axi;
        std::freopen(FILE_SCR1_OUT, "w", stdout);
    }
    
    Processor::~Processor()
    {
        this->scr1->final();
        delete this->scr1;
        std::remove(FILE_SCR1_OUT);
    }
    
    void Processor::reset()
    {
        this->clk=0;
        this->scr1->rst_n=0;
        this->step();
        this->scr1->rst_n=1;
    }
    
    void Processor::load(const char * program)
    {
        Verilated::commandArgs(1, &program);
        this->reset();
    }
    
    bool Processor::is_finished()
    {
        return Verilated::gotFinish();
    }
    
    void Processor::step()
    {
        this->scr1->clk = 1;
        for(int clk_front=0; clk_front<2; ++clk_front)
        {
            for (size_t tick = 0; tick < SCR1_CLK_TICKS; ++tick)
            {
                if(!this->is_finished())
                {
                    this->scr1->eval();
                    ++g_sim_time;
                } else {
                    break;
                }
            }
            this->scr1->clk = 0;
        }
        ++this->clk;
        std::fflush(stdout);
    }
    
    void Processor::run()
    {
        while(!this->is_finished())
        {
            this->step();
        }
    }
    
    int Processor::get_ipc()
    {
        return this->scr1->pc;
    }
    
    int Processor::next_ipc()
    {
        int ipc = this->get_ipc();
        while(!this->is_finished())
        {
            this->step();
            int cur_ipc = this->get_ipc();
            if (cur_ipc != ipc)
            {
                ipc = cur_ipc;
                break;
            }
        }
        return ipc;
    }
    
    int Processor::get_register(int num)
    {
        /* Rewrite it! */
        switch (num) {
            case 1: return this->scr1->gpr_x01;
            case 2: return this->scr1->gpr_x02;
            case 3: return this->scr1->gpr_x03;
            case 4: return this->scr1->gpr_x04;
            case 5: return this->scr1->gpr_x05;
            case 6: return this->scr1->gpr_x06;
            case 7: return this->scr1->gpr_x07;
            case 8: return this->scr1->gpr_x08;
            case 9: return this->scr1->gpr_x09;
            case 10: return this->scr1->gpr_x10;
            case 11: return this->scr1->gpr_x11;
            case 12: return this->scr1->gpr_x12;
            case 13: return this->scr1->gpr_x13;
            case 14: return this->scr1->gpr_x14;
            case 15: return this->scr1->gpr_x15;
            case 16: return this->scr1->gpr_x16;
            case 17: return this->scr1->gpr_x17;
            case 18: return this->scr1->gpr_x18;
            case 19: return this->scr1->gpr_x19;
            case 20: return this->scr1->gpr_x20;
            case 21: return this->scr1->gpr_x21;
            case 22: return this->scr1->gpr_x22;
            case 23: return this->scr1->gpr_x23;
            case 24: return this->scr1->gpr_x24;
            case 25: return this->scr1->gpr_x25;
            case 26: return this->scr1->gpr_x26;
            case 27: return this->scr1->gpr_x27;
            case 28: return this->scr1->gpr_x28;
            case 29: return this->scr1->gpr_x29;
            case 30: return this->scr1->gpr_x30;
            case 31: return this->scr1->gpr_x31;
            default: return 0;
        }
    }
    
    int Processor::get_jump_state()
    {
        return this->scr1->jump;
    }
    
    int Processor::get_branch_taken_state()
    {
        return this->scr1->branch_taken;
    }
    
    int Processor::get_branch_not_taken_state()
    {
        return this->scr1->branch_not_taken;
    }
    
    int Processor::get_jb_addr_state()
    {
        return this->scr1->jb_addr;
    }
    
    int Processor::read_mem(int address)
    {
        if (address >= 0 && address <= SCR1_MEM_MAX)
        {
            return this->scr1->scr1_top_tb_axi__DOT__i_memory_tb__DOT__memory[address];
        }
        else
        {
            return 0;
        }
    }
    
    void Processor::write_mem(int address, int data)
    {
        if (address >= 0 && address <= SCR1_MEM_MAX)
        {
            this->scr1->scr1_top_tb_axi__DOT__i_memory_tb__DOT__memory[address] = data;
        }
    }
    
    int Processor::read_dmem_bus_addr()
    {
        return this->scr1->ls_addr;
    }
    
    int Processor::read_dmem_bus_bytewidth()
    {
        switch (this->scr1->ls_width)
        {
            case 0: return 1;
            case 2: return 2;
            case 3: return 4;
            default: return 0;
        }
    }
}
