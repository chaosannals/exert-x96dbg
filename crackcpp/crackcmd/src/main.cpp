#include<iostream>
#include<argparse/argparse.hpp>

int main(int argc, char *argv[]) {
	argparse::ArgumentParser program("crack");
	program.add_argument("target")
		//.default_value("false")
		.help("a arg target");
	program.add_argument("--count")
		.help("a arg count")
		.scan<'i', int>()
		.default_value(1);
	program.add_argument("--number")
		.nargs(1, 10)
		.help("a arg number")
		.scan<'g', float>()
		.default_value(1.0);
	program.add_argument("-n")
		.help("a arg number")
		.scan<'g', float>()
		.default_value(1.0);

	try {
		program.parse_args(argc, argv);
	}
	catch (const std::runtime_error& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << program;
		std::cin.get();
	}

	if (program.is_used("-n")) {
		std::cout << "is used -n" << std::endl;
	}

	return 0;
}