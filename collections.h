#pragma once

namespace rsl {

// A default initialized or zero initialized array is completely valid.
template<typename Value>
struct Array {
	using value_type      = Value;
	using size_type       = size_t;
	
	using reference 	  = value_type&;
	using const_reference = const value_type&;
	
	using pointer         = value_type*;
	using const_pointer   = const pointer;

	using iterator        = value_type*;
	using const_iterator  = const iterator;

	pointer   data;
	size_type capacity;
	size_type count;

	reference operator[](size_type index) noexcept {
		return data[index];
	}

	// No need to implement special constructors because the default ones already
	// do what I need.

	// The only difference being that data, capacity and count are public.
	// Although I think it's actually a desirable feature because it allows users to extend
	// the library by for example implementing their own version of a make_array_...()
};

// Here I would argue that 'begin' and 'end' as paradigm is not the best

// I have found that something like this is more versatile 
/*

template<typename Value>
constexpr Array<Value>::iterator first(const Array<Value>& array) noexcept {	
}

template<typename Value>
constexpr Array<Value>::iterator last(const Array<Value>& array) noexcept {	// NOTE: this is the equivalent of "std::back()" not "std::end()" 
}

template<typename Value>
constexpr bool valid(const Array<Value>& array, const Array<Value>::itarator& itr) noexcept {	
}

template<typename Value>
constexpr bool next(const Array<Value>& array, Array<Value>::itarator& itr) noexcept {	
}
*/

template<typename Value>
constexpr typename Array<Value>::iterator begin(const Array<Value>& array) noexcept {	
	return array.data;
}

template<typename Value>
constexpr typename Array<Value>::iterator end(const Array<Value>& array) noexcept {	
	return array.data + array.count;
}

template<typename Value>
constexpr size_t size(const Array<Value>& array) noexcept {	
	return array.count;
}

// Here I am not 100% compliant with the standard library because I don't want to throw just because an array was empty. 
// I think it's better to just have front() and back() return iterators that could be null.

template<typename Value>
constexpr typename Array<Value>::iterator front(const Array<Value>& array) noexcept {
	return begin(array);
}

template<typename Value>
constexpr typename Array<Value>::iterator back(const Array<Value>& array) noexcept {	
	typename Array<Value>::iterator result = nullptr;
	
	if(array.count) {
		result = array.data + array.count - 1;
	} else {
		result = array.data;
	}

	return result;
}

template<typename Value>
constexpr typename Array<Value>::iterator at(const Array<Value>& array, typename Array<Value>::size_type index) noexcept {	
	typename Array<Value>::iterator result = nullptr;
	if(index < array.count){
		result = array.data + index;
	}
	return result;
}


// -------------- Another solution to at, front and back that return iterators could be this:

template<typename Value>
constexpr typename Array<Value>::reference front_or(const Array<Value>& array, typename Array<Value>::reference default_value) noexcept {
	typename Array<Value>::pointer result = &default_value;
	if(array.count) {
		result = array.data;
	}
	return *result;
}

template<typename Value>
constexpr typename Array<Value>::reference back_or(const Array<Value>& array, typename Array<Value>::reference default_value) noexcept {	
	typename Array<Value>::pointer result = &default_value;
	if(array.count) {
		result = array.data + array.count - 1;
	}
	return *result;
}

template<typename Value>
constexpr typename Array<Value>::reference at_or(const Array<Value>& array, typename Array<Value>::size_type index, typename Array<Value>::reference default_value) noexcept {	
	typename Array<Value>::pointer result = &default_value;
	if(index < array.count){
		result = array.data + index;
	}
	return *result;
}

// --------------


template<typename Value>
constexpr Array<Value> make_array(typename Array<Value>::pointer data, typename Array<Value>::size_type count) noexcept {	
	Array<Value> result = {};
	result.data     = data;
	result.count    = count;
	result.capacity = count;
	return result;
}

template<typename Value>
constexpr Array<Value> make_array_from_memory(void* data, size_t memory_size) noexcept {	
	Array<Value> result = {};
	result.data     = (typename Array<Value>::pointer) data;
	result.count    = memory_size / sizeof Value;
	result.capacity = result.count;
	return result;
}

}

/*
#ifndef RSL_NAMESPACE_ALIAS
#define RSL_NAMESPACE_ALIAS rsl
#endif

namespace RSL_NAMESPACE_ALIAS = reasonable_standard;
*/