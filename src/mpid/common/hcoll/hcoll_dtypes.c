#include "hcoll/api/hcoll_dte.h"
#include "hcoll_dtypes.h"
#include <mpidimpl.h>

/* This will only get called once */
int hcoll_type_commit_hook(MPIR_Datatype *dtype_p)
{
    int ret;
  
    dtype_p->dev.hcoll_datatype = DTE_ZERO;

    ret = hcoll_create_mpi_type((void *)(&dtype_p->handle), &dtype_p->dev.hcoll_datatype);
    if (HCOLL_SUCCESS != ret) {
        return MPI_ERR_OTHER;
    }
     
    return MPI_SUCCESS;
}

int hcoll_type_free_hook(MPIR_Datatype *dtype_p)
{
    int rc = hcoll_dt_destroy(dtype_p->dev.hcoll_datatype);
    if (HCOLL_SUCCESS != rc) {
        return MPI_ERR_OTHER;
    }
    
    dtype_p->dev.hcoll_datatype = DTE_ZERO;

    return MPI_SUCCESS;
}
