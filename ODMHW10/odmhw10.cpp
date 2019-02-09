#include <fstream>
#include <iostream>
#include <cstdio>
class Matrix{// 2x2 matrix
    unsigned a11, a12, a21, a22;
    public:
    unsigned _11(){return a11;}
    unsigned _12(){return a12;}
    unsigned _21(){return a21;}
    unsigned _22(){return a22;}
    Matrix(unsigned b11,unsigned b12,unsigned b21, unsigned b22){
        a11 = b11;
        a12 = b12;
        a21 = b21;
        a22 = b22;
    }
    Matrix& operator = (const Matrix& m){
        a11 = m.a11;
        a12 = m.a12;
        a21 = m.a21;
        a22 = m.a22;
        return *this;
    }
    Matrix operator * (const Matrix& m){
        Matrix res(a11 * m.a11 + a12 * m.a21, a11 * m.a12 + a12 * m.a22, a21 * m.a11 + a22 * m.a21, a21 * m.a12 + a22 * m.a22);
        return res;
    }
    Matrix operator % (unsigned Base){
        Matrix res(a11 % Base, a12 % Base, a21 % Base, a22 % Base);
        return res;
    }
};

Matrix binpow(Matrix m,long long unsigned n, unsigned Base){
    Matrix res(1, 0, 0, 1);
    while(n){
        if (n & 1)
            res = (res * m) % Base;
        m = (m * m) % Base;
        n >>= 1;
    }
    return res;
}

unsigned sequence_member(unsigned x1,unsigned x2,unsigned a, unsigned b, unsigned m,long long unsigned k){
    Matrix base(x1 , x2, 0, 0);
    Matrix P(0 , b, 1, a);
    Matrix res(0, 0, 0, 0);
    res = base * binpow(P, k - 1, m);
    return res._11() % m;   
}
        
int main(int argc, char* argv[]){
    if (argc < 2){
        std::cout << "Incorrect launch\n";
        return 0;
    }
    std::ifstream file;
    file.open(argv[1]);
    unsigned n, x1, x2, a, b, m;
    long long unsigned k;
    file >> n ;
    for (int i = 0; i < n; ++i){
        file >> x1 >> x2 >> a >> b >> m >> k;
        unsigned res = sequence_member(x1, x2, a, b, m, k);
        std::cout << "result: " << res << "\n";
    }
    file.close();
    return 0;
}
