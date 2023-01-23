#include <iostream>

int main(){
    int n = 0;
    double A = 0;

    std::cin>>n>>A;
    double* heights = new double[n];
    heights[0] = A;

    double right = A;
    double left = 0;
    double med;
    double min = 1000001.000000;

    while(right - left  >= 0.000000000001){
        bool flag = true;
        med = (right + left) / 2;
        heights[1] = med;
        for (int i = 1; i < n - 1; i++){
            double temp = 2 * heights[i] - heights[i-1] + 2;
            if(temp > 0){
                heights[i+1] = temp;
            }
            else{
                flag = false;
                break;
            }
        }
        if (flag){
            right = med;
            if (heights[n-1] < min) {
                min = heights[n - 1];
            }
        }
        else
            left = med;
    }

    printf("%.2f\n", min);
    return 0;
}