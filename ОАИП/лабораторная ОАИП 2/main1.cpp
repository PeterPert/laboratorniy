#include <iostream>
#include <cstring>
#include <sstream>
#include <cctype> // to lower
#include <vector>
#include <algorithm> 
#include <numeric>
using namespace std;
int main() {
    string res;
    cout << "Введите 10 слов через пробел: ";
    for (int i = 0; i < 10; i++) {
        string word;
        cin >> word;
        res += word + " ";
    }
    
    cout << "Результат: " << res << endl;

    // нахождение количества слов нач на а
    istringstream s1(res);
    string word;
    int count = 0;
    while (s1 >> word) {
        if (word[0] == 'a' || word[0] == 'A') {
            count++;
        }
    }
    
    cout << "Количество слов, начинающихся на 'a': " << count << endl;
    
    //длина самого короткого слова
    istringstream s2(res);
    int min = 999; 
    while (s2 >> word) {
        if (word.length() < min) {
            min = word.length();
        }
    }
    cout << "min" << min << endl;

    //подсчитываем количесвто букв а в последнем слове
    istringstream s3(res);
    string lw, cw;
    while (s3 >> cw) {
        lw = cw;
    }
    int ln = lw.length();
    int h = 0;
    for (int i = 0; i < ln; i++) {
        if (lw[i] == 'a' || lw[i] == 'A') {
            h++;
        }
    }
    cout << "в полед слове а" << h << endl;

    //заменить все буквы в верхнем регистре на строчные 
    for (int i = 0; i < res.length(); i++) {
        if (isupper(res[i])) {  // проверяем, является ли символ заглавной буквой
            res[i] = tolower(res[i]);  
        }
    }
    
    cout << "Строка в нижнем регистре: " << res << endl;

    //колво слов первый и послед символы совпад 
    istringstream s4(res);
    string worde;
    int cov = 0;
    while (s4 >> worde) {
        int ln4 = worde.length();
        if (worde[0] == worde[ln4-1]) {
            cov++;
        }
    }
    cout << "колво совпад " << cov << endl;

    //найти самую короткую общую подстроку между двумя словами в предложении
     istringstream ss(res);
    vector<string> words;
    string w;
    
    while (ss >> w) {
        words.push_back(w);
    }

    string shortest_common = "";
    string word1_result = "", word2_result = "";
    int min_length = 999; // Большое число

    // Перебираем все пары слов
    for (int i = 0; i < words.size(); i++) {
        for (int j = i + 1; j < words.size(); j++) {
            string word1 = words[i];
            string word2 = words[j];
            for (int start = 0; start < word1.length(); start++) {
                for (int len = 1; len <= word1.length() - start; len++) {
                    string substring = word1.substr(start, len); //исходная_строка.substr(начальная_позиция, длина) длина это сколько мы хотим взять
                    if (word2.find(substring) != string::npos) {
                        if (substring.length() < min_length) {
                            min_length = substring.length();
                            shortest_common = substring;
                        }
                    }
                }
            }
        }
    }

    // Вывод результатов
    if (!shortest_common.empty()) {
        cout << "Самая короткая общая подстрока: \"" << shortest_common << "\"" << endl;
        cout << "Длина подстроки: " << shortest_common.length() << " символов" << endl;
    } else {
        cout << "Общих подстрок между словами не найдено" << endl;
    }
}