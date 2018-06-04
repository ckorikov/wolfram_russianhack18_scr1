#include "test.h"
#include "scr1_wrapper.h"

static SCR1::processor* p_proc;

mint
WolframLibrary_getVersion()
{
    return WolframLibraryVersion;
}

DLLEXPORT
int
WolframLibrary_initialize(WolframLibraryData libData)
{
    p_proc = new SCR1::processor;
    return 0;
}

void
WolframLibrary_uninitialize(WolframLibraryData libData)
{
    delete p_proc;
    return;
}

int
constantzero(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    MArgument_setInteger(Res, 0);
    return LIBRARY_NO_ERROR;
}

int
hello(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    mint I0;
    mint I1;
    mint I2;
    I0 = MArgument_getInteger (Args[0]);
    I1 = MArgument_getInteger (Args[1]);
    // p_proc->step();
    I2 = 0;
    MArgument_setInteger (Res, I2);
    return LIBRARY_NO_ERROR;
}

int
reset(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    mint I0;
    I0 = 0;
    p_proc->reset();
    MArgument_setInteger (Res, I0);
    return LIBRARY_NO_ERROR;
}
