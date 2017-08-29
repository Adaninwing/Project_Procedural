#pragma once

/// incudes
#include <assert.h>
#include <vector>

namespace TPGE
{
	/// wrapper class for an n-dimensional array of values
	template <typename T>
	class NArray
	{
	public:
		typedef T NArrayContent;
		typedef std::vector<size_t> NArraySize;

		NArray() {}
		NArray(size_t dim, NArraySize size) : dimension_(dim)
		{
			/// does not work with dim == 0 yet
			assert(dim > 0);

			size_ = size;
			size_t totalSize = 1;
			for (size_t i = 0; i < dim; i++) {
				totalSize *= size[i];
			}
			length_ = 0;
			for (size_t i = 0; i < dim; i++)
			{
				if (!i)
					length_ = size[i];
				else
					length_ *= size[i];
			}

			arr_ = new NArrayContent[totalSize];
		}
		~NArray() 
		{
			delete[] arr_;
		}

		NArrayContent& operator[](const size_t at)
		{
			return arr_[at];
		}

		/// Fill the array with a copy of the value
		void Fill(const NArrayContent& toCopy)
		{
			size_t length = GetLength();
			for (size_t i = 0; i < length; i++)
			{
				arr_[i] = NArrayContent(toCopy);
			}
		}
		/// Get the dimension of the structure
		size_t GetDimension() const { return dimension_; }
		/// Get an element of the array
		NArrayContent& GetElement(NArraySize args)
		{
			size_t positionCalculated = GetPositionInArray(args);

			return arr_[positionCalculated];
		}
		/// Get an element of the array
		NArrayContent& GetElement(const size_t at)
		{
			return arr_[at];
		}
		/// Get the size of the dimensions
		size_t GetLength() const 
		{ 
			return length_;
		}
		/// Get the size of the dimensions
		NArraySize& GetSize() const { return const_cast<NArraySize&>(size_); }

		/// Set an element
		void SetElement(NArrayContent value, NArraySize args)
		{
			size_t positionCalculated = GetPositionInArray(args);

			arr_[positionCalculated] = value;
		}

	private:
		/// Get the position in the array from the position arguments
		size_t GetPositionInArray(NArraySize args)
		{
			size_t positionCalculated = args[0];
			for (size_t i = 1; i < dimension_; i++)
			{
				size_t value = args[i];
				for (size_t j = 0; j < i; j++)
				{
					value *= args[j];
				}
				positionCalculated += value;
			}
			return positionCalculated;
		}

		/// the values hold by the array
		NArrayContent* arr_;
		/// cached length variable for performace boost
		size_t length_;
		/// The dimension for reference
		size_t dimension_;
		/// The dimension sizes
		NArraySize size_;
	};
};