from .module_a import module_a_func, module_var_a
from .module_b import Module_B, module_var_b

__all__ = ["module_a_func", "module_var_a", "Module_B", "module_var_b"]


def package_func():
    print("이것은 패키지에 정의된 함수입니다.")


print("테스트 패키지가 불러와 졌다!!")


def main():
    print(module_var_a)
    module_a_func()
    print(module_var_b)
    print(Module_B())
    print(module_var_a)
    package_func()


if __name__ == "__main__":
    main()