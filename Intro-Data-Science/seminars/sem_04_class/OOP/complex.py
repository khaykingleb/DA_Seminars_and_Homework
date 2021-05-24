class ComplexError(BaseException):
    def __init__(self, complex, other):
        self.first = complex
        self.second = other


class Complex:
    def __init__(self, re=0, im=0):
        self.re = re
        self.im = im

    def __str__(self):
        str_comp = str(self.re)
        if self.im > 0:
            str_comp += "+"
        str_comp += str(self.im) + "i"
        return str_comp

    def __add__(self, other):
        new_re = self.re + other.re
        new_im = self.im + other.im
        return Complex(new_re, new_im)

    def __mul__(self, other):
        if isinstance(other, Complex):  # проверяем, относится ли другой объект к классу
            new_re = self.re * other.re - self.im * other.im  # комплексных чисел
            new_im = self.re * other.im + self.im * other.re
        elif isinstance(other, int) or isinstance(other, float):
            new_re = self.re * other
            new_im = self.im * other
        else:
            error = ComplexError(self, other)
            raise error
        return Complex(new_re, new_im)

    __rmul__ = __mul__


class Point(Complex):  # наследование
    def length(self):
        return (self.re ** 2 + self.im ** 2) ** 0.5

    def __str__(self):  # полиморфизм
        return str((self.re, self.im))

