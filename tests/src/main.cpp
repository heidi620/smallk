#include <iostream>
#include <string>
#include "nmf.hpp"
#include "tests.hpp"
#include "utils.hpp"
#include "sparse_matrix.hpp"

using std::cout;
using std::cerr;
using std::endl;

bool TestSparseMatrixGet();

//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    bool all_ok = true;

    if (1 == argc)
    {
        cerr << "Usage: " << argv[0] << "  <path_to_data_dir>" << endl;
        return -1;
    }

    std::string data_dir = EnsureTrailingPathSep(std::string(argv[1]));

    NmfInitialize(argc, argv);

    TestParallelInit();
    
    if (!TestSparseMatrixGet())
    {
        all_ok = false;
        cerr << "TestSparseMatrixGet failed" << endl;
    }
    
    if (!TestOpenMP())
    {
        all_ok = false;
        cerr << "OpenMP test failed" << endl;
    }

    if (!TestBpp(data_dir))
    {
        all_ok = false;
        cerr << "BPP operations test failed" << endl;
    }

    if (!TestDenseNmf())
    {
        all_ok = false;
        cerr << "dense nmf test failed " << endl;
    }

    if (!TestRank2SystemSolve())
    {
        all_ok = false;
        cerr << "Rank2 system solver test failed " << endl;
    }

    if (!TestSparseGemm())
    {
        all_ok = false;
        cerr << "sparse gemm test failed " << endl;
    }

    NmfFinalize();

    if (all_ok)
        cout << "all tests passed" << endl;

    return 0;
}

//-----------------------------------------------------------------------------
bool TestSparseMatrixGet()
{
    SparseMatrix<double> M(3, 4, 5);

    M.BeginLoad();
    M.Load(1, 0, 1.0);
    M.Load(1, 1, 2.0);
    M.Load(2, 0, 3.0);
    M.Load(2, 1, 4.0);
    M.Load(2, 3, 5.0);
    M.EndLoad();

    double m00 = M.Get(0, 0);
    double m01 = M.Get(0, 1);
    double m02 = M.Get(0, 2);
    double m03 = M.Get(0, 3);
    double m10 = M.Get(1, 0);
    double m11 = M.Get(1, 1);
    double m12 = M.Get(1, 2);
    double m13 = M.Get(1, 3);
    double m20 = M.Get(2, 0);
    double m21 = M.Get(2, 1);
    double m22 = M.Get(2, 2);
    double m23 = M.Get(2, 3);

    if ( (0.0 != m00) || (0.0 != m01) || (0.0 != m02) || (0.0 != m03) ||
         (1.0 != m10) || (2.0 != m11) || (0.0 != m12) || (0.0 != m13) ||
         (3.0 != m20) || (4.0 != m21) || (0.0 != m22) || (5.0 != m23))
    {
        return false;
    }

    return true;
}

    // if (!TestSparseGemmIndexed())
    // {
    //     all_ok = false;
    //     cerr << "sparse gemm indexed test failed " << endl;
    // }

    // if (!TestIndexedRank2Nmf())
    // {
    //     all_ok = false;
    //     cerr << "indexed rank2 nmf test failed" << endl;
    // }
