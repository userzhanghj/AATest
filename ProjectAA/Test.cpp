#include "pch.h"
#include "Test.h"

//说明
//求取空间中离散点的拟合平面
//


//AX+BY+CZ+D=0;
//平面法向量为	(A,B,C)

void cvFitPlane(const CvMat* points, float* plane) {
	//Estimate geometric centroid.
	int nrows = points->rows;
	int ncols = points->cols;
	int type = points->type;
	CvMat* centroid = cvCreateMat(1, ncols, type);
	cvSet(centroid, cvScalar(0));
	for (int c = 0; c < ncols; c++) {
		for (int r = 0; r < nrows; r++) {
			centroid->data.fl[c] += points->data.fl[ncols*r + c];

		}
		centroid->data.fl[c] /= nrows;
	}

	//Subtract geometric centroid from each point. points2存放的是各个点减去几何重心的值
	CvMat* points2 = cvCreateMat(nrows, ncols, type);
	for (int r = 0; r < nrows; r++)
		for (int c = 0; c < ncols; c++)
			points2->data.fl[ncols*r + c] = points->data.fl[ncols*r + c] - centroid->data.fl[c];
	//Evaluate SVD of covariance matrix
	CvMat* A = cvCreateMat(ncols, ncols, type);
	CvMat* W = cvCreateMat(ncols, ncols, type);
	CvMat* V = cvCreateMat(ncols, ncols, type);
	cvGEMM(points2, points, 1, NULL, 0, A, CV_GEMM_A_T);
	cvSVD(A, W, NULL, V, CV_SVD_V_T);
	//Mat A1(A);
	//cout << "A:" << A1 << endl;
	//Mat V1(V);
	//cout << "V:" << V1 << endl;
	//Assign plane coefficients by singular vector corresponding to smallest singular value
	plane[ncols] = 0;
	for (int c = 0; c < ncols; c++) {
		plane[c] = V->data.fl[ncols*(ncols - 1) + c];
		plane[ncols] += plane[c] * centroid->data.fl[c];
	}
	plane[ncols] = -plane[ncols];
	//Release allocated resources
	//cvReleaseMat();
	cvReleaseMat(&points2);
	cvReleaseMat(&A);
	cvReleaseMat(&W);
	cvReleaseMat(&V);
}


void column_principle_gauss(int N, double **a)
{
	int k = 0, i = 0, r = 0, j = 0;
	double t;
	for (k = 0; k < N - 1; k++)
	{
		for (i = k; i < N; i++)
		{
			r = i;
			t = (double)fabs(a[r][k]);
			if (fabs(a[i][k]) > t)
			{
				r = i;
			}
		}
		if (a[r][k] == 0)
		{
			break;
		}
		for (j = k; j < N + 1; j++)
		{
			t = a[r][j];
			a[r][j] = a[k][j];
			a[k][j] = t;
		}
		for (i = k + 1; i < N; i++)
		{
			for (j = k + 1; j < N + 1; j++)
			{
				a[i][j] = a[i][j] - a[i][k] / a[k][k] * a[k][j];
			}
		}
	}

	double he = 0;
	for (k = N - 1; k >= 0; k--)
	{
		he = 0;
		for (j = k + 1; j < N; j++)
		{
			he = he + a[k][j] * a[j][N];
		}
		a[k][N] = (a[k][N] - he) / a[k][k];
	}
}


void Least_squares(vector<Point3D>&v_Point, double M2[3])
{
	double **c = NULL;
	c = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		c[i] = new double[4];
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			c[i][j] = 0;
		}
	}
	c[0][0] = v_Point.size();
	for (int i = 0; i < v_Point.size(); i++)
	{
		c[0][1] = c[0][1] + v_Point.at(i).x;
		c[0][2] = c[0][2] + v_Point.at(i).y;
		c[0][3] = c[0][3] + v_Point.at(i).z;
		c[1][1] = c[1][1] + v_Point.at(i).x*v_Point.at(i).x;
		c[1][2] = c[1][2] + v_Point.at(i).x*v_Point.at(i).y;
		c[1][3] = c[1][3] + v_Point.at(i).x*v_Point.at(i).z;
		c[2][2] = c[2][2] + v_Point.at(i).y*v_Point.at(i).y;
		c[2][3] = c[2][3] + v_Point.at(i).y*v_Point.at(i).z;
	}
	c[1][0] = c[0][1];
	c[2][0] = c[0][2];
	c[2][1] = c[1][2];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%f", c[i][j]);
		}
	}
	column_principle_gauss(3, c);

	for (int i = 0; i < 3; i++)
	{
		M2[i] = c[i][3];
	}

	for (int i = 0; i < 3; i++)
	{
		delete[]c[i];
		c[i] = NULL;
	}
	delete[]c;
	c = NULL;
}

//int  main()
//{
//	Point3D temp[23];
//	for (int i = 0; i < 24; i++)
//	{
//
//		temp[i].x = test[i][0];
//		temp[i].y = test[i][1];
//		temp[i].z = test[i][2];
//	}
//
//	vector<Point3D>v_Point;
//	double M[3];
//	for (int i = 0; i < 24; i++)
//	{
//		v_Point.push_back(temp[i]);
//	}
//
//	Least_squares(v_Point, M);
//
//	for (int i = 0; i < 3; i++)
//	{
//		printf("M%d = %lf\n", i, M[i]);
//	}
//
//	Sleep(100000);
//	return 0;
//}