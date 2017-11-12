//�ֱ��������Ӧ��ֵ����ʹ�򷨽���ͼ��ָ�
#include<opencv2\opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
void getGrayValue(Mat &dstImage,double *value);
int GlobalThresh(double *value, int T1, int dT);
int OtsuThresh(double *value);
void Segmentation(Mat &dstImage, int T);
int main(void)
{
	Mat srcImage = imread("Fig1039(a)(polymersomes).tif",CV_LOAD_IMAGE_GRAYSCALE);
	if (!srcImage.data) { cout << "ͼ���ʧ��" << endl; return -1; }
	imshow("ԭʼͼ", srcImage);
	Mat copyImage = srcImage.clone();
	double value[256] = { 0 };
	getGrayValue(srcImage, value);

	int T=GlobalThresh(value, 128, 1);//��ʼ��ֵҪѡ���ʵ�����֤T���߶�������
	Segmentation(srcImage, T);
	cout << "T " << T << endl;
	imshow("�Զ�����ֵ��Ч��ͼ", srcImage);

	int T2 = OtsuThresh(value);
	Segmentation(copyImage, T2);
	imshow("�������ֵЧ��ͼ", copyImage);
	waitKey(0);
	return 0;
}

//��ûҶ�ֵ
void getGrayValue(Mat &dstImage, double * value)
{
	for (int i = 0; i != dstImage.rows; ++i)
	{
		uchar *p = dstImage.ptr<uchar>(i);
		for (int j = 0; j != dstImage.cols; ++j)
			value[p[j]]++;
	}
	int sum = dstImage.rows*dstImage.cols;
	for (int i = 0; i < 256; ++i)
		value[i] /= sum;
}
//����Ӧ��ֵ��
int GlobalThresh(double * value, int T1, int dT)
{
	int T2 = 0;
	bool flag = false;
	while (!flag)
	{
		double p1 = 0, p2 = 0;
		double m1 = 0, m2 = 0;
		for (int i = 0; i <= T1; ++i)
			p1 += value[i];
		p2 = 1 - p1;
		for (int i = 0; i <= T1; ++i)
			m1 += (i + 1)*value[i];
		if(p1!=0)
			m1 = m1 / p1;
		for (int i = T1 + 1; i < 256; ++i)
			m2 += (i + 1)*value[i];
		if(p2!=0)
			m2 = m2 / p2;
		T2 = (int)(m1 + m2) / 2;
		if (abs(T1 - T2) < dT)
			flag = true;
		T1 = T2;
	}
	return T1;
}
//���Ѱ����ֵ
int OtsuThresh(double * value)
{
	int Thresh;
	double p1, p2, m1, m2, mG, deltatmp, deltmax = 0;
	for (int count = 1; count < 255; ++count)
	{
		int K = count;
		p1 = p2 = m1 = m2 = 0;
		for (int i = 0; i < 256; ++i)
		{
			if (i <= K)
			{
				p1 += value[i];
				m1 += (i + 1)*value[i];
			}
			else if (i > K)
				m2 += (i + 1)*value[i];
		}
		p2 = 1 - p1;
		mG = m1 + m2;
		if (p1 != 0)
			m1 = m1 / p1;
		if (p2 != 0)
			m2 = m2 / p2;
		deltatmp = p1*(m1 - mG)*(m1 - mG) + p2*(m2 - mG)*(m2 - mG);
		if (deltatmp > deltmax)
		{
			deltmax = deltatmp;
			Thresh= count;
		}
	}
	return Thresh;
}
//������ֵ�ָ�
void Segmentation(Mat & dstImage, int T)
{
	for (int i = 0; i != dstImage.rows; ++i)
	{
		uchar *p = dstImage.ptr(i);
		for (int j = 0; j != dstImage.cols; ++j)
		{
			p[j] <= T ? p[j] = 0 : p[j] = 255;
		}
	}
}
