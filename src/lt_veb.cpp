```cpp
/**
 * LT-vEB (Logical Thermal van Emde Boas) - Version 7.0 'Sentinel'
 * Auteur : Ibrahima Diallo (vpinoss)
 * 
 * "Que ce code serve de fondation à ceux qui veulent construire un monde meilleur."
 * 
 * Licence : MIT (voir fichier LICENSE)
 */

#include "lt_veb.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>

// --- Méthodes statiques ---
uint32_t LTVebNode::compute_sqrt(uint32_t u) {
    if (u <= 2) return 0;
    return static_cast<uint32_t>(std::pow(2, std::ceil(std::log2(u) / 2.0)));
}

// --- Constructeur ---
LTVebNode::LTVebNode(uint32_t universe, LogicalEnv* e, LTVebNode* p)
    : u(universe), env(e), parent(p), last_tau(e->tau) {
    env->node_count++;
    sqrt_u = (u > 2) ? compute_sqrt(u) : 0;
}

// --- Gestion thermique ---
uint32_t LTVebNode::get_current_heat() const {
    uint64_t delta_tau = env->tau - last_tau;
    uint32_t shifts = static_cast<uint32_t>(delta_tau / env->decay_interval);
    if (shifts >= 31) return 0;
    return (shifts > 0) ? (heat >> shifts) : heat;
}

void LTVebNode::update_heat() {
    heat = get_current_heat();
    last_tau = env->tau;
}

void LTVebNode::access_path() {
    LTVebNode* curr = this;
    while (curr) {
        curr->update_heat();
        curr->heat += 1;
        curr = curr->parent;
    }
}

// --- Destruction récursive ---
void LTVebNode::destroy_subtree() {
    for (auto& pair : clusters) {
        pair.second->parent = nullptr;
        pair.second->destroy_subtree();
    }
    clusters.clear();
    if (summary) {
        summary->parent = nullptr;
        summary->destroy_subtree();
        summary = nullptr;
    }
    env->node_count--;
}

// --- Élagage adaptatif ---
void LTVebNode::prune_adaptive(uint32_t aggressiveness) {
    if (u <= 2 || clusters.empty()) return;

    std::vector<uint32_t> heats;
    for (auto const& [h, cluster] : clusters) {
        heats.push_back(cluster->get_current_heat());
    }

    uint32_t idx = std::min((uint32_t)heats.size() - 1, aggressiveness);
    std::nth_element(heats.begin(), heats.begin() + idx, heats.end());
    uint32_t threshold = std::max(1u, heats[idx]);

    std::vector<uint32_t> to_prune;
    for (auto& [h, cluster] : clusters) {
        if (cluster->get_current_heat() <= threshold) {
            to_prune.push_back(h);
        } else {
            cluster->prune_adaptive(aggressiveness);
        }
    }

    for (uint32_t h : to_prune) {
        force_evict_cluster(h);
    }
}

void LTVebNode::force_evict_cluster(uint32_t h) {
    auto it = clusters.find(h);
    if (it == clusters.end()) return;

    bool is_min_h = (!is_empty && (min_val / sqrt_u == h) && u > 2);
    bool is_max_h = (!is_empty && (max_val / sqrt_u == h) && u > 2);

    it->second->destroy_subtree();
    clusters.erase(it);

    if (summary) {
        summary->delete_val(h);
        if (summary->is_empty) {
            summary->destroy_subtree();
            summary = nullptr;
        }
    }

    // Recalcul des métadonnées min/max après éviction
    if (is_min_h) {
        if (summary && !summary->is_empty) {
            uint32_t next_h = summary->min_val;
            min_val = next_h * sqrt_u + clusters[next_h]->min_val;
        } else {
            min_val = max_val;
        }
    }
    if (is_max_h) {
        if (summary && !summary->is_empty) {
            uint32_t prev_h = summary->max_val;
            max_val = prev_h * sqrt_u + clusters[prev_h]->max_val;
        } else {
            max_val = min_val;
        }
    }
    if (min_val == max_val && clusters.empty() && !summary) {
        is_empty = true;
    }
}

// --- Garantie de capacité ---
void LTVebNode::ensure_capacity(uint32_t needed) {
    LTVebNode* root = this;
    while (root->parent) root = root->parent;

    uint32_t aggressiveness = 1;
    while (env->node_count + needed > env->max_nodes) {
        uint32_t before = env->node_count;
        root->prune_adaptive(aggressiveness);
        if (env->node_count == before) aggressiveness += 2;
        if (aggressiveness > 25) throw std::runtime_error("Limite memoire atteinte : Elagage impossible.");
    }
}

// --- Insertion ---
void LTVebNode::insert(uint32_t x) {
    access_path();

    if (is_empty) {
        min_val = max_val = x;
        is_empty = false;
        return;
    }

    if (x == min_val || x == max_val) return;

    if (x < min_val) std::swap(x, min_val);

    if (u > 2) {
        uint32_t h = x / sqrt_u;
        uint32_t l = x % sqrt_u;

        if (clusters.find(h) == clusters.end()) {
            ensure_capacity(2); // Cluster + Summary potentiel
            clusters[h] = std::make_shared<LTVebNode>(sqrt_u, env, this);
            if (!summary) summary = std::make_shared<LTVebNode>(sqrt_u, env, this);
            summary->insert(h);
        }
        clusters[h]->insert(l);
    }

    if (x > max_val) max_val = x;
}

// --- Suppression ---
void LTVebNode::delete_val(uint32_t x) {
    access_path();
    if (is_empty) return;

    if (min_val == max_val) {
        if (x == min_val) is_empty = true;
        return;
    }

    if (u == 2) {
        if (x == 0) min_val = 1;
        else min_val = 0;
        max_val = min_val;
        return;
    }

    if (x == min_val) {
        uint32_t first_h = summary->min_val;
        x = first_h * sqrt_u + clusters[first_h]->min_val;
        min_val = x;
    }

    uint32_t h = x / sqrt_u;
    uint32_t l = x % sqrt_u;

    if (clusters.count(h)) {
        clusters[h]->delete_val(l);
        if (clusters[h]->is_empty) {
            force_evict_cluster(h);
        } else if (x == max_val) {
            max_val = h * sqrt_u + clusters[h]->max_val;
        }
    }
}

// --- Recherche ---
bool LTVebNode::contains(uint32_t x) {
    access_path();
    if (is_empty) return false;
    if (x == min_val || x == max_val) return true;
    if (u <= 2) return false;

    uint32_t h = x / sqrt_u;
    uint32_t l = x % sqrt_u;
    if (clusters.find(h) == clusters.end()) return false;
    return clusters[h]->contains(l);
}
```
