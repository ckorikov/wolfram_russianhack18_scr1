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

#ifndef SCR1_GUARD_CLK_MAX
# define SCR1_GUARD_CLK_MAX 1000
#endif

#define WRONG_VALUE 0

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
        uint32_t next_ipc();
        uint32_t get_ipc();
        uint32_t run_until_ipc(const uint32_t to_ipc);
        /* Registers */
        uint32_t get_register(const uint8_t num);
        void set_register(const uint8_t num, const IData data);
        /* Memory */
        uint32_t read_mem(const uint32_t address);
        void write_mem(const uint32_t address, const uint32_t data);
        /* Memory bus */
        uint32_t read_dmem_bus_addr();
        uint32_t read_dmem_bus_bytewidth();
        /* Branching */
        uint32_t get_jump_state();
        uint32_t get_jb_addr_state();
        uint32_t get_branch_taken_state();
        uint32_t get_branch_not_taken_state();
    };
}
#endif //SCR1_WRAPPER_H
