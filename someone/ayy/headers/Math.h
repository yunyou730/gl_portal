#pragma once
#include <iostream>

namespace ayy {

const float PI = 3.1415926;

/*
    基于 行向量,向量 x 矩阵 时，向量在左侧,矩阵在右侧 的原则, 实现数学库

 
  [
      3x3 仿射变换,        0,
                          0
                          ratio
      tx,ty,tz,              1
  ]
 
    shader 里、cpp 里， 都是从左往右 的顺序

    vec = origin_vec * mat1 * mat2 * mat3 * ...
    
    从左往右开始变换
 
    cpp 给 shader 传矩阵值时，需要 做 转秩
    glUniformMatrix4fv(location,1,GL_TRUE,data)
    即 参数3 需要传为 GL_TRUE
    
    右手坐标系
    体现在 camera 的 View矩阵 和 Projection 矩阵里
 */

/*
    Vector is row major.seem as a row
 */
template<typename T,int N>
struct Vec
{
    union
    {
        T data[N];
    };
    
    Vec()
    {
        assert(N > 0);
        
        for(int i = 0;i < N;i++)
        {
            data[i] = 0;
        }
    }
    
    Vec(T x,T y = 0,T z = 0,T w = 0)
    {
        assert(N > 0);
        data[0] = x;

        if(N >= 2)
        {
            data[1] = y;
        }
        if(N >= 3)
        {
            data[2] = z;
        }
        if(N >= 4)
        {
            data[3] = w;
        }
    }
    
    Vec(T value)
    {
        for(int i = 0;i < N;i++)
        {
            data[i] = value;
        }
    }
    
    Vec(const Vec& other)
    {
        for(int i = 0;i < N;i++)
        {
            data[i] = other.data[i];
        }
    }
    
    T x() const {assert(N > 0);return data[0];}
    T y() const {assert(N > 1);return data[1];}
    T z() const {assert(N > 2);return data[2];}
    T w() const {assert(N > 3);return data[3];}
    
    void SetX(T v) {assert(N > 0);data[0] = v;}
    void SetY(T v) {assert(N > 1);data[1] = v;}
    void SetZ(T v) {assert(N > 2);data[2] = v;}
    void SetW(T v) {assert(N > 3);data[3] = v;}
    
    int Dimension() const {return N;}
    
    T operator[](int index) const { return data[index]; }
    
    
    void operator=(const Vec& other)
    {
        for(int i = 0;i < N;i++)
        {
            if(i < other.Dimension())
            {
                data[i] = other.data[i];
            }
        }
    }
    
    T Length() const
    {
        float total = 0;
        for(int i = 0;i < N;i++)
        {
            if(data[i] != T(0))
            {
                total += data[i] * data[i];
            }
        }
        if(total == T(0))
            return 0;
        return sqrt(total);
    }
    
    Vec<T,N>& Normalize()
    {
        T len = Length();
        if(len > T(0))
        {
            for(int i = 0;i < N;i++)
            {
                data[i] /= len;
            }
        }
        return *this;
    }
    
