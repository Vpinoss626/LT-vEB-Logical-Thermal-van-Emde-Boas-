```python
import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'python')))

import lt_veb
import unittest

class TestLTVeb(unittest.TestCase):
    def setUp(self):
        self.veb = lt_veb.LTVebSentinel(65536, max_nodes=200)

    def test_insert_contains(self):
        self.veb.insert(42)
        self.assertTrue(self.veb.contains(42))
        self.assertFalse(self.veb.contains(999))

    def test_delete(self):
        self.veb.insert(100)
        self.veb.delete(100)
        self.assertFalse(self.veb.contains(100))

    def test_memory_limit(self):
        for i in range(500):
            try:
                self.veb.insert(1000 + i)
            except MemoryError:
                pass
        self.assertLessEqual(self.veb.node_count(), 200)

if __name__ == '__main__':
    unittest.main()
```
