#include <symengine/expression.h>
using SymEngine::Expression;
using SymEngine::factorial;
using SymEngine::map_basic_basic;
using SymEngine::DenseMatrix;

Expression diffn(Expression f, Expression x, unsigned int n)
{
    for(int i = 0;i<n;i++)
    {
        f = f.diff(x);
    }
    return f;
}

Expression carlemanFunc(Expression f, Expression x, unsigned int j, unsigned int k)
{
    Expression a = diffn(pow(f,j), x, k);

   return a/factorial(k);
}

void carlemanMatrix(Expression f, Expression x, DenseMatrix &C)
{
    for(int i =0;i<C.nrows();i++)
    {
        for(int j=0; j < C.ncols(); j++)
        {
            C.set(i, j, carlemanFunc(f, x, i, j));
        }
    }

}

void carlemanVector(Expression x, DenseMatrix &v)
{
    for(int i = 0; i < v.nrows(); i++)
    {
            v.set(i,0, pow(x,i ));
    }
}

void pow(DenseMatrix &A, unsigned int p, DenseMatrix &B)
{
    B = A;
    for(int i = 1; i < p; i++) 
    {
        mul_dense_dense(A, B, B);
    }
}

#define CMATRIX_SIZE 8 
int main() 
{
    Expression x("x");

    //Expression iteratingFunc = (x*x + 2);
    //Logistic map
    Expression r = 3.56996;
    Expression iteratingFunc = r*x*(x - 1) + 0.1;
    int iterationSteps = 2;

    DenseMatrix A = DenseMatrix(CMATRIX_SIZE, CMATRIX_SIZE);
    DenseMatrix B = DenseMatrix(CMATRIX_SIZE, CMATRIX_SIZE);
    DenseMatrix C = DenseMatrix(CMATRIX_SIZE, CMATRIX_SIZE);
    DenseMatrix v = DenseMatrix(CMATRIX_SIZE, 1);

    Expression x0 = 0;
    map_basic_basic submap = map_basic_basic();

    //Fill A with Carleman/Bell entries
    carlemanMatrix(iteratingFunc, x, A);

    //std::cout << A << std::endl;

    //Generate the 2nd step of the iteration via matrix multiplication
    pow(A, iterationSteps, B);

    carlemanVector(x, v);

    dot(B, v, C);

    submap[x] = x0;

    Expression n = C.get(0,1)->subs(submap);

    std::cout << "The value of x_" << iterationSteps << " for " << iteratingFunc << " :" << std::endl;
    std::cout << n << std::endl;
    

}