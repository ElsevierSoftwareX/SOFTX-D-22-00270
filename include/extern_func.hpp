//H**********************************************************************
// FILENAME :        extern_func.cpp              
//
// DESCRIPTION :
//       Header file for external function interfaces 
//       
//
// Univeristy of Michigan Ann Arbor 
// Computational AeroSciences Laboratory
// AUTHOR :    Nicholas Arnold-Medabalimi        
// DATE :      6/17/2022
//
//H*/


#ifndef EXTERN_FUNC_H
#define EXTERN_FUNC_H



#include <mpi.h>

#ifdef USE_MKL
#include "mkl.h"
#include <mkl_cblas.h>
#include <mkl_pblas.h>
#include <mkl_scalapack.h>

#endif
//#include <pblas.h>

/// CBLACS functions
extern "C" void Cblacs_pinfo(int *MYPNUM, int *NPROCS);
extern "C" void Cblacs_get(int ICONTXT, int WHAT, int *VAL);
extern "C" void Cblacs_gridinit(int *ICONTXT, char *ORDER, int prow, int pcol);
extern "C" void Cblacs_gridinfo(int ICONTXT, int *nprow, int *npcol, int *myprow, int *mypcol);
extern "C" void Cblacs_gridexit(int ICONTXT);

#ifndef USE_MKL
/// BLAS routines


///
/// Complex structure if not using MKL
///
struct complex16
{
    
    double real;///< Real part of the complex number
    double imag;///< Imaginary part of the complex number
};

extern "C" double cblas_dnrm2(const int n, const double *x, const int incx);

extern "C" int numroc_(const int *n, const int *nb, const int *iproc, const int *srcproc, const int *nprocs);
extern "C" void descinit_(int *desc, const int *m, const int *n, const int *mb, const int *nb, const int *irsrc, const int *icsrc, const int *ictxt, const int *lld, int *info);
extern "C" void pdgeadd_(const char *trans, const int *m, const int *n, const double *alpha, const double *a, const int *ia, const int *ja, const int *desca, const double *beta, double *c, const int *ic, const int *jc, const int *descc);
extern "C" void pzgeadd_(const char *trans, const int *m, const int *n, const complex16 *alpha, const complex16 *a, const int *ia, const int *ja, const int *desca, const complex16 *beta, complex16 *c, const int *ic, const int *jc, const int *descc);
extern "C" void pdgemm_(const char *transa, const char *transb, const int *m, const int *n, const int *k, const double *alpha, const double *a, const int *ia, const int *ja, const int *desca, const double *b, const int *ib, const int *jb, const int *descb, const double *beta, double *c, const int *ic, const int *jc, const int *descc);
extern "C" void pdamax_(const int *n, double *amax, int *indx, const double *x, const int *ix, const int *jx, const int *descx, const int *incx);
extern "C" void pdasum_(const int *n, double *asum, const double *x, const int *ix, const int *jx, const int *descx, const int *incx);
extern "C" void pdtran_(const int *m, const int *n, const double *alpha, const double *a, const int *ia, const int *ja, const int *desca, const double *beta, double *c, const int *ic, const int *jc, const int *descc);
extern "C" void pzgemm_(const char *transa, const char *transb, const int *m, const int *n, const int *k, const complex16 *alpha, const complex16 *a, const int *ia, const int *ja, const int *desca, const complex16 *b, const int *ib, const int *jb, const int *descb, const complex16 *beta, complex16 *c, const int *ic, const int *jc, const int *descc);
extern "C" void pdsyrk_(const char *uplo, const char *trans, const int *n, const int *k, const double *alpha, const double *a, const int *ia, const int *ja, const int *desca, const double *beta, double *c, const int *ic, const int *jc, const int *descc);
extern "C" void pdgemv_(const char *trans, const int *m, const int *n, const double *alpha, const double *a, const int *ia, const int *ja, const int *desca, const double *x, const int *ix, const int *jx, const int *descx, const int *incx, const double *beta, double *y, const int *iy, const int *jy, const int *descy, const int *incy);
extern "C" void pdscal_(const int *n, const double *alpha, const double *x, const int *ix, const int *jx, const int *desc, const int *incx);

extern "C" void pdgesvd_(const char *, const char *, const int *, const int *, const double *, const int *, const int *, const int *, const double *, const double *, const int *, const int *, const int *, const double *, const int *, const int *, const int *, const double *, const int *, const int *);
extern "C" void pdgesvd_(const char *, const char *, const int *, const int *, const double *, const int *, const int *, const int *, const double *, const double *, const int *, const int *, const int *, const double *, const int *, const int *, const int *, const double *, const int *, const int *);
extern "C" void pdgeqpf_(const int *, const int *, double *, const int *, const int *, const int *, const int *, double *, double *work, const int *, const int *);
extern "C" void pdgels_(const char *trans, const int *m, const int *n, const int *nrhs, const double *a, const int *ia, const int *ja, const int *desca, const double *b, const int *ib, const int *jb, const int *descb, const double *work, const int *lwork, const int *info);

extern "C" void pdgemr2d_(const int *, const int *, const double *, const int *, const int *, const int *, const double *, const int *, const int *, const int *, const int *);
extern "C" void pzgemr2d_(const int *, const int *, const complex16 *, const int *, const int *, const int *, const complex16 *, const int *, const int *, const int *, const int *);

#endif

#endif
