void tests_dir(void);
void tests_stash(void);
void tests_resource(void);
void tests_location(void);
void tests_tile(void);

int main()
{
  tests_dir();
  tests_stash();
  tests_resource();
  tests_location();
  tests_tile();

  return 0;
}
