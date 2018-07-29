#include "WolframLibrary.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /* Wolfram basic library functions */
    DLLEXPORT mint WolframLibrary_getVersion();
    DLLEXPORT  int WolframLibrary_initialize(WolframLibraryData libData);
    DLLEXPORT void WolframLibrary_uninitialize(WolframLibraryData libData);
    DLLEXPORT  int constantzero(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

    /* SCR1 Functionality */
    DLLEXPORT int scr1_hard_reset(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_reset(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_load(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_run(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_run_until_ipc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

    DLLEXPORT int scr1_step(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_get_state(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_next_ipc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_get_register_list(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_get_branch_state(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_read_memory(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_write_memory(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_set_register(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);
    DLLEXPORT int scr1_get_dmem_bus_state(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

#ifdef __cplusplus
}
#endif
