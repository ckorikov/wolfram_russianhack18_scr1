#include "test.h"

namespace MathLibrary
{
    mint add(mint a, mint b)
    {
        return a - b;
    }
}

mint
WolframLibrary_getVersion()
{
    return WolframLibraryVersion;
}

DLLEXPORT
int
WolframLibrary_initialize(WolframLibraryData libData)
{
    return 0;
}

void
WolframLibrary_uninitialize(WolframLibraryData libData)
{
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
    I2 = MathLibrary::add(I0, I1);
    MArgument_setInteger (Res, I2);
    return LIBRARY_NO_ERROR;
}
