#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP
//#include <cstddef> //size_t
//#include <typeinfo>
#include <iostream>
#include <cmath>



///---DECLARATION---///
namespace mym
{
    ///Main Vec Class
    template<const unsigned int _D, typename _T>
    class Vec
    {
    public:
        Vec();
        virtual ~Vec();

        virtual _T& operator[](const unsigned int index) = 0;

        template<const unsigned int _I, typename _U>
        friend std::ostream& operator<<(std::ostream& os, Vec<_I, _U> vec);

    protected:
        _T data[_D];

    };

    ///Vec2 Class
    template<typename _T>
    class Vec2 : public Vec<2, _T>
    {
    public:
        Vec2() = default;
        Vec2(_T _x, _T _y = 0);

        virtual _T& operator[](const unsigned int index) override;

        template<typename _U>
        constexpr _T operator*(const Vec2<_U>& v) const noexcept;

    public:
        _T x, y;
    };

    ///Vec3 Class
    template<typename _T>
    class Vec3 : public Vec<3, _T>
    {
    public:
        Vec3() = default;
        Vec3(_T _x, _T _y = 0, _T _z = 0);

        virtual _T& operator[](const unsigned int index) override;
        constexpr _T operator*(const Vec3<_T>& v) const noexcept;

    public:
        _T x, y, z;
    };

    ///Vec2 Class
    template<typename _T>
    class Vec4 : public Vec<4, _T>
    {
    public:
        Vec4() = default;
        Vec4(_T _x, _T _y = 0, _T _z = 0, _T _w = 0);

        virtual _T& operator[](const unsigned int index) override;
        constexpr _T operator*(const Vec4<_T>& v) const noexcept;

    public:
        _T x, y, z, w;
    };


}


///---IMPLEMENTATION---///
namespace mym
{
    template<const unsigned int _D, typename _T>
    Vec<_D, _T>::Vec()
    {
        for(unsigned int i = 0; i < _D; i++)
            this->data[i] = static_cast<_T>(0);
    }

    template<const unsigned int _D, typename _T>
    Vec<_D, _T>::~Vec()
    {
        //dtor
    }

    template<const unsigned int _D, typename _T>
    std::ostream& operator<<(std::ostream& os, Vec<_D, _T> vec)
    {
        for(unsigned int i = 0; i < _D; i++)
        {
            os << vec[i];
            if(i != _D-1)
                os<< ", ";
        }
        return os;
    }



    ///VEC2
    template<typename _T>
    Vec2<_T>::Vec2(_T _x, _T _y):
            x(_x), y(_y)
    { }

    template<typename _T>
    _T& Vec2<_T>::operator[](const unsigned int index)
    {
        this->data[0] = x;
        this->data[1] = y;
        return this->data[index];
    }

    template<typename _T> template<typename _U>
    constexpr _T Vec2<_T>::operator*(const Vec2<_U>& v) const noexcept
    {
        return this->x * v.x + this->y * v.y;
    }

    ///VEC3
    template<typename _T>
    Vec3<_T>::Vec3(_T _x, _T _y, _T _z):
            x(_x), y(_y), z(_z)
    { }

    template<typename _T>
    _T& Vec3<_T>::operator[](const unsigned int index)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
        return this->data[index];
    }

    template<typename _T>
    constexpr _T Vec3<_T>::operator*(const Vec3<_T>& v) const noexcept
    {
        return this->x * v.x + this->y * v.y + this->z * v.z;
    }

    ///VEC4
    template<typename _T>
    Vec4<_T>::Vec4(_T _x, _T _y, _T _z, _T _w):
            x(_x), y(_y), z(_z), w(_w)
    { }

    template<typename _T>
    _T& Vec4<_T>::operator[](const unsigned int index)
    {
        this->data[0] = x;
        this->data[1] = y;
        this->data[2] = z;
        this->data[3] = w;
        return this->data[index];
    }

    template<typename _T>
    constexpr _T Vec4<_T>::operator*(const Vec4<_T>& v) const noexcept
    {
        return this->x * v.x + this->y * v.y + this->z * v.z + this->w * v.w;
    }





typedef Vec2<int>           Vec2i;
typedef Vec2<unsigned int>  Vec2ui;
typedef Vec2<double>        Vec2d;
typedef Vec2<float>         Vec2f;

typedef Vec3<int>           Vec3i;
typedef Vec3<unsigned int>  Vec3ui;
typedef Vec3<double>        Vec3d;
typedef Vec3<float>         Vec3f;

typedef Vec4<int>           Vec4i;
typedef Vec4<unsigned int>  Vec4ui;
typedef Vec4<double>        Vec4d;
typedef Vec4<float>         Vec4f;


}


///RANDOM_GENERATOR_64:

