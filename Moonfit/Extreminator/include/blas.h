/*
 * Copyright 1984-2012 The MathWorks, Inc.
 * All Rights Reserved.
 */

/*
 *  Header File include/blas.h
 *  Auto generated by f2h.pl, do not modify by hand
 */

#if defined(_MSC_VER)
# pragma once
#endif
#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3))
# pragma once
#endif

#ifndef blas_h
#define blas_h

#if defined(_WIN32) || defined(__hpux)
#define FORTRAN_WRAPPER(x) x
#else
#define FORTRAN_WRAPPER(x) x ## _
#endif

#ifndef COMPLEX_TYPES
#define COMPLEX_TYPES
  typedef struct{float r,i;} complex;
  typedef struct{double r,i;} doublecomplex;
#endif

#ifdef __cplusplus
    extern "C" {
#endif


/* Source: caxpy.f */
#define caxpy FORTRAN_WRAPPER(caxpy)
extern void caxpy(
    ptrdiff_t *n,
    float  *ca,
    float  *cx,
    ptrdiff_t *incx,
    float  *cy,
    ptrdiff_t *incy
);

/* Source: ccopy.f */
#define ccopy FORTRAN_WRAPPER(ccopy)
extern void ccopy(
    ptrdiff_t *n,
    float  *cx,
    ptrdiff_t *incx,
    float  *cy,
    ptrdiff_t *incy
);

/* Source: cdotc.f */
#define cdotc FORTRAN_WRAPPER(cdotc)
#ifndef FORTRAN_COMPLEX_FUNCTIONS_RETURN_VOID
extern complex cdotc(
#else
extern void cdotc(
    complex* retval,
#endif 
    ptrdiff_t *n,
    float  *cx,
    ptrdiff_t *incx,
    float  *cy,
    ptrdiff_t *incy
);

/* Source: cdotu.f */
#define cdotu FORTRAN_WRAPPER(cdotu)
#ifndef FORTRAN_COMPLEX_FUNCTIONS_RETURN_VOID
extern complex cdotu(
#else
extern void cdotu(
    complex* retval,
#endif 
    ptrdiff_t *n,
    float  *cx,
    ptrdiff_t *incx,
    float  *cy,
    ptrdiff_t *incy
);

/* Source: cgbmv.f */
#define cgbmv FORTRAN_WRAPPER(cgbmv)
extern void cgbmv(
    char   *trans,
    ptrdiff_t *m,
    ptrdiff_t *n,
    ptrdiff_t *kl,
    ptrdiff_t *ku,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx,
    float  *beta,
    float  *y,
    ptrdiff_t *incy
);

/* Source: cgemm.f */
#define cgemm FORTRAN_WRAPPER(cgemm)
extern void cgemm(
    char   *transa,
    char   *transb,
    ptrdiff_t *m,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: cgemv.f */
#define cgemv FORTRAN_WRAPPER(cgemv)
extern void cgemv(
    char   *trans,
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx,
    float  *beta,
    float  *y,
    ptrdiff_t *incy
);

/* Source: cgerc.f */
#define cgerc FORTRAN_WRAPPER(cgerc)
extern void cgerc(
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *y,
    ptrdiff_t *incy,
    float  *a,
    ptrdiff_t *lda
);

/* Source: cgeru.f */
#define cgeru FORTRAN_WRAPPER(cgeru)
extern void cgeru(
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *y,
    ptrdiff_t *incy,
    float  *a,
    ptrdiff_t *lda
);

/* Source: chbmv.f */
#define chbmv FORTRAN_WRAPPER(chbmv)
extern void chbmv(
    char   *uplo,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx,
    float  *beta,
    float  *y,
    ptrdiff_t *incy
);

/* Source: chemm.f */
#define chemm FORTRAN_WRAPPER(chemm)
extern void chemm(
    char   *side,
    char   *uplo,
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: chemv.f */
#define chemv FORTRAN_WRAPPER(chemv)
extern void chemv(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx,
    float  *beta,
    float  *y,
    ptrdiff_t *incy
);

/* Source: cher.f */
#define cher FORTRAN_WRAPPER(cher)
extern void cher(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *a,
    ptrdiff_t *lda
);

/* Source: cher2.f */
#define cher2 FORTRAN_WRAPPER(cher2)
extern void cher2(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *y,
    ptrdiff_t *incy,
    float  *a,
    ptrdiff_t *lda
);

/* Source: cher2k.f */
#define cher2k FORTRAN_WRAPPER(cher2k)
extern void cher2k(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: cherk.f */
#define cherk FORTRAN_WRAPPER(cherk)
extern void cherk(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: chpmv.f */
#define chpmv FORTRAN_WRAPPER(chpmv)
extern void chpmv(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *ap,
    float  *x,
    ptrdiff_t *incx,
    float  *beta,
    float  *y,
    ptrdiff_t *incy
);

/* Source: chpr.f */
#define chpr FORTRAN_WRAPPER(chpr)
extern void chpr(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *ap
);

/* Source: chpr2.f */
#define chpr2 FORTRAN_WRAPPER(chpr2)
extern void chpr2(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *y,
    ptrdiff_t *incy,
    float  *ap
);

/* Source: crotg.f */
#define crotg FORTRAN_WRAPPER(crotg)
extern void crotg(
    float  *ca,
    float  *cb,
    float  *c,
    float  *s
);

/* Source: cscal.f */
#define cscal FORTRAN_WRAPPER(cscal)
extern void cscal(
    ptrdiff_t *n,
    float  *ca,
    float  *cx,
    ptrdiff_t *incx
);

/* Source: csrot.f */
#define csrot FORTRAN_WRAPPER(csrot)
extern void csrot(
    ptrdiff_t *n,
    float  *cx,
    ptrdiff_t *incx,
    float  *cy,
    ptrdiff_t *incy,
    float  *c,
    float  *s
);

/* Source: csscal.f */
#define csscal FORTRAN_WRAPPER(csscal)
extern void csscal(
    ptrdiff_t *n,
    float  *sa,
    float  *cx,
    ptrdiff_t *incx
);

/* Source: cswap.f */
#define cswap FORTRAN_WRAPPER(cswap)
extern void cswap(
    ptrdiff_t *n,
    float  *cx,
    ptrdiff_t *incx,
    float  *cy,
    ptrdiff_t *incy
);

/* Source: csymm.f */
#define csymm FORTRAN_WRAPPER(csymm)
extern void csymm(
    char   *side,
    char   *uplo,
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: csyr2k.f */
#define csyr2k FORTRAN_WRAPPER(csyr2k)
extern void csyr2k(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: csyrk.f */
#define csyrk FORTRAN_WRAPPER(csyrk)
extern void csyrk(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: ctbmv.f */
#define ctbmv FORTRAN_WRAPPER(ctbmv)
extern void ctbmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx
);

/* Source: ctbsv.f */
#define ctbsv FORTRAN_WRAPPER(ctbsv)
extern void ctbsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx
);

/* Source: ctpmv.f */
#define ctpmv FORTRAN_WRAPPER(ctpmv)
extern void ctpmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    float  *ap,
    float  *x,
    ptrdiff_t *incx
);

/* Source: ctpsv.f */
#define ctpsv FORTRAN_WRAPPER(ctpsv)
extern void ctpsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    float  *ap,
    float  *x,
    ptrdiff_t *incx
);

/* Source: ctrmm.f */
#define ctrmm FORTRAN_WRAPPER(ctrmm)
extern void ctrmm(
    char   *side,
    char   *uplo,
    char   *transa,
    char   *diag,
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb
);

/* Source: ctrmv.f */
#define ctrmv FORTRAN_WRAPPER(ctrmv)
extern void ctrmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx
);

/* Source: ctrsm.f */
#define ctrsm FORTRAN_WRAPPER(ctrsm)
extern void ctrsm(
    char   *side,
    char   *uplo,
    char   *transa,
    char   *diag,
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb
);

/* Source: ctrsv.f */
#define ctrsv FORTRAN_WRAPPER(ctrsv)
extern void ctrsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx
);

/* Source: dasum.f */
#define dasum FORTRAN_WRAPPER(dasum)
extern double dasum(
    ptrdiff_t *n,
    double *dx,
    ptrdiff_t *incx
);

/* Source: daxpy.f */
#define daxpy FORTRAN_WRAPPER(daxpy)
extern void daxpy(
    ptrdiff_t *n,
    double *da,
    double *dx,
    ptrdiff_t *incx,
    double *dy,
    ptrdiff_t *incy
);

/* Source: dcabs1.f */
#define dcabs1 FORTRAN_WRAPPER(dcabs1)
extern double dcabs1(
    double *z
);

/* Source: dcopy.f */
#define dcopy FORTRAN_WRAPPER(dcopy)
extern void dcopy(
    ptrdiff_t *n,
    double *dx,
    ptrdiff_t *incx,
    double *dy,
    ptrdiff_t *incy
);

/* Source: ddot.f */
#define ddot FORTRAN_WRAPPER(ddot)
extern double ddot(
    ptrdiff_t *n,
    double *dx,
    ptrdiff_t *incx,
    double *dy,
    ptrdiff_t *incy
);

/* Source: dgbmv.f */
#define dgbmv FORTRAN_WRAPPER(dgbmv)
extern void dgbmv(
    char   *trans,
    ptrdiff_t *m,
    ptrdiff_t *n,
    ptrdiff_t *kl,
    ptrdiff_t *ku,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx,
    double *beta,
    double *y,
    ptrdiff_t *incy
);

/* Source: dgemm.f */
#define dgemm FORTRAN_WRAPPER(dgemm)
extern void dgemm(
    char   *transa,
    char   *transb,
    ptrdiff_t *m,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: dgemv.f */
#define dgemv FORTRAN_WRAPPER(dgemv)
extern void dgemv(
    char   *trans,
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx,
    double *beta,
    double *y,
    ptrdiff_t *incy
);

/* Source: dger.f */
#define dger FORTRAN_WRAPPER(dger)
extern void dger(
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *y,
    ptrdiff_t *incy,
    double *a,
    ptrdiff_t *lda
);

/* Source: dnrm2.f */
#define dnrm2 FORTRAN_WRAPPER(dnrm2)
extern double dnrm2(
    ptrdiff_t *n,
    double *x,
    ptrdiff_t *incx
);

/* Source: drot.f */
#define drot FORTRAN_WRAPPER(drot)
extern void drot(
    ptrdiff_t *n,
    double *dx,
    ptrdiff_t *incx,
    double *dy,
    ptrdiff_t *incy,
    double *c,
    double *s
);

/* Source: drotg.f */
#define drotg FORTRAN_WRAPPER(drotg)
extern void drotg(
    double *da,
    double *db,
    double *c,
    double *s
);

/* Source: drotm.f */
#define drotm FORTRAN_WRAPPER(drotm)
extern void drotm(
    ptrdiff_t *n,
    double *dx,
    ptrdiff_t *incx,
    double *dy,
    ptrdiff_t *incy,
    double *dparam
);

/* Source: drotmg.f */
#define drotmg FORTRAN_WRAPPER(drotmg)
extern void drotmg(
    double *dd1,
    double *dd2,
    double *dx1,
    double *dy1,
    double *dparam
);

/* Source: dsbmv.f */
#define dsbmv FORTRAN_WRAPPER(dsbmv)
extern void dsbmv(
    char   *uplo,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx,
    double *beta,
    double *y,
    ptrdiff_t *incy
);

/* Source: dscal.f */
#define dscal FORTRAN_WRAPPER(dscal)
extern void dscal(
    ptrdiff_t *n,
    double *da,
    double *dx,
    ptrdiff_t *incx
);

/* Source: dsdot.f */
#define dsdot FORTRAN_WRAPPER(dsdot)
extern double dsdot(
    ptrdiff_t *n,
    float  *sx,
    ptrdiff_t *incx,
    float  *sy,
    ptrdiff_t *incy
);

/* Source: dspmv.f */
#define dspmv FORTRAN_WRAPPER(dspmv)
extern void dspmv(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *ap,
    double *x,
    ptrdiff_t *incx,
    double *beta,
    double *y,
    ptrdiff_t *incy
);

/* Source: dspr.f */
#define dspr FORTRAN_WRAPPER(dspr)
extern void dspr(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *ap
);

/* Source: dspr2.f */
#define dspr2 FORTRAN_WRAPPER(dspr2)
extern void dspr2(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *y,
    ptrdiff_t *incy,
    double *ap
);

/* Source: dswap.f */
#define dswap FORTRAN_WRAPPER(dswap)
extern void dswap(
    ptrdiff_t *n,
    double *dx,
    ptrdiff_t *incx,
    double *dy,
    ptrdiff_t *incy
);

/* Source: dsymm.f */
#define dsymm FORTRAN_WRAPPER(dsymm)
extern void dsymm(
    char   *side,
    char   *uplo,
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: dsymv.f */
#define dsymv FORTRAN_WRAPPER(dsymv)
extern void dsymv(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx,
    double *beta,
    double *y,
    ptrdiff_t *incy
);

/* Source: dsyr.f */
#define dsyr FORTRAN_WRAPPER(dsyr)
extern void dsyr(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *a,
    ptrdiff_t *lda
);

/* Source: dsyr2.f */
#define dsyr2 FORTRAN_WRAPPER(dsyr2)
extern void dsyr2(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *y,
    ptrdiff_t *incy,
    double *a,
    ptrdiff_t *lda
);

/* Source: dsyr2k.f */
#define dsyr2k FORTRAN_WRAPPER(dsyr2k)
extern void dsyr2k(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: dsyrk.f */
#define dsyrk FORTRAN_WRAPPER(dsyrk)
extern void dsyrk(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: dtbmv.f */
#define dtbmv FORTRAN_WRAPPER(dtbmv)
extern void dtbmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx
);

/* Source: dtbsv.f */
#define dtbsv FORTRAN_WRAPPER(dtbsv)
extern void dtbsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx
);

/* Source: dtpmv.f */
#define dtpmv FORTRAN_WRAPPER(dtpmv)
extern void dtpmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    double *ap,
    double *x,
    ptrdiff_t *incx
);

/* Source: dtpsv.f */
#define dtpsv FORTRAN_WRAPPER(dtpsv)
extern void dtpsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    double *ap,
    double *x,
    ptrdiff_t *incx
);

/* Source: dtrmm.f */
#define dtrmm FORTRAN_WRAPPER(dtrmm)
extern void dtrmm(
    char   *side,
    char   *uplo,
    char   *transa,
    char   *diag,
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb
);

/* Source: dtrmv.f */
#define dtrmv FORTRAN_WRAPPER(dtrmv)
extern void dtrmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx
);

/* Source: dtrsm.f */
#define dtrsm FORTRAN_WRAPPER(dtrsm)
extern void dtrsm(
    char   *side,
    char   *uplo,
    char   *transa,
    char   *diag,
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb
);

/* Source: dtrsv.f */
#define dtrsv FORTRAN_WRAPPER(dtrsv)
extern void dtrsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx
);

/* Source: dzasum.f */
#define dzasum FORTRAN_WRAPPER(dzasum)
extern double dzasum(
    ptrdiff_t *n,
    double *zx,
    ptrdiff_t *incx
);

/* Source: dznrm2.f */
#define dznrm2 FORTRAN_WRAPPER(dznrm2)
extern double dznrm2(
    ptrdiff_t *n,
    double *x,
    ptrdiff_t *incx
);

/* Source: icamax.f */
#define icamax FORTRAN_WRAPPER(icamax)
extern ptrdiff_t icamax(
    ptrdiff_t *n,
    float  *cx,
    ptrdiff_t *incx
);

/* Source: idamax.f */
#define idamax FORTRAN_WRAPPER(idamax)
extern ptrdiff_t idamax(
    ptrdiff_t *n,
    double *dx,
    ptrdiff_t *incx
);

/* Source: isamax.f */
#define isamax FORTRAN_WRAPPER(isamax)
extern ptrdiff_t isamax(
    ptrdiff_t *n,
    float  *sx,
    ptrdiff_t *incx
);

/* Source: izamax.f */
#define izamax FORTRAN_WRAPPER(izamax)
extern ptrdiff_t izamax(
    ptrdiff_t *n,
    double *zx,
    ptrdiff_t *incx
);

/* Source: lsame.f */
#define lsame FORTRAN_WRAPPER(lsame)
extern ptrdiff_t lsame(
    char   *ca,
    char   *cb
);

/* Source: sasum.f */
#define sasum FORTRAN_WRAPPER(sasum)
#ifdef FORTRAN_FLOAT_FUNCTIONS_RETURN_DOUBLE
extern double sasum(
#else
extern float sasum(
#endif 
    ptrdiff_t *n,
    float  *sx,
    ptrdiff_t *incx
);

/* Source: saxpy.f */
#define saxpy FORTRAN_WRAPPER(saxpy)
extern void saxpy(
    ptrdiff_t *n,
    float  *sa,
    float  *sx,
    ptrdiff_t *incx,
    float  *sy,
    ptrdiff_t *incy
);

/* Source: scasum.f */
#define scasum FORTRAN_WRAPPER(scasum)
#ifdef FORTRAN_FLOAT_FUNCTIONS_RETURN_DOUBLE
extern double scasum(
#else
extern float scasum(
#endif 
    ptrdiff_t *n,
    float  *cx,
    ptrdiff_t *incx
);

/* Source: scnrm2.f */
#define scnrm2 FORTRAN_WRAPPER(scnrm2)
#ifdef FORTRAN_FLOAT_FUNCTIONS_RETURN_DOUBLE
extern double scnrm2(
#else
extern float scnrm2(
#endif 
    ptrdiff_t *n,
    float  *x,
    ptrdiff_t *incx
);

/* Source: scopy.f */
#define scopy FORTRAN_WRAPPER(scopy)
extern void scopy(
    ptrdiff_t *n,
    float  *sx,
    ptrdiff_t *incx,
    float  *sy,
    ptrdiff_t *incy
);

/* Source: sdot.f */
#define sdot FORTRAN_WRAPPER(sdot)
#ifdef FORTRAN_FLOAT_FUNCTIONS_RETURN_DOUBLE
extern double sdot(
#else
extern float sdot(
#endif 
    ptrdiff_t *n,
    float  *sx,
    ptrdiff_t *incx,
    float  *sy,
    ptrdiff_t *incy
);

/* Source: sdsdot.f */
#define sdsdot FORTRAN_WRAPPER(sdsdot)
#ifdef FORTRAN_FLOAT_FUNCTIONS_RETURN_DOUBLE
extern double sdsdot(
#else
extern float sdsdot(
#endif 
    ptrdiff_t *n,
    float  *sb,
    float  *sx,
    ptrdiff_t *incx,
    float  *sy,
    ptrdiff_t *incy
);

/* Source: sgbmv.f */
#define sgbmv FORTRAN_WRAPPER(sgbmv)
extern void sgbmv(
    char   *trans,
    ptrdiff_t *m,
    ptrdiff_t *n,
    ptrdiff_t *kl,
    ptrdiff_t *ku,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx,
    float  *beta,
    float  *y,
    ptrdiff_t *incy
);

/* Source: sgemm.f */
#define sgemm FORTRAN_WRAPPER(sgemm)
extern void sgemm(
    char   *transa,
    char   *transb,
    ptrdiff_t *m,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: sgemv.f */
#define sgemv FORTRAN_WRAPPER(sgemv)
extern void sgemv(
    char   *trans,
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx,
    float  *beta,
    float  *y,
    ptrdiff_t *incy
);

/* Source: sger.f */
#define sger FORTRAN_WRAPPER(sger)
extern void sger(
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *y,
    ptrdiff_t *incy,
    float  *a,
    ptrdiff_t *lda
);

/* Source: snrm2.f */
#define snrm2 FORTRAN_WRAPPER(snrm2)
#ifdef FORTRAN_FLOAT_FUNCTIONS_RETURN_DOUBLE
extern double snrm2(
#else
extern float snrm2(
#endif 
    ptrdiff_t *n,
    float  *x,
    ptrdiff_t *incx
);

/* Source: srot.f */
#define srot FORTRAN_WRAPPER(srot)
extern void srot(
    ptrdiff_t *n,
    float  *sx,
    ptrdiff_t *incx,
    float  *sy,
    ptrdiff_t *incy,
    float  *c,
    float  *s
);

/* Source: srotg.f */
#define srotg FORTRAN_WRAPPER(srotg)
extern void srotg(
    float  *sa,
    float  *sb,
    float  *c,
    float  *s
);

/* Source: srotm.f */
#define srotm FORTRAN_WRAPPER(srotm)
extern void srotm(
    ptrdiff_t *n,
    float  *sx,
    ptrdiff_t *incx,
    float  *sy,
    ptrdiff_t *incy,
    float  *sparam
);

/* Source: srotmg.f */
#define srotmg FORTRAN_WRAPPER(srotmg)
extern void srotmg(
    float  *sd1,
    float  *sd2,
    float  *sx1,
    float  *sy1,
    float  *sparam
);

/* Source: ssbmv.f */
#define ssbmv FORTRAN_WRAPPER(ssbmv)
extern void ssbmv(
    char   *uplo,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx,
    float  *beta,
    float  *y,
    ptrdiff_t *incy
);

/* Source: sscal.f */
#define sscal FORTRAN_WRAPPER(sscal)
extern void sscal(
    ptrdiff_t *n,
    float  *sa,
    float  *sx,
    ptrdiff_t *incx
);

/* Source: sspmv.f */
#define sspmv FORTRAN_WRAPPER(sspmv)
extern void sspmv(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *ap,
    float  *x,
    ptrdiff_t *incx,
    float  *beta,
    float  *y,
    ptrdiff_t *incy
);

/* Source: sspr.f */
#define sspr FORTRAN_WRAPPER(sspr)
extern void sspr(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *ap
);

/* Source: sspr2.f */
#define sspr2 FORTRAN_WRAPPER(sspr2)
extern void sspr2(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *y,
    ptrdiff_t *incy,
    float  *ap
);

/* Source: sswap.f */
#define sswap FORTRAN_WRAPPER(sswap)
extern void sswap(
    ptrdiff_t *n,
    float  *sx,
    ptrdiff_t *incx,
    float  *sy,
    ptrdiff_t *incy
);

/* Source: ssymm.f */
#define ssymm FORTRAN_WRAPPER(ssymm)
extern void ssymm(
    char   *side,
    char   *uplo,
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: ssymv.f */
#define ssymv FORTRAN_WRAPPER(ssymv)
extern void ssymv(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx,
    float  *beta,
    float  *y,
    ptrdiff_t *incy
);

/* Source: ssyr.f */
#define ssyr FORTRAN_WRAPPER(ssyr)
extern void ssyr(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *a,
    ptrdiff_t *lda
);

/* Source: ssyr2.f */
#define ssyr2 FORTRAN_WRAPPER(ssyr2)
extern void ssyr2(
    char   *uplo,
    ptrdiff_t *n,
    float  *alpha,
    float  *x,
    ptrdiff_t *incx,
    float  *y,
    ptrdiff_t *incy,
    float  *a,
    ptrdiff_t *lda
);

/* Source: ssyr2k.f */
#define ssyr2k FORTRAN_WRAPPER(ssyr2k)
extern void ssyr2k(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: ssyrk.f */
#define ssyrk FORTRAN_WRAPPER(ssyrk)
extern void ssyrk(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *beta,
    float  *c,
    ptrdiff_t *ldc
);

/* Source: stbmv.f */
#define stbmv FORTRAN_WRAPPER(stbmv)
extern void stbmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx
);

/* Source: stbsv.f */
#define stbsv FORTRAN_WRAPPER(stbsv)
extern void stbsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    ptrdiff_t *k,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx
);

/* Source: stpmv.f */
#define stpmv FORTRAN_WRAPPER(stpmv)
extern void stpmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    float  *ap,
    float  *x,
    ptrdiff_t *incx
);

/* Source: stpsv.f */
#define stpsv FORTRAN_WRAPPER(stpsv)
extern void stpsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    float  *ap,
    float  *x,
    ptrdiff_t *incx
);

/* Source: strmm.f */
#define strmm FORTRAN_WRAPPER(strmm)
extern void strmm(
    char   *side,
    char   *uplo,
    char   *transa,
    char   *diag,
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb
);

/* Source: strmv.f */
#define strmv FORTRAN_WRAPPER(strmv)
extern void strmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx
);

/* Source: strsm.f */
#define strsm FORTRAN_WRAPPER(strsm)
extern void strsm(
    char   *side,
    char   *uplo,
    char   *transa,
    char   *diag,
    ptrdiff_t *m,
    ptrdiff_t *n,
    float  *alpha,
    float  *a,
    ptrdiff_t *lda,
    float  *b,
    ptrdiff_t *ldb
);

/* Source: strsv.f */
#define strsv FORTRAN_WRAPPER(strsv)
extern void strsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    float  *a,
    ptrdiff_t *lda,
    float  *x,
    ptrdiff_t *incx
);

/* Source: xerbla.f */
#define xerbla FORTRAN_WRAPPER(xerbla)
extern void xerbla(
    char   *srname,
    ptrdiff_t *info
);

/* Source: zaxpy.f */
#define zaxpy FORTRAN_WRAPPER(zaxpy)
extern void zaxpy(
    ptrdiff_t *n,
    double *za,
    double *zx,
    ptrdiff_t *incx,
    double *zy,
    ptrdiff_t *incy
);

/* Source: zcopy.f */
#define zcopy FORTRAN_WRAPPER(zcopy)
extern void zcopy(
    ptrdiff_t *n,
    double *zx,
    ptrdiff_t *incx,
    double *zy,
    ptrdiff_t *incy
);

/* Source: zdotc.f */
#define zdotc FORTRAN_WRAPPER(zdotc)
#ifndef FORTRAN_COMPLEX_FUNCTIONS_RETURN_VOID
extern doublecomplex zdotc(
#else
extern void zdotc(
    doublecomplex* retval,
#endif 
    ptrdiff_t *n,
    double *zx,
    ptrdiff_t *incx,
    double *zy,
    ptrdiff_t *incy
);

/* Source: zdotu.f */
#define zdotu FORTRAN_WRAPPER(zdotu)
#ifndef FORTRAN_COMPLEX_FUNCTIONS_RETURN_VOID
extern doublecomplex zdotu(
#else
extern void zdotu(
    doublecomplex* retval,
#endif 
    ptrdiff_t *n,
    double *zx,
    ptrdiff_t *incx,
    double *zy,
    ptrdiff_t *incy
);

/* Source: zdrot.f */
#define zdrot FORTRAN_WRAPPER(zdrot)
extern void zdrot(
    ptrdiff_t *n,
    double *cx,
    ptrdiff_t *incx,
    double *cy,
    ptrdiff_t *incy,
    double *c,
    double *s
);

/* Source: zdscal.f */
#define zdscal FORTRAN_WRAPPER(zdscal)
extern void zdscal(
    ptrdiff_t *n,
    double *da,
    double *zx,
    ptrdiff_t *incx
);

/* Source: zgbmv.f */
#define zgbmv FORTRAN_WRAPPER(zgbmv)
extern void zgbmv(
    char   *trans,
    ptrdiff_t *m,
    ptrdiff_t *n,
    ptrdiff_t *kl,
    ptrdiff_t *ku,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx,
    double *beta,
    double *y,
    ptrdiff_t *incy
);

/* Source: zgemm.f */
#define zgemm FORTRAN_WRAPPER(zgemm)
extern void zgemm(
    char   *transa,
    char   *transb,
    ptrdiff_t *m,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: zgemv.f */
#define zgemv FORTRAN_WRAPPER(zgemv)
extern void zgemv(
    char   *trans,
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx,
    double *beta,
    double *y,
    ptrdiff_t *incy
);

/* Source: zgerc.f */
#define zgerc FORTRAN_WRAPPER(zgerc)
extern void zgerc(
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *y,
    ptrdiff_t *incy,
    double *a,
    ptrdiff_t *lda
);

/* Source: zgeru.f */
#define zgeru FORTRAN_WRAPPER(zgeru)
extern void zgeru(
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *y,
    ptrdiff_t *incy,
    double *a,
    ptrdiff_t *lda
);

/* Source: zhbmv.f */
#define zhbmv FORTRAN_WRAPPER(zhbmv)
extern void zhbmv(
    char   *uplo,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx,
    double *beta,
    double *y,
    ptrdiff_t *incy
);

/* Source: zhemm.f */
#define zhemm FORTRAN_WRAPPER(zhemm)
extern void zhemm(
    char   *side,
    char   *uplo,
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: zhemv.f */
#define zhemv FORTRAN_WRAPPER(zhemv)
extern void zhemv(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx,
    double *beta,
    double *y,
    ptrdiff_t *incy
);

/* Source: zher.f */
#define zher FORTRAN_WRAPPER(zher)
extern void zher(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *a,
    ptrdiff_t *lda
);

/* Source: zher2.f */
#define zher2 FORTRAN_WRAPPER(zher2)
extern void zher2(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *y,
    ptrdiff_t *incy,
    double *a,
    ptrdiff_t *lda
);

/* Source: zher2k.f */
#define zher2k FORTRAN_WRAPPER(zher2k)
extern void zher2k(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: zherk.f */
#define zherk FORTRAN_WRAPPER(zherk)
extern void zherk(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: zhpmv.f */
#define zhpmv FORTRAN_WRAPPER(zhpmv)
extern void zhpmv(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *ap,
    double *x,
    ptrdiff_t *incx,
    double *beta,
    double *y,
    ptrdiff_t *incy
);

/* Source: zhpr.f */
#define zhpr FORTRAN_WRAPPER(zhpr)
extern void zhpr(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *ap
);

/* Source: zhpr2.f */
#define zhpr2 FORTRAN_WRAPPER(zhpr2)
extern void zhpr2(
    char   *uplo,
    ptrdiff_t *n,
    double *alpha,
    double *x,
    ptrdiff_t *incx,
    double *y,
    ptrdiff_t *incy,
    double *ap
);

/* Source: zrotg.f */
#define zrotg FORTRAN_WRAPPER(zrotg)
extern void zrotg(
    double *ca,
    double *cb,
    double *c,
    double *s
);

/* Source: zscal.f */
#define zscal FORTRAN_WRAPPER(zscal)
extern void zscal(
    ptrdiff_t *n,
    double *za,
    double *zx,
    ptrdiff_t *incx
);

/* Source: zswap.f */
#define zswap FORTRAN_WRAPPER(zswap)
extern void zswap(
    ptrdiff_t *n,
    double *zx,
    ptrdiff_t *incx,
    double *zy,
    ptrdiff_t *incy
);

/* Source: zsymm.f */
#define zsymm FORTRAN_WRAPPER(zsymm)
extern void zsymm(
    char   *side,
    char   *uplo,
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: zsyr2k.f */
#define zsyr2k FORTRAN_WRAPPER(zsyr2k)
extern void zsyr2k(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: zsyrk.f */
#define zsyrk FORTRAN_WRAPPER(zsyrk)
extern void zsyrk(
    char   *uplo,
    char   *trans,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *beta,
    double *c,
    ptrdiff_t *ldc
);

/* Source: ztbmv.f */
#define ztbmv FORTRAN_WRAPPER(ztbmv)
extern void ztbmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx
);

/* Source: ztbsv.f */
#define ztbsv FORTRAN_WRAPPER(ztbsv)
extern void ztbsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    ptrdiff_t *k,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx
);

/* Source: ztpmv.f */
#define ztpmv FORTRAN_WRAPPER(ztpmv)
extern void ztpmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    double *ap,
    double *x,
    ptrdiff_t *incx
);

/* Source: ztpsv.f */
#define ztpsv FORTRAN_WRAPPER(ztpsv)
extern void ztpsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    double *ap,
    double *x,
    ptrdiff_t *incx
);

/* Source: ztrmm.f */
#define ztrmm FORTRAN_WRAPPER(ztrmm)
extern void ztrmm(
    char   *side,
    char   *uplo,
    char   *transa,
    char   *diag,
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb
);

/* Source: ztrmv.f */
#define ztrmv FORTRAN_WRAPPER(ztrmv)
extern void ztrmv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx
);

/* Source: ztrsm.f */
#define ztrsm FORTRAN_WRAPPER(ztrsm)
extern void ztrsm(
    char   *side,
    char   *uplo,
    char   *transa,
    char   *diag,
    ptrdiff_t *m,
    ptrdiff_t *n,
    double *alpha,
    double *a,
    ptrdiff_t *lda,
    double *b,
    ptrdiff_t *ldb
);

/* Source: ztrsv.f */
#define ztrsv FORTRAN_WRAPPER(ztrsv)
extern void ztrsv(
    char   *uplo,
    char   *trans,
    char   *diag,
    ptrdiff_t *n,
    double *a,
    ptrdiff_t *lda,
    double *x,
    ptrdiff_t *incx
);

#ifdef __cplusplus
    }   /* extern "C" */
#endif

#endif /* blas_h */
