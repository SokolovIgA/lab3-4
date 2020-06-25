#ifndef  HISTOGRAM_H_INCLUDED
#define  HISTOGRAM_H_INCLUDED
#include<vector>

struct Input {
    std::vector<double> numbers;
    size_t bin_count;
};

void find_minmax (const std::vector<double>& numbers, double& min, double& max);
std::vector<size_t> make_histogram(Input data);
void show_histogram_text(std::vector<size_t> bins);

#endif
