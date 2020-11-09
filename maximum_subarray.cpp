#include <vector>

using namespace std;

vector<int> find_max_subvec_mid(vector<int> input, int high, int low) {
    int max_sum = -1;
    int left_sum = 0;
    int mid = (high + low)/2;

    int left_max = 0;
    int right_max = 0;

    for (int i = mid - 1; i >= low; i--) {
        left_sum += input[i];
        if (left_sum > max_sum) {
            max_sum = left_sum;
            left_max = i;
        }
    }

    max_sum = -1;
    int right_sum = 0;

    for (int i = mid; i < high; i++) {
        right_sum += input[i];
        if (right_sum > max_sum) {
            max_sum = right_sum;
            right_max = i;
        }
    }

    return vector<int> {left_max, right_max, left_sum + right_sum};
}


vector<int> find_max_subvec(vector<int> input, int low, int high) {
    if ((high - low) > 1) {
        int mid = (high + low) / 2;
        vector<int> r1 = find_max_subvec(input, low, mid);
        vector<int> r2 = find_max_subvec(input, mid, high);
        vector<int> rmid = find_max_subvec_mid(input, high, low);
        if (r1[2] > r2[2] && r1[2] > rmid[2]) {
            return r1;
        } else if (r2[2] > r1[2] && r2[2] > rmid[2]) {
            return r2;
        } else {
            return rmid;
        }
    } else {
        return vector<int> {low, high, input[low]};
    }
}





