
// Copyright (c) 2010-2012 niXman (i dot nixman dog gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef _yas_test__buffer_hpp__included_
#define _yas_test__buffer_hpp__included_

/***************************************************************************/

template<typename archive_traits>
bool buffer_test(const char* archive_type, const char* io_type) {
	const std::string str1 = "intrusive buffer test"; // 21 + 4(header) + 4(size of array) = 29
	const unsigned char ostr1_64[] = {
		 0x79,0x61,0x73,0x81,0x15,0x00,0x00,0x00,0x69,0x6e,0x74,0x72,0x75,0x73
		,0x69,0x76,0x65,0x20,0x62,0x75,0x66,0x66,0x65,0x72,0x20,0x74,0x65,0x73,0x74
	};
	const unsigned char ostr1_32[] = {
		 0x79,0x61,0x73,0x01,0x15,0x00,0x00,0x00,0x69,0x6e,0x74,0x72,0x75,0x73
		,0x69,0x76,0x65,0x20,0x62,0x75,0x66,0x66,0x65,0x72,0x20,0x74,0x65,0x73,0x74
	};
	const unsigned char* ostr1 = (YAS_PLATFORM_BITS_IS_64())?ostr1_64:ostr1_32;

	yas::intrusive_buffer buf1(str1.c_str(), str1.length());
	typename archive_traits::oarchive oa1;
	archive_traits::ocreate(oa1, archive_type, io_type);
	oa1 & buf1;
	if ( yas::is_binary_archive<typename archive_traits::oarchive_type>::value ){
		if ( oa1.size() != sizeof(ostr1_64) )
		{
			std::cout << "BUFFER intrusive serialization error! [1]" << std::endl;
			return false;
		}
		if ( !oa1.compare(ostr1, sizeof(ostr1_64)) ) {
			std::cout << "BUFFER intrusive serialization error! [2]" << std::endl;
			return false;
		}
	} else if ( yas::is_text_archive<typename archive_traits::oarchive_type>::value ) {
		const char* res = (YAS_PLATFORM_BITS_IS_64())
			?"yas91 21 intrusive buffer test"
			:"yas11 21 intrusive buffer test"
		;
		if ( oa1.size() != strlen(res) ) {
			std::cout << "BUFFER intrusive serialization error! [3]" << std::endl;
			return false;
		}
		if ( !oa1.compare(res, strlen(res)) ) {
			std::cout << "BUFFER intrusive serialization error! [4]" << std::endl;
			return false;
		}
	}

#if defined(YAS_SHARED_BUFFER_USE_STD_SHARED_PTR)
	const std::string str2 = "std shared buffer test"; // 22 + 4(header) + 4(size of array) = 30
	const unsigned char ostr2_64[] = {
		 0x79,0x61,0x73,0x81,0x16,0x00,0x00,0x00,0x73,0x74,0x64,0x20,0x73,0x68,0x61
		,0x72,0x65,0x64,0x20,0x62,0x75,0x66,0x66,0x65,0x72,0x20,0x74,0x65,0x73,0x74
	};
	const unsigned char ostr2_32[] = {
		 0x79,0x61,0x73,0x01,0x16,0x00,0x00,0x00,0x73,0x74,0x64,0x20,0x73,0x68,0x61
		,0x72,0x65,0x64,0x20,0x62,0x75,0x66,0x66,0x65,0x72,0x20,0x74,0x65,0x73,0x74
	};
	const unsigned char* ostr2 = (YAS_PLATFORM_BITS_IS_64())?ostr2_64:ostr2_32;

	yas::shared_buffer buf2(str2.c_str(), str2.length());
	typename archive_traits::oarchive oa2;
	archive_traits::ocreate(oa2, archive_type, io_type);
	oa2 & buf2;
	if ( yas::is_binary_archive<typename archive_traits::oarchive_type>::value ){
		if ( oa2.size() != sizeof(ostr2_64) ) {
			std::cout << "BUFFER intrusive serialization error! [5]" << std::endl;
			return false;
		}
		if ( !oa2.compare(ostr2, sizeof(ostr2_64)) ) {
			std::cout << "BUFFER intrusive serialization error! [6]" << std::endl;
			return false;
		}
	} else if ( yas::is_text_archive<typename archive_traits::oarchive_type>::value ) {
		const char* res = (YAS_PLATFORM_BITS_IS_64())
			?"yas91 22 std shared buffer test"
			:"yas11 22 std shared buffer test"
		;
		if ( oa2.size() != strlen(res) ) {
			std::cout << "BUFFER intrusive serialization error! [7]" << std::endl;
			return false;
		}
		if ( !oa2.compare(res, strlen(res)) ) {
			std::cout << "BUFFER intrusive serialization error! [8]" << std::endl;
			return false;
		}
		typename archive_traits::iarchive ia1;
		archive_traits::icreate(ia1, oa2, archive_type, io_type);
		yas::shared_buffer buf4;
		ia1 & buf4;
		if ( buf4.size != str2.length() || str2 != buf4.data.get() ) {
			std::cout << "BUFFER std shared buffer deserialization error! [9]" << std::endl;
			return false;
		}
	}
#endif

#if defined(YAS_SHARED_BUFFER_USE_BOOST_SHARED_PTR)
	const std::string str3 = "boost shared buffer test"; // 24 + 4(header) + 4(size of array) = 32
	const unsigned char ostr3_64[] = {
		 0x79,0x61,0x73,0x81,0x18,0x00,0x00,0x00,0x62,0x6f,0x6f,0x73,0x74,0x20,0x73,0x68
		,0x61,0x72,0x65,0x64,0x20,0x62,0x75,0x66,0x66,0x65,0x72,0x20,0x74,0x65,0x73,0x74
	};
	const unsigned char ostr3_32[] = {
		 0x79,0x61,0x73,0x01,0x18,0x00,0x00,0x00,0x62,0x6f,0x6f,0x73,0x74,0x20,0x73,0x68
		,0x61,0x72,0x65,0x64,0x20,0x62,0x75,0x66,0x66,0x65,0x72,0x20,0x74,0x65,0x73,0x74
	};
	const unsigned char* ostr3 = (YAS_PLATFORM_BITS_IS_64())?ostr3_64:ostr3_32;

	yas::shared_buffer buf3(str3.c_str(), str3.length());
	typename archive_traits::oarchive oa3;
	archive_traits::ocreate(oa3, archive_type, io_type);
	oa3 & buf3;
	if ( yas::is_binary_archive<typename archive_traits::oarchive_type>::value ){
		if ( oa3.size() != sizeof(ostr3_64) ) {
			std::cout << "BUFFER intrusive serialization error! [10]" << std::endl;
			return false;
		}
		if ( !oa3.compare(ostr3, sizeof(ostr3_64)) ) {
			std::cout << "BUFFER intrusive serialization error! [11]" << std::endl;
			return false;
		}
	} else if ( yas::is_text_archive<typename archive_traits::oarchive_type>::value ) {
		const char* res = (YAS_PLATFORM_BITS_IS_64())
			?"yas91 24 boost shared buffer test"
			:"yas11 24 boost shared buffer test"
		;
		if ( oa3.size() != strlen(res) ) {
			std::cout << "BUFFER intrusive serialization error! [12]" << std::endl;
			return false;
		}
		if ( !oa3.compare(res, strlen(res)) ) {
			std::cout << "BUFFER intrusive serialization error! [13]" << std::endl;
			return false;
		}
		typename archive_traits::iarchive ia2;
		archive_traits::icreate(ia2, oa3, archive_type, io_type);
		yas::shared_buffer buf5;
		ia2 & buf5;
		if ( buf5.size != str3.length() || str3 != buf5.data.get() ) {
			std::cout << "BUFFER std shared buffer deserialization error! [14]" << std::endl;
			return false;
		}
	}
#endif

	return true;
}

/***************************************************************************/

#endif // _yas_test__buffer_hpp__included_
