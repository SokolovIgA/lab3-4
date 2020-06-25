#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <curl/curl.h>
#include <cstdio>
#include "histogram.h"
#include "svg.h"
using namespace std;

vector<double> input_numbers(istream& in, const size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input
read_input(istream& in, bool prompt)
{
    Input data;
    size_t number_count;

    if (prompt)
    {
        cerr << "Enter number count: ";
        in >> number_count;

        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, number_count);

        cerr << "Enter column count: ";
        in >> data.bin_count;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >> data.bin_count;
    }
    return data;
}

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}

Input
download(const string& address) {
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            cout << curl_easy_strerror(res) << endl;
            exit(1);
        }
        else
        {
            double namelookup_time;
            res = curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &namelookup_time);
            if (res == CURLE_OK)
            {
                cerr << "Name lookup time: " << namelookup_time << endl;
            }
        }
        curl_easy_cleanup(curl);
    }
   return read_input(buffer, false);
}


int main(int argc, char* argv[])
{
     Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }
    const auto bins = make_histogram(input);

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

    char computer_name[MAX_COMPUTERNAME_LENGTH+1];
    DWORD size = sizeof(computer_name);
    GetComputerName(computer_name, &size);

    // Вывод данных
    show_histogram_svg(bins, version_major, version_minor, build, computer_name);
    return 0;
}
