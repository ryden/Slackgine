#ifndef MATRIX_H
#define	MATRIX_H

#include <sstream>
#include <cmath>
#include <cstring>
#include "shared/platform.h"
#include "vector.h"

#define FAST_MATRIX_INVERSION

class Matrix
{
private:
    union
    {
        f32 v [ 16 ];
        f32 m [ 4 ][ 4 ];
    };
    
public:
    Matrix ( )
    {
    }
    
    f32*              vector  () { return v; }
    const f32*        vector  () const { return v; }
    
    // To string
    std::string toString () const
    {
        std::ostringstream os;
        for ( u8 i = 0; i < 4; ++i )
            os << m[0][i] << "\t" << m[1][i] << "\t" << m[2][i] << "\t" << m[3][i] << "\n";
        return os.str ();
    }
    
    // Copy, assignment, compare.
    Matrix ( const Matrix& m )
    {
        operator=(m);
    }
    Matrix& operator= ( const Matrix& m )
    {
        memcpy ( v, m.v, sizeof(m.v) );
        return *this;
    }
    Matrix ( const f32* vec )
    {
        operator= ( vec );
    }
    Matrix& operator= ( const float* vec )
    {
        memcpy ( v, vec, sizeof(v) );
        return *this;
    }
    
    bool operator== ( const Matrix& m ) const
    {
        return memcmp ( v, m.v, sizeof(m.v) ) == 0;
    }
    bool operator!= ( const Matrix& m ) const
    {
        return memcmp ( v, m.v, sizeof(m.v) ) != 0;
    }
    
    // Operations
    Matrix& Transpose ()
    {
        *this = Matrix::Transpose(*this);
        return *this;
    }
    static Matrix Transpose ( const Matrix& thiz )
    {
        Matrix ret;
        for ( u8 i = 0; i < 4; ++i )
            for ( u8 j = 0; j < 4; ++j )
                ret.m[i][j] = thiz.m[j][i];
        return ret;
    }
    
    Matrix& Invert ()
    {
        *this = Matrix::Invert(*this);
        return *this;
    }
    static Matrix Invert ( const Matrix& thiz )
    {
        Matrix ret;
#ifdef FAST_MATRIX_INVERSION
        for ( u8 i = 0; i < 3; ++i )
            for ( u8 j = 0; j < 3; ++j )
                ret.m[i][j] = thiz.m[j][i];
        for ( u8 i = 0; i < 3; ++i )
            ret.m[3][i] = -thiz.m[3][i];
#endif
        return ret;
    }
    
    void LoadIdentity ()
    {
        for ( u8 i = 0; i < 4; ++i )
            for ( u8 j = 0; j < 4; ++j )
                m[i][j] = ( i==j ? 1.0f : 0.0f );
    }
    
    // M + M
    Matrix operator+ ( const Matrix& m ) const
    {
        Matrix ret;
        for ( u8 i = 0; i < 16; ++i )
            ret.v[i] = v[i] + m.v[i];
        return ret;
    }
    Matrix& operator+= ( const Matrix& m )
    {
        for ( u8 i = 0; i < 16; ++i )
            v[i] += m.v[i];
        return *this;
    }
    
    // M - M
    Matrix operator-( const Matrix& m ) const
    {
        Matrix ret;
        for ( u8 i = 0; i < 16; ++i )
            ret.v[i] = v[i] - m.v[i];
        return ret;
    }
    Matrix& operator-= ( const Matrix& m )
    {
        for ( u8 i = 0; i < 16; ++i )
            v[i] -= m.v[i];
        return *this;
    }
    
    // M*M
    Matrix operator* ( const Matrix& Right ) const
    {
        Matrix ret;
        for ( u8 i = 0; i < 16; ++i )
            ret.v[i] = 0;
        
        f32 elem;
        for ( u8 i = 0; i < 4; ++i )
        {
            for ( u8 k = 0; k < 4; ++k )
            {
                elem = Right.m[i][k];
                for ( u8 j = 0; j < 4; ++j )
                {
                    ret.m[i][j] += elem * this->m[k][j];
                }
            }
        }
        
        return ret;
    }
    Matrix& operator*= ( const Matrix& m )
    {
        Matrix ret = operator*(m);
        *this = ret;
        return *this;
    }
    
    // M + s
    Matrix operator+ ( float s ) const
    {
        Matrix ret;
        for ( u8 i = 0; i < 16; ++i )
            ret.v[i] = v[i] + s;
        return ret;
    }
    Matrix& operator+= ( float s )
    {
        for ( u8 i = 0; i < 16; ++i )
            v[i] += s;
        return *this;
    }
    
    // M - s
    Matrix operator- ( float s ) const
    {
        Matrix ret;
        for ( u8 i = 0; i < 16; ++i )
            ret.v[i] = v[i] - s;
        return ret;
    }
    Matrix& operator-= ( float s )
    {
        for ( u8 i = 0; i < 16; ++i )
            v[i] -= s;
        return *this;
    }
    
