#include <vector>
#include <unordered_map>

#include <string>
#include <opencv2/opencv.hpp>

#include "Point.h"
#include "Randfloat.h"

#define M_PI 3.1415927

struct transformation {
	Point p;
	double angle;
};

struct sNearestPoint {
	Point p;
	Point nearestPoint;
};

struct IterationData {
	std::vector<sNearestPoint> nPs;
	Point centroids[2];
};

transformation ICP(std::vector<Point> cloudA, std::vector<Point> cloudB, transformation guess = transformation{Point(0,0),0}) {
	transformation T = guess;
	std::vector<IterationData> data;

	for (Point& p : cloudA) {
		p = p.rotate(T.angle);
		p += T.p;
	}
	std::vector<Point> _cloudA = cloudA;

	int nA = _cloudA.size(), nB = _cloudA.size();
	int N = 100;


	for (int i = 0; i < N; i++) {
		Point centroidA = Point(0, 0), centroidB = Point(0, 0);
		std::vector<sNearestPoint> nPs;

		for (Point pA : _cloudA) {
			centroidA += pA;

			Point nearestPoint;
			double minDist = INT_MAX;
			for (Point pB : cloudB) {
				double dist = pA.getDistance(pB);
				if (dist < minDist) {
					minDist = dist;
					nearestPoint = pB;
				}
			}

			centroidB += nearestPoint;
			nPs.push_back(sNearestPoint({ pA, nearestPoint }));
		}

		centroidA *= 1.0 / nA;
		centroidB *= 1.0 / nA;

		cv::Mat H(2, 2, CV_64F);
		H = 0;
		int N = MIN(_cloudA.size(), _cloudA.size());
		for (int i = 0; i < N; i++) {
			Point pA = _cloudA[i] - centroidA, pB = cloudB[i] - centroidB;
			double pa[2] = { pA.x(), pA.y() };
			double pb[2] = { pB.x(), pB.y() };

			for (int k = 0; k < 4; k++) {
				int x = k % 2, y = k / 2;
				H.at<double>(x, y) += pa[x] * pb[y];
			}
		}

		cv::SVD svd;
		svd(H);
		cv::Mat u = svd.u;
		cv::Mat vt = svd.vt;
		cv::Mat R;
		cv::gemm(u, vt, 1, vt, 0, R);

		double a = acos(R.at<double>(0, 0));
		Point cAR = centroidA.rotate(a);
		Point cBR = centroidB.rotate(a);
		Point translation = centroidB - cAR;

		T.angle += a;
		T.p = T.p.rotate(a);
		T.p += translation;

		for (Point& p : _cloudA) {
			p = p.rotate(a);
			p += translation;
		}
		
		IterationData d;
		d.centroids[0] = centroidA, d.centroids[1] = centroidB;
		d.nPs = nPs;
		data.push_back(d);
	}

	Point min(0,0), max(0,0);

	std::vector<Point> points;
	for (IterationData d : data) {
		for (int i = 0; i < d.nPs.size(); i++) {
			points.push_back(d.nPs[i].p);
			points.push_back(d.nPs[i].nearestPoint);
		}
	}
	for (Point p : cloudA) points.push_back(p);
	for (Point p : cloudB) points.push_back(p);


	for (Point p : points) {
		min.x() = MIN(p.x(), min.x());
		min.y() = MIN(p.y(), min.y());
		max.x() = MAX(p.x(), max.x());
		max.y() = MAX(p.y(), max.y());
	}
	

	Point translation = Point(0,0) - min;
	Point scale = Point(abs(max.x() - min.x()), abs(max.y() - min.y()));

	for (Point& p : cloudA) {
		p += translation;
		p.x() /= scale.x();
		p.y() /= scale.y();
	}

	for (Point& p : cloudB) {
		p += translation;
		p.x() /= scale.x();
		p.y() /= scale.y();
	}

	int width = 1720, height = 980, r = 3;
	cv::Vec3b colorCloud = cv::Vec3b(120, 40, 0), colorActiveTarget = cv::Vec3b(0, 40, 240), colorPassiveTarget = colorActiveTarget * 0.5, colorLine = cv::Vec3b(60, 60, 60), colorCentroidA = cv::Vec3b(255,0,0), colorCentroidB = cv::Vec3b(0,0,255);

	for (IterationData d : data) {
		cv::Mat img(cv::Size(width, height), CV_8UC3);
		for (int i = 0; i < 2; i++) {
			d.centroids[i] += translation;
			d.centroids[i].x() *= width / scale.x();
			d.centroids[i].y() *= height / scale.y();
		}
		for (sNearestPoint& np : d.nPs) {
			np.nearestPoint += translation;
			np.nearestPoint.x() *= width / scale.x();
			np.nearestPoint.y() *= height / scale.y();

			np.p += translation;
			np.p.x() *= width / scale.x();
			np.p.y() *= height / scale.y();
		}
		for (int i = 0; i < d.nPs.size(); i++) cv::line(img, d.nPs[i].nearestPoint.getCVPoint(), d.nPs[i].p.getCVPoint(), colorLine);
		cv::Rect rectA(d.centroids[0].getCVPoint(), cv::Size(r, r) * 2);
		cv::rectangle(img, rectA, colorCentroidA, -1);
		cv::Rect rectB(d.centroids[1].getCVPoint(), cv::Size(r, r) * 2);
		cv::rectangle(img, rectB, colorCentroidB, -1);
		for (Point p : cloudB) cv::circle(img, p.getCVPoint(width, height), r, colorPassiveTarget, -1);
		for (sNearestPoint np : d.nPs) {
			cv::circle(img, np.nearestPoint.getCVPoint(), r, colorActiveTarget, -1);
			cv::circle(img, np.p.getCVPoint(), r, colorCloud, -1);
		}
		cv::imshow("Image", img);
		cv::waitKey();
	}

	return T;
}

int main() {
	std::vector<Point> A;
	
	srand(time(NULL));
	    
	int N = 100;
	for (int i = 0; i < N; i++) {
		A.push_back(Point(RandFloat(), RandFloat()));
	}
	std::vector<Point> B = A;
 	for (int i = 0; i < N * 0.2; i++) A.erase(A.begin());

	transformation t0;
	t0.p = Point(1, 1);
	t0.angle = (rand() % 7000) / 1000.0;

	transformation T = ICP(A, B, t0);

	return 0;
}