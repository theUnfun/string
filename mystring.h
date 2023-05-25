#pragma once

namespace my_string {

	class RawMemory {
	public:

		RawMemory() = default;

		explicit RawMemory(size_t size);

		~RawMemory();

		const char* GetAddress() const noexcept;

		char* GetAddress() noexcept;

		void Swap(RawMemory& other) noexcept;

	private:

		char* data_ = nullptr;

	};

	class String {
	public:

		String() = default;

		String(const char* str);

		String(const char* str, size_t size);

		String(const String& other);

		String(String&& other) noexcept;

		String& operator= (const String& other);

		String& operator=(String&& other) noexcept;

		String& operator+=(const String& other);

		bool operator<(const String& other) const;

		const char* c_str() const;

		size_t length() const;

		friend String operator+(const String& lhs, const String& rhs);

	private:
		size_t length_ = 0;

		RawMemory data_;

		static String ConcatenateStrings(const String& lhs, const String& rhs);

	};

	String operator+(const String& lhs, const String& rhs);

	template <class T>
	void my_swap(T& left, T& right) noexcept {
		T temp = left;
		left = right;
		right = temp;
	}

} //namespace String