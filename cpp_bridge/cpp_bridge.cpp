#include "cpp_bridge.h"
#include "scr1_wrapper.h"

static SCR1::Processor* p_proc;

using namespace std;

/* Wolfram basic library functions */

mint WolframLibrary_getVersion()
{
    return WolframLibraryVersion;
}

int WolframLibrary_initialize(WolframLibraryData libData)
{
    try
    {
        p_proc = new SCR1::Processor;
    }
    catch (...)
    {
        libData->Message("Cannot create a SCR1 instance");
        return LIBRARY_MEMORY_ERROR;
    }
    return LIBRARY_NO_ERROR;
}

void WolframLibrary_uninitialize(WolframLibraryData libData)
{
    delete p_proc;
}

int constantzero(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    MArgument_setInteger(Res, 0);
    return LIBRARY_NO_ERROR;
}

/* SCR1 Functionality */
int scr1_hard_reset(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    delete p_proc;
    return WolframLibrary_initialize(libData);
}

int scr1_reset(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    try
    {
        p_proc->reset();
    }
    catch (...)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    return LIBRARY_NO_ERROR;
}

int scr1_run(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    try
    {
        p_proc->run();
    }
    catch (...)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    return LIBRARY_NO_ERROR;
}

int scr1_run_until_ipc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    uint32_t ipc = static_cast<uint32_t>(MArgument_getInteger(Args[0]));

    try
    {
        p_proc->run_until_ipc(ipc);
    }
    catch (...)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    return LIBRARY_NO_ERROR;
}

int scr1_trace_ipc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    MTensor out_tensor_data;
    const mint out_tensor_rank=1;
    mint out_tensor_dim[1] = {0};
    try
    {
        auto trace = p_proc->trace_ipc();
        out_tensor_dim[0] = trace.size();
        
        auto err = libData->MTensor_new(MType_Integer, out_tensor_rank, out_tensor_dim, &out_tensor_data);
        if(err)
        {
            return LIBRARY_FUNCTION_ERROR;
        }
        
        mint *out_cpointer=libData->MTensor_getIntegerData(out_tensor_data);
        copy(trace.begin(),trace.end(),out_cpointer);
        MArgument_setMTensor(Res, out_tensor_data);
    }
    catch (...)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    return LIBRARY_NO_ERROR;
}

int scr1_load(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    const char *file_name = MArgument_getUTF8String(Args[0]);
    if (access( file_name, F_OK ) == -1)
    {
        libData->Message("Cannot find the program");
        return LIBRARY_FUNCTION_ERROR;
    }
    else
    {
        try
        {
            char path_arg[strlen(file_name)+5];
            strcpy(path_arg, "+mem=");
            strcat(path_arg, file_name);
            p_proc->load(path_arg);
        }
        catch (...)
        {
            return LIBRARY_FUNCTION_ERROR;
        }
    }
    return LIBRARY_NO_ERROR;
}

int scr1_step(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    try
    {
        auto step_cnt = p_proc->step();
        MArgument_setInteger(Res, step_cnt);
    }
    catch (...)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    return LIBRARY_NO_ERROR;
}

int scr1_get_state(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    MTensor out_tensor_data;
    const mint out_tensor_rank=1;
    const mint out_tensor_dim[]={4};

    auto err = libData->MTensor_new(MType_Integer, out_tensor_rank, out_tensor_dim, &out_tensor_data);
    if(err)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    else
    {
        try
        {
            mint *out_cpointer=libData->MTensor_getIntegerData(out_tensor_data);
            out_cpointer[0] = p_proc->get_state()==SCR1::scr1_state::IDLE     ? 0 :
                              p_proc->get_state()==SCR1::scr1_state::WORK     ? 1 :
                              p_proc->get_state()==SCR1::scr1_state::FINISHED ? 2 :
                                                                               -1;
            out_cpointer[1] = p_proc->is_finished();
            out_cpointer[2] = p_proc->get_steps();
            out_cpointer[3] = p_proc->get_ipc();

            MArgument_setMTensor(Res, out_tensor_data);
        }
        catch (...)
        {
            return LIBRARY_FUNCTION_ERROR;
        }
    }
    return LIBRARY_NO_ERROR;
}

int scr1_get_max_memory(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    MArgument_setInteger(Res, SCR1_MEM_MAX);
    return LIBRARY_NO_ERROR;
}

