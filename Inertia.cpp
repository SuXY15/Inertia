#include <opencv2\opencv.hpp>  
#include <string>
#include <iostream>
#include <windows.h>
#include <sstream>
#include <fstream>

using namespace cv;
using namespace std;
using std::cout;

#define distance 3
#define dotNum	 100
#define pi		 3.141592653

typedef unsigned int uint;

string do_fraction(string head,long double value, int decplaces);

int main(int rgc,int* argv[])
{
	char* filename[7];
	int cnt = 7;
	filename[0] = "input.bmp";
	filename[1] = "input.jpg";
	filename[2] = "input.png";
	filename[3] = "input.tif";
	filename[4] = "input.dib";
	filename[5] = "input.jpe";
	filename[6] = "input.jpeg";
	int filecount = 0;
	for( int count=0; count<cnt; count++){
		string imagename = filename[count];
		string temp = imagename;
		temp[5] = '_';
		string inputName = do_fraction("Input",count,3)+temp;
		string outputName = do_fraction("Output",count,3)+temp;
		Mat img = imread(imagename);
		if(img.empty()){
			cout << "File \"" << imagename <<"\" Not found. Please check." << endl;
		}else{
		cout<< "================================" << endl;
		filecount++;
		double unit = 0.01;
		uint Ysize = img.rows;
		uint Xsize = img.cols;
		double	Sx= 0,Sy= 0,Ix = 0,Iy = 0,Ixy = 0,A = 0;
		for (uint px = 1; px<Xsize; px++){
			for (uint py = 1; py<Ysize; py++){
				if (img.at<Vec3b>(py,px)[0]<100 || img.at<Vec3b>(py,px)[1]<100 || img.at<Vec3b>(py,px)[2]<100 ){
					A += unit*unit;
					double x = px*unit;
					double y = py*unit;
					Sx += y*unit*unit;
					Sy += x*unit*unit;
					Ix += y*y*unit*unit;
					Iy += x*x*unit*unit;
					Ixy+= x*y*unit*unit;
				}
			}
		};
		double Xc  = Sy/A;  
		double Yc  = Sx/A;  
		double Pxc = Xc/unit;
		double Pyc = Yc/unit;
		double Ixc = Ix - A*Yc*Yc;
		double Iyc = Iy - A*Xc*Xc;
		double Ixyc= Ixy- A*Xc*Yc;
		double sita;
		if (Ix != Iy)
			sita = atan(2*Ixyc/(Ix-Iy))/2;
		else
			sita = 0;
		double Ix0 = (Ixc+Iyc)/2 + sqrt((Ixc-Iyc)*(Ixc-Iyc)+4*Ixyc*Ixyc)/2;
		double Iy0 = (Ixc+Iyc)/2 - sqrt((Ixc-Iyc)*(Ixc-Iyc)+4*Ixyc*Ixyc)/2;
		string outfilename = outputName+".txt";
		ofstream outfile(outfilename);
		outfile << "There is the calculate results of \"" << imagename << "\":" << endl;
		outfile << "Xsize:" << "\t" << Xsize << endl;
		outfile << "Ysize:" << "\t" << Ysize << endl;
		outfile << "Area:"  << "\t" << A     << endl;
		outfile << "Xc:"    << "\t" << Xc    << endl;
		outfile << "Yc:"    << "\t" << Yc    << endl;
		outfile << "Ix:"    << "\t" << Ix    << endl;
		outfile << "Iy:"    << "\t" << Iy    << endl;
		outfile << "Ixy:"   << "\t" << Ixy   << endl;
		outfile << "Ixc:"   << "\t" << Ixc   << endl;
		outfile << "Iyc:"   << "\t" << Iyc   << endl;
		outfile << "Ixyc:"  << "\t" << Ixyc  << endl;
		outfile << "sita:"  << "\t" << sita*180/pi << "deg" << endl;
		outfile << "Ix0:"   << "\t" << Ix0   << endl;
		outfile << "Iy0:"   << "\t" << Iy0   << endl;
		outfile.close();

		cout << "There is the calculate results of \""<< imagename <<"\":"<< endl;
		cout << "Xsize:" << "\t" << Xsize << endl;
		cout << "Ysize:" << "\t" << Ysize << endl;
		cout << "Area:"  << "\t" << A     << endl;
		cout << "Xc:"    << "\t" << Xc    << endl;
		cout << "Yc:"    << "\t" << Yc    << endl;
		cout << "Ix:"    << "\t" << Ix    << endl;
		cout << "Iy:"    << "\t" << Iy    << endl;
		cout << "Ixy:"   << "\t" << Ixy   << endl;
		cout << "Ixc:"   << "\t" << Ixc   << endl;
		cout << "Iyc:"   << "\t" << Iyc   << endl;
		cout << "Ixyc:"  << "\t" << Ixyc  << endl;
		cout << "sita:"  << "\t" << sita*180/pi << "deg" << endl;
		cout << "Ix0:"   << "\t" << Ix0   << endl;
		cout << "Iy0:"   << "\t" << Iy0   << endl;
		cout << "The results have been saved to file \"" << outfilename <<"\",please check." << endl;

		imshow(inputName,img);

		int min = (int)-dotNum*distance/2; 
		int max = (int) dotNum*distance/2;
		int* MainX = new int[dotNum];
		int* MainY = new int[dotNum];;
		int* Main2X = new int[dotNum];
		int* Main2Y = new int[dotNum];
		for (int i=1; i<=dotNum; i++){
			MainX[i-1] = 0;
			Main2X[i-1] = 0;
			MainY[i-1] = 0;
			Main2Y[i-1] = 0;
		}
		cout << "Puting Dots..." << endl;
		for (int i=1; i <= dotNum; i++){
			int I = i*distance;
			MainX[i-1] = (int)(Pxc + (min + I)*cos(sita));
			MainY[i-1] = (int)(Pyc + (min + I)*sin(sita));
			Main2X[i-1]= (int)(Pxc + (min + I)*cos(sita+pi/2));
			Main2Y[i-1]= (int)(Pyc + (min + I)*sin(sita+pi/2));
			if( MainX[i-1]<Xsize && MainY[i-1]<Ysize && MainX[i-1]>1 && MainY[i-1]>1){
				img.at<Vec3b>(MainY[i-1]-1,MainX[i-1])[1]   = 0;
				img.at<Vec3b>(MainY[i-1]-1,MainX[i-1]-1)[1] = 0;
				img.at<Vec3b>(MainY[i-1],  MainX[i-1]-1)[1] = 0;
				img.at<Vec3b>(MainY[i-1],  MainX[i-1])[1]   = 0;
				img.at<Vec3b>(MainY[i-1]+1,MainX[i-1])[1]   = 0;
				img.at<Vec3b>(MainY[i-1]+1,MainX[i-1]+1)[1] = 0;
				img.at<Vec3b>(MainY[i-1],  MainX[i-1]+1)[1] = 0;
				cout<<".";
			}
			if( Main2X[i-1]<Xsize && Main2Y[i-1]<Ysize && Main2X[i-1]>1 && Main2Y[i-1]>1){
				img.at<Vec3b>(Main2Y[i-1],  Main2X[i-1])[2]   = 0;
				img.at<Vec3b>(Main2Y[i-1]+1,Main2X[i-1])[2]   = 0;
				img.at<Vec3b>(Main2Y[i-1]+1,Main2X[i-1]+1)[2] = 0;
				img.at<Vec3b>(Main2Y[i-1],  Main2X[i-1]-1)[2] = 0;
				img.at<Vec3b>(Main2Y[i-1]-1,Main2X[i-1])[2]   = 0;
				img.at<Vec3b>(Main2Y[i-1]-1,Main2X[i-1]-1)[2] = 0;
				img.at<Vec3b>(Main2Y[i-1],  Main2X[i-1]-1)[2] = 0;
				cout<<"-";
			}
		}
		cout <<"Dots have been put."<<endl << "Text putting..." << endl;
		if(Xsize>240&&Ysize>100){
			putText(img,do_fraction("Xsize: ",Xsize,5),Point(10,10), CV_FONT_HERSHEY_PLAIN,1.0,cv::Scalar(255,0,0));
			putText(img,do_fraction("Ysize: ",Ysize,5),Point(150,10),CV_FONT_HERSHEY_PLAIN,1.0,cv::Scalar(255,0,0));
			putText(img,do_fraction("Xc:    ",Xc,5),   Point(10,30), CV_FONT_HERSHEY_PLAIN,1.0,cv::Scalar(255,0,0));
			putText(img,do_fraction("Yc:    ",Yc,5),   Point(150,30),CV_FONT_HERSHEY_PLAIN,1.0,cv::Scalar(255,0,0));
			putText(img,do_fraction("Ix0:   ",Ix0,5),  Point(10,50), CV_FONT_HERSHEY_PLAIN,1.0,cv::Scalar(255,0,0));
			putText(img,do_fraction("Iy0:   ",Iy0,5),  Point(150,50),CV_FONT_HERSHEY_PLAIN,1.0,cv::Scalar(255,0,0));
			putText(img,do_fraction("sita:  ",(double)(int)(sita*1800000/pi)/10000,5),Point(10,70),CV_FONT_HERSHEY_PLAIN,1.0,cv::Scalar(255,0,0));
			putText(img,do_fraction("Ixyc:  ",Ixyc,5), Point(10,90), CV_FONT_HERSHEY_PLAIN,1.0,cv::Scalar(255,0,0));
			putText(img,do_fraction("unit:  ",unit,5), Point(Xsize-120,Ysize-10),CV_FONT_HERSHEY_PLAIN,1.0,cv::Scalar(255,0,0));
			cout << "Text putting is finfished." << endl;
		}
		else cout << "The image \"" << imagename << "\" is too small to put text." << endl;
		line(img,Point(0,(int)Pyc),Point(Xsize,(int)Pyc),cv::Scalar(255,255,0),1);
		line(img,Point((int)Pxc,0),Point((int)Pxc,Ysize),cv::Scalar(255,0,255),1);
		line(img,Point(0,(int)(Pyc-Pxc*tan(sita))),Point(Xsize,(int)(Pyc+(Xsize-Pxc)*tan(sita))),cv::Scalar(0,255,0),1);
		line(img,Point((int)(Pxc-Pyc/tan(sita+pi/2)),0),Point((int)(Pxc+(Ysize-Pyc)/tan(sita+pi/2)),Ysize),cv::Scalar(0,0,255),1);
		imshow(outputName,img);
		imwrite(outputName+".bmp",img);
		cout << "The result image \""<< imagename <<"\" has been shown." << endl;
		cout<< "================================" << endl;
		}
	}
	cout << "Calculating is finfished. " << filecount << " image file solved." << endl;
	if(filecount==0){
		cout << "No supported file founded. Please check." << endl;
		system("pause");
	}
	waitKey();
	return 0;
}


string do_fraction(string head,long double value, int decplaces)
{
	ostringstream out;
	int prec = 10;
	out.precision(prec);
	out << value;
	string str = out.str();
	size_t n =str.find('.');
	if ((n!=string::npos)&&(str.size()>n+decplaces)){
		str[n+decplaces]='\0';
	}
	str.swap(string(str.c_str()));
	return head+str;
}