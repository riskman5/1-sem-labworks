#include <iostream>

int main() {
    int n;
    std::cin>>n;
    int id[1000];
    int points[1000];
    for (int i = 0; i < n; i++)
        std::cin >> id[i] >> points[i];
    //sort by id
    for (int i = 1; i < n; i++){
        int key_id = id[i];
        int key_points = points[i];
        int j = i - 1;
        while (j >= 0 && id[j] > key_id){
            id[j+1] = id[j];
            points[j+1] = points[j];
            j--;
        }
        id[j+1] = key_id;
        points[j+1] = key_points;
    }

    //reversed sort by point
    for (int i = 1; i < n; i++){
        int key_points = points[i];
        int key_id = id[i];
        int j = i - 1;
        while (j >= 0 && points[j] < key_points){
            points[j+1] = points[j];
            id[j+1] = id[j];
            j--;
        }
        points[j+1] = key_points;
        id[j+1] = key_id;
    }
    for(int i = 0; i < n; i++){
        std::cout<<id[i]<<' '<<points[i]<<std::endl;
    }
    return 0;
}
