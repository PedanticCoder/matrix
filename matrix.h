#ifndef MATRIX_H
#define MATRIX_H

#include <map>
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>

template<typename T, T defaultValue, std::size_t dim = 2>
class Matrix
{
    static_assert(dim > 0, "Число измерений должно быть положительно!");

    using matrix_t = std::map<std::tuple<int, int>, T>;

public:
    Matrix() : defaultValue_(defaultValue) { }

    struct MatrixProxy {

        MatrixProxy() = default;

        MatrixProxy(Matrix* matr, int i) {
            mtx = matr;
            mi = i;
        }

        T operator[](int j) {
            // TODO проверку наличия индексов, как в перегруженном операторе ()()
            std::tuple<int, int> indexes = std::make_tuple(mi, j);
            return mtx->noDefaultValues[indexes];
        }

        private:
            Matrix *mtx;
            int mi;
    };

    MatrixProxy operator[](int i) {
        return MatrixProxy(this, i);
    }

    T& operator()(int i, int j) {

        auto indexes_to_find = std::make_tuple(i, j);

        if(indexesVector.empty()) {
            return defaultValue_;
        }
        else {
            auto it = std::find_if(indexesVector.begin(), indexesVector.end(),
                                   [&indexes_to_find](const auto& item) {
                                       return std::get<0>(indexes_to_find)==std::get<0>(item)
                                              && std::get<1>(indexes_to_find)==std::get<0>(item);
                                   });
            if(it!=indexesVector.end()) {
                return noDefaultValues[indexes_to_find];
            }
            else {
                return defaultValue_;
            }
        }
    }

    size_t size() const {
        return indexesVector.size();
    }

private:
    std::vector<std::tuple<int, int>> indexesVector;
    std::map<std::tuple<int, int>, T> noDefaultValues;
    T defaultValue_;
    MatrixProxy matrixProxy_;
};

#endif // MATRIX_H

