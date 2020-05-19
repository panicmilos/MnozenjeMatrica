#pragma once

#include <vector>
#include <string>

#include "../src/Structures.h"

constexpr int numberOfTestCasesForMultipliers = 5;
std::string testCasesFiles[numberOfTestCasesForMultipliers] =
{
	"res\\tests\\TestCase1.txt",
	"res\\tests\\TestCase2.txt",
	"res\\tests\\TestCase3.txt",
	"res\\tests\\TestCase4.txt",
	"res\\tests\\TestCase5.txt"
};

std::vector<MultiplicationElements> testCases;

void readAllMultiplicationElementsFromFiles();
