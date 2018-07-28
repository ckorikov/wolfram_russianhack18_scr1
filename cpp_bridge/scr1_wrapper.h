#ifndef SCR1_WRAPPER_H
#define SCR1_WRAPPER_H

#include <verilated.h>                      // Defines common routines
#include "Vscr1_top_tb_axi.h"               // From Verilating "top.v"

#ifndef SCR1_MEM_MAX
# define SCR1_MEM_MAX 32768
#endif

#ifndef SCR1_CLK_TICKS
# define SCR1_CLK_TICKS 10
#endif

double sc_time_stamp ();
extern uint64_t g_sim_time;

namespace SCR1
{
    class Processor {
        Vscr1_top_tb_axi *scr1;
    public:
        Processor();
        ~Processor();
        /* Processor main controls and status */
        void run();
        void step();
        void reset();
        void load(const char * mem);
        bool is_finished();
        /* IPC controls and status */
        int next_ipc();
        int get_ipc();
        /* Registers */
        int get_register(int num);
        /* Memory */
        int read_mem(int address);
        int read_dmem_bus_addr();
        int read_dmem_bus_bytewidth();
        void write_mem(int address, int data);
        /* Branching */
        int get_jump_state();
        int get_jb_addr_state();
        int get_branch_taken_state();
        int get_branch_not_taken_state();
    };
}
#endif //SCR1_WRAPPER_H
