 #include "matrix.h"
#include "profile.h"

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
	for (size_t i = 0; i < height; i++)
	{
		std::vector<int> matrix_line;
		for (size_t j = 0; j < width; j++)
		{
			matrix_line.push_back(0);
		}
		data_.push_back(matrix_line);
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
	if (data_.size() > 0)
	{
		return data_[0].size();
	}
    return 0;
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


Matrix Matrix::operator*(const Matrix& rhs)
{LOG DURATION("matrix")
	Matrix new_matrix(data_.size(), rhs.GetWidth());

	int element = 0;
	for (size_t i = 0; i < data_.size(); i++)
	{
		for (size_t j = 0; j < rhs.GetWidth(); j++)
		{
			for (size_t k = 0; k < data_[0].size(); k++)
			{
				element += data_[i][k] * rhs.GetValue(k, j);
			}
			new_matrix.SetValue(i, j, element);
			element = 0;
		}
	}
	return new_matrix;
}

