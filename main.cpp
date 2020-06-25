#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include "histogram.h"
#include "svg.h"
using namespace std;

vector<double> input_numbers(const size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }

    return result;
}

int main() {
    // Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    // Обработка данных
    const auto bins = make_histogram(numbers, bin_count);

    DWORD mask = 0x0000ffff;
    DWORD mask_major = 0x000000f;
    DWORD info = GetVersion();
    DWORD platform = info >> 16;
    DWORD version = info & mask;
    DWORD version_major = version & mask_major;
    DWORD version_minor = version >>8;
    DWORD build;

    if ((info & 0x40000000) == 0);
    {
        build = platform;
    }

    // Вывод данных
    show_histogram_svg(bins, version_major, version_minor, build);

    return 0;
}
