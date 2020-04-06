//#include <Windows.h>
#include <cmath>
#include <cstdio>
const double eps = 1e-7;
int n = 0;
double alpha = 0, cota = 0;
double h[510], r[510];

inline double max(double a, double b) { return a < b ? b : a; }
inline double min(double a, double b) { return a < b ? a : b; }
double le[510], ri[510];
double k[510], b[510];

double f(double x) {
	double ret = 0.0;
	for (int i = 1; i <= n; ++i)
		if (h[i] - r[i] <= x && x <= h[i] + r[i])
			ret = max(ret, sqrt(r[i] * r[i] - (h[i] - x) * (h[i] - x)));
	for (int i = 1; i <= n; ++i)
		if (le[i] <= x && x <= ri[i])
			ret = max(ret, k[i] * x + b[i]);
	return ret;
}
inline double simpson(double L, double R) { return (R - L) * (f(L) + 4 * f((L + R) / 2.00) + f(R)) / 6.0; }
double calc(double L, double R, double ans) {
	double mid = (L + R) / 2.00;
	double lR = simpson(L, mid), rR = simpson(mid, R);
	if (fabs(lR + rR - ans) < eps)
		return lR + rR;
	else
		return calc(L, mid, lR) + calc(mid, R, rR);
}
int main() {
	scanf("%d %lf", &n, &alpha);
	cota = 1 / tan(alpha);
	for (int i = 1; i <= n + 1; ++i) {
		scanf("%lf", h + i);
		h[i] += h[i - 1];
	}
	for (int i = 1; i <= n; ++i)
		scanf("%lf", r + i);
	double L = 99999999, R = -9999999;
	for (int i = 0; i <= n + 1; ++i) {
		h[i] *= cota;
		L = min(L, h[i] - r[i]);
		R = max(R, h[i] + r[i]);
	}
	for (int i = 1; i <= n; ++i) {
		double th = asin((r[i + 1] - r[i]) / (h[i + 1] - h[i]));
		k[i] = tan(th);
		b[i] = -k[i] * h[i] + r[i] / cos(th);
		le[i] = h[i] - r[i] * sin(th);
		ri[i] = h[i + 1] - r[i + 1] * sin(th);
	}
	double sum = 0;

	for (double i = L; i <= R; i += 1.0)
		sum += calc(i, i + 1.0, simpson(i, i + 1.0));
	sum *= 2.0;
	printf("%.2f", sum);
	//{
	//	HWND hWnd = GetConsoleWindow();
	//	ShowWindow(hWnd, SW_MAXIMIZE);
	//	RECT rect;
	//	GetWindowRect(hWnd, &rect);
	//	HDC hdc = GetWindowDC(hWnd);
	//	int Ox = (rect.right - rect.left) * 3 / 10, Oy = (rect.bottom - rect.top) / 2;
	//	double Bei = 20;
	//	MessageBox(0, "AA", "aa", 0);
	//	for (int i = 0; i <= n + 1; ++i)
	//		for (double the = 0.0; the <= 2 * 3.1415926535; the += 0.001)
	//			SetPixel(hdc, Ox + (h[i] + cos(the) * r[i]) * Bei, Oy - (sin(the) * r[i]) * Bei, RGB(255, 0, 0));
	//	MessageBox(0, "AA", "aa", 0);
	//	for (double i = L; i <= R; i += 0.001) {
	//		SetPixel(hdc, Ox + i * Bei, Oy - f(i) * Bei, RGB(0, 255, 0));
	//		SetPixel(hdc, Ox + i * Bei, Oy + f(i) * Bei, RGB(0, 255, 0));
	//	}
	//	ReleaseDC(hWnd, hdc);
	//}
	return 0;
}