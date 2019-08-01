#ifndef SFMATH_H
#define SFMATH_H

/**
 * A Vector representation somewhat in the style of the IBM/Sony Vectormath library.
 */
class Vector2 {
public:
    inline Vector2(const float x, const float y) : x(x), y(y) {}
    inline Vector2(const Vector2& v) : x(v.x), y(v.y) {}
    inline const float getX() const { return x; }
    inline const float getY() const { return y; }

    inline const Vector2 operator +(const Vector2& vec) const { return Vector2(x + vec.x, y + vec.y); }
    inline const Vector2 operator *(float scalar) const { return Vector2(x * scalar, y * scalar); }

private:
    float x, y;
};

/**
 * A Point representation somewhat in the style of the IBM/Sony Vectormath library.
 */
class Point2 {
public:
    inline Point2(const float x, const float y) : x(x), y(y) {}
    inline Point2(const Vector2& v) : x(v.getX()), y(v.getY()) {}
    inline Point2(const Point2& p) : x(p.x), y(p.y) {}
    inline const float getX() const { return x; }
    inline const float getY() const { return y; }
private:
    float x, y;
};

#endif
