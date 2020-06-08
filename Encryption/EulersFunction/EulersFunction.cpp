
namespace Math {
    int euler(int n) {

    }

    bool isPrime(int n) {
        int upper = n;
        for (int i = 1; i <= upper; i += 1, upper = n / i) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

}