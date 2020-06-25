#ifndef  HISTOGRAM_H_INCLUDED
#define  HISTOGRAM_H_INCLUDED
#include<vector>

void find_minmax (const std::vector<double>& numbers, double& min, double& max);
std::vector<size_t> make_histogram(const std::vector<double>& numbers, const size_t count);
void show_histogram_text(std::vector<size_t> bins);
#endif