    Vec<T,N> GetNormalize() const
    {
        T len = Length();
        Vec<T,N> result = *this;
        if(len > T(0))
        {
            for(int i = 0;i < N;i++)
            {
                result.data[i] = data[i] / len;
            }
        }
        return result;
    }
    
    
    Vec<T,N> GetNormal()
    {
        Vec<T,N> result(*this);
        T len = Length();
        if(len > T(0))
        {
            for(int i = 0;i < N;i++)
            {
                result /= len;
            }
        }
        return result;
    }
    
    
    Vec<T,N> operator+(const Vec<T,N>& other) const
    {
        Vec<T,N> result;
        for(int i = 0;i < N;i++)
        {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }
    
    Vec<T,N> operator-(const Vec<T,N>& other) const
    {
        Vec<T,N> result;
        for(int i = 0;i < N;i++)
        {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }
    
    /*
     Geo meaning: |A| * |B| * Cos(theta)
     */
    T Dot(const Vec<T,N>& other)
    {
        T v = 0;
        for(int i = 0;i < N;i++)
        {
            v += data[i] * other.data[i];
        }
        return v;
    }
    
    /*
        Geo meaning ,length: |A| x |B| * sin(theta)
     **/
    Vec<T,N> Cross(const Vec<T,N>& other) const
    {
        Vec<T,N> result;
        
        assert(N == 3);
        T x1 = data[0];
        T y1 = data[1];
        T z1 = data[2];
        
        T x2 = other.data[0];
        T y2 = other.data[1];
        T z2 = other.data[2];
        
        T x = y1 * z2 - z1 * y2;
        T y = z1 * x2 - x1 * z2;
        T z = x1 * y2 - y1 * x2;
        
        result.SetX(x);
        result.SetY(y);
        result.SetZ(z);
        
        return result;
    }
    
    Vec<T,N> operator*(T val)
    {
        Vec<T,N> result;
        for(int i = 0;i < N;i++)
        {
            result.data[i] = data[i] * val;
        }
        return result;
    }
    
    Vec<T,N> operator/(T val)
    {
        assert(val != 0);
        T inverse = 1.0/val;
        Vec<T,N> result;
        for(int i = 0;i < N;i++)
        {
            result.data[i] *= inverse;
        }
        return result;
    }
    
    
    void InvserSelf()
    {
        for(int i = 0;i < N;i++)
        {
            data[i] = -data[i];
        }
    }
    
    void Dump()
    {
        printf("-------\n");
        for(int i = 0;i < N;i++)
        {
            printf("[%d] %.3f,",i,data[i]);
        }
        printf("\n");
    }
};

template<typename T,int RN,int CN>
struct Mat
{
    /*
     [0][0] [0][1] [0][2] [0][3]
     [1][0] [1][1] [1][2] [1][3]
     [2][0] [2][1] [2][2] [2][3]
     [3][0] [3][1] [3][2] [3][3]
     */
    T data[RN][CN];   // sub index 1: row, sub index 2: col
//    int sideLen = N;
    
    Mat()
    {
        for(int row = 0;row < RN;row++)
        {
            for(int col = 0;col < CN;col++)
            {
                data[row][col] = 0;
            }
        }
    }
    
    Mat(T val)
    {
        for(int row = 0;row < RN;row++)
        {
            for(int col = 0;col < CN;col++)
            {
                data[row][col] = (row == col) ? val : 0;
            }
        }
    }
    
    void Identify()
    {
        for(int row = 0;row < RN;row++)
        {
            for(int col = 0;col < CN;col++)
            {
                data[row][col] = (row == col) ? 1 : 0;
            }
        }
    }
    
    void GetDimension(int& rows,int& cols)
    {
        rows = RN;
        cols = CN;
    }
    
    void Set(int r,int c,T v)
    {
        assert(r >= 0 && r < RN && c >= 0 && c < CN);
        data[r][c] = v;
    }
    
    T Get(int r,int c)
    {
        assert(r >= 0 && r < RN && c >= 0 && c < CN);
        return data[r][c];
    }
    
    // @miao @todo
    void InverseSelf()
    {
        assert(RN == CN);
        
        for(int r = 0;r < RN;r++)
        {
            for(int c = 0;c < CN;c++)
            {
                
            }
        }
    }
    
    void Dump()
    {
        printf("---------------\n");
        for(int row = 0;row < RN;row++)
        {
            for(int col = 0;col < CN;col++)
            {
                printf("[%d][%d] %.3f,\t",row,col,data[row][col]);
            }
            printf("\n");
        }
        printf("---------------\n");
    }
};


template<typename T,int N>
Vec<T,N> operator*(T val,const Vec<T,N>& other)
{
    Vec<T,N> result;
    for(int i = 0;i < N;i++)
    {
        result.data[i] = other.data[i] * val;
    }
    return result;
}


template<typename T,int N,int RN,int CN>
Vec<T,N> operator*(
                   const Vec<T,N>& other,
                   const Mat<T,RN,CN>& mat
)
{
    assert(N == RN);
    // m1
    Mat<T,1,N> m1;
    for(int i = 0;i < N;i++)
    {
        m1.Set(0,i,other.data[i]);
    }
    Mat<T,1,CN> mr = m1 * mat;
    Vec<T,N> result;
    for(int i = 0;i < N;i++)
    {
        result.data[i] = mr.Get(0,i);
    }
    return result;
}

template<typename T,int R1,int C1,int R2,int C2>
Mat<T,R1,C2> operator*(const Mat<T,R1,C1>& m1,const Mat<T,R2,C2>& m2)
{
    assert(C1 == R2);
    
    Mat<T,R1,C2> result;
    for(int r = 0;r < R1;r++)
    {
        for(int c = 0;c < C2;c++)
        {
            // each element
            T sum = 0;
            for(int i = 0;i < C1;i++)
            {
                T v = m1.data[r][i] * m2.data[i][c];
                sum += v;
            }
            result.data[r][c] = sum;
        }
    }
    
    return result;
}

typedef Vec<float,2>        Vec2f;
typedef Vec<float,3>        Vec3f;
typedef Vec<float,4>        Vec4f;
typedef Mat<float,4,4>      Mat4x4f;

extern void MakeScaleMatrix(Mat4x4f& mat,float scale);
extern void MakeTranslateMatrix(Mat4x4f& mat,float ox,float oy,float oz);
extern void MakeRotateByXMatrix(Mat4x4f& mat,float rad);
extern void MakeRotateByYMatrix(Mat4x4f& mat,float rad);
extern void MakeRotateByZMatrix(Mat4x4f& mat,float rad);
extern void MakeRotateByAxisMatrix(Mat4x4f& mat,const Vec3f& axis,float rad);


extern float RadToDeg(float rad);
extern float DegToRad(float deg);


template<typename T>
void Clamp(T& v,T min,T max)
{
    assert(min <= max);
    
    if(v < min)
        v = min;
    if(v > max)
        v = max;
}

}

