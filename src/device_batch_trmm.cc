// Copyright (c) 2017-2022, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include <limits>
#include <cstring>
#include "blas/batch_common.hh"
#include "blas/device_blas.hh"

// -----------------------------------------------------------------------------
/// @ingroup trmm
void blas::batch::trmm(
    blas::Layout                   layout,
    std::vector<blas::Side> const &side,
    std::vector<blas::Uplo> const &uplo,
    std::vector<blas::Op>   const &trans,
    std::vector<blas::Diag> const &diag,
    std::vector<int64_t>    const &m,
    std::vector<int64_t>    const &n,
    std::vector<float >     const &alpha,
    std::vector<float*>     const &Aarray, std::vector<int64_t> const &ldda,
    std::vector<float*>     const &Barray, std::vector<int64_t> const &lddb,
    const size_t batch,                    std::vector<int64_t>       &info,
    blas::Queue &queue )
{
    blas_error_if( layout != Layout::ColMajor && layout != Layout::RowMajor );
    blas_error_if( batch < 0 );
    blas_error_if( !(info.size() == 0 || info.size() == 1 || info.size() == batch) );
    if (info.size() > 0) {
        // perform error checking
        blas::batch::trmm_check<float>( layout, side, uplo, trans, diag,
                                        m, n,
                                        alpha, Aarray, ldda,
                                               Barray, lddb,
                                        batch, info );
    }

    // rocm 4.0 seems to have bug with trmm when using multiple streams.
    #ifdef BLAS_HAVE_ROCBLAS
        const bool fork = false;
    #else
        const bool fork = true;
    #endif

    #ifndef BLAS_HAVE_ONEMKL
    blas::set_device( queue.device() );
    #endif

    if (fork)
        queue.fork();
    for (size_t i = 0; i < batch; ++i) {
        Side side_   = blas::batch::extract<Side>(side, i);
        Uplo uplo_   = blas::batch::extract<Uplo>(uplo, i);
        Op   trans_  = blas::batch::extract<Op>(trans, i);
        Diag diag_   = blas::batch::extract<Diag>(diag, i);
        int64_t m_   = blas::batch::extract<int64_t>(m, i);
        int64_t n_   = blas::batch::extract<int64_t>(n, i);
        int64_t lda_ = blas::batch::extract<int64_t>(ldda, i);
        int64_t ldb_ = blas::batch::extract<int64_t>(lddb, i);
        float alpha_ = blas::batch::extract<float>(alpha, i);
        float* dA_   = blas::batch::extract<float*>(Aarray, i);
        float* dB_   = blas::batch::extract<float*>(Barray, i);
        blas::trmm(
            layout, side_, uplo_, trans_, diag_, m_, n_,
            alpha_, dA_, lda_,
                    dB_, ldb_, queue );
        if (fork)
            queue.revolve();
    }
    if (fork)
        queue.join();
}


// -----------------------------------------------------------------------------
/// @ingroup trmm
void blas::batch::trmm(
    blas::Layout                   layout,
    std::vector<blas::Side> const &side,
    std::vector<blas::Uplo> const &uplo,
    std::vector<blas::Op>   const &trans,
    std::vector<blas::Diag> const &diag,
    std::vector<int64_t>    const &m,
    std::vector<int64_t>    const &n,
    std::vector<double >     const &alpha,
    std::vector<double*>     const &Aarray, std::vector<int64_t> const &ldda,
    std::vector<double*>     const &Barray, std::vector<int64_t> const &lddb,
    const size_t batch,                     std::vector<int64_t>       &info,
    blas::Queue &queue )
{
    blas_error_if( layout != Layout::ColMajor && layout != Layout::RowMajor );
    blas_error_if( batch < 0 );
    blas_error_if( !(info.size() == 0 || info.size() == 1 || info.size() == batch) );
    if (info.size() > 0) {
        // perform error checking
        blas::batch::trmm_check<double>( layout, side, uplo, trans, diag,
                                        m, n,
                                        alpha, Aarray, ldda,
                                               Barray, lddb,
                                        batch, info );
    }

    // rocm 4.0 seems to have bug with trmm when using multiple streams.
    #ifdef BLAS_HAVE_ROCBLAS
        const bool fork = false;
    #else
        const bool fork = true;
    #endif

    #ifndef BLAS_HAVE_ONEMKL
    blas::set_device( queue.device() );
    #endif

    if (fork)
        queue.fork();
    for (size_t i = 0; i < batch; ++i) {
        Side side_   = blas::batch::extract<Side>(side, i);
        Uplo uplo_   = blas::batch::extract<Uplo>(uplo, i);
        Op   trans_  = blas::batch::extract<Op>(trans, i);
        Diag diag_   = blas::batch::extract<Diag>(diag, i);
        int64_t m_   = blas::batch::extract<int64_t>(m, i);
        int64_t n_   = blas::batch::extract<int64_t>(n, i);
        int64_t lda_ = blas::batch::extract<int64_t>(ldda, i);
        int64_t ldb_ = blas::batch::extract<int64_t>(lddb, i);
        double alpha_ = blas::batch::extract<double>(alpha, i);
        double* dA_   = blas::batch::extract<double*>(Aarray, i);
        double* dB_   = blas::batch::extract<double*>(Barray, i);
        blas::trmm(
            layout, side_, uplo_, trans_, diag_, m_, n_,
            alpha_, dA_, lda_,
                    dB_, ldb_, queue );
        if (fork)
            queue.revolve();
    }
    if (fork)
        queue.join();
}