namespace mym
{
    ///Clasic Simple PRNG64
    //LINK --> https://stackoverflow.com/questions/4720822/best-pseudo-random-number-generator.
    typedef struct _RandomGenerator64
    {
    private:
        static inline unsigned long long rng_a, rng_b, rng_c, rng_counter;
    public:
        static unsigned long long nextRandom()
        {
            unsigned long long tmp = _RandomGenerator64::rng_a + _RandomGenerator64::rng_b + _RandomGenerator64::rng_counter++;
            _RandomGenerator64::rng_a = _RandomGenerator64::rng_b ^ (_RandomGenerator64::rng_b >> 12);
            _RandomGenerator64::rng_b = _RandomGenerator64::rng_c + (_RandomGenerator64::rng_c << 3);
            _RandomGenerator64::rng_c = ((_RandomGenerator64::rng_c << 25) | (_RandomGenerator64::rng_c >> (64-25))) + tmp;
            return tmp;
        }

        static void seed(unsigned long long s)
        {
            _RandomGenerator64::rng_a = _RandomGenerator64::rng_b = _RandomGenerator64::rng_c = s;
            _RandomGenerator64::rng_counter = 1;
            for (int i = 0; i < 12; i++) nextRandom();
        }

    }RandomGenerator64;


    static float choose(float a, float b)
    {
        return RandomGenerator64::nextRandom()%10 < 5 ? a : b;
    }
    //LINK --> https://stackoverflow.com/questions/4720822/best-pseudo-random-number-generator.

}


namespace mym
{
    template<typename _T>
    static _T distance(_T x1, _T y1, _T x2, _T y2)
    {
        return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
    }

    ///Linear Interpolation
    static double lerp(double a, double b, double t)
    {
        return b + t*(a - b);
    }

    static double lerp3(double a, double b, double t)
    {
        return (b - a) * (3.0 - t * 2.0) * t * t + a;
    }

    template<typename _T>
    static _T LinearInterpolation(_T x1, _T y1, _T x2, _T y2, _T yourX)
    {
        _T m = (y2 - y1)/(x2 - x1);
        return y1 + m * (yourX - x1);
    }

    template<typename _T>
    static _T LinearInterpolation(Vec2<_T> v1, Vec2<_T> v2, _T yourX)
    {
        _T m = (v2.y - v1.y)/(v2.x - v1.x);
        return v1.y + m * (yourX - v1.x);
    }

    template<typename _T>
    static _T sigmoid(_T x)
    {
        return 1 / (1 + exp(-x));
    }

    template<typename _T>
    static _T sigmoidDerivative(_T x)
    {
        return sigmoid(x) * (1 - sigmoid(x));
    }

    //LINK --> https://en.wikipedia.org/wiki/Fast_inverse_square_root
    float Q_rsqrt(float number)
    {
        long i;
        float x2, y;
        const float threehalfs = 1.5F;

        x2 = number * 0.5F;
        y = number;
        i = *(long*)&y;                       // evil floating point bit level hacking
        i = 0x5f3759df - (i >> 1);               // what the fuck? 
        y = *(float*)&i;
        y = y * (threehalfs - (x2 * y * y));   // 1st iteration
    //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

        return y;
    }
    //LINK --> https://en.wikipedia.org/wiki/Fast_inverse_square_root
}


namespace mym
{
    //LINK --> https://en.wikipedia.org/wiki/Perlin_noise
    static Vec2d randomGradient(int ix, int iy) {
        // Random float. No precomputed gradients mean this works for any number of grid coordinates
        double random = 2567.f * sin(ix * 27942.f + iy * 179324.f + 8914.f) * cos(ix * 23157.f * iy * 217832.f + 9758.f);
        Vec2d a;
        a.x = cos(random);
        a.y = sin(random);
        //std::cout << a.x << std::endl;
        return a;
    }

    
    static double perlinNoise2D(double x, double y)
    {
        //RandomGenerator64::seed(RandomGenerator64::nextRandom()%1000000);             
        //std::cout<<RandomGenerator64::nextRandom()%10000<<std::endl;
        ///Gradient Vector:
        int g_x1 = (int)x;
        int g_x2 = g_x1 + 1;
        int g_y1 = (int)y;
        int g_y2 = g_y1 + 1;
        ///Distance Vector:
        double d_x1 = x - (double)g_x1;
        double d_y1 = y - (double)g_y1;
        double d_x2 = x - (double)g_x2;
        double d_y2 = y - (double)g_y2;
        

        double sx = x - (double)g_x1;
        double sy = y - (double)g_y1;

        Vec2d gradient1 = randomGradient(g_x1, g_y1);
        Vec2d gradient2 = randomGradient(g_x1, g_y2);
        Vec2d gradient3 = randomGradient(g_x2, g_y1);
        Vec2d gradient4 = randomGradient(g_x2, g_y2);

        
        double left_up_value = gradient1 * Vec2d(d_x1, d_y1);
        double left_down_value = gradient2 * Vec2d(d_x1, d_y2);
        double left = lerp3(left_up_value, left_down_value, sy);

        double right_up_value = gradient3 * Vec2d(d_x2, d_y1);
        double right_down_value = gradient4 * Vec2d(d_x2, d_y2);
        double right = lerp3(right_up_value, right_down_value, sy);

        double value = lerp3(left, right, sx);

        return value;

    }
    //LINK --> https://en.wikipedia.org/wiki/Perlin_noise

}








#endif // PERLIN_NOISE_HPP