int scr1_next_ipc(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    try
    {
        auto ipc = p_proc->next_ipc();
        MArgument_setInteger(Res, ipc);
    }
    catch (...)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    return LIBRARY_NO_ERROR;
}

int scr1_get_register_list(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    MTensor out_tensor_data;
    const mint out_tensor_rank=1;
    const mint out_tensor_dim[]={31};

    auto err = libData->MTensor_new(MType_Integer, out_tensor_rank, out_tensor_dim, &out_tensor_data);
    if(err)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    else
    {
        try
        {
            mint *out_cpointer=libData->MTensor_getIntegerData(out_tensor_data);

            for (unsigned int i = 0; i < 30; i++) {
                out_cpointer[i]=p_proc->get_register(i+1);
            }

            MArgument_setMTensor(Res, out_tensor_data);
        }
        catch (...)
        {
            return LIBRARY_FUNCTION_ERROR;
        }
    }
    return LIBRARY_NO_ERROR;
}

int scr1_get_branch_state(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    MTensor out_tensor_data;
    const mint out_tensor_rank=1;
    const mint out_tensor_dim[]={5};

    auto err = libData->MTensor_new(MType_Integer, out_tensor_rank, out_tensor_dim, &out_tensor_data);
    if(err)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    else
    {
        try
        {
            mint *out_cpointer=libData->MTensor_getIntegerData(out_tensor_data);
            out_cpointer[0] = p_proc->get_ipc();
            out_cpointer[1] = p_proc->get_jump_state();
            out_cpointer[2] = p_proc->get_branch_taken_state();
            out_cpointer[3] = p_proc->get_branch_not_taken_state();
            out_cpointer[4] = p_proc->get_jb_addr_state();

            MArgument_setMTensor(Res, out_tensor_data);
        }
        catch (...)
        {
            return LIBRARY_FUNCTION_ERROR;
        }
    }
    return LIBRARY_NO_ERROR;
}

int scr1_read_memory(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    uint32_t addr   = static_cast<uint32_t>(MArgument_getInteger (Args[0]));
    uint32_t length = static_cast<uint32_t>(MArgument_getInteger (Args[1]));

    MTensor out_tensor_data;
    const mint out_tensor_rank=1;
    const mint out_tensor_dim[]={length};

    auto err = libData->MTensor_new(MType_Integer, out_tensor_rank, out_tensor_dim, &out_tensor_data);
    if(err)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    else
    {
        try
        {
            mint *out_cpointer=libData->MTensor_getIntegerData(out_tensor_data);

            for (uint32_t i = 0; i < length; i++) {
                out_cpointer[i]=p_proc->read_mem(addr+i);
            }

            MArgument_setMTensor(Res, out_tensor_data);
        }
        catch (...)
        {
            return LIBRARY_FUNCTION_ERROR;
        }
    }
    return LIBRARY_NO_ERROR;
}

int scr1_write_memory(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    uint32_t addr = static_cast<uint32_t>(MArgument_getInteger(Args[0]));
    uint32_t data = static_cast<uint32_t>(MArgument_getInteger(Args[1]));

    try
    {
        p_proc->write_mem(addr, data);
    }
    catch (...)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    return LIBRARY_NO_ERROR;
}

int scr1_set_register(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    uint8_t numb = static_cast<uint8_t>(MArgument_getInteger(Args[0]));
      IData data = static_cast<IData>(MArgument_getInteger(Args[1]));
    
    try
    {
        p_proc->set_register(numb, data);
    }
    catch (...)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    return LIBRARY_NO_ERROR;
}

int scr1_get_dmem_bus_state(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res)
{
    MTensor out_tensor_data;
    const mint out_tensor_rank=1;
    const mint out_tensor_dim[]={2};

    auto err = libData->MTensor_new(MType_Integer, out_tensor_rank, out_tensor_dim, &out_tensor_data);
    if(err)
    {
        return LIBRARY_FUNCTION_ERROR;
    }
    else
    {
        try
        {
            mint *out_cpointer=libData->MTensor_getIntegerData(out_tensor_data);

            out_cpointer[0] = p_proc->read_dmem_bus_addr();
            out_cpointer[1] = p_proc->read_dmem_bus_bytewidth();

            MArgument_setMTensor(Res, out_tensor_data);
        }
        catch (...)
        {
            return LIBRARY_FUNCTION_ERROR;
        }
    }
    return LIBRARY_NO_ERROR;
}
