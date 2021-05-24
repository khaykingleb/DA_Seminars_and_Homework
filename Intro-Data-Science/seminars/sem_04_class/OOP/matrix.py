from copy import deepcopy


class MatrixError(BaseException):
    def __init__(self, matrix, other):
        self.matrix1 = matrix
        self.matrix2 = other


class Matrix:
    def __init__(self, matrix):
        self.matrix = deepcopy(matrix)

    def __str__(self):
        return "\n".join(["\t".join(map(str, row)) for row in self.matrix])

    def size(self):
        return (len(self.matrix), len(self.matrix[0]))

    def __add__(self, other):
        res = []
        if isinstance(other, Matrix) and self.size() == other.size():
            for i in range(len(self.matrix)):
                nrow = [x + y for x, y in zip(self.matrix[i], other.matrix[i])]
                res.append(nrow)
        else:
            error = MatrixError(self, other)
            raise error
        return Matrix(res)

    def __mul__(self, other):
        res = []
        if isinstance(other, int) or isinstance(other, float):
            for i in range(len(self.matrix)):
                new_row = list(map(lambda x: other * x, self.matrix[i]))
                res.append(new_row)
        return Matrix(res)

    __rmul__ = __mul__

    def transpose(self):
        res = []
        old_res = [list(map(str, i)) for i in self.matrix]
        for i in range(self.size()[1]):
            row = []
            for j in range(self.size()[0]):
                row.append(old_res[j][i])
            res.append(row)
        self.matrix = res
        return Matrix(res)

    @staticmethod
    def transposed(x):
        res = []
        for i in range(len(x.matrix[0])):
            row = []
            for j in range(len(x.matrix)):
                k = x.matrix[j][i]
                row.append(k)
            res.append(row)
        return Matrix(res)
