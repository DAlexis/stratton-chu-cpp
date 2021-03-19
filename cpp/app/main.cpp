#include "stratton-chu/plane-surface.hpp"
#include "stratton-chu/parallel-beam.hpp"
#include "stratton-chu/stratton-chu-field.hpp"

#include <iostream>

int main()
{
    std::cout << "Running stratton-chu computation" << std::endl;

    PlaneSurface surface(
        {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, 1.0, -1.0}
    );

    ParallelBeamZ beam(
        0.1,
        [](double x, double y) {
            return exp(-(sqr(x) + sqr(y)) / sqr(0.5));
        },
        [](double, double) { return 0.0; },
        0.0
    );

    SurfaceRegion region;

    StrattonChuReflection reflection(surface, beam, region);

    int n_points = 10;

    double z_from = -2.0;
    double z_to = 2.0;

    for (int i = 0; i < n_points; i++)
    {
        Position p(0.0, 2.05, z_from + (z_to - z_from) / (n_points-1) * i);
        FieldValue val = reflection.get(p);
        std::cout << "Point " << p.str() << ": " << val.E.str() << std::endl;
    }
    return 0;
}
