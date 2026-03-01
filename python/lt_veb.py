```python
import ctypes
import os

class LTVebSentinel:
    def __init__(self, universe_size, max_nodes=1000, decay=100):
        # Charger la bibliothèque partagée
        lib_path = os.path.join(os.path.dirname(__file__), 'libltveb.so')
        self.lib = ctypes.CDLL(lib_path)
        
        self.lib.lt_env_create.restype = ctypes.c_void_p
        self.lib.lt_veb_create.restype = ctypes.c_void_p
        self.lib.lt_veb_contains.restype = ctypes.c_int32
        self.lib.lt_veb_insert.restype = ctypes.c_int32
        self.lib.lt_veb_get_node_count.restype = ctypes.c_uint32

        self.env = self.lib.lt_env_create(decay, max_nodes)
        self.handle = self.lib.lt_veb_create(universe_size, self.env)

    def insert(self, x):
        res = self.lib.lt_veb_insert(self.handle, x)
        if res == -1:
            raise MemoryError("LT-vEB Sentinel : Capacité mémoire épuisée.")

    def delete(self, x):
        self.lib.lt_veb_delete(self.handle, x)

    def contains(self, x):
        return bool(self.lib.lt_veb_contains(self.handle, x))

    def tick(self, steps=1):
        self.lib.lt_env_tick(self.env, steps)

    def node_count(self):
        return self.lib.lt_veb_get_node_count(self.handle)

    def prune(self, aggressiveness=1):
        self.lib.lt_veb_prune(self.handle, aggressiveness)

    def __del__(self):
        if hasattr(self, 'handle'):
            self.lib.lt_veb_destroy(self.handle)
        if hasattr(self, 'env'):
            self.lib.lt_env_destroy(self.env)
```
