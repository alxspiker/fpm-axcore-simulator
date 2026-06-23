#include <iostream>
#include "src/fpm_axcore_simulator.cpp"
int main() {
    Axioms ax;
    DerivedConstants d = derive_all(ax);
    Z3Lattice lattice(10, 4, 4, d, 1337);
    ThermodynamicScheduler sched(lattice, d);
    Daemon& dm = lattice.arena[0];
    dm.E = d.E_max;
    dm.R[0][0] += 5.0;
    dm.tau = 1.0;
    double Oi, ki, C_Ni;
    viscosity_update(dm, d, 0.0, Oi, ki, C_Ni);
    double C_sem, C_geo, sm;
    double L_out = axcore_lagrangian(dm, d, Oi, sched.cfg, C_sem, C_geo, sm);
    std::cout << "L_out for x=5: " << L_out << std::endl;
    return 0;
}
