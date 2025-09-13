template <typename T>
class Vec
{
  private:
	T *data;		 // pointer to the array holding elements
	size_t capacity; // total allocated capacity
	size_t length;	 // current number of elements

	void resize_capacity(size_t new_capacity)
	{
		T *new_data = new T[new_capacity];
		for (size_t i = 0; i < length; ++i)
		{
			new_data[i] = std::move(data[i]);
		}
		delete[] data;
		data = new_data;
		capacity = new_capacity;
	}

	void merge_sort(int left, int right)
	{
		if (left >= right)
			return;
		int mid = left + (right - left) / 2;
		merge_sort(left, mid);
		merge_sort(mid + 1, right);
		merge_arrays(left, mid, right);
	}

	void merge_arrays(int left, int mid, int right)
	{
		int n1 = mid - left + 1, n2 = right - mid;
		T *leftArr = new T[n1];
		T *rightArr = new T[n2];

		for (int i = 0; i < n1; ++i)
			leftArr[i] = std::move(data[left + i]);
		for (int j = 0; j < n2; ++j)
			rightArr[j] = std::move(data[mid + 1 + j]);

		int i = 0, j = 0, k = left;
		while (i < n1 and j < n2)
		{
			data[k++] = (leftArr[i] <= rightArr[j]) ? std::move(leftArr[i++]) : std::move(rightArr[j++]);
		}
		while (i < n1)
			data[k++] = std::move(leftArr[i++]);
		while (j < n2)
			data[k++] = std::move(rightArr[j++]);
		delete[] leftArr;
		delete[] rightArr;
	}

  public:
	Vec() : data(nullptr), capacity(0), length(0) {}
	Vec(size_t size, const T &init_value) : data(nullptr), capacity(0), length(0)
	{
		if (size > 0)
		{
			resize_capacity(size);
			length = size;
			for (size_t i = 0; i < size; ++i)
				data[i] = init_value;
		}
	}

	Vec(std::initializer_list<T> init_list) : data(nullptr), capacity(0), length(0)
	{
		size_t auto_size = init_list.size();
		resize_capacity(auto_size);
		length = auto_size;
		size_t i = 0;
		for (const T &item : init_list)
			data[i++] = item;
	}

	~Vec()
	{
		delete[] data;
	}
	Vec(const Vec<T> &other) : data(nullptr), capacity(0), length(0)
	{
		if (other.length > 0)
		{
			resize_capacity(other.length);
			length = other.length;
			for (size_t i = 0; i < length; ++i)
				data[i] = other.data[i];
		}
	}
	Vec<T> &operator=(const Vec<T> &other)
	{
		if (this != &other)
		{
			Vec<T> temp(other);
			swap(temp);
		}
		return *this;
	}
	Vec(Vec<T> &&other) noexcept : data(nullptr), capacity(0), length(0)
	{
		swap(other);
	}
	Vec<T> &operator=(Vec<T> &&other) noexcept
	{
		if (this != &other)
		{
			delete[] data;
			data = nullptr;
			capacity = length = 0;
			swap(other);
		}
		return *this;
	}
	void push_back(const T &value)
	{
		if (length == capacity)
		{
			size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
			resize_capacity(new_capacity);
		}
		data[length++] = value;
	}
	void pop_back()
	{
		if (length == 0)
		{
			throw std::out_of_range("pop_back() called on empty Vec");
		}
		length--;
	}
	void resize(size_t new_size)
	{
		if (new_size > capacity)
		{
			size_t new_capacity = (capacity == 0) ? 1 : capacity;
			while (new_capacity < new_size)
				new_capacity *= 2;
			resize_capacity(new_capacity);
		}
		if (new_size > length)
		{
			for (size_t i = length; i < new_size; ++i)
				data[i] = T();
		}
		length = new_size;
	}

	T &front()
	{
		if (length == 0)
		{
			throw std::out_of_range("front() called on empty Vec");
		}
		return data[0];
	}

	T &back()
	{
		if (length == 0)
		{
			throw std::out_of_range("back() called on empty Vec");
		}
		return data[length - 1];
	}

	void insert(size_t index, const T &value)
	{
		if (index > length)
		{
			throw std::out_of_range("insert() index out of range");
		}
		if (length == capacity)
		{
			size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
			resize_capacity(new_capacity);
		}
		for (size_t i = length; i > index; --i)
			data[i] = std::move(data[i - 1]);
		data[index] = value;
		++length;
	}

	void merge(const Vec<T> &other)
	{
		if (length + other.length > capacity)
		{
			size_t new_capacity = (capacity == 0) ? 1 : capacity;
			while (new_capacity < length + other.length)
				new_capacity *= 2;
			resize_capacity(new_capacity);
		}
		for (size_t i = 0; i < other.length; ++i)
		{
			data[length + i] = other.data[i];
		}
		length += other.length;
		merge_sort(0, length - 1);
	}
	void clear() { length = 0; }
	T &operator[](size_t index)
	{
		if (index >= length)
		{
			throw std::out_of_range("Index out of range");
		}
		return data[index];
	}
	void sort()
	{
		if (length > 1)
			merge_sort(0, length - 1);
	}

	void swap(Vec<T> &other)
	{
		std::swap(data, other.data);
		std::swap(length, other.length);
		std::swap(capacity, other.capacity);
	}
	friend void swap(Vec<T> &a, Vec<T> &b)
	{
		using std::swap;
		swap(a.data, b.data);
		swap(a.length, b.length);
		swap(a.capacity, b.capacity);
	}
	T *begin() { return data; }
	T *end() { return data + length; }

	const T *begin() const { return data; }
	const T *end() const { return data + length; }
	size_t size() const
	{
		return length;
	}

	bool empty() const
	{
		return length == 0;
	}
};