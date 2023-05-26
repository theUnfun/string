#include "mystring.h"
#include <string.h>

namespace my_string {


	template <class T>
	void my_swap(T& left, T& right) noexcept {
		T temp = left;
		left = right;
		right = temp;
	}

	template <>
	void my_swap(RawMemory& left, RawMemory& right) noexcept {
		left.Swap(right);
	}

	RawMemory::RawMemory(size_t size)
		: data_(new char[size]) {
	}

	RawMemory::~RawMemory() {
		delete[] data_;
	}

	const char* RawMemory::GetAddress() const noexcept {
		return data_;
	}

	char* RawMemory::GetAddress() noexcept {
		return data_;
	}

	void RawMemory::Swap(RawMemory& other) noexcept {
		my_swap(data_, other.data_);
	}


	String::String(const char* str)
		: length_(strlen(str)) {
		if (length_ > 0) {
			RawMemory temp(length_ + 1);
			data_.Swap(temp);
			strcpy_s(data_.GetAddress(), length_ + 1, str);
		}
	}

	String::String(const String& other)
		: length_(other.length_)
		, data_(other.length_ + 1)
	{
		strcpy_s(data_.GetAddress(), length_ + 1, other.data_.GetAddress());
	}

	String::String(String&& other) noexcept {
		my_swap(data_, other.data_);
		my_swap(length_, other.length_);
	}

	String& String::operator= (const String& other) {
		if (this != &other) {
			String other_copy(other);
			my_swap(data_, other_copy.data_);
			my_swap(length_, other_copy.length_);
		}
		return *this;
	}

	String& String::operator=(String&& other) noexcept {
		if (this != &other) {
			my_swap(data_, other.data_);
			my_swap(length_, other.length_);
		}
		return *this;
	}

	String& String::operator+=(const String& other) {
		if (!other.empty()) {
			*this = ConcatenateStrings(*this, other);
		}
		return *this;
	}

	bool String::operator<(const String& other) const {
		const size_t cmp_len = (length_ < other.length_) ? length_ : other.length_;
		return (_strnicmp(data_.GetAddress(), other.data_.GetAddress(), cmp_len) < 0);
	}

	const char* String::c_str() const {
		return data_.GetAddress();
	}

	size_t String::length() const {
		return length_;
	}

	bool String::empty() const {
		return length_ == 0;
	}

	String operator+(const String& lhs, const String& rhs) {
		if (lhs.empty() && rhs.empty()) {
			return String();
		}
		return String::ConcatenateStrings(lhs, rhs);
	}


	String String::ConcatenateStrings(const String& lhs, const String& rhs) {
		size_t new_length = lhs.length_ + rhs.length_;
		RawMemory temp(new_length + 1);

		strcpy_s(temp.GetAddress(), new_length + 1, lhs.data_.GetAddress());
		strcpy_s(temp.GetAddress() + lhs.length_, rhs.length_ + 1, rhs.data_.GetAddress());

		String result;
		my_swap(result.data_, temp);
		my_swap(result.length_, new_length);
		return result;
	}

} //namespace String