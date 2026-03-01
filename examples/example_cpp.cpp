```cpp
#include "lt_veb.hpp"
#include <iostream>

int main() {
    LogicalEnv env;
    env.max_nodes = 500;
    auto root = std::make_shared<LTVebNode>(65536, &env);

    root->insert(42);
    root->insert(100);

    std::cout << "Contient 42 ? " << root->contains(42) << std::endl;
    std::cout << "Contient 999 ? " << root->contains(999) << std::endl;

    // Simuler une pression mémoire
    for (int i = 0; i < 1000; ++i) {
        try {
            root->insert(2000 + i);
        } catch (...) {
            std::cout << "Mémoire saturée après " << i << " insertions." << std::endl;
            break;
        }
    }

    std::cout << "Nœuds finaux : " << root->get_node_count() << std::endl;
    return 0;
}
```
