import math


class Shape:
    def calculate_area(self):
        pass


class Circle(Shape):
    def __init__(self, radius):
        self.radius = radius

    def calculate_area(self):
        return math.pi * self.radius * self.radius


class Rectangle(Shape):
    def __init__(self, length, width):
        self.length = length
        self.width = width

    def calculate_area(self):
        return self.length * self.width


circle = Circle(5)
print("Area of circle:", circle.calculate_area())

rectangle = Rectangle(3, 4)
print("Area of rectangle:", rectangle.calculate_area())