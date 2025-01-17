// clang-format off
int f1(int *arr) __CPROVER_ensures(__CPROVER_forall {
  int i;
  (0 <= i && i < 10) ==> arr[i] == i
})
// clang-format on
{
  for(int i = 0; i < 10; i++)
  {
    if(i == 0)
      arr[i] = -1;
    else
      arr[i] = i;
  }

  return 0;
}

int main()
{
  int arr[10];
  f1(arr);
}
