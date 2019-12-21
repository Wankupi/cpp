
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

struct Result
{
	Result(int _d, int _x, int _y)
	{
		d = _d;
		x = _x;
		y = _y;
	}
	int d, x, y;
};

Result exgcd(int a, int b)
{
	if (b == 0)
		return Result(a, 1, 0);
	Result r = exgcd(b, a % b);
	return Result(r.d, r.y, r.x - (a / b) * r.y);
}
