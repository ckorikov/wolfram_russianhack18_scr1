#ifndef SCR1_WRAPPER_H
#define SCR1_WRAPPER_H

#include <verilated.h>                      // Defines common routines
#include "Vscr1_top_tb_axi.h"               // From Verilating "top.v"

#ifndef SCR1_MEM_MAX
# define SCR1_MEM_MAX 32768
#endif

#ifndef SCR1_CLK_TICKS
# define SCR1_CLK_TICKS 1
#endif

#define FILE_SCR1_OUT "src1_output.txt"

namespace SCR1
{
    typedef enum class enum_scr1_state {IDLE, WORK, FINISHED} scr1_state;

    class Processor {
        Vscr1_top_tb_axi *scr1;
        scr1_state state;
    public:
        Processor();
        ~Processor();
        /* State control */
        scr1_state get_state();
        /* Processor main controls and status */
        void run();
        void reset();
        void load(const char * program);
        uint64_t step();
        bool is_finished();
        uint64_t get_steps();
        uint64_t get_ticks();
        /* IPC controls and status */
        unsigned int next_ipc();
        unsigned int get_ipc();
        unsigned int run_until_ipc(unsigned int to_ipc);
        /* Registers */
        int get_register(unsigned int num);
        void set_register(unsigned int num, int data);
        /* Memory */
        int read_mem(const size_t address);
        void write_mem(const size_t address, const int data);
        /* Memory bus */
        int read_dmem_bus_addr();
        int read_dmem_bus_bytewidth();
        /* Branching */
        int get_jump_state();
        int get_jb_addr_state();
        int get_branch_taken_state();
        int get_branch_not_taken_state();
    };
}
#endif //SCR1_WRAPPER_H
