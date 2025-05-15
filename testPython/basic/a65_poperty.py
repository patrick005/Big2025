import math
class Circle:
    def __init__(self, radius):
        self._radius = radius

    def get_area(self):
        return math.pi*self._radius**2
    
def main():
    circle = Circle(10)
    print(circle.get_area())


if __name__ == "__main__":
    main()