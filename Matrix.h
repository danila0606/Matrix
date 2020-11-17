#pragma once

#include <iostream>
#include <initializer_list>
#include <exception>
#include <cmath>
#include <string>
#include <cassert>
#include <iomanip>
#include <ctime>

namespace linal {

    const double eps = 0.001;


    template<typename T = double>
    class Matrix final {

    public:

        Matrix() = default;
        Matrix(const size_t &rows, const size_t &columns, T value = T{});
        Matrix(const size_t &rows, const size_t &columns, const std::initializer_list<T> &elems);
        Matrix(const std::initializer_list<std::initializer_list<T>> &elems);


        const T& at(size_t i, size_t j) const&;
        T& at(size_t i, size_t j) &;

        size_t GetRows() const noexcept { return rows_; };
        size_t GetColumns() const noexcept { return columns_; };
        std::pair<size_t, size_t> GetRowsAndColumns() const noexcept { return std::make_pair(rows_, columns_); };
        size_t GetSize() const noexcept {return size_;};
        size_t GetCapacity() const noexcept {return capacity_;};
        void Print() const;

        void resize(size_t rows, size_t columns);
        void clear();

        template <typename U> void Copy(const Matrix<U>& m) noexcept ;
        template <typename U> explicit Matrix(const Matrix<U> &m) noexcept;
        Matrix(const Matrix& m) noexcept;
        Matrix& operator=(const Matrix& m) noexcept;

        Matrix(Matrix&& m) noexcept;
        Matrix& operator= (Matrix&& m) noexcept;


        Matrix& operator += (const Matrix& m)&;
        Matrix& operator += (Matrix<T>&& m)&;
        Matrix& operator -= (const Matrix& m)&;
        Matrix& operator -= (Matrix&& m)&;
        Matrix& operator *= (const T& number)&;
        Matrix  operator - () const&;

        Matrix& multiply(const Matrix& m)&;

        template <typename U>
        bool operator == (const Matrix<U>& m) const;
        template <typename U>
        bool operator != (const Matrix<U>& m) const;

        void SwapRows(size_t r1, size_t r2);
        void SwapColumns(size_t c1, size_t c2);
        Matrix GetMinor(size_t row, size_t col) const;

        double determinant() const;
        double determinantGaus() const;


        T trace() const;
        Matrix& negate()&;
        Matrix& transpose()&;

        ~Matrix();

    private:

        T *data_ = nullptr;

        size_t rows_{}, columns_{};
        size_t size_{}, capacity_{};

    };


    void RandomFill(Matrix<int>& m, int d1, int d2) {

        srand(time(0));

        for (int i = 0; i < m.GetRows(); i++) {
            for (int j = 0; j < m.GetColumns(); j++)
                m.at(i,j) = d1 + rand()%(d2 - d1);
        }

    }

