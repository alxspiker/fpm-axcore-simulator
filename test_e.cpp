#include <iostream>
#include "src/fpm_axcore_simulator.cpp"
int main() {
    Axioms ax;
    DerivedConstants d = derive_all(ax);
    Z3Lattice lattice(100, 4, 4, d, 1337);
    int cnt = 0;
    for (int i=0; i<1600; i++) if (lattice.arena[i].E > 0.51) cnt++;
    std::cout << "Nodes with E > 0.51: " << cnt << std::endl;
    return 0;
}
