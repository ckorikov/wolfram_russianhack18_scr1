#include "WolframLibrary.h"

#ifdef __cplusplus
extern "C"
{
#endif

DLLEXPORT mint
WolframLibrary_getVersion();

DLLEXPORT
int
WolframLibrary_initialize(WolframLibraryData libData);

DLLEXPORT
int
constantzero(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
reset(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
run(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
step(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
is_finished(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
get_pc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
next_pc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
get_register(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
get_register_list(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
get_branch_state(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
read_memory(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
read_dmem_bus(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

#ifdef __cplusplus
}
#endif
