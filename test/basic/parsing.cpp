/*
 * Copyright (c) 2011, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
//#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE uri
#include <boost/test/unit_test.hpp>

#include <iostream>

#include "../../src/uri.hpp"

// Test a regular valid ws URI
BOOST_AUTO_TEST_CASE( uri_valid ) {
	bool exception = false;
	try {
		websocketpp::uri uri("ws://localhost:9000/chat");
		
		BOOST_CHECK( uri.get_secure() == false );
		BOOST_CHECK( uri.get_host() == "localhost");
		BOOST_CHECK( uri.get_port() == 9000 );
		BOOST_CHECK( uri.get_resource() == "/chat" );
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == false);
}

// Test a regular valid ws URI
BOOST_AUTO_TEST_CASE( uri_valid_no_port_unsecure ) {
	bool exception = false;
	try {
		websocketpp::uri uri("ws://localhost/chat");
		
		BOOST_CHECK( uri.get_secure() == false );
		BOOST_CHECK( uri.get_host() == "localhost");
		BOOST_CHECK( uri.get_port() == 80 );
		BOOST_CHECK( uri.get_resource() == "/chat" );
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == false);
}



// Valid URI with no port (secure)
BOOST_AUTO_TEST_CASE( uri_valid_no_port_secure ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss://localhost/chat");
		
		BOOST_CHECK( uri.get_secure() == true );
		BOOST_CHECK( uri.get_host() == "localhost");
		BOOST_CHECK( uri.get_port() == 443 );
		BOOST_CHECK( uri.get_resource() == "/chat" );
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == false);
}

// Valid URI with no resource
BOOST_AUTO_TEST_CASE( uri_valid_no_resource ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss://localhost:9000");
		
		BOOST_CHECK( uri.get_secure() == true );
		BOOST_CHECK( uri.get_host() == "localhost");
		BOOST_CHECK( uri.get_port() == 9000 );
		BOOST_CHECK( uri.get_resource() == "/" );		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == false);
}

// Valid URI IPv6 Literal
BOOST_AUTO_TEST_CASE( uri_valid_ipv6_literal ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss://[::1]:9000/chat");
		
		BOOST_CHECK( uri.get_secure() == true );
		BOOST_CHECK( uri.get_host() == "[::1]");
		BOOST_CHECK( uri.get_port() == 9000 );
		BOOST_CHECK( uri.get_resource() == "/chat" );		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == false);
}



// Valid URI with more complicated host
BOOST_AUTO_TEST_CASE( uri_valid_2 ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss://thor-websocket.zaphoyd.net:88/");
		
		BOOST_CHECK( uri.get_secure() == true );
		BOOST_CHECK( uri.get_host() == "thor-websocket.zaphoyd.net");
		BOOST_CHECK( uri.get_port() == 88 );
		BOOST_CHECK( uri.get_resource() == "/" );		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == false);
}


// Invalid URI (port too long)
BOOST_AUTO_TEST_CASE( uri_invalid_long_port ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss://localhost:900000/chat");		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == true);
}

// Invalid URI (http method)
BOOST_AUTO_TEST_CASE( uri_invalid_http ) {
	bool exception = false;
	try {
		websocketpp::uri uri("http://localhost:9000/chat");		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == true);
}

// Valid URI IPv4 literal
BOOST_AUTO_TEST_CASE( uri_valid_ipv4_literal ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss://127.0.0.1:9000/chat");
		
		BOOST_CHECK( uri.get_secure() == true );
		BOOST_CHECK( uri.get_host() == "127.0.0.1");
		BOOST_CHECK( uri.get_port() == 9000 );
		BOOST_CHECK( uri.get_resource() == "/chat" );		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == false);
}

// Valid URI complicated resource path
BOOST_AUTO_TEST_CASE( uri_valid_3 ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss://localhost:9000/chat/foo/bar");
		
		BOOST_CHECK( uri.get_secure() == true );
		BOOST_CHECK( uri.get_host() == "localhost");
		BOOST_CHECK( uri.get_port() == 9000 );
		BOOST_CHECK( uri.get_resource() == "/chat/foo/bar" );		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == false);
}

// Invalid URI broken method separator
BOOST_AUTO_TEST_CASE( uri_invalid_method_separator ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss:/localhost:9000/chat");		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == true);
}

// Invalid URI port > 65535
BOOST_AUTO_TEST_CASE( uri_invalid_gt_16_bit_port ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss:/localhost:70000/chat");		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == true);
}

// Invalid URI includes uri fragment
BOOST_AUTO_TEST_CASE( uri_invalid_fragment ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss:/localhost:70000/chat#foo");		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == true);
}

// Valid URI complicated resource path with query
BOOST_AUTO_TEST_CASE( uri_valid_4 ) {
	bool exception = false;
	try {
		websocketpp::uri uri("wss://localhost:9000/chat/foo/bar?foo=bar");
		
		BOOST_CHECK( uri.get_secure() == true );
		BOOST_CHECK( uri.get_host() == "localhost");
		BOOST_CHECK( uri.get_port() == 9000 );
		BOOST_CHECK( uri.get_resource() == "/chat/foo/bar?foo=bar" );		
	} catch (websocketpp::uri_exception& e) {
		exception = true;
	}

	BOOST_CHECK( exception == false);
}

// TODO: tests for the other two constructors