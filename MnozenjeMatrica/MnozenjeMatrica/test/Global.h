#pragma once

#include <vector>
#include <string>

#include "../src/Structures.h"

std::vector<std::string> testCasesFiles =
{
	"res\\tests\\TestCase1.txt",
	"res\\tests\\TestCase2.txt",
	"res\\tests\\TestCase3.txt",
	"res\\tests\\TestCase4.txt",
	"res\\tests\\TestCase5.txt"
};

std::vector<MultiplicationElements> testCases;

void readAllMultiplicationElementsFromFiles();
