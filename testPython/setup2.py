# python3 setup.py build
# python3 setup.py install
#sudo python3 setup2.py bdist_wheel
# pip install dist/test_package-0.1.0-py3-none-any.whl
# test_package_main이란 이름으로 생성
# pip uninstall test_package

from setuptools import Extension, setup

setup(name = 'test_package',
    version = '0.1.0', 
    description = 'A test package',
    packages=['test_package'],
    entry_points={
        'console_scripts': ["test_package_main = test_package:main"]},
    include_package_data=True,
    zip_safe=False,

    )


# UV


