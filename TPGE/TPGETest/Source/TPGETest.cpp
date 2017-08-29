/// PeTBAGELTest.cpp : Defines the entry point for the console application.

// Include Precompiled Headers
#include "stdafx.h"

// inlude
#include <chrono>
#include <fstream>
#include <iostream>
#include <time.h>
#include "MemoryUse.h"

// Include Library
#include <Generation/Random.h>
#include <Model/Generated/GeneratedData.h>
#include <Model/Generated/GeneratedGraph.h>
#include <Model/Generated/GeneratedNode.h>
#include <Model/Templates/Template.h>
#include <TemplateProject.h>
#include <Util/IndexedMap.h>
#include <Util/NArray.h>

// used namespaces for convinience
using namespace TPGE;

void TestIndexedMap();
void TestNArray();
void TestRandom();
void WriteToFile(GeneratedData* data, double time, size_t memory);

int main()
{
	TestIndexedMap();
	TestNArray();
	TestRandom();

	time_t start = clock();

	TemplateProject project = TemplateProject();
	project.SetProjectDir(std::string("C:\\Users\\Dani\\Documents\\ZHAW\\BA\\BA_Project_Procedural\\TPGE\\TPGETest\\TestProject\\"));
	std::string dir = project.GetProjectDir();
	project.InitializeProject();
	project.LoadProject("Template.xml");
	Template* temp = project.GetTemplate();
	GeneratedGraph* root = project.GetRootGraph();
	GeneratedData* data = root->GetData(0).get();
	GeneratedNode* node = root->GetNode(0).get();

	time_t end = clock();
	size_t memory = getPeakRSS();

	WriteToFile(data, (double)(end - start) / CLOCKS_PER_SEC, memory);

    return 0;
}


void TestIndexedMap()
{
	IndexedMap<int> mp = IndexedMap<int>();
	mp.Insert(0, "a", 1);
	mp.Insert(1, "b", 2);
	mp.Insert(2, "c", 3);
	size_t size = mp.Size(); // 3

	mp.Insert(2, 4); // not possible
	mp.Insert("c", 5); // not possible

	mp.Insert(3, 6);
	mp.Insert("e", 7);
	size = mp.Size(); // 5

	std::shared_ptr<int> a = mp[0];		// 1
	std::shared_ptr<int> b = mp["b"];	// 2
	std::shared_ptr<int> three = mp[3];	// 6
	std::shared_ptr<int> e = mp["e"];	// 7
}

void TestNArray()
{
	NArray<int> arr = NArray<int>(3, { 2, 3, 4 });
	arr.SetElement(0, { 0, 0, 0 });
	int element = arr.GetElement({ 0, 0, 0 });
	int element2 = arr.GetElement(0);
}

void TestRandom()
{
	Random rand = Random();
	rand.SetMin(1);
	rand.SetMax(6);
	int dice_roll = rand.GetRandomInt("Uniform");
}

void WriteToFile(GeneratedData* data, double time, size_t memory)
{
	std::ofstream myfile;
	myfile.open("TestProject\\mask.txt");
	for (unsigned i = 0; i < data->GetContent("Mask")->GetLength(); i++)
		myfile << data->GetContent("Mask")->GetElement(i).GetUInt() << "\n";
	myfile.close();

	myfile.open("TestProject\\data.txt");
	for (unsigned i = 0; i < data->GetContent("Data")->GetLength(); i++)
		myfile << data->GetContent("Data")->GetElement(i).GetUInt() << "\n";
	myfile.close();

	myfile.open("TestProject\\info.txt");
	myfile << "Time taken: " << time << "s\n" << "Memory used: " << (double)memory / 1024 / 1024 << " MB\n";
	myfile.close();
}