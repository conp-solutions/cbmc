// clang-format off
int f1(int *arr) __CPROVER_requires(
  (__CPROVER_forall {
    int i;
    (0 <= i && i < 10) ==> arr[i] == 0
  } ? __CPROVER_exists {
    int i;
    (0 <= i && i < 10) ==> arr[i] == 0
  } : 1 == 0) &&
  (__CPROVER_forall {
    int i;
    (0 <= i && i < 10) ==> arr[i] == i
  } ? 1 == 0 :
    __CPROVER_forall {
      int i;
      (0 <= i && i < 10) ==> arr[i] == 0
  })) __CPROVER_ensures(__CPROVER_return_value == 0)
// clang-format on
{
  return 0;
}

int main()
{
  int arr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  f1(arr);
}
