#include <iostream>
#include <string>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<pcl/io/pcd_io.h>
#include <pcl/point_types.h>

typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;

using namespace std;
// using namespace cv;

const double camera_factor = 1000;
const double camera_cx = 325.5;
const double camera_cy = 253.5;
const double camera_fx = 518.0;
const double camera_fy = 519.0;

int main(int argc,char** argv)
{
	cv::Mat rgb,depth;
	rgb = cv::imread("/home/ppatel/clutter/rgbd_slam_tut/src/part2/data/rgb.png");
	depth = cv::imread("/home/ppatel/clutter/rgbd_slam_tut/src/part2/data/depth.png", -1);
	imshow("img",rgb);

	PointCloud::Ptr cloud(new PointCloud);

	for(int m=0;m<depth.rows;m++)
	{
		for(int n=0;n<depth.cols;n++)
		{
			ushort d = depth.ptr<ushort>(m)[n];
			if(d==0)
				continue;

			PointT p;

			p.z = double(d);
			p.x = (n - camera_cx)*p.z/camera_fx;
			p.y = (m - camera_cy)*p.z/camera_fy;

			p.b = rgb.ptr<uchar>(m)[n*3];
			p.g = rgb.ptr<uchar>(m)[n*3+1];
			p.r = rgb.ptr<uchar>(m)[n*3+2];

			cloud->points.push_back(p);

		}
	}
	cloud->height = 1;
	cloud->width = cloud->points.size();
	cout<<"point cloud size = "<<cloud->points.size()<<endl;
	cloud->is_dense = false;
	pcl::io::savePCDFile("./pointcloud.pcd",*cloud);
	cloud->points.clear();
	cout<<"task complete"<<endl;
	return 0;
}
