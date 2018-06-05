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
reset(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    const char *string = MArgument_getUTF8String(Args[0]);
    try {
        p_proc->reset(string);
    } catch (...) {
        res = LIBRARY_FUNCTION_ERROR;
    }
    return res;
}

int
run(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    try {
        p_proc->run();
    } catch (...) {
        res = LIBRARY_FUNCTION_ERROR;
    }
    return res;
}

int
step(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    try {
        p_proc->step();
    } catch (...) {
        res = LIBRARY_FUNCTION_ERROR;
    }
    return res;
}

int
is_finished(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    mbool state = p_proc->is_finished();
    // libData->Message("is_finished");
    MArgument_setBoolean(Res, state);
    return res;
}

int
get_pc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    mint pc = p_proc->get_pc();
    MArgument_setInteger(Res, pc);
    return res;
}

int
next_pc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    mint pc = p_proc->next_pc();
    MArgument_setInteger(Res, pc);
    return res;
}

int
get_register(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    int num = MArgument_getInteger (Args[0]);
    mint reg = p_proc->get_register(num);
    MArgument_setInteger(Res, reg);
    return res;
}

int
get_register_list(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    MTensor out_MT;
    const mint out_dim[]={31};
    mint out_rank=1;
    int err = libData->MTensor_new(MType_Integer, out_rank, out_dim, &out_MT);
    mint *out_cpointer=libData->MTensor_getIntegerData(out_MT);

    for (size_t i = 0; i < 32; i++) {
        out_cpointer[i]=p_proc->get_register(i);
    }

    MArgument_setMTensor(Res, out_MT);
    return res;
}

int
get_branch_state(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    MTensor out_MT;
    const mint out_dim[]={5};
    mint out_rank=1;
    int err = libData->MTensor_new(MType_Integer, out_rank, out_dim, &out_MT);
    mint *out_cpointer=libData->MTensor_getIntegerData(out_MT);

    out_cpointer[0] = p_proc->get_pc();
    out_cpointer[1] = p_proc->get_jump_state();
    out_cpointer[2] = p_proc->get_branch_taken_state();
    out_cpointer[3] = p_proc->get_branch_not_taken_state();
    out_cpointer[4] = p_proc->get_jb_addr_state();

    MArgument_setMTensor(Res, out_MT);
    return res;
}

int
read_memory(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    int addr = MArgument_getInteger (Args[0]);
    int length = MArgument_getInteger (Args[1]);
    MTensor out_MT;
    const mint out_dim[]={length};
    mint out_rank=1;
    int err = libData->MTensor_new(MType_Integer, out_rank, out_dim, &out_MT);
    mint *out_cpointer=libData->MTensor_getIntegerData(out_MT);

    for (size_t i = 0; i < length; i++) {
        out_cpointer[i]=p_proc->read_mem(addr+i);
    }

    MArgument_setMTensor(Res, out_MT);
    return res;
}

int
read_dmem_bus(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    int res = LIBRARY_NO_ERROR;
    MTensor out_MT;
    const mint out_dim[]={2};
    mint out_rank=1;
    int err = libData->MTensor_new(MType_Integer, out_rank, out_dim, &out_MT);
    mint *out_cpointer=libData->MTensor_getIntegerData(out_MT);

    out_cpointer[0] = p_proc->read_dmem_bus_addr();
    out_cpointer[1] = p_proc->read_dmem_bus_bytewidth();

    MArgument_setMTensor(Res, out_MT);
    return res;
}
