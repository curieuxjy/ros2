#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <fstream>

using namespace cv;
using namespace dnn;
using namespace std;

const string cfgFile = "./yolov4.cfg";
const string weightFile = "./yolov4.weights";
float confThreshold = 0.3f;
float nmsThreshold = 0.3f;

Mat letterbox_image(Mat & im, int w, int h, int & _w, int & _h);
Mat analyzeDivot(cv::Mat & image, const cv::Rect & bbox);

int main() {
	Net net = readNetFromDarknet(cfgFile, weightFile);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);

	Mat image = imread("./image.jpg");
	Mat dst = image.clone();

	int x = 0, y = 0;
	Mat ori = letterbox_image(image, 640, 640, x, y);
	Mat blob;
	blobFromImage(ori, blob, 1 / 255.0, Size(640, 640), Scalar(0, 0, 0), true, false);
	vector<Mat> outs;
	net.setInput(blob);
	net.forward(outs, net.getUnconnectedOutLayersNames());
	
	vector<int> classIds;
	vector<float> confidences;
	vector<Rect> boxes;

	for (size_t i = 0; i < outs.size(); ++i)
	{
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
			Point classIdPoint;
			double confidence;
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
			if (confidence > confThreshold)
			{
				int centerX = 0, centerY = 0, width = 0, height = 0;
				if (image.cols > image.rows) {
					centerX = (int)(data[0] * (image.cols));
					centerY = (int)(data[1] * (image.cols)) - y;
					width = (int)(data[2] * (image.cols));
					height = (int)(data[3] * (image.cols));
				}
				else {
					centerX = (int)(data[0] * (image.rows)) - x;
					centerY = (int)(data[1] * (image.rows));
					width = (int)(data[2] * (image.rows));
					height = (int)(data[3] * (image.rows));
				}
				int left = centerX - width / 2;
				int top = centerY - height / 2;
				classIds.push_back(classIdPoint.x);
				confidences.push_back((float)confidence);
				boxes.push_back(Rect(left, top, width, height));
			}
		}
	}

	vector<int> indices;
	cv::dnn::NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);

	for (size_t i = 0; i < indices.size(); ++i)
	{

		int idx = indices[i];
		Rect box = boxes[idx];

		if (classIds[idx] == 0) { // DIVOT

			if (box.x < 0 || box.y < 0 ||
				box.x + box.width > image.cols ||
				box.y + box.height > image.rows)
			{
				return 1;
			}
			else {
				analyzeDivot(dst, box);
			}

			line(dst, Point(box.x, box.y), Point(box.x + box.width, box.y), Scalar(164, 73, 164), 3);
			line(dst, Point(box.x, box.y), Point(box.x, box.y + box.height), Scalar(164, 73, 164), 3);
			line(dst, Point(box.x + box.width, box.y + box.height), Point(box.x, box.y + box.height), Scalar(164, 73, 164), 3);
			line(dst, Point(box.x + box.width, box.y + box.height), Point(box.x + box.width, box.y), Scalar(164, 73, 164), 3);

		}
		else if (classIds[idx] == 1) { 
			line(dst, Point(box.x, box.y), Point(box.x + box.width, box.y), Scalar(0, 0, 255), 2);
			line(dst, Point(box.x, box.y), Point(box.x, box.y + box.height), Scalar(0, 0, 255), 2);
			line(dst, Point(box.x + box.width, box.y + box.height), Point(box.x, box.y + box.height), Scalar(0, 0, 255), 2);
			line(dst, Point(box.x + box.width, box.y + box.height), Point(box.x + box.width, box.y), Scalar(0, 0, 255), 2);

			line(dst, Point(box.x, box.y), Point(box.x + box.width, box.y + box.height), Scalar(0, 0, 255), 2);
			line(dst, Point(box.x + box.width, box.y), Point(box.x, box.y + box.height), Scalar(0, 0, 255), 2);
		}


	}
	imshow("result", dst);

	waitKey(0);
	return 0;
}

Mat letterbox_image(Mat & im, int w, int h, int & _w, int & _h)
{
	int new_w = im.cols;
	int new_h = im.rows;
	double multi = 0;
	if (((float)w / im.cols) < ((float)h / im.rows)) {
		new_w = w;
		new_h = (im.rows * w) / im.cols;
		multi = (im.cols / w);
	}
	else {
		new_h = h;
		new_w = (im.cols * h) / im.rows;
		multi = (im.rows / h);
	}
	Mat resized;
	resize(im, resized, Size(new_w, new_h), INTER_AREA);
	Mat boxed = Mat::Mat(w, h, CV_8UC3, Scalar(128, 128, 128));

	resized.copyTo(boxed(Rect(int(w / 2 - new_w / 2), int(h / 2 - new_h / 2), new_w, new_h)));

	_w = (int)((double)(w / 2 - new_w / 2) * multi);
	_h = (int)((double)(h / 2 - new_h / 2) * multi);
	return boxed;
}

Mat analyzeDivot(cv::Mat & image, const cv::Rect & bbox) {
	cv::Mat roi = image(bbox);

	cv::Mat hsv;
	cv::cvtColor(roi, hsv, cv::COLOR_BGR2HSV);

	cv::Mat mask;
	cv::inRange(hsv, cv::Scalar(0, 0, 0), cv::Scalar(30, 255, 255), mask);
	cv::Mat mask2;
	cv::inRange(hsv, cv::Scalar(150, 0, 0), cv::Scalar(180, 255, 255), mask2);
	mask = mask | mask2;

	cv::Mat green_mask;
	cv::inRange(hsv, cv::Scalar(35, 25, 25), cv::Scalar(85, 255, 255), green_mask);

	// �ʷϻ��� �ƴ� ���� ����ũ ���� (green_mask�� ����)
	cv::Mat non_green_mask;
	cv::bitwise_not(green_mask, non_green_mask);

	// ������ ����
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
	cv::morphologyEx(non_green_mask, non_green_mask, cv::MORPH_OPEN, kernel);

	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(non_green_mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// ���� ū ������
	int maxArea = 0;
	int maxIdx = -1;
	for (int i = 0; i < contours.size(); i++) {
		int area = cv::contourArea(contours[i]);
		if (area > maxArea) {
			maxArea = area;
			maxIdx = i;
		}
	}

	// ���⼺ �м�
	if (maxIdx >= 0) {
		cv::RotatedRect rect = cv::minAreaRect(contours[maxIdx]);
		cv::Point2f vertices[4];
		rect.points(vertices);

		cv::drawContours(roi, contours, maxIdx, cv::Scalar(0, 255, 255), 2);

		for (int i = 0; i < 4; i++)
		{
			// minAreaRect ǥ��
			//cv::line(roi, vertices[i], vertices[(i + 1) % 4], cv::Scalar(0, 255, 0), 2);
		}

		std::vector<std::pair<float, int>> sides(4);
		for (int i = 0; i < 4; i++) {
			int next = (i + 1) % 4;
			float length = cv::norm(vertices[i] - vertices[next]);
			sides[i] = std::make_pair(length, i);
		}

		std::sort(sides.begin(), sides.end());

		// ���� ª�� �� ���� �߽����� ����
		cv::Point2f shortSide1Center = (vertices[sides[0].second] + vertices[(sides[0].second + 1) % 4]) * 0.5f;
		cv::Point2f shortSide2Center = (vertices[sides[1].second] + vertices[(sides[1].second + 1) % 4]) * 0.5f;
		cv::line(roi, shortSide1Center, shortSide2Center, cv::Scalar(255, 0, 0), 2);
	}

	return roi;
}