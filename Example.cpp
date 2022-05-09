// This file serves as a documentation so I recommend you keeping it.

// HOW TO INCLUDE IN YOUR PROJECT?
// Simply include "ColorfulLogging.h" to your project.
#include "ColorfulLogging.h"

///// USEFUL INFORMATION \\\\\
// IMPORTANT: You can enable debug mode for the Colorful Logging lib at line 9 in "ColorfulLogging.h".
// Debug mode allows CL lib to log its errors.

// enum Color - It's a list of all possible colors to use. 
// The list may vary between the Windows version and the Linux/Mac version.

// enum Level - It's a list of all possible Log(..) messages colors.
// The list is the same for both Windows and Linux/Mac.

// std::map<std::string, std::chrono::system_clock::time_point> benchmarks - It's a map of every currently running benchmark.

// HANDLE hConsole - If you're compiling on windows, then it's the main output console.
// If you're compiling on Linux/Mac, this doesn't exist.
// - - - - - - - - - - - - - - - - - - - - - -

///// ALL POSSIBLE FUNCTIONS \\\\\\
// std::string Time()
// void   SetConsoleColor(Color color)
// void   Log(std::string text, Level importance, bool logTime = true)
// void   BenchmarkBegin(std::string benchmarkName)
// double BenchmarkGetTime(std::string benchmarkName)
// double BenchmarkReset(std::string benchmarkName)
// double BenchmarkStop(std::string benchmarkName)
// void   BenchmarkStopAll()
// 
// They are all explained later on.
// - - - - - - - - - - - - - - - - - - - - - -

// It's here only for the example's needs
#include <iostream>
#include <thread>

void Wait(int milliseconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
#define NEWLINE std::cout << '\n'
// - - - - - - - - - - - - - - - - - - - - - -

int main()
{
// Logging

	/// cl::Log(std::string text, Level importance, bool logTime = true)
	// 'text' - Text to be printed.
	// 'importance' - This sets color of the text (see the cl::Level declaration in "ColorfulLogging.h").
	// 'logTime' - If true, current time will be also included in the printed 'text'.

	cl::Log("This is an information\n", cl::Level::Info);
	cl::Log("This is a warning\n"	  , cl::Level::Warning);
	cl::Log("This is an error\n"	  , cl::Level::Error);
	cl::Log("This is a success\n"	  , cl::Level::Success);

	NEWLINE;

	cl::Log("I can log with time\n", cl::Level::Info);
	cl::Log("And without time..\n" , cl::Level::Info, false);

	NEWLINE;


// Utility

	/// cl::SetConsoleColor(cl::Color color)
	// 'color' - The color in which text will be printed from now on.

	cl::SetConsoleColor(cl::Color::Blue);
	std::cout << "I'm blue\n";
	std::cout << "Me either\n";

	cl::SetConsoleColor(cl::Color::Red);
	std::cout << "Red\n";

	/// cl::Time()
	// Returns current system time in std::string.

	cl::SetConsoleColor(cl::Color::Default);
	std::cout << "It's " << cl::Time() << '\n';

	std::string currentTime = cl::Time();

	NEWLINE;

// Benchmark

	/// cl::BenchmarkBegin(std::string benchmarkName)
	// Starts a benchmark which just measures time since the launch of it.
	// 'benchmarkName' - It's a unique identifier of a benchmark. There can't be two identically named benchmark because those will overwrite each other.
	cl::BenchmarkBegin("benchmark");

	cl::Log("The benchmark has began!\n", cl::Level::Info);
	Wait(1000);

	/// cl::BenchmarkGetTime(std::string benchmarkName)
	// Returns the time since benchmark's last launch in seconds. 
	// 'benchmarkName' - It's a unique identifier of a benchmark.
	double elapsed = cl::BenchmarkGetTime("benchmark");

	/// cl::BenchmarkStop(std::string benchmarkName)
	// Stops the benchmark and removes it from the 'benchmarks' map. Returns the time since benchmark's last launch in seconds. 
	// 'benchmarkName' - It's a unique identifier of a benchmark.
	cl::BenchmarkStop("benchmark");

	cl::Log("The benchmark took " + std::to_string(elapsed) + " seconds\n", cl::Level::Info);

	NEWLINE;

	cl::BenchmarkBegin("Loop");

	/// cl::BenchmarkReset(std::string benchmarkName)
	// Resets the benchmark, basically re-launches it. Returns the time since benchmark's last launch in seconds. 
	// 'benchmarkName' - It's a unique identifier of a benchmark.

	Wait(300);
	double resetTime = cl::BenchmarkReset("Loop");
	Wait(300);
	resetTime = cl::BenchmarkReset("Loop");
	Wait(300);

	double lastTime = cl::BenchmarkStop("Loop");
	cl::Log("The last iteration took " + std::to_string(lastTime) + " seconds\n", cl::Level::Info);

	NEWLINE;

	cl::BenchmarkBegin("1");
	cl::BenchmarkBegin("2");
	cl::BenchmarkBegin("3");

	/// cl::BenchmarkReset(std::string benchmarkName)
	// Stops every running benchmark and removes them from the 'benchmarks' map.
	// 'benchmarkName' - It's a unique identifier of a benchmark.
	cl::BenchmarkStopAll();

	NEWLINE;
}