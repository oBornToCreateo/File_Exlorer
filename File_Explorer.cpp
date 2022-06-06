#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <filesystem>
#include <locale>

namespace fs = std::filesystem;

int main() {

    try {
        const char* const localeName = "pl_PL.utf-8";
        std::setlocale(LC_ALL, localeName);
        std::locale::global(std::locale(localeName));

        do {
            std::wstring path;
            int item_number = 1;
            std::vector<std::pair<int,std::wstring>>  Names_Old, Names_New;
            std::wcout << L"enter directory path : ";
            std::wcin >> path; std::cout << std::endl;

            std::wcout << L"Choosen directory content" << std::endl << std::endl;

            for (const auto& entry : fs::directory_iterator(path)) {
                auto pathfiles_names = entry.path().filename().wstring();
                auto pathfiles_size = entry.file_size();
                std::wcout << item_number << L" " << pathfiles_names << std::endl;
                Names_Old.push_back(std::make_pair(pathfiles_size,pathfiles_names));
                item_number++;
            }
            item_number = 1;

            do {
                std::wcout << std::endl;
                std::wcout << L"Refresh? [Y/N] : ";

                std::wstring choise;
                std::wcin >> choise;

                if (choise == L"Y") {
                    for (const auto& entry : fs::directory_iterator(path)) {
                        auto pathfiles_names = entry.path().filename().wstring();
                        auto pathfiles_size = entry.file_size();
                        std::wcout << item_number << L" " << pathfiles_names << std::endl;
                        Names_New.push_back(std::make_pair(pathfiles_size, pathfiles_names));
                        item_number++;
                    }
                    item_number = 1;

                    if (Names_New == Names_Old)
                        std::cout << " There are no changes in the contents " << std::endl;
                    else
                        std::cout << " There are changes in the contents " << std::endl;

                    continue;

                }
                else if (choise == L"N")
                    break; // display beginning

                else
                    std::wcout << L"Wrong command !" << std::endl;

            } while (true);

        } while (true);

    }
    catch (const std::exception& error)
    {
        std::wcout << error.what() << std::endl;
    }

    return 0;


}