    // M * s
    Matrix operator* ( float s ) const
    {
        Matrix ret;
        for ( u8 i = 0; i < 16; ++i )
            ret.v[i] = v[i] * s;
        return ret;
    }
    Matrix& operator*= ( float s )
    {
        for ( u8 i = 0; i < 16; ++i )
            v[i] *= s;
        return *this;
    }
    
    // M / s
    Matrix operator/ ( float s ) const
    {
        Matrix ret;
        for ( u8 i = 0; i < 16; ++i )
            ret.v[i] = v[i] / s;
        return ret;
    }
    Matrix& operator/= ( float s )
    {
        for ( u8 i = 0; i < 16; ++i )
            v[i] /= s;
        return *this;
    }
    
    // M^i
    Matrix operator^( i32 i ) const
    {
        Matrix ret ( *this );
        
        if ( i == 0 )
            ret.LoadIdentity ();
        else
        {
            if ( i < 0 )
            {
                ret.Invert();
                i = -i;
            }
            while ( --i > 0 )
                ret *= ret;
        }
        
        return ret;
    }
    
    // M*V
    Vector3 operator* ( const Vector3& v ) const
    {
        float res[3] = { 0, 0, 0 };
        
        f32 elem;
        for ( u8 i = 0; i < 3; ++i )
        {
            elem = v.vector()[i];
            for ( u8 k = 0; k < 3; ++k )
                res[k] += m[i][k] * elem;
        }
        
        return Vector3(res);
    }
};

class IdentityMatrix : public Matrix
{
public:
    IdentityMatrix ()
    {
        static f32 const s_identity[] = { 1.0f, 0.0f, 0.0f, 0.0f,
                                          0.0f, 1.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 1.0f };
        Matrix::operator= ( s_identity );
    }
};

class TranslationMatrix : public Matrix
{
public:
    TranslationMatrix ( f32 x, f32 y, f32 z )
    {
        f32 v [ 16 ] = { 1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         x, y, z, 1.0f };
        Matrix::operator= ( v );
    }
    
    TranslationMatrix ( f32* v )
    {
        *this = TranslationMatrix ( v[0], v[1], v[2] );
    }
};

class ScalingMatrix : public Matrix
{
public:
    ScalingMatrix ( f32 scale )
    {
        f32 v [ 16 ] = { scale, 0.0f, 0.0f, 0.0f,
                         0.0f, scale, 0.0f, 0.0f,
                         0.0f, 0.0f, scale, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f };
        Matrix::operator= ( v );
    }
    
    ScalingMatrix ( f32 x, f32 y, f32 z )
    {
        f32 v [ 16 ] = { x, 0.0f, 0.0f, 0.0f,
                         0.0f, y, 0.0f, 0.0f,
                         0.0f, 0.0f, z, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f };
        Matrix::operator= ( v );
    }
    
    ScalingMatrix ( f32* v )
    {
        Matrix::operator= ( ScalingMatrix ( v[0], v[1], v[2] ) );
    }
};


class RotationMatrix : public Matrix
{
public:
    RotationMatrix ( f32 angle, f32 x, f32 y, f32 z )
    {
        f32 v [ 16 ];
        f32 c = cos(angle);
        f32 s = sin(angle);
        f32 norm = sqrt(x*x+y*y+z*z);
        x /= norm;
        y /= norm;
        z /= norm;
        
        v[0] = x*x*(1-c)+c;   v[1] = y*x*(1-c)+z*s; v[2] = x*z*(1-c)-y*s; v[3] = 0;
        v[4] = x*y*(1-c)-z*s; v[5] = y*y*(1-c)+c;   v[6] = y*z*(1-c)+x*s; v[7] = 0;
        v[8] = x*z*(1-c)+y*s; v[9] = y*z*(1-c)-x*s; v[10] = z*z*(1-c)+c;  v[11] = 0;
        v[12] = 0;            v[13] = 0;            v[14] = 0;            v[15] = 1;
        
        Matrix::operator= ( v );
    }
    
    RotationMatrix ( f32 rotX, f32 rotY, f32 rotZ )
    {
        Matrix::operator= ( RotationMatrix ( rotZ, 0, 0, 1 ) * RotationMatrix ( rotY, 0, 1, 0 ) * RotationMatrix ( rotX, 1, 0, 0 ) );
    }
    
    RotationMatrix ( f32* v )
    {
        Matrix::operator= ( RotationMatrix ( v[0], v[1], v[2] ) );
    }
};

class OrthographicMatrix : public Matrix
{
public:
    OrthographicMatrix ( f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far )
    {
        const f32& l = left; const f32& r = right;
        const f32& t = top; const f32& b = bottom;
        const f32& n = near; const f32& f = far;
        f32 v [ 16 ] =
        {
            2.0f/(r-l), 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f/(t-b), 0.0f, 0.0f,
            0.0f, 0.0f, 2.0f/(n-f), 0.0f,
            -(r+l)/(r-l), -(t+b)/(t-b), -(n+f)/(n-f), 1.0f
        };
        
        Matrix::operator= ( v );
    }
};

#endif	/* MATRIX_H */

