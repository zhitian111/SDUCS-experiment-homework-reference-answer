#include <iostream>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>

using namespace Eigen;
using namespace std;

double vec2_cross(Vector2f a, Vector2f b)
{
    return a.x() * b.y() - a.y() * b.x();
}

bool is_in_line_segment(Vector2f A, Vector2f B, Vector2f P)
{
    double k = (B.y() - A.y()) / (B.x() - A.x());
    double b = A.y() - k * A.x();
    double x = (P.y() - b) / k;
    double y = k * x + b;
    if (x >= 0 && x <= 1 && y >= 0 && y <= 1)
    {
        return true;
    }
    return false;
}

bool is_in_straightness(Vector2f A, Vector2f B, Vector2f P)
{
    double k = (B.y() - A.y()) / (B.x() - A.x());
    double b = A.y() - k * A.x();
    double y = k * P.x() + b;
    if (y == P.y())
    {
        return true;
    }
    return false;
}

bool is_in_ray(Vector2f A, Vector2f B, Vector2f P)
{
    double k = (B.y() - A.y()) / (B.x() - A.x());
    double b = A.y() - k * A.x();
    double y = k * P.x() + b;
    if (y == P.y())
    {
        if ((P.x() >= A.x() && P.x() <= B.x()) || (P.x() <= A.x() && P.x() >= B.x()))
        {            
            return true;
        }
    }
    return false;
}
bool is_crossed(Vector2f A, Vector2f B, Vector2f P, Vector2f p0)
{
    if (vec2_cross(p0, B - A) == 0.0)
    {
        double k = (B.y() - A.y()) / (B.x() - A.x());
        double b = A.y() - k * A.x();
        double x = (P.y() - b) / k;
        double y = k * x + b;
        if (x >= 0 && x <= 1 && y >= 0 && y <= 1)
        {
            return true;
        }
        return false;
    }
    double tem1 = vec2_cross(A - P, B - A);
    double tem2 = vec2_cross(p0, B - A);
    double tem3 = vec2_cross(A - P, p0);
    double t = tem1 / tem2;
    double s = tem3 / tem2;
    if (t >= 0 && s >= 0)
    {
        return true;
    }
    return false;
}

int rectangle_cross(Vector2f A, Vector2f B, Vector2f C, Vector2f P, Vector2f p0)
{
    int cnt = 0;
    if (is_crossed(A, B, P, p0))
    {
        cnt++;
    }
    if (is_crossed(B, C, P, p0))
    {
        cnt++;
    }
    if (is_crossed(C, A, P, p0))
    {
        cnt++;
    }
    return cnt;
}

bool is_inside_rectangle(Vector2f A, Vector2f B, Vector2f C, Vector2f P)
{
    Vector2f p0(1.0f, 0.0f);
    Vector2f p1(-1.0f, 0.0f);
    Vector2f p2(0.0f, 1.0f);
    Vector2f p3(0.0f, -1.0f);
    if (rectangle_cross(A, B, C, P, p0) == 1 || rectangle_cross(A, B, C, P, p1) == 1 || rectangle_cross(A, B, C, P, p2) == 1 || rectangle_cross(A, B, C, P, p3) == 1)
    {
        return true;
    }
    return false;
}

double Helen_formula(Vector2f A, Vector2f B, Vector2f C)
{
    double a = (A - B).norm();
    double b = (B - C).norm();
    double c = (C - A).norm();
    double s = (a + b + c) / 2.0;
    double area = sqrt(s * (s - a) * (s - b) * (s - c));
    return area;
}

bool is_inside_rectangle_with_Helen_formula(Vector2f A, Vector2f B, Vector2f C, Vector2f P)
{
    double area = Helen_formula(A, B, C);
    double area1 = Helen_formula(A, B, P);
    double area2 = Helen_formula(A, P, C);
    double area3 = Helen_formula(B, P, C);
    if (area1 + area2 + area3 - area >= -0.00001 && area1 + area2 + area3 - area <= 0.00001)
    {
        return true;
    }
    return false;
}

bool is_inside_triangle_with_noname_method(Vector2f A, Vector2f B, Vector2f C, Vector2f P)
{
    Vector2f AB = B - A;
    Vector2f AC = C - A;
    Vector2f AP = P - A;
    double u = (AB.dot(AB) * AP.dot(AC) - (AC.dot(AB) * AP.dot(AB))) / (AC.dot(AC) * AB.dot(AB) - AB.dot(AC) * AC.dot(AB));
    double v = (AC.dot(AC) * AP.dot(AB) - (AB.dot(AC) * AP.dot(AC))) / (AB.dot(AB) * AC.dot(AC) - AC.dot(AB) * AB.dot(AC));
    if (u >= 0 && v >= 0 && u + v <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    Vector2f A(0.0f, 0.0f), B(1.0f, 0.0f), C(0.0f, 1.0f);
    Vector2f P(1.0f, 1.0f);
    if (is_inside_rectangle(A, B, C, P))
    {
        cout << "inside" << endl;
    }
    else
    {
        cout << "outside" << endl;
    }

    if (is_inside_rectangle_with_Helen_formula(A, B, C, P))
    {
        cout << "inside" << endl;
    }
    else
    {
        cout << "outside" << endl;
    }
    if (is_inside_triangle_with_noname_method(A, B, C, P))
    {
        cout << "inside" << endl;
    }
    else
    {
        cout << "outside" << endl;
    }
}