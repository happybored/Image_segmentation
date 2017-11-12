//�ֶ�ѡ����ֵ���зָ�
#include<opencv2\opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(void)
{
	Mat srcImage=imread("Fig1001(a)(constant_gray_region).tif", CV_LOAD_IMAGE_GRAYSCALE); 

	if (!srcImage.data) { cout << "ͼƬ��ʧ��" << endl; return -1; }
	imshow("�Ҷ�ͼ", srcImage);
	cout << srcImage.rows << " " << srcImage.cols << endl;
	//ͳ�ƻҶȼ�ֵ������Ѱ�Һ�����ֵ
	int table[256] = { 0 };
	for (size_t i = 0; i != srcImage.rows; ++i)
	{
		uchar *p = srcImage.ptr<uchar>(i);
		for (size_t j = 0; j != srcImage.cols; ++j)
		{
			table[p[j]]++;
		}
	}
	for (int i = 0; i < 256; ++i) {
		if (table[i])
			cout << "i: " << i << " " << "value: " << table[i] << endl;
	}
	//����ͼ��ָ�ֶ���д��ֵ
	int threshold = 150;
	for (size_t i = 0; i != srcImage.rows; ++i)
	{
		uchar *p = srcImage.ptr<uchar>(i);
		for (size_t j = 0; j != srcImage.cols; ++j)
		{
			p[j] < threshold ? p[j] = 0 : p[j] = 255;
		}
	}
	imshow("Ч��ͼ", srcImage);
	waitKey(0);
	return 0;
}