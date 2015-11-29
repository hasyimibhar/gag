#include <cmath>

#ifndef _VECTOR2D_H
#define _VECTOR2D_H

/**********************************************/

struct Vec
{
	float x, y;

	Vec& operator +=(const Vec &v) {x += v.x; y += v.y; return *this;};
	Vec& operator -=(const Vec &v) {x -= v.x; y -= v.y; return *this;};
	Vec& operator *=(float k) {x *= k; y *= k; return *this;};

	Vec& operator=(const Vec &v2)
	{
		x = v2.x; y = v2.y; return *this;
	};

	float length() const {return std::sqrt(x * x + y * y);};
	float lengthSquared() const {return x * x + y * y;};
	void normalize() {float l = length(); if (l){x /= l; y /= l;}};
	Vec normalized() {float l = length(); return l ? Vec(x / l, y / l) : Vec();}
	bool isZero() const {return x == 0 && y == 0;};
	bool isNonZero() const {return x != 0 || y != 0;};
	Vec rightNormal() const {return Vec(-y, x);};
	Vec leftNormal() const {return Vec(y, -x);};

	Vec() : x(0.0), y(0.0){};
	Vec(float x, float y) : x(x), y(y) {};
};

/**********************************************/

inline Vec operator+(const Vec &v1, const Vec &v2)
{
	return Vec(v1.x + v2.x, v1.y + v2.y);
}

inline Vec operator-(const Vec &v1, const Vec &v2)
{
	return Vec(v1.x - v2.x, v1.y - v2.y);
}


inline bool operator==(const Vec &v1, const Vec &v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

inline bool operator!=(const Vec &v1, const Vec &v2)
{
	return (v1.x != v2.x || v1.y != v2.y);
}

inline Vec operator*(float k, const Vec &v)
{
	return Vec(v.x * k, v.y * k);
}

inline Vec operator*(const Vec &v, float k)
{
	return Vec(v.x * k, v.y * k);
}

inline Vec operator/(const Vec &v, float k)
{
	return Vec(v.x / k, v.y / k);
}

inline float dot(const Vec &v1, const Vec &v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

inline float cross(const Vec &v1, const Vec &v2)
{
	return v1.x * v2.y - v1.y * v2.x;
}

inline Vec normalize(const Vec &v)
{
	return v / v.length();
}

inline bool perpendicular(const Vec &v1, const Vec &v2)
{
	return dot(v1, v2) == 0;
}

inline bool parallel(const Vec &v1, const Vec &v2)
{
	if (v1.isZero())
		return true;
	return (v1.x / v2.x == v1.y / v2.y);
}

struct Rect
{
   private:
      Vec topleft, bottomright;

   public:
      Rect(float left, float top, float right, float bottom) : topleft(left,top), bottomright(right,bottom) {}
      Vec tl() { return topleft; }
      Vec br() { return bottomright; }
      float left() { return topleft.x; }
      float right() { return bottomright.x; }
      float top() { return topleft.y; }
      float bottom() { return bottomright.y; }

      Vec leftCenter() { return Vec(topleft.x, (topleft.y + bottomright.y) * 0.5); }
      Vec rightCenter() { return Vec(bottomright.x, (topleft.y + bottomright.y) * 0.5); }
      Vec topCenter() { return Vec((topleft.x + bottomright.x) * 0.5, topleft.y); }
      Vec bottomCenter() { return Vec((topleft.x + bottomright.x) * 0.5, bottomright.y); }

      Vec dimensions() { return Vec(width(), height()); }
      float width() { return bottomright.x - topleft.x; }
      float height() { return bottomright.y - topleft.y; }

      bool contains(Vec p) { return (p.x >= topleft.x) && (p.x < bottomright.x) && (p.y >= topleft.y) && (p.y < bottomright.y); }
      void move(Vec p) { topleft += p; bottomright += p; }

      bool collide(Rect r)
      {
         if (r.left() > right()) return false;
         if (r.right() < left()) return false;
         if (r.top() > bottom()) return false;
         if (r.bottom() < top()) return false;
         return true;
      }
};

#endif
