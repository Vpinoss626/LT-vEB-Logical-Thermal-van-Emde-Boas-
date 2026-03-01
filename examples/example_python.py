```python
import lt_veb

veb = lt_veb.LTVebSentinel(65536, max_nodes=200)

veb.insert(42)
print("Présence de 42 :", veb.contains(42))
print("Nombre de nœuds :", veb.node_count())

# Stress test
for i in range(500):
    try:
        veb.insert(1000 + i)
    except MemoryError:
        pass

print("Après stress, nœuds :", veb.node_count())
```
