#include "scr1_wrapper.h"

static uint64_t g_sim_time; // Current simulation time

// Called by $time in Verilog
double sc_time_stamp()
{
    return static_cast<double>(g_sim_time);
}

namespace SCR1
{
    Processor::Processor(): state(scr1_state::IDLE)
    {
        this->scr1 = new Vscr1_top_tb_axi;
        freopen(FILE_SCR1_OUT, "w", stdout);
    }

    Processor::~Processor()
    {
        this->scr1->final();
        delete this->scr1;
        remove(FILE_SCR1_OUT);
        Verilated::gotFinish(false);
        g_sim_time = 0;
    }

    scr1_state Processor::get_state()
    {
        return this->state;
    }

    void Processor::reset()
    {
        this->scr1->rst_n=0;
        this->step();
        this->scr1->rst_n=1;
        this->state = scr1_state::WORK;
    }

    void Processor::load(const char * program)
    {
        Verilated::commandArgs(1, &program);
        this->reset();
    }

    bool Processor::is_finished()
    {
        auto res = Verilated::gotFinish();
        if (res) this->state = scr1_state::FINISHED;
        return res;
    }

    uint64_t Processor::step()
    {
        this->scr1->clk = 1;
        for(int clk_front=0; clk_front<2; ++clk_front)
        {
            for (uint32_t tick = 0; tick < SCR1_CLK_TICKS; ++tick)
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
        fflush(stdout);
        return this->get_steps();
    }

    void Processor::run()
    {
        while(!this->is_finished())
        {
            this->step();
        }
    }

    uint32_t Processor::get_ipc()
    {
        return this->scr1->pc;
    }

    uint32_t Processor::next_ipc()
    {
        uint32_t guard_clk_cnt = SCR1_GUARD_CLK_MAX;
        uint32_t ipc = this->get_ipc();
        while(!this->is_finished())
        {
            this->step();
            uint32_t cur_ipc = this->get_ipc();
            if (cur_ipc != ipc)
            {
                ipc = cur_ipc;
                break;
            }
            if (guard_clk_cnt==0)
            {
                return WRONG_VALUE;
            }
            else
            {
                --guard_clk_cnt;
            }
        }
        return ipc;
    }
    
    vector<uint32_t> Processor::trace_ipc()
    {
        vector<uint32_t> trace {this->get_ipc()};
        while(!this->is_finished())
        {
            uint32_t ipc = this->next_ipc();
            trace.push_back(ipc);
        }
        return trace;
    }

    uint32_t Processor::run_until_ipc(const uint32_t to_ipc)
    {
        uint32_t ipc = 0;
        while(!this->is_finished())
        {
            this->step();
            ipc = this->get_ipc();
            if (ipc == to_ipc)
            {
                break;
            }
        }
        return ipc;
    }

    uint64_t Processor::get_ticks()
    {
        return g_sim_time;
    }

    uint64_t Processor::get_steps()
    {
        return this->get_ticks()/SCR1_CLK_TICKS;
    }

    uint32_t Processor::get_register(const uint8_t num)
    {
        /* Is there a better solution? */
        switch (num) {
                /* The register gpr_x00 is always zero */
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
            default: return WRONG_VALUE;
        }
    }

    void Processor::set_register(const uint8_t num, const IData data)
    {
        /* Is there a better solution? */
        switch (num) {
            /* The register gpr_x00 is always zero */
            case 1: this->scr1->gpr_x01 = data; break;
            case 2: this->scr1->gpr_x02 = data; break;
            case 3: this->scr1->gpr_x03 = data; break;
            case 4: this->scr1->gpr_x04 = data; break;
            case 5: this->scr1->gpr_x05 = data; break;
            case 6: this->scr1->gpr_x06 = data; break;
            case 7: this->scr1->gpr_x07 = data; break;
            case 8: this->scr1->gpr_x08 = data; break;
            case 9: this->scr1->gpr_x09 = data; break;
            case 10: this->scr1->gpr_x10 = data; break;
            case 11: this->scr1->gpr_x11 = data; break;
            case 12: this->scr1->gpr_x12 = data; break;
            case 13: this->scr1->gpr_x13 = data; break;
            case 14: this->scr1->gpr_x14 = data; break;
            case 15: this->scr1->gpr_x15 = data; break;
            case 16: this->scr1->gpr_x16 = data; break;
            case 17: this->scr1->gpr_x17 = data; break;
            case 18: this->scr1->gpr_x18 = data; break;
            case 19: this->scr1->gpr_x19 = data; break;
            case 20: this->scr1->gpr_x20 = data; break;
            case 21: this->scr1->gpr_x21 = data; break;
            case 22: this->scr1->gpr_x22 = data; break;
            case 23: this->scr1->gpr_x23 = data; break;
            case 24: this->scr1->gpr_x24 = data; break;
            case 25: this->scr1->gpr_x25 = data; break;
            case 26: this->scr1->gpr_x26 = data; break;
            case 27: this->scr1->gpr_x27 = data; break;
            case 28: this->scr1->gpr_x28 = data; break;
            case 29: this->scr1->gpr_x29 = data; break;
            case 30: this->scr1->gpr_x30 = data; break;
            case 31: this->scr1->gpr_x31 = data; break;
        }
    }

    uint32_t Processor::get_jump_state()
    {
        return this->scr1->jump;
    }

    uint32_t Processor::get_branch_taken_state()
    {
        return this->scr1->branch_taken;
    }

    uint32_t Processor::get_branch_not_taken_state()
    {
        return this->scr1->branch_not_taken;
    }

    uint32_t Processor::get_jb_addr_state()
    {
        return this->scr1->jb_addr;
    }

    uint32_t Processor::read_mem(const uint32_t address)
    {
        return address > SCR1_MEM_MAX
        ? -1
        : this->scr1->scr1_top_tb_axi__DOT__i_memory_tb__DOT__memory[address];
    }

    void Processor::write_mem(const uint32_t address, const uint32_t data)
    {
        if (address <= SCR1_MEM_MAX)
        {
            this->scr1->scr1_top_tb_axi__DOT__i_memory_tb__DOT__memory[address] = data;
        }
    }

    uint32_t Processor::read_dmem_bus_addr()
    {
        return this->scr1->ls_addr;
    }

    uint32_t Processor::read_dmem_bus_bytewidth()
    {
        /* This is convention */
        switch (this->scr1->ls_width)
        {
            case 0: return 1;
            case 2: return 2;
            case 3: return 4;
            default: return WRONG_VALUE;
        }
    }
}
