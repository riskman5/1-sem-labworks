#include <iostream>

int main(){
    int n, m;
    std::cin >> n >> m;
    int plotiki[1600];
    for (int i = 0; i < n*m; i++)
        std::cin>>plotiki[i];
    int mes_count = 0;
    std::cin >> mes_count;
    int mescolit[2000];
    for (int i = 0; i < mes_count; i++)
        std::cin>>mescolit[i];

    //отсортируем оба массива вставками
    for (int i = 1; i < n*m; i++){
        int key = plotiki[i];
        int j = i - 1;
        while (j >= 0 && plotiki[j] > key){
            plotiki[j+1] = plotiki[j];
            j--;
        }
        plotiki[j+1] = key;
    }

    for (int i = 1; i < mes_count; i++){
        int key = mescolit[i];
        int j = i - 1;
        while (j >= 0 && mescolit[j] > key){
            mescolit[j+1] = mescolit[j];
            j--;
        }
        mescolit[j+1] = key;
    }

    int seats = 0;
    int key_plotiki = 0;
    int key_mesc = 0;

    while (key_plotiki < n *m && key_mesc < mes_count){
        if (plotiki[key_plotiki] >= mescolit[key_mesc]){
            seats++;
            key_plotiki++;
            key_mesc++;
        }
        else
            key_plotiki++;
    }

    std::cout<<seats;

    return 0;
}