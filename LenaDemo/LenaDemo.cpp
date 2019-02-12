// LenaDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <Windows.h>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat edges;
	int scale = 3;
	namedWindow("edges", 1);
	for (;;)
	{
		if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/ && (scale< 7))
		{
			scale += 2;
			cout << scale << endl;
		}

		if (GetKeyState('Z') & 0x8000 && (scale > 3))
		{
			scale -= 2;
			cout << scale << endl;
		}

		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, scale);
		imshow("edges", edges);
		if ((waitKey(30) >= 0) && !(GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/) && !(GetKeyState('Z') & 0x8000)) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
