```python
from setuptools import setup, Extension
import os

module = Extension('ltveb',
                   sources=['src/lt_veb_api.cpp'],
                   extra_compile_args=['-O3'],
                   include_dirs=['include'])

setup(name='ltveb',
      version='1.0.0',
      description='LT-vEB Sentinel Algorithm',
      author='Ibrahima Diallo (vpinoss)',
      author_email='vpinoss@example.com',
      url='https://github.com/vpinoss/LT-vEB',
      ext_modules=[module],
      py_modules=['lt_veb'],
      package_dir={'': 'python'},
      license='MIT')
```
