class Solution {
    private:
    // int rotatesum(vector<int>& num, int k){
    //     int cnt = 0;
    //     int n = num.size();
    //     for(int i=0; i<n;i++){
    //         cnt+= i*num[(i+k)%n];
    //         // cout << num[n-1-(i+k)%n] << " ";
    //     }
    //     // cout << cnt << endl;

    //     return cnt;
    // }
public:
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        long long sum = 0, x = 0;
        long long maxy;
        for(int i = 0; i<n; i++){
            // maxy = max(maxy, rotatesum(nums, i));
            // cout << maxy << endl;
            sum+=nums[i];
            x += (long long)i*nums[i];
        }
        maxy = x;
        
        for(int i = 1; i<n; i++){
            x = x+sum-nums[n - i]*(long long)n;
            maxy = max(x, maxy);
        }
        return maxy;
    }
};