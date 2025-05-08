# python3 setup.py build
# python3 setup.py install


from setuptools import Extension, setup
# c에서의 cmake 대용으로 python에서는 setuptools를 쓴다. poetry를 쓰기도 했지만 요즘은 UV를 더 많이 쓴다
module = Extension("mymodule", sources=['mymodule.c'])

setup(name = 'mymodule',
    version = '1.0', ext_modules=[module],
    packages=['mymodule'],
    ext_modules=[Extension('mymodule', ['mymodule/mymodule.c'])],
    package_data={'mymodule': ['*.pyi', 'py.typed']},
    include_package_data=True,
    zip_safe=False,
      
      
      
    )


# UV