    void RandomFill(Matrix<double>& m, int d1, int d2) {

        srand(time(0));

        for (int i = 0; i < m.GetRows(); i++) {
            for (int j = 0; j < m.GetColumns(); j++) {
                double k = (double)rand() / RAND_MAX;
                m.at(i, j) = d1 + (d2 - d1) * k;
            }
        }

    }
    template<typename T>
    std::istream& operator>>(std::istream& str, Matrix<T>& m) {

        int r,c;
        str>>r>>c;
        m.resize(r,c);

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++)
                str>>m.at(i,j);
        }

        return str;
    }

    //................Constructor..........................

    template<typename T>
    Matrix<T>::Matrix(const size_t &rows, const size_t &columns, T value) :
            rows_(rows), columns_(columns), size_(rows * columns), capacity_(rows*columns) {

        if(rows_ < 0 || columns_ < 0)
            throw std::invalid_argument("the dimensions of the matrix must be positive");

        if(!size_)
            data_ = nullptr;
        else {
            data_ = new T[size_]{value};

            // for (int i = 0; i < size_; i++)
            //   data_[i] = value;
        }

    }

    template<typename T>
    Matrix<T>::Matrix(const size_t &rows, const size_t &columns, const std::initializer_list<T> &elems) :
            rows_(rows), columns_(columns), size_(rows * columns), capacity_(rows*columns) {

        if(rows_ < 0 || columns_ < 0)
            throw std::invalid_argument("the dimensions of the matrix must be positive");

        const size_t size = elems.size();

        if(size_ < size)
            data_ = nullptr;
        else {
            data_ = new T[size_];

            int i = 0;
            for (const auto& elem : elems) {
                data_[i] = elem;
                i++;
            }

            for (; i < size_; i++)
                data_[i] = T{};
        }

    }

    template<typename T>
    Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> &elems) :
            rows_(elems.size()) {

        size_t columns = 0;

        for (const auto& row : elems)
            columns = std::max(columns, row.size());

        columns_ = columns;
        size_ = rows_ * columns_;
        capacity_ = size_;

        data_ = new T[size_];

        int i = 0;
        for (const auto& str : elems) {
            int j = 0;
            for (const auto& elem : str) {
                at(i, j) = elem;
                j++;
            }

            for (; j < columns_; j++)
                at(i,j) = T();

            i++;
        }

    }

    //................Constructor_end......................

    template <typename T>
    T& Matrix<T>::at(size_t i, size_t j)&
    {
        return const_cast<T&>(static_cast<const Matrix<T>*>(this)->at(i, j));
    }


    template <typename T>
    const T& Matrix<T>::at(size_t i, size_t j) const&
    {
        if (i >= rows_ || j >= columns_)
            throw std::out_of_range("Out of range");
        else
            return *(data_ + i * columns_ + j);
    }


    //................Copy.................................

    template <typename T>
    template <typename U>
    void Matrix<T>::Copy(const Matrix<U>& m) noexcept
    {
        const size_t min_row = std::min(rows_, m.GetRows());
        const size_t min_col = std::min(columns_, m.GetColumns());

        for (size_t i = 0; i < min_row; i++)
        {
            for (size_t k = 0; k < min_col; k++)
                at(i, k) = m.at(i, k);
        }

    }

    template <typename T>
    template <typename U>
    Matrix<T>::Matrix(const Matrix<U> &m) noexcept
            : Matrix(m.GetRows(), m.GetColumns()) {

        Copy(m);
    }

    template <typename T>
    Matrix<T>::Matrix(const Matrix& m) noexcept
            : Matrix(m.rows_, m.columns_)
    {
        Copy(m);
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator = (const Matrix& m) noexcept
    {
        if (this == &m)
            return *this;

        resize(m.rows_, m.columns_);
        Copy(m);

        return *this;
    }


    //..................Copy_end........................

    template <typename T>
    Matrix<T>::Matrix(Matrix&& m) noexcept
            : Matrix()
    {
        std::swap(data_, m.data_);
        rows_ = m.rows_;
        columns_ = m.columns_;
        size_ = m.size_;
        capacity_ = m.capacity_;

        m.rows_ = 0;
        m.columns_ = 0;
        m.size_ = m.capacity_ = 0;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator= (Matrix&& m) noexcept {

        if (this == &m)
            return *this;

        std::swap(data_, m.data_);

        rows_ = m.rows_;
        columns_ = m.columns_;
        size_ = m.size_;
        capacity_ = m.capacity_;

        m.rows_ = 0;
        m.columns_ = 0;
        m.size_ = m.capacity_ = 0;

        return *this;
    }

    template <typename T>
    void Matrix<T>::resize(size_t rows, size_t columns) {
        if (rows < 0 || columns < 0)
            throw std::invalid_argument("the dimensions of the matrix must be positive");

        if (!rows || !columns) {
            clear();
            return;
        }

        if (!data_) {
            data_ = new T[rows * columns]{T{}};
            rows_ = rows;
            columns_ = columns;
            size_ = rows * columns;
            return;
        }


        if (columns_ == columns && columns * rows <= capacity_) {
            for (size_t k = rows_; k < rows; k++) {
                for (size_t i = 0; i < columns_; i++)
                    at(k, i) = T();
            }
            rows_ = rows;

        }
        else if (rows_ == rows && columns_ >= columns) {

            columns_ = columns;
        }
        else {
            Matrix<T> tmp(rows, columns);
            tmp.Copy(*this);
            *this = std::move(tmp);
        }

        size_ = columns * rows;
    }


    // (+=, -=, *=, =, -, *).............................


    template <typename T>
    Matrix<T>& Matrix<T>::operator += (const Matrix& m)& {

        if (rows_ != m.rows_ || columns_ != m.columns_)
            throw std::invalid_argument("the dimensions of the matrices must be the same");

        for (size_t i = 0; i < m.rows_; i++)
        {
            for (size_t j = 0; j < m.columns_; j++)
                at(i, j) += m.at(i, j);
        }
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator += (Matrix&& m)& {

        if (rows_ != m.rows_ || columns_ != m.columns_)
            throw std::invalid_argument("the dimensions of the matrices must be the same");

        for (size_t i = 0; i < m.rows_; i++)
        {
            for (size_t j = 0; j < m.columns_; j++)
                at(i, j) += m.at(i, j);
        }
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator -= (const Matrix<T>& m)& {

        if (rows_ != m.rows_ || columns_ != m.columns_)
            throw std::invalid_argument("the dimensions of the matrices must be the same");

        for (size_t i = 0; i < m.rows_; i++)
        {
            for (size_t j = 0; j < m.columns_; j++)
                at(i, j) -= m.at(i, j);
        }
        return  *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator -= (Matrix<T>&& m)& {

        if (rows_ != m.rows_ || columns_ != m.columns_)
            throw std::invalid_argument("the dimensions of the matrices must be the same");

        for (size_t i = 0; i < m.rows_; i++)
        {
            for (size_t j = 0; j < m.columns_; j++)
                at(i, j) -= m.at(i, j);
        }
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator *= (const T& number)& {

        for (size_t i = 0; i < rows_; i++)
        {
            for (size_t j = 0; j < columns_; j++)
                at(i, j) *= number;
        }
    }


    template <typename T>
    Matrix<T> operator + (const Matrix<T>& l, const Matrix<T>& r)
    {
        Matrix<T> res(l);
        res += r;
        return res;
    }

    template <typename T>
    Matrix<T> operator + (const Matrix<T>& l, Matrix<T>&& r)
    {
        Matrix<T> res(std::move(r));
        r += l;
        return res;
    }
    template <typename T>
    Matrix<T> operator + (Matrix<T>&& l, const Matrix<T>& r)
    {
        Matrix<T> res(std::move(l));
        res += r;
        return res;
    }
    template <typename T>
    Matrix<T> operator + (Matrix<T>&& l, Matrix<T>&& r)
    {
        Matrix<T> res(std::move(l));
        res += r;
        return res;
    }



    template <typename T>
    Matrix<T> operator - (const Matrix<T>& l, const Matrix<T>& r)
    {
        Matrix<T> res(l);
        res -= r;
        return res;
    }
    template <typename T>
    Matrix<T> operator - (const Matrix<T>& l, Matrix<T>&& r)
    {
        Matrix<T> res(std::move(r));
        res -= l;
        return res;
    }
    template <typename T>
    Matrix<T> operator - (Matrix<T>&& l, const Matrix<T>& r)
    {
        Matrix<T> res(std::move(l));
        res -= r;
        return res;
    }
    template <typename T>
    Matrix<T> operator - (Matrix<T>&& l, Matrix<T>&& r)
    {
        Matrix<T> res(std::move(l));
        res -= r;
        return res;
    }


    template <typename T>
    Matrix<T> operator * (const Matrix<T>& m, const T& number)
    {
        Matrix<T> res(m);
        res.mul(number);
        return res;
    }
    template <typename T>
    Matrix<T> operator * (Matrix<T>&& m, const T& number)
    {
        Matrix<T> res(std::move(m));
        res.mul(number);
        return res;
    }
    template <typename T>
    Matrix<T> operator * (const T& number, const Matrix<T>& m)
    {
        Matrix<T> res(m);
        res.mul(number);
        return res;
    }
    template <typename T>
    Matrix<T> operator * (const T& number, Matrix<T>&& m)
    {
        Matrix<T> res(std::move(m));
        res.mul(number);
        return res;
    }


    template <typename T>
    Matrix<T>& Matrix<T>::multiply(const Matrix& m)&
    {

        if (columns_ != m.rows_)
            throw std::logic_error("matrix sizes are not valid for their composition");

        Matrix<T> res(rows_, m.columns_);

        for (int r = 0; r < rows_; r++)
        {
            for (int c = 0; c < m.columns_; c++)
            {
                T cur_res = T{};

                for (int j = 0; j < columns_; j++)
                    cur_res += at(r, j) * m.at(j, c);

                res.at(r,c) = cur_res;
            }
        }

        *this = std::move(res);

        return *this;
    }

    template <typename T>
    Matrix<T> operator * (const Matrix<T>& l, const Matrix<T>& r)
    {
        Matrix<T> res(l);
        res.multiply(r);
        return res;
    }
    template <typename T>
    Matrix<T> operator * (const Matrix<T>& l, Matrix<T>&& r)
    {
        Matrix<T> res(std::move(r));
        res.multiply(l);
        return res;
    }
    template <typename T>
    Matrix<T> operator * (Matrix<T>&& l, const Matrix<T>& r)
    {
        Matrix<T> res(std::move(l));
        res.multiply(r);
        return res;
    }
    template <typename T>
    Matrix<T> operator * (Matrix<T>&& l, Matrix<T>&& r)
    {
        Matrix<T> res(std::move(l));
        res.multiply(r);
        return res;
    }

    // (+=, -=, *=, =, -, *).......................end


    template<typename T>
    Matrix<T> Matrix<T>::operator -() const& {

        Matrix<T> res(*this);
        res.negate();

        return res;
    }

    template <typename T>
    template <typename U>
    bool Matrix<T>::operator == (const Matrix<U>& m) const {

        if (columns_ != m.GetColumns() || rows_ != m.GetRows())
            return false;

        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < columns_; j++) {

                if (at(i, j) != m.at(i, j))
                    return false;
            }
        }

        return true;
    }

    template <typename T>
    template <typename U>
    bool Matrix<T>::operator != (const Matrix<U>& m) const {
        return !(*this == m);
    }




    template <typename T>
    void Matrix<T>::SwapRows(size_t r1, size_t r2) {

        for (size_t j = 0; j < columns_; j++)
            std::swap(at(r1, j), at(r2, j));
    }


    template <typename T>
    void Matrix<T>::SwapColumns(size_t c1, size_t c2) {

        for (size_t i = 0; i < rows_; i++)
            std::swap(at(i, c1), at(i, c2));
    }

    template <typename T>
    T Matrix<T>::trace() const {

        if (rows_ != columns_)
            throw std::logic_error("Only the square matrix has a trace");

        if (!rows_)
            return T{};

        T res = at(0, 0);

        for (int i = 1; i < rows_; i++)
            res *= at(i, i);

        return res;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::transpose()& {

        if (!rows_ || !columns_)
            return *this;

        size_t r = rows_;
        size_t c = columns_;

        if (r >= c)
            resize(r, r);
        else
            resize(c, c);

        for (int i = 0; i < rows_; i++) {
            for (int j = i + 1; j < columns_; j++)
                std::swap(at(i, j), at(j,i));
        }

        if (r >= c)
            resize(c, r);
        else
            resize(r, c);

        return *this;
    }


    template <typename T>
    Matrix<T> Matrix<T>::GetMinor(size_t row, size_t col) const {

        if (!size_)
            throw std::logic_error("the null matrix has no submatrix");


        Matrix<T> res(columns_ - 1, rows_ - 1);

        for (int i = 0, i_res = 0; i < rows_; i++) {

            if (i == row)
                continue;

            for (int j = 0, j_res = 0; j < columns_; j++) {

                if (j == col)
                    continue;

                res.at(i_res, j_res) = at(i, j);
                j_res++;
            }
            i_res++;
        }

        return res;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::negate()& {

        for (int i = 0; i < size_; i++)
            data_[i] = -data_[i];

        return *this;
    }


    template <typename T>
    double Matrix<T>::determinant() const {

        double res;

        if (rows_ != columns_)
            throw std::logic_error("Only the square matrix has a determinant");

        if (rows_ == 1)
            return at(0, 0);

        for (int j = 0; j < rows_; j++) {

            const int k = (j % 2) ? -1 : 1;
            res += at(0, j) * (GetMinor(0, j).determinant()) * k;
        }

        return res;
    }


    template <typename T>
    double Matrix<T>::determinantGaus() const {

        if (rows_ != columns_)
            throw std::logic_error("Only the square matrix has a determinant");

        Matrix<double> copy_m{*this};

        bool sign = false;
        for (int i = 0; i < rows_; i++) {

            for (int ii = i; ii < rows_; ii++) {
                if (std::abs(copy_m.at(ii, i)) > eps) {
                    if (ii != i) {
                        copy_m.SwapRows(i, ii);
                        sign = !sign;
                    }
                    break;
                }
            }

            if (std::abs(copy_m.at(i, i)) < eps)
                return 0.0;


            auto elem = static_cast<double>(copy_m.at(i, i));
            for (int r = i + 1; r < rows_; r++) {

                const double k = copy_m.at(r, i) / elem;
                for (int j = 0; j < rows_; j++)
                    copy_m.at(r, j) -= copy_m.at(i, j) * k;
            }
        }
        const int res_sign = (sign) ? -1 : 1;

        return copy_m.trace() * res_sign;
    }




    template<typename T>
    Matrix<T>::~Matrix() {
        delete(data_);
    }

    template<typename T>
    void Matrix<T>::clear() {
        delete(data_);
        rows_ = 0;
        columns_ = 0;
        size_ = 0;
        capacity_ = 0;
        data_ = nullptr;
    }

    template<typename T>
    void Matrix<T>::Print() const {

        std::cout<<"________________________________________\n";
        std::cout<<"rows: "<<rows_<<" columns: "<<columns_<<"\n";
        std::cout<<"size: "<<size_<<" capacity: "<<capacity_<<"\n\n";

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < columns_; j++) {
                std::cout<<at(i,j)<<" ";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
        std::cout<<"________________________________________\n";
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Matrix<T>& m) {

        os << m.GetRows()<<" "<<m.GetColumns()<<"\n";

        for (int i = 0; i < m.GetRows(); i++) {
            for (int j = 0; j < m.GetColumns(); j++) {
                os<<m.at(i,j)<<" ";
            }
            os<<"\n";
        }
        return os;
    }


}