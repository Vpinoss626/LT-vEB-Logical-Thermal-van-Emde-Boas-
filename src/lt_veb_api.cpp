```cpp
/**
 * LT-vEB (Logical Thermal van Emde Boas) - Version 7.0 'Sentinel'
 * Auteur : Ibrahima Diallo (vpinoss)
 * 
 * Interface C pour l'intégration avec d'autres langages.
 * 
 * Licence : MIT (voir fichier LICENSE)
 */

#include "lt_veb.hpp"
#include <cstdint>

extern "C" {

    // Structure opaque pour le contexte utilisateur
    typedef void* LTVebHandle;
    typedef void* LTEnvHandle;

    LTEnvHandle lt_env_create(uint32_t decay_interval, uint32_t max_nodes) {
        return reinterpret_cast<LTEnvHandle>(new LogicalEnv{0, decay_interval, 0, max_nodes});
    }

    void lt_env_destroy(LTEnvHandle env) {
        delete reinterpret_cast<LogicalEnv*>(env);
    }

    void lt_env_tick(LTEnvHandle env, uint32_t steps) {
        reinterpret_cast<LogicalEnv*>(env)->tick(steps);
    }

    LTVebHandle lt_veb_create(uint32_t universe_size, LTEnvHandle env) {
        auto logical_env = reinterpret_cast<LogicalEnv*>(env);
        auto node = new std::shared_ptr<LTVebNode>(std::make_shared<LTVebNode>(universe_size, logical_env));
        return reinterpret_cast<LTVebHandle>(node);
    }

    void lt_veb_destroy(LTVebHandle handle) {
        auto node_ptr = reinterpret_cast<std::shared_ptr<LTVebNode>*>(handle);
        (*node_ptr)->destroy_subtree();
        delete node_ptr;
    }

    int32_t lt_veb_insert(LTVebHandle handle, uint32_t x) {
        auto node = *reinterpret_cast<std::shared_ptr<LTVebNode>*>(handle);
        try {
            node->insert(x);
            return 0;
        } catch (...) {
            return -1;
        }
    }

    void lt_veb_delete(LTVebHandle handle, uint32_t x) {
        auto node = *reinterpret_cast<std::shared_ptr<LTVebNode>*>(handle);
        node->delete_val(x);
    }

    int32_t lt_veb_contains(LTVebHandle handle, uint32_t x) {
        auto node = *reinterpret_cast<std::shared_ptr<LTVebNode>*>(handle);
        return node->contains(x) ? 1 : 0;
    }

    uint32_t lt_veb_get_node_count(LTVebHandle handle) {
        auto node = *reinterpret_cast<std::shared_ptr<LTVebNode>*>(handle);
        return node->get_node_count();
    }

    void lt_veb_prune(LTVebHandle handle, uint32_t aggressiveness) {
        auto node = *reinterpret_cast<std::shared_ptr<LTVebNode>*>(handle);
        node->prune_adaptive(aggressiveness);
    }
}
```

