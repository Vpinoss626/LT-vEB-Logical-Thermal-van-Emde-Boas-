```cpp
/**
 * LT-vEB (Logical Thermal van Emde Boas) - Version 7.0 'Sentinel'
 * Auteur : Ibrahima Diallo (vpinoss)
 * 
 * "Que ce code serve de fondation à ceux qui veulent construire un monde meilleur."
 * 
 * Licence : MIT (voir fichier LICENSE)
 */

#ifndef LT_VEB_HPP
#define LT_VEB_HPP

#include <memory>
#include <map>
#include <cstdint>

struct LogicalEnv {
    uint64_t tau = 0;
    uint32_t decay_interval = 100;
    uint32_t node_count = 0;
    uint32_t max_nodes = 1000;

    void tick(uint32_t steps = 1) { tau += steps; }
};

class LTVebNode : public std::enable_shared_from_this<LTVebNode> {
private:
    uint32_t u;
    LogicalEnv* env;
    LTVebNode* parent;
    
    uint32_t min_val = 0;
    uint32_t max_val = 0;
    bool is_empty = true;

    uint32_t heat = 0;
    uint64_t last_tau = 0;

    uint32_t sqrt_u;
    std::shared_ptr<LTVebNode> summary = nullptr;
    std::map<uint32_t, std::shared_ptr<LTVebNode>> clusters;

    static uint32_t compute_sqrt(uint32_t u);
    void force_evict_cluster(uint32_t h);

public:
    LTVebNode(uint32_t universe, LogicalEnv* e, LTVebNode* p = nullptr);
    ~LTVebNode() = default;

    // Gestion thermique
    uint32_t get_current_heat() const;
    void update_heat();
    void access_path();

    // Opérations vEB
    void insert(uint32_t x);
    void delete_val(uint32_t x);
    bool contains(uint32_t x);

    // Élagage et gestion mémoire
    void prune_adaptive(uint32_t aggressiveness);
    void destroy_subtree();
    void ensure_capacity(uint32_t needed);

    // Utilitaires
    uint32_t get_node_count() const { return env->node_count; }
};

#endif // LT_VEB_HPP
```
