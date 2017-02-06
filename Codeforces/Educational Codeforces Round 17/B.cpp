#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	long long a, b, c;
	cin >> a >> b >> c;

	vector<long long> usb;
	vector<long long> ps;

	long long m;
	cin >> m;

	long long val;
	string type;
	for (int i = 0; i < m; ++i) {
		cin >> val >> type;
		if (type == "USB")
			usb.push_back(val);
		else
			ps.push_back(val);
	}

	sort(usb.begin(), usb.end());
	sort(ps.begin(), ps.end());

	long long usbIndex = 0;
	long long psIndex = 0;

	int cnt = 0;
	long long price = 0;

	a = min(a, (long long)usb.size());
	for (int i = 0; i < a; ++i) {
		cnt++;
		price += usb[i];
		usbIndex++;
	}

	b = min(b, (long long)ps.size());
	for (int i = 0; i < b; ++i) {
		cnt++;
		price += ps[i];
		psIndex++;
	}


	for (int i = 0; i < c; ++i) {
		if (usbIndex < usb.size() && psIndex < ps.size()) {
			if (usb[usbIndex] < ps[psIndex])
				price += usb[usbIndex++];
			else
				price += ps[psIndex++];
			cnt++;
		}
		else if (usbIndex < usb.size()) {
			price += usb[usbIndex++];
			cnt++;
		}
		else if (psIndex < ps.size()) {
			price += ps[psIndex++];
			cnt++;
		}
	}

	cout << cnt << " " << price;
}