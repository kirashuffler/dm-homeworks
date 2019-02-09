#include <iostream>
#include <cmath>
#include <random>

using namespace std;

ostream& manip(ostream &out);

class Matrix {
    unsigned int width;
    unsigned int height;
    double **ptr;
public:
    Matrix() {cout << "\nthis is matrix class\n";}
    Matrix(unsigned w, unsigned h) {
        if(w == 0 || h == 0)
            throw -1.0;
        width = w;
        height = h;
        ptr = new double*[width];
        for(int i = 0; i < width; ++i)
            ptr[i] = new double[height];
   	}
    Matrix(Matrix &M) {
        width = M.width;
        height = M.height;
        ptr = new double*[width];
        for(int i = 0; i < width; ++i)
            ptr[i] = new double[height];
        for(int i = 0; i < width; ++i)
            for(int j = 0; j < height; ++j)
                ptr[i][j] = M.ptr[i][j];
    }
    ~Matrix() { cout << "\ndeleting..\n"; delete[] ptr; }
    
    
    void print() {
        cout << "\n";
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; ++j)
                cout << ptr[i][j] << " ";
            cout << endl;
        }
        cout << "\n";
    }
    void scan() {
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; ++j)
                cin >> ptr[i][j];
        }
    }
    
    double& operator()(unsigned i, unsigned j) {
        return ptr[i][j];
    }
    
    Matrix& operator = (const Matrix& m) {
        width = m.width;
        height = m.height;
        ptr = new double*[width];
        for(int i = 0; i < width; ++i)
            ptr[i] = new double[height];
        for(int i = 0; i < m.width; ++i)
            for(int j = 0; j < m.height; ++j)
                ptr[i][j] = m.ptr[i][j];
        return *this;
    }
    
    Matrix& operator+(Matrix &m) {
        if(width == m.width && height == m.height) {
            Matrix *res = new Matrix(width, height);
            for(int i = 0; i < width; ++i){
                for(int j = 0; j < height; ++j){
                    res->ptr[i][j] = ptr[i][j] + m(i, j);
                }
            }
            return *res;
        }
        throw -0.01;
    }
    
    Matrix& operator-(Matrix &m) {
        if(width == m.width && height == m.height) {
            Matrix *res = new Matrix(width, height);
            for(int i = 0; i < width; ++i){
                for(int j = 0; j < height; ++j){
                    res->ptr[i][j] = ptr[i][j] - m(i, j);
                }
            }
            return *res;
        }
        throw -0.01;
    }
    
    Matrix& operator*(Matrix &m) {
        if (height != m.width) throw -0.01;
        Matrix *res = new Matrix(width, m.height);
        for(int i = 0; i < res->width; ++i) {
            for(int j = 0; j < res->height; ++j) {
                res->ptr[i][j] = 0;
                for(int k = 0; k < height; ++k) {
                    res->ptr[i][j] += ptr[i][k] * m(k, j);
                }
            }
        }
        return *res;
    }
    
   /* friend Matrix& operator*(Matrix &m, double a) {
        Matrix *res = new Matrix(m.width, m.height);
        for(int i = 0; i < m.width; ++i)
            for(int j = 0; j < m.height; ++j)
                res->ptr[i][j] = a * m.ptr[i][j];
        return *res;
    }*/
    friend Matrix& operator*(Matrix &m, double a) {
        Matrix *res = new Matrix(m.width, m.height);
        for(int i = 0; i < m.width; ++i)
            for (int j = 0; j < m.height; ++j)
                res->ptr[i][j] = m(i, j) * a;
        return *res;
    }
    friend Matrix& operator*(double a, Matrix &m) {
        Matrix *res = new Matrix(m.width, m.height);
        for(int i = 0; i < m.width; ++i)
            for (int j = 0; j < m.height; ++j)
                res->ptr[i][j] = m(i, j) * a;
        return *res;
    }
    
    friend Matrix& operator+(Matrix &m, double a) {
        Matrix *res = new Matrix(m.width, m.height);
        for(int i = 0; i < m.width; ++i)
            for (int j = 0; j < m.height; ++j)
                res->ptr[i][j] = m(i, j) + a;
        return *res;
    }
    friend Matrix& operator+(double a, Matrix &m) {
        Matrix *res = new Matrix(m.width, m.height);
        for(int i = 0; i < m.width; ++i)
            for (int j = 0; j < m.height; ++j)
                res->ptr[i][j] = m(i, j) + a;
        return *res;
    }
    
    friend ostream& operator<<(ostream &out, Matrix m) {
        out << manip;
        for (int i = 0; i < m.width; ++i)  {
            for (int j = 0; j < m.width; ++j)
                out << m(i, j) << "\t";
            cout << endl;
        }
        return out;
    }
    friend istream& operator>>(istream &in, Matrix &m) {
        for (int i = 0; i < m.width; ++i)
            for (int j = 0; j < m.width; ++j)
                in >> m(i, j);
        return in;
    }
    bool operator==(Matrix &m) {
        if(width != m.width || height != m.height) return false;
        for(int i = 0; i < width; ++i)
            for(int j = 0; j < height; ++j)
                if(ptr[i][j] != m(i, j)) return false;
        return true;
    }
    void fillWithRands(double from, double to) {
        for(int i = 0; i < width; ++i)
            for(int j = 0; j < height; ++j)
                ptr[i][j] = from + double(random())/to;
    }
};

ostream& manip(ostream &out) {
    out << scientific;
    out.precision(5);
    return out;
}


int main() {
    int w, h; // size n*m
    cin >> w >> h; //creating and initiliazing width and height of matrix
    Matrix a(w, h), c(w, h), m(w, h); //making matrix obj
    double b, d; //nums
    a.scan();
    a.print();
    cout << "enter nums\n";
    cin >> b >> d; //enter nums
    c = d * a * b; //multiplying
    a.print();
    c.print();
    cin >> m;
    cout << m;
    Matrix m1(3, 3), m2(3, 3), m3(3, 3), m4(3, 3); //making a bunch of matrixes
    m1.fillWithRands(2.3, 23.07); m2.fillWithRands(7.4, 32.7); //filling it with random doubles
    m3 = m1 * m2; m4 = m1 + m2; //some operations
    cout << m3; // results
    cout << m4;
    return 0;
}

