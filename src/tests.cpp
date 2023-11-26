// This file is part of the Chaos Compiler Collection.
// SPDX-License-Identifier: MIT

#include <gtest/gtest.h>

#include "ccc/ccc.h"
#include "platform/file.h"

using namespace ccc;

static void main_test(const fs::path& input_directory);

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	int result = RUN_ALL_TESTS();
	if(result != 0) {
		return result;
	}
	
	if(argc == 2) {
		main_test(std::string(argv[1]));
	}
}

static void main_test(const fs::path& input_directory) {
	CCC_CHECK_FATAL(fs::is_directory(input_directory), "Input path is not a directory.");
	
	for(auto entry : fs::recursive_directory_iterator(input_directory)) {
		if(entry.is_regular_file()) {
			printf("%s ", entry.path().string().c_str());
			
			Result<std::vector<u8>> file = platform::read_binary_file(entry.path());
			CCC_EXIT_IF_ERROR(file);
			
			printf("\n");
		}
	}
}