// -----------------------------------------------------------------------------
/// @ingroup trmm
void blas::batch::trmm(
    blas::Layout                   layout,
    std::vector<blas::Side> const &side,
    std::vector<blas::Uplo> const &uplo,
    std::vector<blas::Op>   const &trans,
    std::vector<blas::Diag> const &diag,
    std::vector<int64_t>    const &m,
    std::vector<int64_t>    const &n,
    std::vector<std::complex<float> >     const &alpha,
    std::vector<std::complex<float>*>     const &Aarray, std::vector<int64_t> const &ldda,
    std::vector<std::complex<float>*>     const &Barray, std::vector<int64_t> const &lddb,
    const size_t batch,                     std::vector<int64_t>       &info,
    blas::Queue &queue )
{
    blas_error_if( layout != Layout::ColMajor && layout != Layout::RowMajor );
    blas_error_if( batch < 0 );
    blas_error_if( !(info.size() == 0 || info.size() == 1 || info.size() == batch) );
    if (info.size() > 0) {
        // perform error checking
        blas::batch::trmm_check<std::complex<float>>( layout, side, uplo, trans, diag,
                                        m, n,
                                        alpha, Aarray, ldda,
                                               Barray, lddb,
                                        batch, info );
    }

    // rocm 4.0 seems to have bug with trmm when using multiple streams.
    #ifdef BLAS_HAVE_ROCBLAS
        const bool fork = false;
    #else
        const bool fork = true;
    #endif

    #ifndef BLAS_HAVE_ONEMKL
    blas::set_device( queue.device() );
    #endif

    if (fork)
        queue.fork();
    for (size_t i = 0; i < batch; ++i) {
        Side side_   = blas::batch::extract<Side>(side, i);
        Uplo uplo_   = blas::batch::extract<Uplo>(uplo, i);
        Op   trans_  = blas::batch::extract<Op>(trans, i);
        Diag diag_   = blas::batch::extract<Diag>(diag, i);
        int64_t m_   = blas::batch::extract<int64_t>(m, i);
        int64_t n_   = blas::batch::extract<int64_t>(n, i);
        int64_t lda_ = blas::batch::extract<int64_t>(ldda, i);
        int64_t ldb_ = blas::batch::extract<int64_t>(lddb, i);
        std::complex<float> alpha_ = blas::batch::extract<std::complex<float>>(alpha, i);
        std::complex<float>* dA_   = blas::batch::extract<std::complex<float>*>(Aarray, i);
        std::complex<float>* dB_   = blas::batch::extract<std::complex<float>*>(Barray, i);
        blas::trmm(
            layout, side_, uplo_, trans_, diag_, m_, n_,
            alpha_, dA_, lda_,
                    dB_, ldb_, queue );
        if (fork)
            queue.revolve();
    }
    if (fork)
        queue.join();
}

// -----------------------------------------------------------------------------
/// @ingroup trmm
void blas::batch::trmm(
    blas::Layout                   layout,
    std::vector<blas::Side> const &side,
    std::vector<blas::Uplo> const &uplo,
    std::vector<blas::Op>   const &trans,
    std::vector<blas::Diag> const &diag,
    std::vector<int64_t>    const &m,
    std::vector<int64_t>    const &n,
    std::vector<std::complex<double> >     const &alpha,
    std::vector<std::complex<double>*>     const &Aarray, std::vector<int64_t> const &ldda,
    std::vector<std::complex<double>*>     const &Barray, std::vector<int64_t> const &lddb,
    const size_t batch,                     std::vector<int64_t>       &info,
    blas::Queue &queue )
{
    blas_error_if( layout != Layout::ColMajor && layout != Layout::RowMajor );
    blas_error_if( batch < 0 );
    blas_error_if( !(info.size() == 0 || info.size() == 1 || info.size() == batch) );
    if (info.size() > 0) {
        // perform error checking
        blas::batch::trmm_check<std::complex<double>>( layout, side, uplo, trans, diag,
                                        m, n,
                                        alpha, Aarray, ldda,
                                               Barray, lddb,
                                        batch, info );
    }

    // rocm 4.0 seems to have bug with trmm when using multiple streams.
    #ifdef BLAS_HAVE_ROCBLAS
        const bool fork = false;
    #else
        const bool fork = true;
    #endif

    #ifndef BLAS_HAVE_ONEMKL
    blas::set_device( queue.device() );
    #endif

    if (fork)
        queue.fork();
    for (size_t i = 0; i < batch; ++i) {
        Side side_   = blas::batch::extract<Side>(side, i);
        Uplo uplo_   = blas::batch::extract<Uplo>(uplo, i);
        Op   trans_  = blas::batch::extract<Op>(trans, i);
        Diag diag_   = blas::batch::extract<Diag>(diag, i);
        int64_t m_   = blas::batch::extract<int64_t>(m, i);
        int64_t n_   = blas::batch::extract<int64_t>(n, i);
        int64_t lda_ = blas::batch::extract<int64_t>(ldda, i);
        int64_t ldb_ = blas::batch::extract<int64_t>(lddb, i);
        std::complex<double> alpha_ = blas::batch::extract<std::complex<double>>(alpha, i);
        std::complex<double>* dA_   = blas::batch::extract<std::complex<double>*>(Aarray, i);
        std::complex<double>* dB_   = blas::batch::extract<std::complex<double>*>(Barray, i);
        blas::trmm(
            layout, side_, uplo_, trans_, diag_, m_, n_,
            alpha_, dA_, lda_,
                    dB_, ldb_, queue );
        if (fork)
            queue.revolve();
    }
    if (fork)
        queue.join();
}
