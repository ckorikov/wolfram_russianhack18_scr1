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
hello(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);

DLLEXPORT
int
reset(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res);


#ifdef __cplusplus
}
#endif
