#include <iostream> //удаление символа
#include <cstring>
using namespace std;
int main() {
    const int max_s = 1000;
    char str[max_s];
    char res[max_s] = "";
    char pstr[max_s];
    char gstr[max_s];

    cout << "Введите строку: ";
    cin.getline(str, max_s);
    cout << "введите подстроку которую заменить" << endl;
    cin.getline(pstr, max_s);
    cout << "введите подстроку на которую заменить" << endl;
    cin.getline(gstr, max_s);

    int len = strlen(str);
    int plen = strlen(pstr);
    int glen = strlen(gstr);
    int h = 0;
    for(int i = 0; i < len; i++) {
         bool match = true;
        for (int j = 0; j < plen; j++) {
            if (i + j >= len || str[i + j] != pstr[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            for (int j = 0; j < glen; j++) {
                res[h] = gstr[j];
                h++;
            }
            i += plen - 1; // Пропускаем обработанные символы
        } 
        else {
            res[h] = str[i];
            h++;
        }
    }
    res[h] = '\0';
    cout << res << endl;
}

    