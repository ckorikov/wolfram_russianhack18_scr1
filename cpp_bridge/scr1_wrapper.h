#ifndef SCR1_WRAPPER_H
#define SCR1_WRAPPER_H

#include <verilated.h>                      // Defines common routines
#include "Vscr1_top_tb_axi.h"               // From Verilating "top.v"

#define MAX_ADDR 32768

double sc_time_stamp ();
extern uint64_t main_time;

namespace SCR1
{
    class processor {
        Vscr1_top_tb_axi *top;
        public:
            processor();
            ~processor();
            void step();
            void reset(const char * mem);
            int get_pc();
            void run();
            bool is_finished();
            int next_pc();
            int get_register(int num);
            int get_jump_state();
            int get_branch_taken_state();
            int get_branch_not_taken_state();
            int get_jb_addr_state();
            int read_mem(int address);
            void write_mem(int address, int data);
    };
}

#endif SCR1_WRAPPER_H
