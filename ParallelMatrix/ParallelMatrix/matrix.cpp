#include "matrix.h"
#include "profile.h"
#include <vector>
#include <utility>
#include <future>


std::istream& operator>>(std::istream& input_stream, Matrix& matrix)
{
    for (size_t y = 0; y < matrix.GetHeight(); y++)
    {
        for (size_t x = 0; x < matrix.GetWidth(); x++)
        {
            int temp_int = 0;
            input_stream >> temp_int;
            matrix.SetValue(y, x, temp_int);
        }
    }

    return input_stream;
}


std::ostream& operator<<(std::ostream& output_stream, const Matrix& matrix)
{
    for (size_t y = 0; y < matrix.GetHeight(); y++)
    {
        for (size_t x = 0; x < matrix.GetWidth(); x++)
        {
            output_stream << matrix.GetValue(y, x) << " ";
        }
        output_stream << "\n";
    }
    return output_stream;
}


Matrix::Matrix(const size_t height, const size_t width)
{
    data_.reserve(height);
    for (size_t i = 0; i < height; i++)
    {
        std::vector<int> matrix_line;
        for (size_t j = 0; j < width; j++)
        {
            matrix_line.push_back(0);
        }
        data_.push_back(std::move(matrix_line));
    }
}


void Matrix::SetValue(const size_t height_index, const size_t width_index,
    const int value)
{
    data_[height_index][width_index] = value;
}


int Matrix::GetValue(const size_t height_index, const size_t width_index) const
{
    return data_[height_index][width_index];
}


size_t Matrix::GetHeight() const
{
    return data_.size();
}


size_t Matrix::GetWidth() const
{
    if (data_.size() == 0)
    {
        return 0;
    }
    else
    {
        return data_[0].size();
    }
}


Matrix Matrix::Transpose() const
{
    if (data_.size() > 0)
    {
        Matrix matrix_transposed(data_[0].size(), data_.size());

        for (size_t i = 0; i < matrix_transposed.GetWidth(); i++)
        {
            for (size_t j = 0; j < matrix_transposed.GetHeight(); j++)
            {
                matrix_transposed.SetValue(j, i, data_[i][j]);
            }
        }
        return matrix_transposed;
    }
}


Matrix Matrix::operator+(const Matrix& rhs)
{
    Matrix new_matrix((*this).GetHeight(), (*this).GetWidth());
    for (size_t i = 0; i < rhs.GetHeight(); ++i)
    {
        for (size_t j = 0; j < rhs.GetWidth(); ++j)
        {
            new_matrix.SetValue(i, j, data_[i][j] + rhs.GetValue(i, j));
        }
    }
    return new_matrix;
}


Matrix MatrixMultiplication(const Matrix& lhs, const Matrix& rhs, const size_t begin_pos, const size_t end_pos)
{
    Matrix rhs_transposed = rhs.Transpose();
    Matrix new_matrix(lhs.GetHeight(), rhs.GetWidth());
    int element = 0;
    for (size_t i = begin_pos; i < end_pos; ++i)
    {
        for (size_t j = 0; j < new_matrix.GetWidth(); ++j)
        {
            size_t length = lhs.GetWidth();
            for (size_t k = 0; k < length; ++k)
            {
                element += lhs.GetValue(i, k) * rhs_transposed.GetValue(j, k);
            }
            new_matrix.SetValue(i, j, element);
        }
    }
    return new_matrix;
}


Matrix Matrix::operator*(const Matrix& rhs)
{
    if (data_[0].size() == rhs.GetHeight())
    {
        Matrix result(data_.size(), rhs.GetWidth());

        {LOG_DURATION("parallel matrix")
        const int threads_count = 4;
        std::vector<std::future<Matrix>> partials;
        partials.reserve(threads_count);

        for (size_t i = 0; i < threads_count; ++i)
        {
            const size_t begin_pos = i * ((*this).GetHeight() / threads_count);
            const size_t end_pos = (i + 1 == threads_count) ?
                (*this).GetHeight() : (i + 1) * ((*this).GetHeight() / threads_count);

            std::future<Matrix> partial_of_matrix_multiplication = std::async(
                std::launch::async,
                MatrixMultiplication, *this, rhs, begin_pos, end_pos
            );
            partials.push_back(std::move(partial_of_matrix_multiplication));
        }

        for (size_t i = 0; i < threads_count; ++i)
        {
            std::cerr << "Waiting thread #" << i << std::endl;
            result = result + partials[i].get();
        }
        }
    return result;
    }
    else
    {
        std::logic_error{ "Multiplying matrix has incorrect sizes" };
    }
}

