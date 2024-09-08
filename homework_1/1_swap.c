void swap(int *left, int *right)
{
    *left ^= *right;
    *right ^= *left;
    *left ^= *right;
}

int main() {}
